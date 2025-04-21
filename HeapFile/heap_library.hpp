/*
Implementation of a Binary Heap Library, includes a Heap class and two derived classes MaxHeap and MinHeap.
*/
#ifndef HEAP_LIBRARY_HPP
#define HEAP_LIBRARY_HPP

#include<iostream>
#include<vector>

class Heap {
    protected:
        std::vector<int> heap;
        int parent(int index) {
            return (index - 1) /2;
        }
        int leftChild(int index) {
            return 2 * index + 1;
        }
        int rightChild(int index) {
            return 2 * index + 2;
        }
        virtual void heapifyUp(int index) = 0;
        virtual void heapifyDown(int index) = 0;
        Heap() {}
        Heap(std::vector<int> v) : heap(std::move(v)) {}
    public:
        
        virtual ~Heap() {}
        // Insert
        void insert(int value) {
            heap.emplace_back(value);
            heapifyUp(heap.size()-1);
        }
        template<typename T>
        void insert(T begin, T end) {   
            for (T it = begin; it != end; it++) {
                insert(*it);
            }
        }
        // Extract
        void extract() {
            if (heap.size() == 0) {
                std::cout << "Heap is empty\n";
                return;
            }
            heap[0] = heap.back();
            heap.pop_back();
            heapifyDown(0);
        }
        int getTop() {
            if (heap.size() == 0) {
                std::cout << "Heap is empty\n";
                return -1;
            }
            return heap[0];
        }
        // Print
        void print() {
            if (heap.size() == 0) {
                std::cout << "Heap is empty\n";
                return;
            }
            int n = heap.size();
            for (int i = 0; i < n; i++) {
                std::cout << heap[i] << " ";
            }
            std::cout << '\n';
        }
};
// clase MaxHeap que hereda de la clase Heap
class MaxHeap:public Heap {
    public:
        using Heap::Heap;
        MaxHeap() {};
        MaxHeap(const std::vector<int>& v) : Heap(v) {
            int n = heap.size();
            for (int i = n/2 - 1; i >= 0; i--) {
                heapifyDown(i);
            }
        }
        void heapifyUp(int index) override {
            while (index && heap[parent(index)] < heap[index]) {
                std::swap(heap[parent(index)],heap[index]);
                index = parent(index);
            }
        }
        void heapifyDown(int index) override {
            int largest = index;
            int left = leftChild(index);
            int right = rightChild(index);
            int n = heap.size();
            // first, we compare the left child with the parent
            if (left < n && heap[left] > heap[largest]) {
                largest = left;
            }
            // then, we compare the right child with the largest element
            if (right < n && heap[right] > heap[largest]) {
                largest = right;
            }
            if (largest != index) {
                std::swap(heap[index],heap[largest]);
                heapifyDown(largest);
            }
        }
};
// clase MinHeap que hereda de la clase Heap
class MinHeap:public Heap {
    public:
        using Heap::Heap;
        MinHeap() {};
        MinHeap(const std::vector<int>& v): Heap(v) {
            int n = heap.size();
            for (int i = n/2 - 1; i >= 0; i--) {
                heapifyDown(i);
            }
        }
        void heapifyUp(int index) override {
            while (index && heap[parent(index)] > heap[index]) {
                std::swap(heap[parent(index)],heap[index]);
                index = parent(index);
            }
        }
        void heapifyDown(int index) override {
            int smallest = index;
            int left = leftChild(index);
            int right = rightChild(index);
            int n = heap.size();
            if (left < n && heap[left] < heap[smallest]) {
                smallest = left;
            }
            if (right < n && heap[right] < heap[smallest]) {
                smallest = right;
            }
            if (smallest != index) {
                std::swap(heap[index],heap[smallest]);
                heapifyDown(smallest);
            }
        }
};

#endif