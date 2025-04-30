#pragma once

#include<iostream>
#include<vector>
// Operaciones, bubble up y down

class MinHeap 
{
private:    
    std::vector<float> heap;
public:
    MinHeap() {};
    int size() {
        return heap.size();
    }
    float min_element() {
        return heap[0];
    }
    void insert(float value) {
        heap.push_back(value);
        bubble_up(heap.size() - 1);
    }
    void bubble_up(int index) {
        if (index == 0) return;
        while (index > 0 && heap[index] < heap[(index - 1) / 2]) {
            std::swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }
    void bubble_down(int index) {
        int min_child_index = index;
        int left_child_index = index * 2 + 1;
        int right_child_index = index * 2 + 2;
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
    void delete_min() {
        if (heap.size() == 0) {
            std::cerr << "El heap esta vacio\n";
            return;
        }
        heap[0] = heap.back();
        heap.pop_back();
        bubble_down(0);
    }
    void print() {
        std::cout << "minHeap: [";
        for (auto &e: heap) {
            std::cout << e << " ";
        }
        std::cout << "]\n";
    }
};