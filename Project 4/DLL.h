#pragma once
#include <iostream>
using std::cout;
using std::ostream;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <sstream>
using std::ostringstream;
// DO NOT MODIFY
//
// Node
//
struct Node {
  string key{};
  int value{};
  Node *next = nullptr;
  Node *prev = nullptr;
  Node() = default;
  Node(string, int, Node * = nullptr, Node * = nullptr);
  bool operator==(const Node &) const;
  friend ostream &operator<<(ostream &out, const Node &n) {
    out << n.key << ":" << n.value;
    return out;
  }
};

Node::Node(string key_, int value_, Node *prev_, Node *next_) {
  key = key_;
  value = value_;
  prev = prev_;
  next = next_;
}

bool Node::operator==(const Node &n) const {
  if ((key == n.key) && (value == n.value)) {
    return true;
  } else {
    return false;
  }
}

// DO NOT MODIFY
//
// DLL
//
class DLL {
private:
  Node *head_ = nullptr;
  Node *tail_ = nullptr;
  size_t sz_ = 0;

public:
  DLL() = default;
  DLL(vector<Node>);
  DLL(const DLL &);
  DLL &operator=(DLL list);
  ~DLL();
  Node *get_head();
  Node *get_tail();
  size_t get_size();
  Node add_back(string, int);
  Node add_front(string, int);
  Node add_after(string, string, int);
  Node search(string);
  Node* pointer_search(string);
  Node remove_front();
  Node remove_back();
  Node remove_key(string);
  int update_value(string, int);
  friend ostream &operator<<(ostream &out, const DLL &list) {
    auto itr = list.head_;
    ostringstream oss;
    for (; itr != nullptr; itr = itr->next) {
      oss << itr->key << ":" << itr->value << ", ";
    }
    string ans = oss.str();
    ans = ans.substr(0, ans.size() - 2);
    out << ans;
    return out;
  }
};

Node *DLL::get_head() { return head_; }
Node *DLL::get_tail() { return tail_; }
size_t DLL::get_size() { return sz_; }

DLL::~DLL() {
  while (head_)
    delete std::exchange(head_, head_->next);
}

DLL & DLL::operator =(DLL list) {
  using std::swap;
  swap(head_,list.head_);
  swap(tail_,list.tail_);
  swap(sz_,list.sz_);
  return *this;
}

DLL::DLL(const DLL &list) {
  for (Node *p = list.head_; p; p = p->next)
    add_back(p->key, p->value);
}

DLL::DLL(vector<Node> vec) {
  for (const auto &node : vec)
    add_back(node.key, node.value);
}

/* BEGIN MODIFICATION BELOW */
Node DLL::add_back(string str, int num) {
	Node *new_node = new Node(str, num);
	// if the list is empty, the new node should be the head and tail
	if (sz_ == 0) // case for if list is empty, set head and tail to the new node
		head_ = new_node; // set head to new node
	else { // list is not empty
		(*tail_).next = new_node; // set the old tail node's next to the new node
		(*new_node).prev = tail_; // set the new node's prev to the old tail node
	}
	tail_ = new_node; // set the tail node to be the new node
	sz_++;
	return *new_node;
}

Node DLL::add_front(string str, int num) {
	Node *new_node = new Node(str, num);
	// if the list is empty, the new node should be the head and tail
	if (sz_ == 0) // case for if list is empty, set head and tail to the new node
		tail_ = new_node; // set tail to new node
	else { // list is not empty
		(*head_).prev = new_node; // set the old head node's prev to the new node
		(*new_node).next = head_; // set the new node's next to the old head node
	}
	head_ = new_node; // set the head node to be the new node
	sz_++;
	return *new_node;
}

