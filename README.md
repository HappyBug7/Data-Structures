# 线性表实现

*线性表是一种数据结构, 其中元素按照顺序线性排列, 除了第一个以及最后一个元素以外, 每一个元素都有唯一的前者和后继*

## 存储结构

该线性表实现支持不同的存储结构, 并已内置`Array`和`LinkedList`两种存储结构 

若要接入其他存储结构需要实现以下接口:

```
/**
* @brief insert an element with certain value at a certain index
* @param idx the index where the element is inserted
* @param val the value
*/
void insert(int idx, T val)

/**
* @brief push an element at the end of the linear list
* @param val the value of the element
*/
void push_back(T val)

/**
* @brief push an element at the start of the linear list
* @param val the value of the element
*/
void push_front(T val) 

/**
* @brief remove the last element
*/
void pop_back()

/**
* @brief remove the element at the certain index
* @param idx the index of the element
*/
void delete_at_idx(int idx)

/**
* @brief update the value of the element at certain index
* @param idx the index of the element
* @param val the new value of the element
*/
void update(int idx, T val)

/**
* @brief return the index of the first elemet with same value, return -1 when there is no such element
* @param val the object value 
*/
int search(T val)

/**
* @brief return the value of the element at index
*/
T index(int idx)

/**
* @brief return whether the linear list is full or not
*/
bool is_full()

/**
* @brief return whether the linear list is empty or not
*/
bool is_empty()

/**
* @brief return the size of the list
*/
int get_size()

/**
* @brief return the previous element's value of the element at the certain index
* @param idx the index
*/
T prev(int idx)

/**
* @brief return the next element's value of the element at the certain index
* @param idx the index
*/
T next(int idx)

/**
* @brief print the whole list, and the form will differ between different storage structure
*/
void print_list()

/**
* @brief copy the whole list to another list
* @param L the receiver list
*/
void duplicate


/**
* @brief merge two list into one, and return
* @param L1 the first list
* @param L2 the second list 
*/
static StorageStructure<T>* merge(StorageStructure* L1, StorageStructure* L2)

/**
* @brief dispose the list into two lists, the first list end at index-1, the second begin at index
* @param L1 the first list receiver
* @param L2 the second list receiver
* @param idx the break index
*/
void dispose(StorageStructure<T>& L1, StorageStructure<T>& L2, int idx)

/**
* @brief bubble sort
*/
void bubble_sort()

/**
* @brief quick sort
*/
void quick_sort()
```

同时存储结构应自行维护`size`成员, 同时有可选的`capacity`成员

## 操作实现

该线性表实现了以下操作

- 插入
  - 在头部插入 `push_front(T val)`
  - 在尾部插入 `push_back(T val)`
  - 在`index`处插入 `insert(T val, int idx)`
- 删除
  - 在尾部删除 `pop_back()`
  - 在`index`处删除 `remove(int idx)`
- 更新
  - 更新`index`处的值 `update(T val, int idx)`
- 查询
  - 查询第一个值为`val`的元素的`index` `search(T val)`
  - 查询`index`处元素的值 `index(int idx)`
  - 查询`index`处元素的前者的值 `prev(int idx)`
  - 查询`index`处元素的后者的值 `next(int idx)`
- 状态检测
  - 是否为满 `is_full()`
  - 是否为空 `is_empty()`
  - 目前大小 `get_size()`
  - 打印整个线性表 `print_list()`
- 多表操作
  - 复制 `duplicate(const LinearList& L)` OR 重载了`=`运算符
  - 合并 `merge(LinearList<StorageStructure, T> L1, LinearList<StorageStructure, T> L2)` OR 重载了`+`运算符
  - 分裂 `dispose(LinearList<StorageStructure, T>& L1, LinearList<StorageStructure, T>& L2, int idx)` 
- 排序 `sort(std::string sort_function)`
  - 冒泡排序 `sort_function = "bubble"`
  - 快速排序 `sort_function = "quick"`

