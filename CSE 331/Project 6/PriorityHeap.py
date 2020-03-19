"""
PROJECT 6 - Priority Queues and Heaps
Name: Aidan Delfuoco
"""


class Node:
    """
    This class represents a node object with k (key) and v (value)
    Node definition should not be changed in any way
    """

    def __init__(self, k, v):
        """
        Initializes node
        :param k: key to be stored in the node
        :param v: value to be stored in the node
        """
        self.key = k
        self.value = v

    def __lt__(self, other):
        """
        Less than comparator
        :param other: second node to be compared to
        :return: True if the node is less than other, False otherwise
        """
        return self.key < other.key or (self.key == other.key and self.value < other.value)

    def __gt__(self, other):
        """
        Greater than comparator
        :param other: second node to be compared to
        :return: True if the node is greater than other, False otherwise
        """
        return self.key > other.key or (self.key == other.key and self.value > other.value)

    def __eq__(self, other):
        """
        Equality comparator
        :param other: second node to be compared to
        :return: True if the nodes are equal, False otherwise
        """
        return self.key == other.key and self.value == other.value

    def __str__(self):
        """
        Converts node to a string
        :return: string representation of node
        """
        return '({0},{1})'.format(self.key, self.value)

    __repr__ = __str__


class PriorityHeap:
    """
    Partially completed data structure. Do not modify completed portions in any way
    """

    def __init__(self, is_min=True):
        """
        Initializes the priority heap
        """
        self._data = []
        self.min = is_min

    def __str__(self):
        """
        Converts the priority heap to a string
        :return: string representation of the heap
        """
        return ', '.join(str(item) for item in self._data)

    def __len__(self):
        """
        Length override function
        :return: Length of the data inside the heap
        """
        return len(self._data)

    __repr__ = __str__

#   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#   Modify below this line

    def empty(self):
        """
        Checks if the priority queue is empty.
        :return (bool): True or False
        """
        if len(self) == 0:
            return True
        else:
            return False

    def top(self):
        """
        Gives the root value.
        :return: type same as Node._value
        """
        if not self.empty(): # priority queue is not empty
            return self._data[0].value
        else:
            return None

    def push(self, key, val):
        """
        Use the key and value parameters to add a Node to the heap.
        :param key: Node key
        :param val: Node value
        :return: None
        """
        new_node = Node(key, val)

        self._data.append(new_node)
        self.percolate_up(len(self) - 1)

    def pop(self):
        """
        Removes the top element from the priority queue.
        :return: type Node
        """
        if len(self) == 0:
            return None

        self.swap(0, len(self) - 1) # put item to remove at end, replace root
        removed_item = self._data.pop() # remove it from the list
        self.percolate_down(0) # fix new root
        return removed_item

    def min_child(self, index):
        """
        Given an index of a node, return the index of the smaller child.
        In the event that they are equal, return the right child.
        In the event that the index is a leaf, return None.
        :param index: Node index
        :return (int): index of the smaller child, or None
        """
        if (2 * index + 1) < len(self): # see if node has left child
            left = 2 * index + 1 # left = index of left child
            if (2 * index + 2) < len(self): # see if node has right child
                right = 2 * index + 2 # right = index of right child
                # cases for when right gets returned
                if self._data[right] == self._data[left] or self._data[right] < self._data[left]:
                    return right
            return left # no left child or left < right
        else: # if node doesn't have a left child it is a leaf (can't have right without left)
            return None

    def max_child(self, index):
        """
        Given an index of a node, return the index of the larger child.
        In the event that they are equal, return the right child.
        In the event that the index is a leaf, return None.
        :param index: Node index
        :return (int): index of the smaller child, or None
        """
        if (2 * index + 1) < len(self): # see if node has left child
            left = 2 * index + 1 # left = index of left child
            if (2 * index + 2) < len(self): # see if node has right child
                right = 2 * index + 2 # right = index of right child
                # cases for when right gets returned
                if self._data[right] == self._data[left] or self._data[right] > self._data[left]:
                    return right
            return left # no left child or left > right
        else: # if node doesn't have a left child it is a leaf (can't have right without left)
            return None

    def swap(self, i, j):
        """Swap the elements at indices i and j of array."""
        self._data[i], self._data[j] = self._data[j], self._data[i]

    def percolate_up(self, index):
        """
        Given the index of a node, move the node up to its valid spot in the heap.
        :param index: the index of node to move
        :return: None
        """
        if index > 0:
            parent = (index - 1) // 2

            if self.min: # is min heap
                if self._data[index] < self._data[parent]:
                    self.swap(index, parent)
                    self.percolate_up(parent)  # recur at position of parent

            else: # is max heap
                if self._data[index] > self._data[parent]:
                    self.swap(index, parent)
                    self.percolate_up(parent)  # recur at position of parent

    def percolate_down(self, index):
        """
        Given the index of a node, move the node down to its valid spot in the heap.
        :param index: the index of node to move
        :return: None
        """
        if self.min:
            small_child = self.min_child(index) # min_child is index of smallest child for index
            if small_child is not None:
                if self._data[small_child] < self._data[index]:
                    self.swap(index, small_child)
                    self.percolate_down(small_child)  # recur at position of small child
        else:
            max_child = self.max_child(index) # max_child is index of largest child for index
            if max_child is not None:
                if self._data[max_child] > self._data[index]:
                    self.swap(index, max_child)
                    self.percolate_down(max_child)

def heap_sort(array):
    """
    Given a list of data, use heap sort to sort the data.
    :param array: array of data (represents a heap)
    :return: list of the sorted data
    """
    if len(array) is not None:
        # build heap from array (backwards)
        heap = PriorityHeap(False)
        for num in array:
            heap.push(num, 1)

        key_list = []

        # turn heap back into array while reversing it
        for i in array:
            key_list.insert(0, heap.pop().key)

        return(key_list)
    else: # array is empty
        return None

def current_medians(values):
    """
    Given a list of values, keep track of the current median after each value is read in and
    return a list of medians in the order calculated.
    :param values: a list of values (ints)
    :return: list of medians
    """
    # requires doubles
    if values == []:
        return []
    else:
        max_heap = PriorityHeap(False) # for smaller half of currently inserted list
        min_heap = PriorityHeap() # for larger half of currently inserted list
        medians = []

        for index, value in enumerate(values):
            if index == 0: # runs once at the beginning of values
                medians.append(value)
                max_heap.push(1, value)
                continue
            elif value > medians[index-1]: # value will go in min heap
                min_heap.push(1, value)
                # redistribute values if necessary
                if len(min_heap) > len(max_heap) + 1:
                    max_heap.push(1, min_heap.pop().value)
            else:
                max_heap.push(1, value) # value will go in max heap
                # redistribute values if necessary
                if len(max_heap) > len(min_heap) + 1:
                    min_heap.push(1, max_heap.pop().value)
                
            # calculating median
            if len(max_heap) == len(min_heap):
                medians.append((max_heap.top() + min_heap.top()) / 2)
            elif len(max_heap) > len(min_heap): # should only ever be one larger
                medians.append(max_heap.top())
            else: # min_heap is larger
                medians.append(min_heap.top())

        return medians
            