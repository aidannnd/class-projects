"""
Project 4 - Circular Queues
Name: Aidan Delfuoco
"""

from collections import defaultdict

class CircularQueue:
    """
    Circular Queue Class.
    """

    # DO NOT MODIFY THESE METHODS
    def __init__(self, capacity=4):
        """
        Initialize the queue with an initial capacity
        :param capacity: the initial capacity of the queue
        """
        self.capacity = capacity
        self.size = 0
        self.data = [None] * capacity
        self.head = 0
        self.tail = 0

    def __eq__(self, other):
        """
        Defines equality for two queues
        :return: true if two queues are equal, false otherwise
        """
        if self.capacity != other.capacity or self.size != other.size:
            return False

        if self.head != other.head or self.tail != other.tail:
            return False

        for i in range(self.capacity):
            if self.data[i] != other.data[i]:
                return False

        return True

    def __str__(self):
        """
        String representation of the queue
        :return: the queue as a string
        """
        if self.is_empty():
            return "Empty queue"

        str_list = [str(self.data[(self.head + i) % self.capacity]) for i in range(self.size)]
        return "Queue: " + ", ".join(str_list)

    # -----------MODIFY BELOW--------------

    def is_empty(self):
        """
        Returns whether the queue is empty or not
        :return: True if the queue is empty, false otherwise
        """
        if not self.size:
            return True
        else:
            return False

    def __len__(self):
        """
        Overrides the len() method.
        :return: the size of the queue
        """
        return self.size

    def head_element(self):
        """
        Returns the head element of the queue
        :return: None if the queue is empty, otherwise returns the head element of the queue
        """
        if self.is_empty():
            return None
        else:
            return self.data[self.head]

    def tail_element(self):
        """
        Returns the tail element of the queue
        :return: None if the queue is empty, otherwise returns the tail element of the queue
        """
        if self.is_empty():
            return None
        else:
            return self.data[self.tail-1]

    def grow(self):
        """
        Doubles the capacity of the queue immediately when capacity is reached to make room for new elements
        Moves the head to the front of the newly allocated list
        """
        if self.size == self.capacity:
            new_data = []

            for i in range(self.head, self.size): # add the data from head rightward in new_data
                new_data.append(self.data[i])
            if self.head != 0: # there is data to the left of head
                for i in range(0, self.head): # add the data from index 0 up to the head
                    new_data.append(self.data[i])

            for i in range(0, self.size): # add on the Nones
                new_data.append(None)

            self.tail = self.size
            self.head = 0

            self.capacity = self.capacity*2

            if self.size == 0:
                new_data.append(0)
                self.capacity += 1

            self.data = [None] * self.capacity

            self.data = new_data

    def shrink(self):
        """
        Halves the capacity of the queue immediately if the size is 1/4 or less of the capacity
        Moves the head to the front of the newly allocated list
        """
        if (self.size <= (self.capacity)//4) and self.capacity > 7:
            new_data = []

            for i in range(self.head, self.capacity): # add the data from head rightward in new_data
                if self.data[i] is not None:
                    new_data.append(self.data[i])
            if self.head != 0: # there is data to the left of head
                for i in range(0, self.head): # add the data from index 0 up to the head
                    if self.data[i] is not None:
                        new_data.append(self.data[i])

                self.head = 0

            for i in range(self.size, self.capacity//2): # add on the Nones
                new_data.append(None)

            self.capacity = self.capacity//2

            self.data = [None] * self.capacity

            self.tail = self.size
            self.data = new_data

    def enqueue(self, val):
        """
        Add a value to the back of the queue.
        Calls grow & grows queue immediately after a value is added, if needed.
        :param val: the value to add
        :return: None
        """
        self.data[self.tail] = val
        self.size += 1
        self.tail = (self.tail + 1) % self.capacity
        self.grow()

    def dequeue(self):
        """
        Remove an element from the front of a queue.
        Calls shrink & shrinks queue immediately after a value is removed, if needed.
        :return: element popped, if empty returns None
        """
        if self.size > 0: # check for empty list
            popped = self.data[self.head]
            self.data[self.head] = None
            self.size -= 1
            self.head = (self.head + 1) % self.capacity
            self.shrink()

            return popped
        else:
            return None

class QStack:
    """
    Stack class, implemented with underlying Circular Queue
    """
    # DO NOT MODIFY THESE METHODS
    def __init__(self):
        self.cq = CircularQueue()
        self.size = 0

    def __eq__(self, other):
        """
        Defines equality for two QStacks
        :return: true if two stacks are equal, false otherwise
        """
        if self.size != other.size:
            return False

        if self.cq != other.cq:
            return False

        return True

    def __str__(self):
        """
        String representation of the QStack
        :return: the stack as a string
        """
        if self.size == 0:
            return "Empty stack"

        str_list = [str(self.cq.data[(self.cq.head + i) % self.cq.capacity]) for i in range(self.size)]
        return "Stack: " + ", ".join(str_list)

    # -----------MODIFY BELOW--------------
    def push(self, val):
        """
        Adds a value to the top of the stack.
        :param val: the value to add
        :return: None
        """
        self.cq.enqueue(val) # add value to bottom of stack
        for i in range(0, len(self.cq)-1): # move everything underneath the value we added
            self.cq.enqueue(self.cq.dequeue())

        self.size += 1

    def pop(self):
        """
        Removes a value to the top of the stack.
        :return: the value popped, if empty returns None.
        """
        popped = self.cq.dequeue()
        if popped is not None:
            self.size -= 1

        return popped

    def top(self):
        """
        Returns but does not remove the top element of the stack.
        :return: the top element of the stack, if the element is None returns None.
        """
        if self.size == 0:
            return None
        else:
            return self.cq.head_element()

def digit_swap(nums, replacements):
    """
    Given a string of characters "nums" and an integer "replacements", return the length of the
    longest substring of "nums" that contains the same character, given that you are allowed
    to swap "replacements" amount of characters.
    :param nums: the string of numbers to swap elements
    :param: replacements: the number of swaps that you are permitted to make
    :return: the length of the longest substring of nums that contains the same character
    """
    queue = CircularQueue()
    queue_dict = defaultdict(int)

    max_length = 0
    length = 0
    for i in nums:
        queue.enqueue(i)
        queue_dict[i] += 1
        max_length = max(max_length, queue_dict[i])
        while replacements < (len(queue) - max_length): # add to dict up to len of requirements
            queue_dict[queue.head_element()] -= 1
            queue.dequeue()
        length = max(length, len(queue))
    return length