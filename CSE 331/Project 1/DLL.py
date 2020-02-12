class DLLError(Exception):
    """
    Class representing an error related to the DLL class implemented below.
    """
    pass

class DLLNode:
    """
    Class representing a node in the doubly linked list implemented below.
    """

    def __init__(self, value, next=None, prev=None):
        """
        Constructor
        @attribute value: the value to give this node
        @attribute next: the next node for this node
        @attribute prev: the previous node for this node
        """
        self.next = next
        self.prev = prev
        self.value = value

    def __repr__(self):
        return str(self.value)

    def __str__(self):
        return str(self.value)

class DLL:
    """
    Class representing a doubly linked list.
    """
    def __init__(self):
        """
        Constructor
        @attribute head: the head of the linked list
        @attribute tail: the tail of the linked list
        @attribute size: the size of the linked list
        """
        self.head = None
        self.tail = None
        self.size = 0

    def __repr__(self):
        """
        iterates through the linked list to generate a string representation
        :return: string representation of the linked list
        """
        res = ""
        node = self.head
        while node:
            res += str(node)
            if node.next:
                res += " "
            node = node.next
        return res

    def __str__(self):
        """
        iterates through the linked list to generate a string representation
        :return: string representation of the linked list
        """
        res = ""
        node = self.head
        while node:
            res += str(node)
            if node.next:
                res += " "
            node = node.next
        return res

    ######### MODIFY BELOW ##########

    def is_empty(self):
        """
        Determines if the linked list is empty or not
        :return: [boolean] true if DLL is empty, false otherwise
        """
        if self.size == 0:
            return True
        else:
            return False

    def insert_front(self, value):
        """
        Inserts a value into the front of the list
        :param value: the value to insert
        """
        new_node = DLLNode(value)
        # if the list is empty, the new node should be the head and tail
        if self.is_empty(): # case for if list is empty, set head and tail to the new node
            self.tail = new_node
        else:
            (self.head).prev = new_node # set the old head node's prev to the new node
            new_node.next = self.head # set the new node's next to the old head node

        self.head = new_node # set the head node to be the new node
        self.size += 1

    def insert_back(self, value):
        """
        Inserts a value into the back of the list
        :param value: the value to insert
        """
        new_node = DLLNode(value)
        # if the list is empty, the new node should be the head and tail
        if self.is_empty(): # case for if list is empty, set head and tail to the new node
            self.head = new_node
        else:
            (self.tail).next = new_node # set the old tail node's next to the new node
            new_node.prev = self.tail # set the new node's prev to the old tail node

        self.tail = new_node # set the tail node to be the new node
        self.size += 1

    def delete_front(self):
        """
        Deletes the front node of the list
        """
        if self.is_empty(): # in case of empty DLL
            raise DLLError('error')
        if self.size == 1: # DLL size 1 case
            self.head = None
            self.tail = None
        else: # DLL is greater than size 1
            (self.head).next.prev = None # set head prev to None
            self.head = (self.head).next # set head to node after head
        self.size -= 1


    def delete_back(self):
        """
        Deletes the back node of the list
        """
        if self.is_empty(): # in case of empty DLL
            raise DLLError('error')
        if self.size == 1: # DLL size 1 case
            self.head = None
            self.tail = None
        else: # DLL is greater than size 1
            (self.tail).prev.next = None # set tail next to None
            self.tail = (self.tail).prev # set tail to node before tail
        self.size -= 1

    def delete_value(self, value):
        """
        Deletes the first instance of the value in the list.
        :param value: The value to remove
        """
        searched_node = self.find_first(value) # get the node to remove

        if searched_node.value != "": # make sure searched node was found
            if searched_node == self.tail: # if searched node is at the end of DLL
                self.delete_back()
            elif searched_node == self.head: # if searched node is at the front of DLL
                self.delete_front()
            else: # searched node is somewhere in the DLL but not at the end or front
                # set the prev of the node to the right of the removed node to the node to the
                # left of the removed node
                (searched_node.next).prev = searched_node.prev
                # set the next of the node to the left of the removed node to the node to the
                # right of the removed node
                (searched_node.prev).next = searched_node.next
                self.size -= 1
        else:
            raise DLLError('error')

    def delete_all(self, value):
        """
        Deletes all instances of the value in the list
        :param value: the value to remove
        """
        node_list = self.find_all(value) # get the list of nodes to remove

        if node_list: # make sure at least one node was found
            for searched_node in node_list:
                if searched_node == self.tail: # if searched node is at the end of DLL
                    self.delete_back()
                elif searched_node == self.head: # if searched node is at the front of DLL
                    self.delete_front()
                else: # searched node is somewhere in the DLL but not at the end or front
                    # set the prev of the node to the right of the removed node to the node to the
                    # left of the removed node
                    (searched_node.next).prev = searched_node.prev
                    # set the next of the node to the left of the removed node to the node to the
                    # right of the removed node
                    (searched_node.prev).next = searched_node.next
                    self.size -= 1
        else:
            raise DLLError('error')

    def find_first(self, value):
        """
        Finds the first instance of the value in the list
        :param value: the value to find
        :return: [DLLNode] the first node containing the value
        """
        if self.size != 0: # make sure there is at least one node in the list

            current_node = self.head
            # start at the head, if the current_node value is equal to value,
            # end the loop and return
		    # if it is not equal, change current_node to the next node and repeat
            while True:
                if current_node.value == value:
                    return current_node
                else:
                    if current_node.next is None: # end of the list, did not find a match
                        raise DLLError('error')
                    current_node = current_node.next # set current node to the next node

        else:
            raise DLLError('error')

    def find_last(self, value):
        """
        Finds the last instance of the value in the list
        :param value: the value to find
        :return: [DLLNode] the last node containing the value
        """
        if self.size != 0: # make sure there is at least one node in the list

            current_node = self.tail
            # start at the tail, if the current_node value is equal to value,
            # end the loop and return
		    # if it is not equal, change current_node to the prev node and repeat
            while True:
                if current_node.value == value:
                    return current_node
                else:
                    if current_node.prev is None: # end of the list, did not find a match
                        raise DLLError('error')
                    current_node = current_node.prev # set current node to the prev node

        else:
            raise DLLError('error')

    def find_all(self, value):
        """
        Finds all of the instances of the value in the list
        :param value: the value to find
        :return: [List] a list of the nodes containing the value
        """
        node_list = []
        if self.size > 0: # make sure there is at least one node in the list
            current_node = self.head
            # start at the head, if the current_node value is equal to value, add to the node_list
		    # if it is not equal, change current_node to the next node and repeat
            while True:
                if current_node.value == value:
                    node_list.append(current_node) # found a matching node
                if current_node.next is None: # end of the list
                    break
                current_node = current_node.next # set current node to the next node
        if node_list: # value was found in list
            return node_list
        raise DLLError('error')

    def count(self, value):
        """
        Finds the count of times that the value occurs in the list
        :param value: the value to count
        :return: [int] the count of nodes that contain the given value
        """
        try:
            node_list = self.find_all(value)
            return len(node_list)
        except DLLError:
            return 0


    def sum(self):
        """
        Finds the sum of all nodes in the list
        :param start: the indicator of the contents of the list
        :return: the sum of all items in the list
        """

        # lists for each required type
        sum = 0
        sum_str = ""
        sum_list = []
        current_node = self.head
        # check the type of each element, add it to the correct list
        while current_node is not None:
            if isinstance(current_node.value, str):
                sum_str += current_node.value
            elif isinstance(current_node.value, int) or isinstance(current_node.value, float):
                sum += current_node.value
            elif isinstance(current_node.value, list):
                sum_list += current_node.value

            current_node = current_node.next

        # return correct type list
        if sum:
            return sum
        elif sum_list:
            return sum_list
        elif sum_str:
            return sum_str
        else:
            return None

def reverse(LL):
    """
    Reverses a linked list in place
    :param LL: The linked list to reverse
    """ 
    
    current_node = LL.head
    temp_node = DLLNode(None)
    
    while current_node is not None:
        # update nodes in LL
        temp_node = current_node.prev
        current_node.prev = current_node.next
        current_node.next = temp_node
        current_node = current_node.prev
    
    if temp_node is not None: # check for empty list
        # update head and tail
        temp_head = LL.head
        LL.head = temp_node.prev
        LL.tail = temp_head