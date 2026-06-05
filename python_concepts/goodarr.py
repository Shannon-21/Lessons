from typing import List
import unittest
import math

class Solution:
    def isGood(self, nums: List[int]) -> bool:
        """
        You are given an integer array nums. We consider an array good if it is a permutation of an array base[n].

        base[n] = [1, 2, ..., n - 1, n, n] (in other words, it is an array of length n + 1 which contains 1 to n - 1 exactly once, plus two occurrences of n). For example, base[1] = [1, 1] and base[3] = [1, 2, 3, 3].

        Return true if the given array is good, otherwise return false.

        Note: A permutation of integers represents an arrangement of these numbers.
        """

        nums.sort()
        max = nums[-1]

        if (len(nums) != abs(max) + 1):
            return False
        
        if nums[-2] != max:
            return False
        
        for i in range(len(nums[:-2])):
            if abs(nums[i] - nums[i+1]) != 1:
                return False
            
        return True

class TestGoodArray(unittest.TestCase):
    def setUp(self):
        self._solution = Solution()

    def test_1(self):
        #Input: nums = [2, 1, 3]
        # Output: false
        self.assertEqual(self._solution.isGood([2, 1, 3]), False)

    def test_2(self):
        # Input: nums = [1, 3, 3, 2]
        # Output: true
        self.assertEqual(self._solution.isGood([1, 3, 3, 2]), True)

    def test_3(self):
        # Input: nums = [1, 1]
        # Output: true
        self.assertEqual(self._solution.isGood([1, 1]), True)

    def test_4(self):
        # Input: nums = [3, 4, 4, 1, 2, 1]
        # Output: false
        self.assertEqual(self._solution.isGood([3, 4, 4, 1, 2, 1]), False)

    def test_5(self):
        # Input: nums = [-1, -3, -3, -2]
        # Output: false
        self.assertEqual(self._solution.isGood([-1, -3, -3, -2]), False)

    def test_5(self):
        # Input: nums = [-1, -1, -3, -2]
        # Output: true
        breakpoint()
        self.assertEqual(self._solution.isGood([-1, -1, -3, -2]), False)

if __name__ == '__main__':
    unittest.main()