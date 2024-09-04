# This is an elegant quicksort algorithm implemented in python, very elegent!


def quickSort(lst):
    # base case: already sorted if len(lst) <= 1
    if len(lst) <= 1: 
        return lst
    smaller = [x for x in lst[1:] if x < lst[0]] 
    larger = [x for x in lst[1:] if x >= lst[0]]
    # above is the partition step: move small elems to the left, big ones to the right
    # note that lst[0] is the pivot
    return quickSort(smaller) + [lst[0]] + quickSort(larger) # recursive step