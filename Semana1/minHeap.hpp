#include<iostream>
#include<vector>

class MinHeap {
    private:
        std::vector<int> heap;
        int parent (int i) {
            return (i - 1) / 2;
        }
        int leftChild (int i) {
            return 2*i + 1;
        }
        int rightChild (int i) {
            return 2*i + 2;
        }
        void heapUp(int index) {
            while (index && heap[parent(index)] > heap[index]) {
                std::swap(heap[parent(index)],heap[index]);
                index = parent(index);
            }
        }
    public:
        void insert(int value) {
            heap.push_back(value);
            heapUp(heap.size()-1);
        }
        template<typename T>
        void insert(T begin, T end) {
            for (T it = begin; it != end; it++) {
                insert(*it);
            }
        }
        void print() {
            for (int i = 0; i < heap.size(); i++) {
                std::cout << heap[i] << " ";
            }
            std::cout << '\n';
        }
};
