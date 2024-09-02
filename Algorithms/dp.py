'''
Dynamic Programming: Save reusable answers from subproblems to solve big problem
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
    


