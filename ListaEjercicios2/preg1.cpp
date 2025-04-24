#include<iostream>
#include "minHeap.hpp"
#include "TopKHeap.hpp"
int main() {
    // Parte 1, implementar el heap
    // y probarlo con los siguientes casos de prueba.
    MinHeap h;
    std::cout << "Insertando: 5, 2, 4, -1 y 7 en ese orden.\n";
    h.insert(5);
    assert(h.min_element() == 5);
    h.insert(2);
    assert(h.min_element() == 2);
    h.insert(4);
    assert(h.min_element() == 2);
    h.insert(-1);
    assert(h.min_element() == -1);
    h.insert(7);
    assert(h.min_element() == -1);
    h.satisfies_assertions();
    std::cout << "\t Heap = ";
    std::cout << h << "\n";
    h.delete_min();
    std::cout << "\t Heap = ";
    std::cout << h << "\n";
    assert((h.min_element() == 2 && "El elemento mínimo del heap ya no es 2"));
    h.delete_min();
    std::cout << "\t Heap = ";
    std::cout << h << "\n";
    assert(h.min_element() == 4);
    h.delete_min();
    std::cout << "\t Heap = ";
    std::cout << h << "\n";
    assert(h.min_element() == 5);
    h.delete_min();
    std::cout << "\t Heap = ";
    std::cout << h << "\n";
    assert(h.min_element() == 7);
    h.delete_min();
    std::cout << "\t Heap = ";
    std::cout << h << "\n";
    std::cout << "All tests passed: 10 points!\n";

    // Parte 2
    // Implementar el TopKHeaps y probarlo con los siguientes casos de prueba.
    TopKHeap th(5);
    th.get_A() = {-10, -9, -8, -4, 0};
    // Forzar el heap con estos elementos
    std::vector<int> heap_elements = {1, 4, 5, 6, 15, 22, 31, 7};
    for (int i: heap_elements) {
        th.get_minHeap().insert(i);
    }
    std::cout << "Estructura de datos inicial: \n";
    std::cout << th << "\n";

    std::cout << "Test 1: Insertando el elemento -2\n";
    th.insert(-2);
    std::cout << th << "\n";
    assert(th.get_minHeap().min_element() == 0 && "El elemento mínimo del heap ya no es 0");
    th.satisfies_assertions();
    
    std::cout << "Test 2: Insertando el elemento -11\n";
    th.insert(-11);
    std::cout << th << "\n";
    assert(th.get_minHeap().min_element() == -2 && "El elemento mínimo del heap ya no es -2");
    th.satisfies_assertions();
    
    std::cout << "Test 3: delete_top_k(3)\n";
    th.delete_top_k(3);
    std::cout << th << "\n";
    th.satisfies_assertions();
    assert(th.get_minHeap().min_element() == 0 && "El elemento mínimo del heap ya no es 0");
    th.satisfies_assertions();
    
    std::cout << "Test 4: delete_top_k(4)\n";
    th.delete_top_k(4);
    std::cout << th << "\n";
    th.satisfies_assertions();

    std::cout << "Test 5: delete_top_k(0)\n";
    th.delete_top_k(0);
    std::cout << th << "\n";
    th.satisfies_assertions();
    
    std::cout << "Test 6: delete_top_k(1)\n";
    th.delete_top_k(1);
    std::cout << th << "\n";
    th.satisfies_assertions();

    std::cout << "Pasamos todas las pruebas\n";
    return 0;
}