"""
PROJECT 5 - AVL Trees
Name: Aidan Delfuoco
"""
import queue

class TreeNode:
    # DO NOT MODIFY THIS CLASS #
    __slots__ = 'value', 'parent', 'left', 'right', 'height'

    def __init__(self, value, parent=None, left=None, right=None):
        """
        Initialization of a node
        :param value: value stored at the node
        :param parent: the parent node
        :param left: the left child node
        :param right: the right child node
        """
        self.value = value
        self.parent = parent
        self.left = left
        self.right = right
        self.height = 0

    def __eq__(self, other):
        """
        Determine if the two nodes are equal
        :param other: the node being compared to
        :return: true if the nodes are equal, false otherwise
        """
        if type(self) is not type(other):
            return False
        return self.value == other.value

    def __str__(self):
        """String representation of a node by its value"""
        return str(self.value)

    def __repr__(self):
        """String representation of a node by its value"""
        return str(self.value)

class AVLTree:

    def __init__(self):
        # DO NOT MODIFY THIS FUNCTION #
        """
        Initializes an empty Binary Search Tree
        """
        self.root = None
        self.size = 0

    def __eq__(self, other):
        # DO NOT MODIFY THIS FUNCTION #
        """
        Describe equality comparison for BSTs ('==')
        :param other: BST being compared to
        :return: True if equal, False if not equal
        """
        if self.root is None and other.root is None:
            return True

        if self.size != other.size or self.root != other.root:
            return False  # size & root comp

        return self._is_equal(self.root.left, other.root.left) and self._is_equal(self.root.right, other.root.right)

    def _is_equal(self, root1, root2):
        # DO NOT MODIFY THIS FUNCTION #
        """
        Checks if roots are both not None then calls _compare, otherwise checks their equality.
        :param root1: root node of first tree
        :param root2: root node of second tree
        :return: True if equal, False if not
        """
        return self._compare(root1, root2) if root1 and root2 else root1 == root2

    def _compare(self, t1, t2):
        # DO NOT MODIFY THIS FUNCTION #
        """
        Recursively compares two trees, used in __eq__.
        :param t1: root node of first tree
        :param t2: root node of second tree
        :return: True if equal, False if not
        """
        if t1 is None or t2 is None:
            return t1 == t2
        if t1 != t2:
            return False
        return self._compare(t1.left, t2.left) and self._compare(t1.right, t2.right)

    def __str__(self):
        """
        Collects a visual representation of AVL tree
        :return: string of AVL tree
        """
        if not self.root:
            return "Empty AVL Tree..."

        root = self.root
        ans = ""
        bfs_queue = []
        track = {}
        bfs_queue.append((root, 0, root.parent))
        h = AVLTree.height(self.root)

        for i in range(h+1):
            track[i] = []

        while bfs_queue:
            node = bfs_queue.pop(0)
            if node[1] > h:
                break
            track[node[1]].append(node)

            if node[0] is None:
                bfs_queue.append((None, node[1] + 1, None))
                bfs_queue.append((None, node[1] + 1, None))
                continue

            if node[0].left:
                bfs_queue.append((node[0].left, node[1] + 1, node[0]))
            else:
                bfs_queue.append((None, node[1] + 1, None))

            if node[0].right:
                bfs_queue.append((node[0].right, node[1] + 1, node[0]))
            else:
                bfs_queue.append((None, node[1] + 1, None))

        spaces = pow(2, h) * 12
        ans += "\n"
        ans += "\t\tVisual Level Order Traversal of AVL Tree - Node (Parent Height)".center(spaces)
        ans += "\n\n"
        for i in range(h+1):
            ans += f"Level {i}: "
            for node in track[i]:
                level = pow(2, i)
                space = int(round(spaces / level))
                if node[0] is None:
                    ans += " " * space
                    continue
                ans += "{} ({} {})".format(node[0], node[2], node[0].height).center(space, " ")
            ans += "\n"
        return ans

    # ------- Implement/Modify the functions below ------- #

    def insert(self, node, value):
        """
        Does nothing if the value is already in the tree, else inserts the value as a node.
        Balances the tree if it needs it.
        :param node: the root of the (sub)tree
        :param value: the value to be inserted into the node in the form of a tree
        :return: None
        """
        # if node == None:
        #     if self.root == None:
        #         self.root = TreeNode(value)
        #         self.root.parent = None
        #         self.size += 1
        #         return
        #     else:
        #         self.size += 1
        #         return TreeNode(value)

        # if node.value > value:
        #     node.left = self.insert(node.left, value)
        #     node.left.parent = node
        # elif node.value < value:
        #     node.right = self.insert(node.right, value)
        #     node.right.parent = node
        # else:
        #     pass

        # self.update_height(node)

        # balance = self.get_balance(node)
        # if balance == -2 or balance == 2:
        #     #print(self)
        #     node = self.rebalance(node)
        #     return node.parent
        # #print(self)
        # # if node == self.root:
        # #     self.insert(self.root, self.root.value)
        # return node

        if self.root is None:
            new_node = TreeNode(value, None)
            self.root = new_node
            self.size += 1
            return

        if node.value == value:
            return

        if value > node.value:
            if node.right is None:
                self.set_child(node, TreeNode(value), False)
                self.size += 1
            else:
                self.insert(node.right, value)

        elif value < node.value:
            if node.left is None:
                self.set_child(node, TreeNode(value), True)
                self.size += 1
            else:
                self.insert(node.left, value)

        self.update_height(node)
        self.rebalance(node)

    def remove(self, node, value):
        """
        Removes a node from the tree. Does nothing if the value is not found.
        When removing a value with two children, replaces with the maximum of the left subtree.
        :param node: the root of the (sub)tree
        :param value: the value to remove from the tree
        :return: the root of the subtree
        """
        if node is None:
            return None

        if value < node.value:
            node.left = self.remove(node.left, value)
        elif value > node.value:
            node.right = self.remove(node.right, value)
        else:
            if node.left is None:
                node = node.right
            elif node.right is None:
                node = node.left
            else:
                min_value = min(node.right)
                node.value = min_value
                node.right = self.remove(node.right, min_value)

        self.update_height(node)
        self.rebalance(node)

        return node

    @staticmethod
    def height(node):
        """
        Returns the height of the given node.
        :param node: the node to find the height of
        :return: None
        """
        if node is None:
            return -1
        return node.height

    @staticmethod
    def update_height(node):
        """
        Updates the height of the node based on its children's heights.
        :param node: the node whos height will be updated
        :return: None
        """
        if node is None:
            return
        right = node.right
        left = node.left
        if node.right is not None:
            right = node.right.height
        else:
            right = -1
        if node.left is not None:
            left = node.left.height
        else:
            left = -1
        node.height = max(left, right) + 1

        # if node != None:
        #     left_height = -1
        #     if node.left != None:
        #         left_height = node.left.height # update left node's height

        #     right_height = -1
        #     if node.right != None:
        #         right_height = node.right.height # update right node's height

        #     node.height = max(left_height, right_height) + 1 # update parent node's height

        # if node == None:
        #     return

        # if node.right != None:
        #     right_height = node.right.height
        # else:
        #     right_height = 0

        # if node.left != None:
        #     left_height = node.left.height
        # else:
        #     left_height = 0

        # node.height = max(left_height, right_height) + 1

    def depth(self, value):
        """
        Returns the depth of the node with the given value. If the node is not found returns -1.
        :param value: the value of a node we are searching for
        :return: the depth of the node, if not found returns -1
        """
        # node = self.search(self.root, value)
        # depth = self.root.height - node.height
        # if node.parent.height > node.height+1:
        #     depth += 1

        # return depth

        depth = 0
        node = self.root
        while node:
            if value == node.value:
                return depth
            node, depth = node.left if node.value > value else node.right, depth + 1
        return -1

    def search(self, node, value):
        """
        Returns the node with the given value if found, else returns the potential parent node.
        :param node: the root of the (sub)tree
        :param value: the value to search for
        :return: the node with the given value if found, else returns the potential parent node
        """
        if node is None:
            return None
        if value < node.value:
            if node.left is None:
                return node
            return self.search(node.left, value)
        if value > node.value:
            if node.right is None:
                return node
            return self.search(node.right, value)
        if value == node.value:
            return node

    def inorder(self, node):
        """
        Returns a generator object of the tree traversed using the inorder method of traversal
        starting at the given node.
        :param node: node to start traversal at
        :return: a generator object of the tree traversed
        """
        if node is None:
            return None

        if node.left is not None:
            for i in self.inorder(node.left):
                yield i
        yield node

        if node.right is not None:
            for i in self.inorder(node.right):
                yield i

    def preorder(self, node):
        """
        Returns a generator object of the tree traversed using the preorder method of traversal
        starting at the given node.
        :param node: node to start traversal at
        :return: a generator object of the tree traversed
        """
        if node is None:
            return None

        yield node

        if node.left is not None:
            for i in self.preorder(node.left):
                yield i

        if node.right is not None:
            for i in self.preorder(node.right):
                yield i

    def postorder(self, node):
        """
        Returns a generator object of the tree traversed using the postorder method of traversal
        starting at the given node.
        :param node: node to start traversal at
        :return: a generator object of the tree traversed
        """
        if node is None:
            return None

        if node.left is not None:
            for i in self.postorder(node.left):
                yield i

        if node.right is not None:
            for i in self.postorder(node.right):
                yield i

        yield node

    def bfs(self):
        """
        Returns a generator object of the tree traversed using the breadth-first method of traversal
        starting at the given node.
        :return: a generator object of the tree traversed
        """
        bfs_queue = queue.Queue()
        if self.root is None:
            return None

        bfs_queue.put(self.root)
        while bfs_queue.qsize() != 0:
            node = bfs_queue.get()
            if node.left is not None:
                bfs_queue.put(node.left)
            if node.right is not None:
                bfs_queue.put(node.right)
            yield node

    def min(self, node):
        """
        Returns the minimum of the tree rooted at the given node.
        :param node: the root of the (sub)tree
        :return: the minimum value of the tree
        """
        if node is None:
            return None

        if node.left is None:
            return node

        return self.min(node.left)

    def max(self, node):
        """
        Returns the maximum of the tree rooted at the given node.
        :param node: the root of the (sub)tree
        :return: the maximum value of the tree
        """
        if node is None:
            return None

        if node.right is None:
            return node

        return self.max(node.right)

    def get_size(self):
        """
        Returns the number of nodes in the AVL Tree.
        :return: number of nodes in the Tree
        """
        return self.size

    @staticmethod
    def get_balance(node):
        """
        Returns the balance factor of the node passed in.
        Balance Factor = height of left subtree – the height of right subtree.
        :param node: the node to calculate the balance factor for
        :return: the balance factor for the given node
        """
        # if node != None:
        #     left_height = -1
        #     if node.left != None:
        #         left_height = AVLTree.height(node.left)

        #     right_height = -1
        #     if node.right != None:
        #         right_height = AVLTree.height(node.right)

        #     return left_height - right_height

        # else:
        #     return 0

        if node is None:
            return 0
        AVLTree.update_height(node)
        return AVLTree.height(node.left) - AVLTree.height(node.right)

    @staticmethod
    def set_child(parent, child, is_left):
        """
        Sets the parent node's child to the child node.
        :param parent: a parent node
        :param child: a child node
        :param is_left: a boolean that determines where the child is to be placed in relation to
        the parent where True is left and False is right
        :return: None
        """
        if parent:
            if is_left: # child to be placed left below parent
                parent.left = child
            else: # child to be placed right below parent
                parent.right = child

            if child is None:
                return
            else:
                child.parent = parent

        AVLTree.update_height(parent)

    @staticmethod
    def replace_child(parent, current_child, new_child):
        """
        Makes the new_child node a child of the parent node in place of the current_child node.
        :param parent: a parent node
        :param current_child: the child node to replace
        :param new_child: the child node to replace the previous with
        :return: None
        """
        if parent.left == current_child:
            AVLTree.set_child(parent, new_child, True)  # child to be repalced left below parent
        elif parent.right == current_child:
            AVLTree.set_child(parent, new_child, False) # child to be replaced right below parent

    def left_rotate(self, node):
        """
        Performs an AVL left rotation on the subtree rooted at node.
        :param node: the root of the (sub)tree
        :return: the root of the new subtree
        """
        # right_left_child = node.right.left
        # if node.parent is not None: # node is not the root
        #     AVLTree.replace_child(node.parent, node, node.right)
        # else: # node is the root
        #     self.root = node.right
        #     self.root.parent = None

        # AVLTree.set_child(node.right, node, True)
        # #AVLTree.set_child(node.right, node.right.right, False)
        # AVLTree.set_child(node, right_left_child, False)

        # self.update_height(node)
        # self.update_height(node.parent.left)
        # self.update_height(node.parent)

        # return node.parent

        root_next = node.right
        left_next = node
        right_next = node.right.right

        node_right_left = node.right.left

        if node.parent is not None:
            AVLTree.replace_child(node.parent, node, node.right)

        else:
            self.root = root_next
            self.root.parent = None
        AVLTree.set_child(root_next, node, True)
        AVLTree.set_child(node, node_right_left, False)

        self.update_height(node)
        self.update_height(node.parent.left)
        self.update_height(node.parent)

    def right_rotate(self, node):
        """
        Performs an AVL right rotation on the subtree rooted at node.
        :param node: the root of the (sub)tree
        :return: the root of the new subtree
        """
        # left_right_child = node.left.right
        # if node.parent is not None: # node is not the root
        #     AVLTree.replace_child(node.parent, node, node.left)
        # else: # node is the root
        #     self.root = node.left
        #     self.root.parent = None

        # AVLTree.set_child(node.left, node, False)
        # #AVLTree.set_child(node.right, node.left.left, True)
        # AVLTree.set_child(node, left_right_child, True)

        # self.update_height(node)
        # self.update_height(node.parent.left)
        # self.update_height(node.parent)

        # return node.parent

        root_next = node.left
        right_next = node
        left_next = node.left.left

        node_left_right = node.left.right

        if node.parent is not None:
            AVLTree.replace_child(node.parent, node, node.left)

        else:
            self.root = root_next
            self.root.parent = None
        AVLTree.set_child(root_next, node, False)
        AVLTree.set_child(right_next, node_left_right, True)

        self.update_height(node)
        self.update_height(node.parent.left)
        self.update_height(node.parent)

    def rebalance(self, node):
        """
        Rebalances the subtree rooted at the node if needed.
        :param node: the root of the (sub)tree
        :return: the root of the new, balanced subtree
        """
        self.update_height(node)
        if self.get_balance(node) == -2:
            if self.get_balance(node.right) == 1: # double rotation
                self.right_rotate(node.right)
            return self.left_rotate(node)

        elif self.get_balance(node) == 2:
            if self.get_balance(node.left) == -1: # double rotation
                self.left_rotate(node.left)
            return self.right_rotate(node)
