
from typing import List
import unittest

def twoSum(nums: List[int], target: int) -> List[int]:
    seen = {}
    for i, num in enumerate(nums):
        diff = target - num
        if diff in seen:
            return (seen[diff], i)
        seen[num] = i

class TestMathOperations(unittest.TestCase): 
    # [2, 7, 11, 15], 9 => 0, 1
    def test_1(self):
        result = twoSum(list([2, 7, 11, 15]), 9)
        self.assertEqual(result, (0, 1))

    # [3, 2, 4], 6 => 1, 2   
    def test_2(self):
        result = twoSum(list([3, 2, 4]), 6)
        self.assertEqual(result, (1, 2))
    
    # [3, 2, 3], 6 => 0, 2   
    def test_3(self):
        result = twoSum(list([3, 2, 3]), 6)
        self.assertEqual(result, (0, 2))

    # [-3, 2, 3], 0 => 0, 2   
    def test_4(self):
        result = twoSum(list([-3, 2, 3]), 0)
        self.assertEqual(result, (0, 2))

    # [-3, 2, 4], 1 => 0, 2   
    def test_5(self):
        result = twoSum(list([-3, 2, 4]), 1)
        self.assertEqual(result, (0, 2))

    # [-3, -2, -5], -8 => 0, 2   
    def test_6(self):
        result = twoSum(list([-3, -2, -5]), -8)
        self.assertEqual(result, (0, 2))

    # [0, 4, -5,  0], 0 => 0, 3
    def test_7(self):
        result = twoSum(list([0, 4, -5, 0]), 0)
        self.assertEqual(result, (0, 3))

    # [3, 2, 95, 4, -3], 92 => 2, 4
    def test_8(self):
        result = twoSum(list([3, 2, 95, 4, -3]), 92)
        self.assertEqual(result, (2, 4))

if __name__ == '__main__':
    unittest.main()