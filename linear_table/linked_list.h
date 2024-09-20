#include <type_traits>

template<typename T>
class LinkedList {
private:
  class Node {
  public:
    Node* next;
    T val;
    Node() : val(T()), next(NULL) {}  
    Node(T val) : val(val), next(NULL) {}  
    Node(T val, Node* next) : val(val), next(next) {}  
  };
  Node* dummy_head;
  int size;

  bool is_index_valid(int idx) {
    return idx>=0 && idx<size;
  }
  
public:
  LinkedList() : dummy_head(new Node()), size(0) {}
  LinkedList(int capasity) : dummy_head(new Node()), size(0) {}
  // LinkedList(T val) : dummy_head(new Node()), size(1) {
  //   Node* first = new Node(val);
  //   dummy_head->next = first;
  // };

  int get_size() {
    return size;
  }

  Node* get_head() {
    return dummy_head -> next;
  } 

  Node* get_tail() {
    Node* tail = dummy_head;
    while (tail -> next != NULL) {
      tail = tail -> next;
    } 
    return tail;
  }

  T prev(int idx) {
    if (is_index_valid(idx-1)) {
      return T();
    }
    Node* node = index(idx-1);
    return node -> val;
  }

  T next(int idx) {
    if (is_index_valid(idx+1)) {
      return T();
    }
    Node* node = index(idx+1);
    return node -> val;
  }

  bool is_full() {
    return false;
  }

  bool is_empty() {
    return dummy_head -> next == NULL;
  }

  void push_back(T val) {
    Node* tail = get_tail();
    tail -> next = new Node(val);
    size++;
  }

  void push_front(T val) {
    Node* head = get_head();
    Node* new_head = new Node(val, head);
    dummy_head -> next = new_head;
    size++;
  }

  void print_list() {
    Node* curr = dummy_head -> next;
    while (curr != NULL) {
      if (curr -> next) {
        std::cout<<curr -> val<<"->";
      } else {
        std::cout<<curr -> val<<std::endl;
      }
      curr = curr -> next;
    }
  }

  void print_list(std::ostream& os) {
    Node* curr = dummy_head -> next;
    while (curr != NULL) {
      if (curr -> next) {
        os<<curr -> val<<"->";
      } else {
        os<<curr -> val;
      }
      curr = curr -> next;
    }
  }

  Node* index(int idx) {
    if (!is_index_valid(idx)) {
      return NULL;
    }
    int idx_curr = 0;
    Node* curr = dummy_head -> next;
    while (idx_curr < idx) {
      curr = curr -> next;
      idx_curr++;
    }
    return curr;
  }

  int search(T val) {
    int idx = 0;
    Node* curr = dummy_head -> next;
    while (idx < size && curr -> val != val) {
      idx++;
      curr = curr -> next;
    }
    if (curr == NULL) {
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
    if (curr == NULL) {
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
    if (curr == NULL) {
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
    if (curr == NULL) {
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
    Node* prev = index(idx-1);
    if (idx == size) {
      prev -> next = new Node(val);
    } else {
      Node* next = prev -> next -> next;
      prev -> next = new Node(val, next);
    }
  }

  void update(int idx, T val) {
    if (!is_index_valid(idx)) {
      return;
    }
    Node* node = index(idx);
    node -> val = val;
  }

  void update(Node* node, T val) {
    node -> val = val;
  }

  void pop_back() {
    if (size <= 0) {
      return;
    }
    if (size == 1) {
      delete dummy_head -> next;
      dummy_head -> next = NULL;
      size--;
      return;
    }
    Node* prev_tail = index(size - 2);
    delete prev_tail -> next;
    prev_tail -> next = NULL;
    size--;
  }

  void delete_at_idx(int idx) {
    if (!is_index_valid(idx)) {
      return;
    }
    if (idx == size - 1) {
      pop_back();
      return;
    }
    Node* prev = index(idx-1);
    Node* node = prev -> next;
    Node* next = node -> next;
    delete node;
    prev -> next = next;
    size--;
  }

  void delete_node(Node* node) {
    Node* prev = dummy_head;
    int idx = 0;
    while (idx < size && prev -> next != node) {
      prev = prev -> next;
      idx++;
    }
    if (idx == size) {
      return;
    }
    Node* next = node -> next;
    prev -> next = next;
    delete node;
    size--;
  }

  void duplicate(LinkedList* L) {
    Node* curr = dummy_head -> next;
    Node* next = L -> dummy_head;
    while(curr != NULL) {
      next -> next = new Node(curr -> val);
      next = next -> next;
      curr = curr -> next;
    }
    L -> size = size;
  }

  static LinkedList* merge(LinkedList* L1, LinkedList* L2) {
    int size_new = L1 -> size + L2 -> size;
    Node* L1_tail = L1 -> get_tail();
    L1_tail -> next = L2 -> dummy_head -> next;
    L1 -> size = size_new;
    return L1;
  }

  void dispose(LinkedList*& L1, LinkedList*& L2, int idx) {
    if (idx == size) {
      L1 = new LinkedList();
      duplicate(L1);
      return;
    }
    if (!is_index_valid(idx)) {
      return;
    }
    if (idx == 0) {
      L2 = new LinkedList();
      duplicate(L2);
      return;
    }
    Node* node = index(idx-1);
    L2->dummy_head->next = node->next;
    node -> next = NULL;
    L1 -> dummy_head -> next = dummy_head -> next;
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
