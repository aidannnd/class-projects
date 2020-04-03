"""
Implemented by: Yash Vesikar and Brandon Field
"""

class HashNode:
    """
    DO NOT EDIT
    """
    __slots__ = ["key", "value", "deleted"]

    def __init__(self, key, value, deleted=False):
        self.key = key
        self.value = value
        self.deleted = deleted

    def __repr__(self):
        return f"HashNode({self.key}, {self.value})"

    def __eq__(self, other):
        return self.key == other.key and self.value == other.value

    def __iadd__(self, other):
        self.value += other

class HashTable:
    """
    Hash Table Class
    """
    __slots__ = ['capacity', 'size', 'table', 'prime_index']

    primes = (
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83,
        89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179,
        181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277,
        281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389,
        397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499,
        503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617,
        619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739,
        743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859,
        863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991,
        997)

    def __init__(self, capacity=8):
        """
        DO NOT EDIT
        Initializes hash table
        :param capacity: capacity of the hash table
        """
        self.capacity = capacity
        self.size = 0
        self.table = [None] * capacity

        i = 0
        while HashTable.primes[i] <= self.capacity:
            i += 1
        self.prime_index = i - 1

    def __eq__(self, other):
        """
        DO NOT EDIT
        Equality operator
        :param other: other hash table we are comparing with this one
        :return: bool if equal or not
        """
        if self.capacity != other.capacity or self.size != other.size:
            return False
        for i in range(self.capacity):
            if self.table[i] != other.table[i]:
                return False
        return True

    def __repr__(self):
        """
        DO NOT EDIT
        Represents the table as a string
        :return: string representation of the hash table
        """
        represent = ""
        bin_no = 0
        for item in self.table:
            represent += "[" + str(bin_no) + "]: " + str(item) + '\n'
            bin_no += 1
        return represent

    def _hash_1(self, key):
        """
        ---DO NOT EDIT---
        Converts a string x into a bin number for our hash table
        :param key: key to be hashed
        :return: bin number to insert hash item at in our table, None if key is an empty string
        """
        if not key:
            return None
        hashed_value = 0

        for char in key:
            hashed_value = 181 * hashed_value + ord(char)
        return hashed_value % self.capacity

    def _hash_2(self, key):
        """
        ---DO NOT EDIT---
        Converts a string x into a hash
        :param x: key to be hashed
        :return: a hashed value
        """
        if not key:
            return None
        hashed_value = 0

        for char in key:
            hashed_value = 181 * hashed_value + ord(char)

        prime = HashTable.primes[self.prime_index]

        hashed_value = prime - (hashed_value % prime)
        if hashed_value % 2 == 0:
            hashed_value += 1
        return hashed_value

    def __len__(self):
        """
        don't edit this plz
        Getter for size
        :return: size
        """
        return self.size

    ########## EDIT BELOW ##########

    def __setitem__(self, key, value):
        """
        Creates a node in the hash table that has the key and value that are passed
        in as parameters.
        :param key: key parameter to be given to node
        :param value: value parameter to be given to node
        """
        self._insert(key, value)

    def __getitem__(self, key):
        """
        Gets the item with the key denoted by the item parameter.
        If the key does not exist in the table, raises a KeyError.
        :param key: key parameter to look for
        :return: the value associated with key
        """
        node = self._get(key)
        if node is None:
            raise KeyError
        return node.value

    def __delitem__(self, key):
        """
        Deletes the node that has the value denoted by the key parameter.
        If the key does not exist in the table, raise a KeyError.
        :param key: key parameter to look for
        """
        try:
            self._delete(key)
            self.size -= 1
        except TypeError: # self.table[location] was None in _delete
            raise KeyError
        
    def __contains__(self, key):
        """
        Determines if a node with the key denoted by the item parameter exists in the table
        :param key: key parameter to look for
        :return: True or False
        """
        location = self.hash(key)

        if self.table[location] is not None: # there is a node at location
            return True
        else: # item at location is None
            return False

    def hash(self, key, inserting=False):
        """
        Given a key string return an index in the hash table.
        If the key exists in the hash table, return the index of the existing HashNode
        If the key does not exist in the hash table, return the index of the next
        available empty position in the hash table.
        :param key: key parameter to look for
        :param inserting: to differentiate if we are looking for a postion to insert a node
        int, or performing a lookup/deletion.
        :return: an index of a location in the hash table (int)
        """
        i = 0
        while i < self.capacity:
            # calculate location based on double hash formula
            location = (self._hash_1(key) + i*self._hash_2(key)) % self.capacity
            
            if inserting:
                # location is None, location has previously been deleted, or
                # key already exists in table
                if self.table[location] is None or self.table[location].deleted or \
                self.table[location].key == key:
                    return location
                else:
                    i += 1
            else: # not inserting
                # location is None or key already exists in table
                if self.table[location] is None or self.table[location].key == key:
                    return location
                else:
                    i += 1

        return None # no open spot found

    def _insert(self, key, value):
        """
        Use the key and value parameters to add a HashNode to the hash table.
        If the key exists, overwrite the existing value.
        In the event that inserting causes the table to have a load factor of 0.5 or greater you must grow the table to double the existing capacity.
        :param key: key parameter to add as a HashNode
        :param value: value parameter to add as a HashNode
        """
        location = self.hash(key, True)

        if location is not None: # there is an open spot in table
            # location is None or previously deleted
            if self.table[location] is None or self.table[location].deleted:
                new_node = HashNode(key, value)
                self.table[location] = new_node
                self.size += 1

                load_factor = self.size/self.capacity
            
                if load_factor >= 0.5:
                    self._grow()
            else: # key already exists
                self.table[location].value = value

    def _get(self, key):
        """
        Find the HashNode with the given key in the hash table.
        :param key: key parameter to look for
        :return: type Node with given key (None if not found)
        """
        location = self.hash(key)

        if self.table[location]: # found the given key
            return self.table[location]
        return None # did not find given key

    def _delete(self, key):
        """
        Removes the HashNode with the given key from the hash table.
        :param key: key parameter to look for
        """
        location = self.hash(key)

        self.table[location].key, self.table[location].value = None, None
        self.table[location].deleted = True

    def _grow(self):
        """
        Double the capacity of the existing hash table.
        """
        self.capacity *= 2

        i = 0
        while HashTable.primes[i] <= self.capacity:
            i += 1
        self.prime_index = i - 1

        old_table = self.table
        self.clear()

        item = 0
        while item < len(old_table):
            if old_table[item]:
                if old_table[item].deleted:
                    continue
                node = old_table[item]
                self._insert(node.key, node.value)
            item += 1

    def update(self, pairs=[]):
        """
        Updates the hash table using an iterable of key value pairs.
        :param pairs: list to iterate over
        """
        for item in pairs:
            self._insert(item[0], item[1])

    def setdefault(self, key, default=None):
        """
        Sets the default value for the key denoted by the key parameter using the default parameter.
        If the key exists in the table already, return the key's value, otherwise return the default parameter.
        :param key: key parameter to look for and set value of
        :param default: value to set as the key's default value
        :return: mixed type
        """
        location = self.hash(key)

        if not self.table[location]:
            self._insert(key, default)
            return default
        elif self.table[location].key == key:
            return self.table[location].value        

    def keys(self):
        """
        Returns a generator object that contains all of the keys in the table.
        :return: type generator
        """
        for item in self.table:
            if item:
                yield item.key

    def values(self):
        """
        Returns a generator object that contains all of the values in the table.
        :return: type generator
        """
        for item in self.table:
            if item:
                yield item.value

    def items(self):
        """
        Returns a generator object that contains tuples of all key/value pairs in the table.
        :return: type generator
        """
        for item in self.table:
            if item:
                yield (item.key, item.value)

    def clear(self):
        """
        Should clear the table of HashNodes completely, in essence a reset of the table
        """
        self.size = 0
        self.table = self.capacity * [None]