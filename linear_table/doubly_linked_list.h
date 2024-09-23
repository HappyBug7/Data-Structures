#include <type_traits>

template<typename T>
class DLList {
private:
  class Node {
  public:
    Node* next;
    Node* prev;
    T val;
    Node() : val(T()), next(NULL), prev(NULL) {}  
    Node(Node* prev, T val) : val(val), next(NULL), prev(prev) {}  
    Node(Node* prev, T val, Node* next) : val(val), next(next), prev(prev) {}  
  };
  Node* dummy_head;
  int size;

  bool is_index_valid(int idx) {
    return idx>=0 && idx<size;
  }

  void set_size(int size_new) const {
    size = size_new;
  }
  
public:
  DLList() : dummy_head(new Node()), size(0) {}
  DLList(int capasity) : dummy_head(new Node()), size(0) {}

  int get_size() {
    return size;
  }

  Node* get_head() {
    return dummy_head -> next;
  } 

  Node* get_tail() const {
    return dummy_head -> prev;
  }

  Node* get_tail() {
    if (!is_empty()) { 
      return dummy_head -> prev;
    } else {
      return dummy_head;
    }
  }

  T prev(int idx) {
    if (is_index_valid(idx-1)) {
      return T();
    }
    Node* node = index_node(idx-1);
    return node -> val;
  }

  T prev(Node* node) {
    return node -> prev -> val;
  } 

  Node* prev_node(Node* node) {
    return node -> prev;
  }

  T next(int idx) {
    if (is_index_valid(idx+1)) {
      return T();
    }
    Node* node = index_node(idx+1);
    return node -> val;
  }

  T next(Node* node) {
    return node -> next -> val;
  }

  Node* next_node(Node* node) {
    return node -> next;
  }

  bool is_full() {
    return false;
  }

  bool is_empty() {
    return size == 0;
  }

  void push_back(T val) {
    Node* tail = get_tail();
    tail -> next = new Node(tail, val, dummy_head);
    dummy_head -> prev = tail -> next;
    size++;
  }

  void push_front(T val) {
    Node* head = get_head();
    Node* new_head = new Node(dummy_head, val, head);
    dummy_head -> next = new_head;
    head -> prev = dummy_head -> next;
    size++;
  }

  void print_list() {
    Node* curr = dummy_head -> next;
    while (curr != dummy_head) {
      if (curr -> next != dummy_head) {
        std::cout<<curr -> val<<"->";
      } else {
        std::cout<<curr -> val<<std::endl;
      }
      curr = curr -> next;
    }
  }

  void print_list(std::ostream& os) {
    Node* curr = dummy_head -> next;
    while (curr != dummy_head) {
      if (curr -> next != dummy_head) {
        os<<curr -> val<<"->";
      } else {
        os<<curr -> val;
      }
      curr = curr -> next;
    }
  }

  Node* index_node(int idx) {
    if (!is_index_valid(idx)) {
      return NULL;
    }
    int idx_curr = 0;
    if (idx < size/2) {
      Node* curr = dummy_head -> next;
      while (idx_curr < idx) {
        curr = curr -> next;
        idx_curr++;
      }
      return curr;  
    } else {
      idx_curr = size-1;
      Node* curr = dummy_head -> next;
      while (idx_curr > idx) {
        curr = curr -> prev;
        idx_curr--;
      }
      return curr;
    }
  }

  T index(int idx) {
    return index_node(idx) -> val;
  }

  int search(T val) {
    int idx = 0;
    Node* curr = dummy_head -> next;
    while (idx < size && curr -> val != val) {
      idx++;
      curr = curr -> next;
    }
    if (curr == dummy_head) {
      return -1;
    }
    return idx;
  }

  int search(Node* node) {
    int idx = 0;
    Node* curr = dummy_head -> next;
    while (idx < size && curr != node) {
      idx++;
      curr = curr -> next;
    }
    if (curr == dummy_head) {
      return -1;
    }
    return idx;
  }

  Node* search_node(Node* node) {
    int idx = 0;
    Node* curr = dummy_head -> next;
    while (idx < size && curr != node) {
      idx++;
      curr = curr -> next;
    }
    if (curr == dummy_head) {
      return NULL;
    }
    return curr;
  }

  Node* search_node(T val) {
    int idx = 0;
    Node* curr = dummy_head -> next;
    while (idx < size && curr -> val != val) {
      idx++;
      curr = curr -> next;
    }
    if (curr == dummy_head) {
      return NULL;
    }
    return curr;
  }

  void swap(Node* a, Node* b) {
    T temp = a -> val;
    a -> val = b -> val;
    b -> val = temp;
  }

