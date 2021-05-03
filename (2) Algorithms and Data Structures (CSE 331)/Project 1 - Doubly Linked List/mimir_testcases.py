import unittest
from DLL import DLL, DLLNode, DLLError, reverse

class TestProject1(unittest.TestCase):

    def test_insert_front_back(self):
        lst = DLL()
        lst.insert_front(1)
        lst.insert_front(2)
        lst.insert_front(3)
        lst.insert_back(4)
        lst.insert_back(5)

        assert lst.head.value == 3
        assert lst.tail.value == 5

        forward, backward = [], []
        head = lst.head
        while head is not None:
            forward.append(head.value)
            head = head.next
        tail = lst.tail
        while tail is not None:
            backward.append(tail.value)
            tail = tail.prev

        assert forward == [3, 2, 1, 4, 5]
        assert backward == [5, 4, 1, 2, 3]

    def test_accessors(self):
        lst = DLL()

        assert lst.is_empty()
        assert lst.size == 0

        for _ in range(5):
            lst.insert_front(1)

        assert not lst.is_empty()
        assert lst.size == 5

        for _ in range(3):
            lst.delete_front()

        assert not lst.is_empty()
        assert lst.size == 2

    def test_delete_front_back(self):
        def condense(linkedlist):
            res = list()
            node = linkedlist.head
            while node is not None:
                res.append(node.value)
                node = node.next
            return res

        lst = DLL()
        inserts = [1, 4, 0, 10, 3, 7, 9]

        for x in inserts:
            lst.insert_back(x)

        lst.delete_front()
        inserts.pop(0)

        assert inserts == condense(lst)

        lst.delete_back()
        inserts.pop()

        assert inserts == condense(lst)

    def test_delete_value_all(self):
        def condense(linkedlist):
            res = list()
            node = linkedlist.head
            while node is not None:
                res.append(node.value)
                node = node.next
            return res

        lst = DLL()
        insert = [1, 2, 3, 4, 5, 6, 1, 1, 2, 4, 1, 9]

        for i in insert:
            lst.insert_back(i)

        lst.delete_value(1)
        assert condense(lst) == insert[1:]

        lst.delete_all(1)
        assert condense(lst) == [2, 3, 4, 5, 6, 2, 4, 9]

    def test_find_first_last_all(self):
        lst = DLL()
        inserts = [9, 16, 5, 58, 32, 1, 4, 58, 67, 2, 4]

        for i in inserts:
            lst.insert_back(i)

        first = lst.find_first(32)

        assert first.value == 32
        assert first.next.value == 1
        assert first.prev.value == 58

        last = lst.find_last(2)

        assert last.value == 2
        assert last.next.value == 4
        assert last.prev.value == 67

        list_of_58s = lst.find_all(58)

        assert len(list_of_58s) == 2
        for i in list_of_58s:
            assert i.value == 58

        first = list_of_58s[0]
        second = list_of_58s[1]

        assert first.next.value == 32
        assert first.prev.value == 5

        assert second.next.value == 67
        assert second.prev.value == 4

    def test_count_sum(self):
        lst = DLL()
        inserts = [1, 3, 1, 4, 5, 6, 1, 3, 8]

        for i in inserts:
            lst.insert_back(i)

        assert lst.count(1) == 3
        assert lst.sum() == 32

    def test_reverse(self):
        def condense(linkedlist):
            res = list()
            node = linkedlist.head
            while node is not None:
                res.append(node.value)
                node = node.next
            return res

        lst = DLL()
        inserts = [1, 2, 3, 4, 5]

        for i in inserts:
            lst.insert_back(i)

        reverse(lst)

        print(condense(lst))
        assert condense(lst) == [5, 4, 3, 2, 1]

if __name__ == '__main__':
    unittest.main()