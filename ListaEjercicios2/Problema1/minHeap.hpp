#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<assert.h>
#include<ostream>
/*
    Clase MinHeap modificada, donde se empieza del indice 1,
    indice 0 se deja vacio.
*/
class MinHeap {
    private:
    std::vector<int> heap;
    public:
    MinHeap() {
        heap.push_back(-100000000); // Se deja el indice 0 vacio
    }
    int size() {
        return heap.size() - 1; // Se resta 1 por el indice 0
    }
    std::vector<int> repr() {
        std::vector<int> v;
        for (int i = 1; i < heap.size(); i++) {
            v.push_back(heap[i]);
        }
        return v;
    }
    void satisfies_assertions() {
        for (int i = 2; i < heap.size(); i++) {
            assert(heap[i] >= heap[i / 2]);
        }
    }
    int min_element() {
        return heap[1];
    }
    void bubble_up(int index) {
        assert(index >= 1);
        if (index == 1) return;
        while (index > 1 && heap[index] < heap[index / 2]) {
            std::swap(heap[index], heap[index / 2]);
            index /= 2;
        }
    }
    void bubble_down(int index) {
        assert(index >= 1 && index < heap.size());
        int min_child_index = index;
        int left_child_index = index * 2;
        int right_child_index = index * 2 + 1;
        if (left_child_index < heap.size() && heap[left_child_index] < heap[min_child_index]) {
            min_child_index = left_child_index;
        }
        if (right_child_index < heap.size() && heap[right_child_index] < heap[min_child_index]) {
            min_child_index = right_child_index;
        }
        if (min_child_index != index) {
            std::swap(heap[index], heap[min_child_index]);
            bubble_down(min_child_index);
        }
    }
    void insert(int value) {
        heap.push_back(value);
        bubble_up(heap.size() - 1);
    }
    void delete_min() {
        if (heap.size() == 0) {
            std::cerr << "El heap esta vacio\n";
            return;
        }
        heap[1] = heap.back();
        heap.pop_back();
        if (heap.size() > 1) {
            bubble_down(1);
        }
    }
    friend std::ostream& operator<<(std::ostream& os, const MinHeap& h) {
        os << "[";
        for (int i = 1; i < h.heap.size(); i++) {
            os << h.heap[i];
            if (i < h.heap.size() - 1) {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }
};