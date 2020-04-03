"""
PROJECT 2 - Linked List Recursion
Name: Aidan Delfuoco
"""

class LinkedNode:
    # DO NOT MODIFY THIS CLASS #
    __slots__ = '_value', '_next'

    def __init__(self, value, next=None):
        """
        DO NOT EDIT
        Initialize a node
        :param value: value of the node
        :param next: pointer to the next node in the LinkedList, default is None
        """
        self._value = value  # element at the node
        self._next = next  # reference to next node in the LinkedList

    def __repr__(self):
        """
        DO NOT EDIT
        String representation of a node
        :return: string of value
        """
        return str(self._value)

    __str__ = __repr__

    def get_value(self):
        return self._value

    def get_next(self):
        return self._next

    def set_value(self, value):
        self._value = value

    def set_next(self, next):
        self._next = next

# IMPLEMENT THESE FUNCTIONS - DO NOT MODIFY FUNCTION SIGNATURES #

def insert(value, node=None):
    """
    Insert the given value into the linked list that has head node
    :param value: value of the node
    :param node: the head node of the linked list
    :return: the starting node of the linked list
    """
    # if node=None there is no existing linked list to insert into

    new_node = LinkedNode(value)
    if node is None:
        return new_node
    elif node.get_next() is None: # hit the tail node, insert after
        node.set_next(new_node)
    else: # somewhere at the beginning or within the list, not at end
        insert(value, node._next) # go to next node

    return node

def to_string(node):
    """
    Generate and return a string representation of the list, starting at head node
    :param node: node to begin at
    :return: string representation of the list
    """
    # return empty string if there are no nodes in list

    if node is None:
        return ""
    elif node.get_next() is None: # hit the tail node, no trailing comma
        return str(node._value)
    else: # somewhere at the beginning or within the list, not at end
        return str(node._value) + ", " + str(to_string(node._next))

def remove(value, node):
    """
    Remove the first node in the list with the given value starting at head node
    :param value: the value to remove
    :param node: the starting head node
    :return: starting node of the linked list
    """
    starting_node = node
    if node is None: # list is empty
        pass
    elif node._value is value: # head is the value to remove
        return node.get_next()
    elif node.get_next() is None: # end of list, no value found
        pass
    elif node.get_next()._value is value: # found value to remove
        node.set_next(node.get_next().get_next())
    else:
        remove(value, node._next) # have not yet found value to remove

    return starting_node

def remove_all(value, node):
    """
    Remove all nodes in the list with the given value starting at head node
    :param value: the value to remove
    :param node: the starting head node
    :return: starting node of the linked list
    """
    starting_node = node
    if node is None: # list is empty
        pass
    elif node._value is value: # head is the value to remove
        starting_node = remove_all(value, node.get_next())
    elif node.get_next() is None: # end of list
        pass
    elif node.get_next()._value is value: # found value to remove
        node.set_next(node.get_next().get_next())
        remove_all(value, starting_node)
    else:
        remove_all(value, node._next) # have not yet found value to remove

    return starting_node

def search(value, node):
    """
    Looks for value in list starting with head node
    :param value: value to look for
    :param node: the starting head node
    :return: True if the value is in the list and False if it is not in the list
    """
    found_node = False
    if node is None: # list is empty
        pass
    elif node._value is value: # found value
        return True
    elif node.get_next() is None: # end of list, no value found
        pass
    else:
        found_node = search(value, node._next) # have not yet found value

    return found_node

def length(node):
    """
    Calculates and returns the length of the list starting with head node
    :param node: the starting head node
    :return: length of the list
    """
    # if the list is empty, it has a length of 0

    list_length = 0
    if node is not None: # not at end of list
        list_length += 1
        list_length += length(node._next)

    return list_length

def sum_list(node):
    """
    Calculates and returns the sum of the list starting with head node
    :param node: the starting head node
    :return: sum of the list
    """
    # if the list is empty, it has a sum of 0

    list_sum = 0
    if node is not None: # not at end of list
        list_sum += node._value
        list_sum += sum_list(node._next)

    return list_sum

def count(value, node):
    """
    counts and returns how many times the given value occurs in the list starting at head node
    :param value: value to look for
    :param node: the starting head node
    :return: how many times the given value occurs in the list
    """
    list_count = 0
    if node is None: # list is empty or end of list
        pass
    elif node._value is value: # found value at current node
        list_count += 1
        list_count += count(value, node._next)
    else: # did not find value at current node
        list_count += count(value, node._next)

    return list_count

def reverse(node):
    """
    Given a list starting with head node, reverse this list
    :param node: the starting head node
    :return: the head node of the reversed list
    """
    if node._next is None: # end of list
        return node

    if node is None: # empty list
        return node

    new_node = reverse(node._next)
    (node._next)._next = node
    node._next = None
    return new_node