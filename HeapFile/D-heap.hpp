/*
Implementation of a d-heap structure
This structure is a generalization of the binary heap, where each node has d children instead of 2.
*/
#ifndef D_HEAP_HPP
#define D_HEAP_HPP
#include<iostream>
#include<vector>
#include<cassert>
#include<algorithm>
#include<cmath>
#include<any>
/*
    min D-heap
    The element that is smaller than its children is at the top of the heap.
    In this case, we are going to implement a heap whose elements has the following way:
    (element, priority)
    Where:
    - element: contain any data type
    - priority: is a number that represents the priority of the element (e.g 1,0.3)
    The smaller the number, the higher the priority.
    Methods of d-heap:
    - insert: insert an element in the heap(the element is added at the end of the heap and then it is moved to its correct position)
    - remove: remove the element with the highest priority (the element at the top of the heap is removed and then the last element is moved to the top and then it is moved to its correct position)
    - getMin: get the element with the highest priority (the element at the top of the heap)
    - decreaseKey: decrease the priority of an element (the element is moved to its correct position)
    - isEmpty: check if the heap is empty
    - len: get the len of the heap
    - clear: clear the heap
    - print: print the heap
    - buildHeap: build the heap from an array of elements
*/
class DHeap {
    private:
        // Array of elements: pair <element, priority>
        std::vector<std::pair<std::any, float>> heap;
        // Branch factor
        int d;
    public:
    // List of methods    
    // Constructor
    DHeap(int d);
    // Destructor
    ~DHeap();
    // Basic methods
    // isEmpty: check if the heap is empty
    bool isEmpty();
    // len: get the len of the heap
    int len();
    // MEthod  for get the i-th child
    int firstChild(int index);
    std::vector<int> allChild(int index);
    int highPriority(int index);
    // Get the parent
    int parent(int index);
    // bubbleUp: move the element at index to its correct position
    void bubbleUp(int index);
    // pushDown: move the element at index to its correct position
    void pushDown(int index);
    // Insertion methods
    void insert(std::any element, float priority);
    // Method for view the element with the highest priority
    // top : get the element with the highest priority and remove it from the heap
    // peek : get the element with the highest priority without removing it from the heap
    void top();
    std::pair<std::any, float> peek();
    // Deletion methods
    // extract: remove the root of the heap, and it will be replaced by the last element of the heap
    void extractRoot();

    void print(int index, int depth);
};
// Implementation of the methods
// Constructor
DHeap::DHeap(int d) {
    assert(d > 1);
    this->d = d;
}
// Destructor
DHeap::~DHeap() {
    heap.clear();
}
// isEmpty: check if the heap is empty
bool DHeap::isEmpty() {
    return heap.empty();
}
// len: get the len of the heap
int DHeap::len() {
    return heap.size();
}
int DHeap::parent(int index) {
    return (index - 1) /d;
}
int DHeap::firstChild(int index) {
    return d * index + 1;
}
std::vector<int> DHeap::allChild(int index) {
    std::vector<int> res = {};
    for (int i = 1; i <= d; i ++) {
        if (d * index + i < len()){
            res.push_back(d*index + i);
        }
    }
    return res;
}
// Before bubbleUp implementation, we need to implement insert method
// Insert method
void DHeap::insert(std::any element, float priority) {
    heap.push_back({element,priority});
    bubbleUp(len() - 1);
}
void DHeap::extractRoot() {
    if (len() == 0) {
        std::cout << "Heap is empty";
        return;
    }
    heap[0] = heap.back();
    heap.pop_back();
    pushDown(0);
}
void DHeap::bubbleUp(int index) {
    while (index >= 0 && heap[parent(index)].second > heap[index].second) {
        std::swap(heap[parent(index)],heap[index]);
        index = parent(index);
    }
}
int DHeap::highPriority(int index) {
    auto childs = allChild(index);
    if (childs.empty()) {
        return -1;
    }
    auto res = childs[0];
    for (auto c:childs) {
        if (heap[res].second > heap[c].second) {
            res = c;
        }
    }
    return res;
}
void DHeap::pushDown(int index) {
    int smallest = index;
    auto best = highPriority(index);
    if (best < len() && best != -1 && heap[best].second < heap[smallest].second) {
        smallest = best;
    }
    if (smallest != index) {
        std::swap(heap[index],heap[smallest]);
        pushDown(smallest);
    }
}
void DHeap::top() {
    if (!isEmpty()) {
        auto e = peek();
        std::cout << "Top element priority: " << e.second << "\n";
    } 
    else {
        std::cout << "Heap is empty\n";
    }
}
std::pair<std::any, float> DHeap::peek() {
    if (isEmpty()) {
        throw std::runtime_error("Heap is empty");
    }
    return heap[0];
}
void DHeap::print(int index = 0, int depth = 0) {
    if (index >= len()) return;

    // Indentación por nivel (profundidad)
    for (int i = 0; i < depth; ++i) std::cout << "  ";

    std::cout << "|--(" << std::any_cast<std::string>(heap[index].first);

    if (heap[index].first.type() == typeid(std::string)) {
        std::cout << ",  " << heap[index].second << ")"; 
    }

    std::cout << "\n";

    for (int i = 1; i <= d; ++i) {
        int child = d * index + i;
        print(child, depth + 1);
    }
}


#endif