  void insert(int idx, T val) {
    if (idx == size) {
      push_back(val);
      return;
    }
    if (!is_index_valid(idx)) {
      return;
    }
    if (idx == 0) {
      push_front(val);
      return;
    }
    Node* prev = index_node(idx-1);
    prev -> prev = prev -> prev -> prev;
    prev -> next -> prev = new Node(prev, val, prev -> next); 
    size++;
  }

  void update(int idx, T val) {
    if (!is_index_valid(idx)) {
      return;
    }
    Node* node = index_node(idx);
    node -> val = val;
  }

  void update(Node* node, T val) {
    node -> val = val;
  }

  void pop_back() {
    Node* tail = get_tail();
    dummy_head->next = tail->prev;
    tail->prev->next = dummy_head;
    delete tail;
    size--;
  }

  void delete_at_idx(int idx) {
    if (!is_index_valid(idx)) {
      return;
    }
    Node* node = index_node(idx);
    node -> prev -> next = node -> next;
    node -> next -> prev = node -> prev;
    delete node;
    size--;
  }

  void delete_node(Node* node) {
    node -> prev -> next = node -> next;
    node -> next -> prev = node -> prev;
    delete node;
    size--;
  }

  void duplicate(DLList* L) {
    Node* curr = dummy_head -> next;
    Node* next = L -> dummy_head;
    while(curr != dummy_head) {
      next -> next = new Node(next, curr -> val);
      next = next -> next;
      curr = curr -> next;
    }
    next -> next = L -> dummy_head; 
    L -> size = size;
  }

  static void duplicate(DLList<T>* from, DLList<T>* to) {
    Node* curr = from -> dummy_head -> next;
    Node* next = to -> dummy_head;
    while(curr != from->dummy_head) {
      next -> next = new Node(next, curr -> val);
      next = next -> next;
      curr = curr -> next;
    }
    next -> next = to -> dummy_head;
    to -> size = from -> size;
  }

  static DLList<T>* merge(const DLList<T>* L1, const DLList<T>* L2) {
    DLList<T>* new_list = new DLList();
    Node* curr = L1->dummy_head->next;
    for (int i = 0; i< L1->size; i++) {
      new_list->push_back(curr->val);
      curr = curr->next;
    }
    curr = L2->dummy_head->next;
    for (int i = 0; i< L2->size; i++) {
      new_list->push_back(curr->val);
      curr = curr->next;
    }
    return new_list;
  }

  
  void dispose(DLList*& L1, DLList*& L2, int idx) {
    if (idx == size) {
      L1 = new DLList();
      duplicate(L1);
      return;
    }
    if (!is_index_valid(idx)) {
      return;
    }
    if (idx == 0) {
      L2 = new DLList();
      duplicate(L2);
      return;
    }
    Node* node = index_node(idx-1);
    L2->dummy_head->next = node->next;
    get_tail() -> next = L2 -> dummy_head;
    L2 -> dummy_head -> prev = get_tail();
    L1 -> dummy_head -> next = dummy_head -> next;
    node -> prev -> next = L1 -> dummy_head;
    dummy_head -> prev = node -> prev;
    L1 -> size = idx;
    L2->size = size-idx;
  }

  T* extract() {
    T* arr = new T[size];
    Node* curr = dummy_head -> next;
    for (int i = 0 ; i< size; i++) {
      arr[i] = curr -> val;
      curr = curr -> next;
    }
    return arr;
  }

  void assign(T* arr) {
    Node* curr = dummy_head -> next;
    for (int i = 0 ; i< size; i++) {
      curr -> val = arr[i];
      curr = curr -> next;
    }
    delete[] arr;
  }

  bool le(T val1, T val2) {
    if (std::is_same<T, int>::value || std::is_same<T, double>::value || std::is_same<T, float>::value) {
      return val1 < val2;
    } else if (std::is_same<T, std::string>::value) {
      if (val1.length() == val2.length()) {
        for (int i = 0; i< val1.length(); i++) {
          if (val1[i] != val2[i]) {
            return val1[i] < val2[i];
          }
        }
        return true;
      } else {
        return val1.length() < val2.length();
      }
    } else {
      return true;
    }
  }

  void bubble_sort() {
    for (int i = 0 ; i< size; i++) {
      Node* curr = dummy_head -> next;
      int idx = 0;
      for (;idx<size-i-1; idx++) {
        if (!le(curr -> val, curr -> next -> val)) {
          swap(curr, curr -> next);
        }
        curr = curr -> next;
      }
    }
  }

  void quick_sort(int low, int high) {
    T* arr = extract();
    quick_sort_list(arr, low, high);
    assign(arr);
  }
  void quick_sort_list(T* arr, int low, int high) {
    if (low < high) {
      int pivot_index = partition(arr, low, high);
      quick_sort_list(arr, low, pivot_index-1);
      quick_sort_list(arr, pivot_index+1, high);
    }
  }
  int partition(T* arr, int low, int high) {
    T pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (le(arr[j], pivot)) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
  }

};
