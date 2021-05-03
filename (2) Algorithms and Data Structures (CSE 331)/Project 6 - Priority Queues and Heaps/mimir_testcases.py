import unittest
from PriorityHeap import PriorityHeap, Node, heap_sort, current_medians

class MimirTests(unittest.TestCase):
    
    def test_push(self):
        min_heap = PriorityHeap()
        min_heap.push(5, 'c')
        min_heap.push(4, 'y')
        min_heap.push(3, 'n')
        min_heap.push(2, 'd')
        min_heap.push(5, 'y')

        assert len(min_heap._data) == 5
        assert min(min_heap._data[:5]) == min_heap._data[0]
        assert min_heap._data[1] < min_heap._data[3]
        assert min_heap._data[1] < min_heap._data[4]
        min_heap.push(6, 'y')
        assert min_heap._data[2] < min_heap._data[5]

        max_heap = PriorityHeap(False)
        max_heap.push(5, 'c')
        max_heap.push(4, 'y')
        max_heap.push(3, 'n')
        max_heap.push(2, 'd')
        max_heap.push(5, 'y')

        assert len(max_heap._data) == 5
        assert max(max_heap._data[:5]) == max_heap._data[0]
        assert max_heap._data[1] > max_heap._data[3]
        assert max_heap._data[1] > max_heap._data[4]
        max_heap.push(6, 'y')
        assert max_heap._data[2] > max_heap._data[5]

    def test_pop(self):
        # test 1: tests pop returns the root
        min_heap = PriorityHeap()
        max_heap = PriorityHeap(False)

        min_heap.push(5, 'c')
        min_heap.push(4, 'y')
        min_heap.push(3, 'n')
        min_heap.push(2, 'd')
        min_heap.push(5, 'y')

        max_heap.push(5, 'c')
        max_heap.push(4, 'y')
        max_heap.push(3, 'n')
        max_heap.push(2, 'd')
        max_heap.push(5, 'y')

        assert min_heap.pop() == Node(2, 'd')
        assert max_heap.pop() == Node(5, 'y')

        # test 2: checks for length and not empty
        min_heap = PriorityHeap()
        max_heap = PriorityHeap(False)
        min_heap.push(4, 'y')
        min_heap.push(3, 'n')
        max_heap.push(4, 'y')
        max_heap.push(3, 'n')

        assert len(min_heap._data) == 2
        assert len(max_heap._data) == 2
        assert min_heap.pop().value == 'n'
        assert max_heap.pop().value == 'y'
        assert not min_heap.empty()
        assert not max_heap.empty()

    def test_min_child(self):
        from string import ascii_lowercase
        def check_min(pheap, idx, lhs=None, rhs=None):
            '''
            function helper for validating the min method
            '''
            min_child = lhs if pheap._data[lhs] < pheap._data[rhs] else rhs
            min_pheap = pheap.min_child(idx)
            assert min_child == min_pheap

        heap = PriorityHeap()
        for child in ascii_lowercase:
            heap.push(ord(child), child)
        assert len(heap._data) == 26

        check_min(heap, 0, 1, 2)
        check_min(heap, 2, 5, 6)
        check_min(heap, 3, 7, 8)

    def test_max_child(self):
        from string import ascii_lowercase
        def check_max(pheap, idx, lhs=None, rhs=None):
            '''
            function helper for validating the max method
            '''
            max_child = lhs if pheap._data[lhs] > pheap._data[rhs] else rhs
            assert max_child == pheap.max_child(idx)

        heap = PriorityHeap(False)
        for child in ascii_lowercase:
            heap.push(ord(child), child)
        assert len(heap._data) == 26

        check_max(heap, 0, 1, 2)
        check_max(heap, 2, 5, 6)
        check_max(heap, 3, 7, 8)

    def test_heap_sort(self):
        array2 = [4,10,3,5,1]
        heap2 = heap_sort(array2)
        assert heap2 == [1,3,4,5,10]

    def test_current_medians(self):
        data_list = [2, 4, 6, 8, 10]
        median_data = current_medians(data_list)
        assert median_data == [2, 3, 4, 5, 6]

        data_list2 = [2, 8, 35, 9]
        median_data2 = current_medians(data_list2)
        assert median_data2 == [2, 5, 8, 8.5]

if __name__ == '__main__':
    unittest.main()