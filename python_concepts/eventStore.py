import unittest
import time
import os
from datetime import datetime
import json
import threading

class Event:
    def __init__(self, key, value, timestamp, ttl):
        self.Key = key
        self.Value = value
        self.Timestamp = timestamp
        self.TTL = ttl
    
    def __str__(self):
        return f"{self.Key}, {self.Value}, {self.Timestamp}, {self.TTL}"

class EventStore:
    def __init__(self):
        self._events = {}
        self._lock = threading.Lock()
        self._running = True
        self._cleanup_thread = threading.Thread(
            target = self._cleanup_loop,
            daemon = True
        )
        self._cleanup_thread.start()

    def put(self, key, value, ttl=None):
        with self._lock:
            if (ttl != None and ttl < 0): raise ValueError()
            ev = Event(key, value, datetime.now().timestamp(), ttl)
            self._events[key] = ev
            return ev
    
    def get(self, key):
        with self._lock:
            v = self._events.get(key)
            if v is None or self._is_expired(v.Timestamp, v.TTL):
                return None
            return v.Value

    def delete(self, key):
        with self._lock:
            r = self._events.pop(key, None)
            return r

    def count(self):
        with self._lock:
            i = 0
            for v in self._events.values():
                if not (self._is_expired(v.Timestamp, v.TTL)):
                    i += 1
            return i

    def backup(self, filepath: str):
        with self._lock:
            if filepath is None or len(filepath) == 0: return
            d = {x:y for x, y in self._events.items() if not self._is_expired(y.Timestamp, y.TTL)}
            with open(filepath, mode="w") as file:
                json.dump(d, file, default=str)

    def restore(self, filepath):
        with self._lock:
            if filepath is None or len(filepath) == 0: return
            with open(filepath, mode="r") as file:
                data = json.load(file)
            if len(data) == 0:
                self._events = {}
            if not isinstance(data, dict):
                return
            self._events = {}
            for k, v in data.items():
                atts = [p.strip() for p in v.split(',')]
                value = int(atts[1]) if atts[1].isdigit() else atts[1]
                timestamp = float(atts[2])
                ttl = int(atts[3]) if atts[3].isdigit() else None
                ev = Event(k, value, timestamp, ttl)
                self._events[k] = ev
    
    def stop(self):
        self._running = False
        self._cleanup_thread.join()

    def _is_expired(self, timestamp, ttl):
        diff = (datetime.now() - datetime.fromtimestamp(timestamp)).seconds
        return ttl != None and diff >= ttl
    
    def _cleanup_loop(self):
        while self._running:
            time.sleep(5)

            with self._lock:
                deleted = []
                for k,v in self._events.items():
                    if self._is_expired(v.Timestamp, v.TTL):
                        deleted.append(k)
                for k in deleted:
                    self.delete(k)

class TestEventStore(unittest.TestCase):

    def setUp(self):
        self.store = EventStore()

    def test_put_and_get(self):
        self.store.put("a", 100)

        self.assertEqual(self.store.get("a"), 100)

    def test_get_missing_key(self):
        self.assertIsNone(self.store.get("missing"))

    def test_overwrite_existing_key(self):
        self.store.put("a", 100)
        self.store.put("a", 200)

        self.assertEqual(self.store.get("a"), 200)
        self.assertEqual(self.store.count(), 1)

    def test_delete_existing_key(self):
        self.store.put("a", 1)
        self.store.put("b", 2)

        self.store.delete("a")

        self.assertIsNone(self.store.get("a"))
        self.assertEqual(self.store.count(), 1)

    def test_delete_missing_key(self):
        self.store.delete("missing")

        self.assertEqual(self.store.count(), 0)

    def test_count_basic(self):
        self.store.put("a", 1)
        self.store.put("b", 2)

        self.assertEqual(self.store.count(), 2)

    def test_ttl_expiration(self):
        self.store.put("temp", "hello", ttl=1)

        self.assertEqual(self.store.get("temp"), "hello")

        time.sleep(2)

        self.assertIsNone(self.store.get("temp"))

    def test_count_does_not_include_expired(self):
        self.store.put("alive", 1)
        self.store.put("expired", 2, ttl=1)

        time.sleep(2)

        self.assertEqual(self.store.count(), 1)

    def test_ttl_none_does_not_expire(self):
        self.store.put("permanent", 999)

        time.sleep(2)

        self.assertEqual(self.store.get("permanent"), 999)

    def test_zero_ttl_expires_immediately(self):
        self.store.put("instant", "x", ttl=0)

        self.assertIsNone(self.store.get("instant"))

    def test_negative_ttl_raises(self):
        with self.assertRaises(ValueError):
            self.store.put("bad", 1, ttl=-5)

    def test_overwrite_expired_key(self):
        self.store.put("x", 1, ttl=1)

        time.sleep(2)

        self.store.put("x", 2)

        self.assertEqual(self.store.get("x"), 2)

    def test_backup_and_restore(self):
        filepath = "test_backup.json"

        try:
            self.store.put("a", 1)
            self.store.put("b", 2)

            self.store.backup(filepath)

            new_store = EventStore()
            new_store.restore(filepath)

            self.assertEqual(new_store.get("a"), 1)
            self.assertEqual(new_store.get("b"), 2)
            self.assertEqual(new_store.count(), 2)

        finally:
            if os.path.exists(filepath):
                os.remove(filepath)

    def test_backup_should_not_store_expired_items(self):
        filepath = "test_backup.json"

        try:
            self.store.put("alive", 1)
            self.store.put("dead", 2, ttl=1)

            time.sleep(2)

            self.store.backup(filepath)

            new_store = EventStore()
            new_store.restore(filepath)

            self.assertEqual(new_store.get("alive"), 1)
            self.assertIsNone(new_store.get("dead"))

        finally:
            if os.path.exists(filepath):
                os.remove(filepath)

    def test_restore_replaces_existing_state(self):
        filepath = "test_backup.json"

        try:
            self.store.put("a", 1)
            self.store.backup(filepath)

            new_store = EventStore()
            new_store.put("old", 999)

            new_store.restore(filepath)

            self.assertEqual(new_store.get("a"), 1)
            self.assertIsNone(new_store.get("old"))

        finally:
            if os.path.exists(filepath):
                os.remove(filepath)

    def test_backup_empty_store(self):
        filepath = "empty_backup.json"

        try:
            self.store.backup(filepath)

            new_store = EventStore()
            new_store.restore(filepath)

            self.assertEqual(new_store.count(), 0)

        finally:
            if os.path.exists(filepath):
                os.remove(filepath)

    def test_restore_missing_file(self):
        with self.assertRaises(FileNotFoundError):
            self.store.restore("does_not_exist.json")

    def test_expired_items_behave_as_deleted(self):
        self.store.put("x", 123, ttl=1)

        time.sleep(2)

        self.assertIsNone(self.store.get("x"))

    def test_many_inserts(self):
        for i in range(1000):
            self.store.put(f"k{i}", i)

        self.assertEqual(self.store.count(), 1000)

    def test_multiple_expired_items(self):
        self.store.put("a", 1, ttl=1)
        self.store.put("b", 2, ttl=1)
        self.store.put("c", 3)

        time.sleep(2)

        self.assertEqual(self.store.count(), 1)
        self.assertEqual(self.store.get("c"), 3)

    def test_store_complex_object(self):
        value = {
            "user": "john",
            "roles": ["admin", "trader"],
            "metadata": {
                "active": True
            }
        }

        self.store.put("user1", value)

        self.assertEqual(self.store.get("user1"), value)


if __name__ == "__main__":
    unittest.main()
