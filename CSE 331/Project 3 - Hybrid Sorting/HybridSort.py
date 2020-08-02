"""
PROJECT 3 - Hybrid Sorting
Name: Aidan Delfuoco
"""

def quick_sort(unsorted, threshold, start, end, reverse=False):
    """
        Performs quick sort on the given list within the given range of indices while the length
        of that list is greater than the given threshold. Once the size of the given range of
        indices is equal to or less than the given threshold insertion sort will be used.
        :param unsorted: the list to be sorted
        :param threshold: the maximum length last can be in order for insertion sort to be called
        over quick sort
        :param start: start index of the range of values in the list the function is working on
        :param end: end index of the range of values in the list the function is working on
        :param reverse: if false the list will sort in increasing order, otherwise the list will
        sort in decreasing order
    """
    if start >= end:
        return
    pivot_loc = subdivide(unsorted, start, end, reverse)

    if abs(pivot_loc-start) <= threshold: # length of current list section is <= threshold
        insertion_sort(unsorted, start, pivot_loc, reverse)
        insertion_sort(unsorted, pivot_loc+1, end, reverse)
    else: # length of current list section is > threshold
        quick_sort(unsorted, threshold, start, pivot_loc, reverse)
        quick_sort(unsorted, threshold, pivot_loc+1, end, reverse)

def subdivide(unsorted, start, end, reverse):
    """
        This function will subdivide the given list within the range of given indices.
        :param unsorted: a list to be used by this function
        :param start: start index of the range of values in the list the function is working on
        :param end: end index of the range of values in the list the function is working on
        :param reverse: if false the list will sort in increasing order, otherwise the list will
        sort in decreasing order
        :return: [int] the index of where the pivot ends up in the list
    """
    pivot = find_pivot(unsorted, start, end)

    if not reverse: # case for reverse=False
        while True:
            # move right through unsorted while unsorted[start] < pivot
            while unsorted[start] < pivot:
                start += 1

            # move left through unsorted while pivot < unsorted[end]
            while pivot < unsorted[end]:
                end -= 1

            if start >= end: # all numbers have been subdivided
                break
            else:
                # Swap numbers[start] and numbers[end],
                temp_start = unsorted[start]
                unsorted[start] = unsorted[end]
                unsorted[end] = temp_start

                # update start and end
                start += 1
                end -= 1
    else: # case for reverse=True
        while True:
            # move right through unsorted while unsorted[start] > pivot
            while unsorted[start] > pivot:
                start += 1

            # move left through unsorted while pivot > unsorted[end]
            while pivot > unsorted[end]:
                end -= 1

            if start >= end: # all numbers have been subdivided
                break
            else:
                # Swap numbers[start] and numbers[end],
                temp_start = unsorted[start]
                unsorted[start] = unsorted[end]
                unsorted[end] = temp_start

                # update start and end
                start += 1
                end -= 1

    return end

def find_pivot(unsorted, start, end):
    """
        This function will use a median of three in order to find the pivot value for the given
        range of indices.
        :param unsorted: a list to be used by this function
        :param start: start index of the range of values in the list the function is working on
        :param end: end index of the range of values in the list the function is working on
        :return: [int] the value of the pivot
    """
    midpoint = (int)((start + end) / 2) # get midpoint index, round down
    pivot_list = [unsorted[start], unsorted[end], unsorted[midpoint]] # unsorted, elements of list
    elem1 = min(pivot_list)
    elem3 = max(pivot_list)
    elem2 = sum(pivot_list) - (elem1 + elem3) # calculate pivot
    return elem2

def insertion_sort(unsorted, start, end, reverse):
    """
        This function will perform insertion sort in-place on the given list within the given
        range of indices.
        :param unsorted: the list to be sorted
        :param start: start index of the range of values in the list the function is working on
        :param end: end index of the range of values in the list the function is working on
        :param reverse: if false the list will sort in increasing order, otherwise the list will
        sort in decreasing order
    """
    if not reverse: # case for reverse=False
        for count in range(start, end+1): # from start to end
            index = count
            # check if we need to swap another two numbers
            while index > 0 and unsorted[index - 1] > unsorted[index]:
                # perform swap on the two numbers
                temp_num = unsorted[index - 1]
                unsorted[index - 1] = unsorted[index]
                unsorted[index] = temp_num
                index -= 1
    else: # case for reverse=True
        for count in range(end, start-1, -1): # from end to start backwards
            index = count
            # check if we need to swap another two numbers
            while index < end and unsorted[index + 1] > unsorted[index]:
                # perform swap on the two numbers
                temp_num = unsorted[index + 1]
                unsorted[index + 1] = unsorted[index]
                unsorted[index] = temp_num
                index += 1
    
def largest_sequential_difference(lst):
    """
        This function will find the largest difference between sequential values in a sorted list
        using the given list.
        :param lst: a list that will be used to find the largest sequential difference
        :return: [int]  the largest difference between sequential numbers. Unless the length of
        the list is less than 2, then None will be returned.
    """
    if len(lst) < 2:
        return None

    quick_sort(lst, 0, 0, len(lst)-1)
    
    # find the largest diff by going through the sorted list
    largest_diff = 0
    for index in range(0, len(lst)):
        if index > 0 and (lst[index]-lst[index-1] > largest_diff):
            largest_diff = lst[index]-lst[index-1]
    
    return largest_diff