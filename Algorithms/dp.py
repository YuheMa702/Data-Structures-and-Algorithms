'''
Dynamic Programming: Save reusable answers from subproblems to solve big problem
'''

'''
Python tricks: use dir(variable) to check all methods of a datatype, then use help(v.method)
'''


def nth_fib(n):
    b0 = 0
    b1 = 1

    if n == 0:
        return b0
    elif n == 1:
        return b1
    else:
        for i in range(n - 1):
            old_b1 = b1
            b1 += b0
            b0 = old_b1
        return b1
    

#Problem: Given an array of integers, find the length of the longest increasing subsequence.
def length_of_LIS(nums):
    if not nums:
        return 0
    
    # Initialize dp array where dp[i] represents the length of LIS ending at index i
    dp = [1] * len(nums)
    
    for i in range(len(nums)):
        for j in range(i):
            if nums[i] > nums[j]:
                dp[i] = max(dp[i], dp[j] + 1)
    
    return max(dp)


def knapsack(values, weights, W):
    n = len(values)
    dp = [[0 for _ in range(W + 1)] for _ in range(n + 1)]
    
    for i in range(1, n + 1):
        for w in range(1, W + 1):
            if weights[i - 1] <= w:
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1])
            else:
                dp[i][w] = dp[i - 1][w]
                
    return dp[n][W]

# Example usage:
values = [60, 100, 120]
weights = [10, 20, 30]
W = 50
print(knapsack(values, weights, W))  # Output: 220

