import unittest
from circularqueue import CircularQueue, QStack, digit_swap

class TestProject1(unittest.TestCase):

    def test_accessors(self):
        queue = CircularQueue()

        # manually set queue variables to test accessors
        queue.data = [5, 10, 15, None]
        queue.head = 0
        queue.tail = 3
        queue.size = 3

        assert queue.is_empty() == False
        assert len(queue) == 3
        assert queue.head_element() == 5

    def test_grow(self):
        queue = CircularQueue(5)
        queue.data = [0, 1, 2, 3, 4]
        queue.head = 0
        queue.tail = 0
        queue.size = 5

        queue.grow()

        assert queue.data == [0, 1, 2, 3, 4, None, None, None, None, None]
        # print(queue.data)
        # print(queue.tail)
        # print(queue.head)
        # print(queue.capacity)

        queue2 = CircularQueue(5)
        queue2.data = [10,20,30,40]
        queue2.head = 1
        queue2.tail = 1
        queue2.capacity = 4
        queue2.size = 4

        queue2.grow()

        # print(queue2.data)
        # print(queue2.tail)
        # print(queue2.head)
        # print(queue2.capacity)

        queue3 = CircularQueue(5)
        queue3.data = [10, 20, 30, 40, 50]
        queue3.head = 1
        queue3.tail = 0
        queue3.size = 5

        queue3.grow()

        # print(queue3.data)
        # print(queue3.tail)
        # print(queue3.head)
        # print(queue3.capacity)

    def test_shrink(self):
        queue = CircularQueue(8)
        queue.data = [0, 1, None, None, None, None, None, None]
        queue.size = 2
        queue.head = 0
        queue.tail = 2

        queue.shrink()

        assert queue.data == [0, 1, None, None]
        assert queue.size == 2
        assert queue.capacity == 4
        assert queue.head == 0
        assert queue.tail == 2

        # print(queue.data)
        # print(queue.tail)
        # print(queue.head)
        # print(queue.capacity)

        queue2 = CircularQueue(5)
        queue2.data = [10, 20, 30, 40, None, None, None, None, None, None, None, None, None, None, None, None]
        queue2.head = 1
        queue2.tail = 0
        queue2.size = 4
        queue2.capacity = 16

        queue2.shrink()

        # print(queue2.data)
        # print(queue2.tail)
        # print(queue2.head)
        # print(queue2.capacity)

        queue3 = CircularQueue(5)
        queue3.data = [4, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, 6, 5]
        queue3.head = 16
        queue3.tail = 1
        queue3.size = 3
        queue3.capacity = 18

        queue3.shrink()

        # print(queue3.data)
        # print("tail: ", queue3.tail)
        # print("head: ", queue3.head)
        # print("size: ", queue3.size)
        # print("capacity: ", queue3.capacity)

    def test_enqueue(self):
        queue = CircularQueue(4)
        queue.data = [1, None]
        queue.size = 1
        queue.head = 0
        queue.tail = 0
        queue.capacity = 1

        queue.enqueue(1)
        queue.enqueue(2)
        queue.enqueue(3)

        ########

        queue = CircularQueue()

        queue.enqueue(10)
        queue.enqueue(20)
        queue.enqueue(30)

        assert queue.data == [10, 20, 30, None]
        assert queue.size == 3
        assert queue.head == 0
        assert queue.tail == 3
        assert queue.capacity == 4

        ##############

        queue = CircularQueue(4)
        queue.data = [3, None, 1, 2]
        queue.size = 3
        queue.head = 2
        queue.tail = 1

        queue.enqueue(4)

        # print(queue.data)
        # print("tail: ", queue.tail)
        # print("head: ", queue.head)
        # print("size: ", queue.size)
        # print("capacity: ", queue.capacity)

    def test_dequeue(self):
        queue = CircularQueue(6)

        for i in range(0, 5):
            queue.enqueue(i * 5)

        assert queue.data == [0, 5, 10, 15, 20, None]
        assert queue.size == 5
        assert queue.capacity == 6
        assert queue.head == 0
        assert queue.tail == 5

        queue.dequeue()

        assert queue.data == [None,5,10,15,20,None]
        assert queue.size == 4
        assert queue.capacity == 6
        assert queue.head == 1
        assert queue.tail == 5

        ###############

        queue = CircularQueue(0)
        queue.data = []
        queue.size = 0
        queue.head = 0
        queue.tail = 0

        queue.dequeue()
        queue.dequeue()
        queue.dequeue()

        # print(queue.data)
        # print("tail: ", queue.tail)
        # print("head: ", queue.head)
        # print("size: ", queue.size)
        # print("capacity: ", queue.capacity)

    def test_qstack_top(self):
        stack = QStack()

        #manually enqueue to test top accessor function
        stack.cq.enqueue(10)
        stack.size = 1

        assert stack.top() == 10

        stack.cq.enqueue(20)
        stack.size += 1

        assert stack.top() == 10

    def test_qstack_push(self):
        stack = QStack()
        stack.push(10)

        assert stack.top() == 10
        assert stack.size == 1

        stack.push(20)

        assert stack.top() == 20
        assert stack.size == 2

        # print(stack)

    def test_qstack_pop(self):
        stack = QStack()

        stack.push(1)
        stack.push(2)
        stack.push(3)

        assert stack.pop() == 3
        assert stack.top() == 2
        assert stack.size == 2

    def test_digit_swap(self):
        nums = "5656"
        replacements = 2
        assert digit_swap(nums, replacements) == 4  # example input 1

        nums = "56787776646"
        replacements = 1
        assert digit_swap(nums, replacements) == 5  # example input 2

if __name__ == '__main__':
    unittest.main()