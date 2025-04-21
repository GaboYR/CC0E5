#include<iostream>
#include "D-heap.hpp"

int main() {
    DHeap heap(3);  // Ternary heap (cada nodo tiene hasta 3 hijos)

    heap.insert(std::string("A"), 5);
    heap.insert(std::string("B"), 3);
    heap.insert(std::string("C"), 8);
    heap.insert(std::string("D"), 2);
    heap.insert(std::string("E"), 4);
    heap.insert(std::string("F"), 1);
    heap.insert(std::string("G"), 6);

    std::cout << "D-Heap visualizado:\n";
    heap.print();

    return 0;
}