Node DLL::search(string find_key) {
	if (sz_ != 0) { // make sure there is at least one node in the list
		Node current_node = *head_;
		// start at the head, if the current_node key is equal to find_key, end the loop and return
		// if it is not equal, change current_node to the next node and repeat
		for (;;) {
			if (current_node.key == find_key)
				return current_node;
			else {
				if (current_node.next == nullptr) // end of the list, did not find a match
					break;
				current_node = *(current_node.next); // set current node to the next node
			}
		}
	}

	Node *empty_node = new Node("", 0); // default node to return in case of no match
	return *empty_node;
}

Node* DLL::pointer_search(string find_key) { // same thing as search but returns a pointer to a Node
	if (sz_ != 0) { // make sure there is at least one node in the list
		Node* current_node = head_;
		// start at the head, if the current_node key is equal to find_key, end the loop and return
		// if it is not equal, change current_node to the next node and repeat
		for (;;) {
			if ((*current_node).key == find_key)
				return current_node;
			else {
				if ((*current_node).next == nullptr) // end of the list, did not find a match
					break;
				current_node = (*current_node).next; // set current node to the next node
			}
		}
	}

	Node *empty_node = new Node("", 0); // default node to return in case of no match
	return empty_node;
}


Node DLL::add_after(string add_key, string str, int num) {
	Node* searched_node = pointer_search(add_key); // gets a pointer to the node to be added after
	Node *new_node;

	if ((*searched_node).key != "") { // make sure searched node was found
		if (searched_node == tail_) { // if searched node is at the end of DLL
			new_node = new Node(str, num, searched_node);
			tail_ = new_node;
		} else { // search node is somewhere in the DLL but not at the end
			new_node = new Node(str, num, searched_node, (*searched_node).next); // create new node whose prev is the searched node
			(*(*searched_node).next).prev = new_node; // set the prev of the node to the right of the new node to the new node
		}
		(*searched_node).next = new_node; // set searched nodes next to new node
		sz_++;

		return *new_node;
	} else // searched node was not found
		return *searched_node;
}


Node DLL::remove_front() {
	if (sz_ == 0) {
		Node *empty_node = new Node("", 0); // default node to return in case of empty DLL
		return *empty_node;
	}
	Node old_head = *head_;
	if (sz_ == 1) { // DLL size 1 case
		head_ = nullptr;
		tail_ = nullptr;
	}
	else { // DLL is greater than size 1
		(*(*head_).next).prev = nullptr; // set head prev to nullptr
		head_ = (*head_).next; // set head to node after head
	}
	sz_--;
	return old_head;
}

Node DLL::remove_back() {
	if (sz_ == 0) {
		Node *empty_node = new Node("", 0); // default node to return in case of empty DLL
		return *empty_node;
	}
	Node old_tail = *tail_;
	if (sz_ == 1) { // DLL size 1 case
		head_ = nullptr;
		tail_ = nullptr;
	}
	else { // DLL is greater than 1
		(*(*tail_).prev).next = nullptr; // set tail next to nullptr
		tail_ = (*tail_).prev; // set tail to node before tail
	}
	sz_--;
	return old_tail;
}

Node DLL::remove_key(string to_remove) {
	Node* searched_node = pointer_search(to_remove); // gets a pointer to the node to be removed

	if ((*searched_node).key != "") { // make sure searched node was found
		if (searched_node == tail_) // if searched node is at the end of DLL
			remove_back();
		else if (searched_node == head_) // if searched node is at the front of DLL
			remove_front();
		else { // search node is somewhere in the DLL but not at the end or front
			(*(*searched_node).next).prev = (*searched_node).prev; // set the prev of the node to the right of the removed node to the node to the left of the removed node
			(*(*searched_node).prev).next = (*searched_node).next;// set the next of the node to the left of the removed node to the node to the right of the removed node
			sz_--;
		}
	}
	return *searched_node;
}

int DLL::update_value(string find_key, int new_value) {
	Node* searched_node = pointer_search(find_key); // gets a pointer to the node to be updated

	if ((*searched_node).key != "") { // make sure searched key was found
		(*searched_node).value = new_value;
		return new_value;
	}
	return -1; // key not found in DLL
}
