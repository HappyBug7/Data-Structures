#include <type_traits>

template<typename T>
class Array {
private:
  int capasity;
  int size;
  T* arr;
  bool is_index_valid(int idx) {
    return idx>=0 && idx<size;
  }

public:
  Array(int capasity) {
    arr = new T[capasity];
    this -> capasity = capasity;
    size = 0;
  }

  int get_size() {
    return size;
  }

  bool is_full() {
    return size >= capasity;
  }

  bool is_empty() {
    return size == 0;
  }

  void push_back(T val) {
    if (is_full()) {
      return;
    }
    arr[size] = val;
    size++;
  }

  void push_front(T val) {
    if (is_full()) {
      return;
    }
    T temp = T();
    T prev = val;
    for (int i = 0; i< size; i++) {
      temp = arr[i];
      arr[i] = prev;
      prev = temp;
    }
    arr[size] = prev;
    size++;
  }

  void print_list() {
    if (size == 0) {
      std::cout << "List is empty" << std::endl;
      return;
    }

    for (int i = 0; i < size - 1; i++) {
      std::cout << arr[i] << ",";
    }
    std::cout << arr[size - 1] << std::endl;
  }

  void print_list(std::ostream& os) {
    if (size == 0) {
      os << "List is empty";
      return;
    }

    for (int i = 0; i < size - 1; i++) {
      os << arr[i] << ",";
    }
    os << arr[size - 1];
  }

  T index(int idx) {
    if (!is_index_valid(idx)) {
      return -1;
    }
    return arr[idx];
  }

  int search(T val) {
    for (int i = 0; i< size; i++) {
      if (arr[i] == val) {
        return i;
      }
    }
    return -1;
  }

  void swap(int idxa, int idxb) {
    if (!(is_index_valid(idxa)&&is_index_valid(idxb))) {
      return;
    }
    T temp = arr[idxa];
    arr[idxa] = arr[idxb];
    arr[idxb] = temp;
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
    if (is_full()) {
      return;
    }
    T prev = val;
    T temp = T(); 
    for (int i = idx; i < size; i++) {
      temp = arr[i];
      arr[i] = prev;
      prev = arr[i];
    }
    arr[size] = prev;
    size++;
  }

  void update(int idx, T val) {
    if (!is_index_valid(idx)) {
      return;
    }
    arr[idx] = val;
  }

  void pop_back() {
    if (!size) {
      return;
    }
    size--;
  }

  void delete_at_idx(int idx) {
    if (!is_index_valid(idx)) {
      return;
    }
    for (int i = idx; i < size-1; i++) {
      arr[i] = arr[i+1];
    }
    size--;
  }

  T prev(int idx) {
    if (is_index_valid(idx-1)) {
      return T();
    }
    return arr[idx-1];
  }

  T next(int idx) {
    if (is_index_valid(idx+1)) {
      return T();
    }
    return arr[idx+1];
  }

  void duplicate(Array* L) {
    int min = size;
    if (size > L -> capasity) {
      min = L -> capasity;
    }
    for (int i = 0; i< min; i++) {
      L -> arr[i] = arr[i];
    }
    L -> size = size;
  }
  
  static Array<T>* merge(Array* L1, Array* L2) {
    int capasity_new = L1 -> capasity + L2 -> capasity;
    int size_new = L1 -> size + L2 -> size;
    Array<T>* L_new = new Array<T>(capasity_new);
    for (int i = 0; i< L1 -> size; i++) {
      L_new -> arr[i] = L1 -> arr[i];
    }
    for (int i = 0; i< L2 -> size; i++) {
      L_new -> arr[i + L1 -> size] = L2 -> arr[i];
    }
    L_new -> size = size_new;
    return L_new;
  }

  void dispose(Array*& L1, Array*& L2, int idx) {
    if (idx == size) {
      L1 = new Array(capasity);
      duplicate(L1);
      return;
    }
    if (!is_index_valid(idx)) {
      return;
    }
    if (idx == 0) {
      L2 = new Array(capasity);
      duplicate(L2);
      return;
    }
    L1 = new Array(capasity);
    L2 = new Array(capasity);
    for (int i = 0 ; i< idx; i++) {
      L1->arr[i] = arr[i];
    }
    for (int i = idx; i< size; i++) {
      L2->arr[i-idx] = arr[i];
    }
    L1->size = idx;
    L2->size = size-idx;
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
      for (int j = 0; j < size-i-1; j++) {
        if (!le(arr[j], arr[j+1])) {
          swap(j, j+1);
        }
      }
    }
  }

  void quick_sort(int low, int high) {
    if (low < high) {
      int pivot_index = partition(low, high);
      quick_sort(low, pivot_index-1);
      quick_sort(pivot_index+1, high);
    }
  }
  int partition(int low, int high) {
    T pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (le(arr[j], pivot)) {
            i++;
            swap(i, j);
        }
    }
    swap(i + 1, high);
    return i + 1;
  }
};
