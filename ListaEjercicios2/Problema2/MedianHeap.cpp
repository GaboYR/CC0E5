#include<iostream>
#include<assert.h>
#include<cmath>
#include "MinHeap.hpp"
#include "MaxHeap.hpp"

class MedianHeap{
    private:
        MinHeap minHeap;
        MaxHeap maxHeap;
    public:
        MedianHeap() {};
        int size() {
            return minHeap.size() + maxHeap.size();
        }
        void insert(int value) {
            /*
            // Esta estructura consta de 2 partes
            Para el caclulo de la mediana , necesitamos los elementos posicionados a la mitad del arreglo,
            esto puede ser logrado con el uso de 2 heaps, un max heap que almacene los menores elemmentos, y
            un min heap que almacene los mayores elementos.
            La mediana seria el promedio de los nodos raiz de ambos heaps, o el nodo raiz del max heap si el tama;o total es impar.
            */
            // Si el maxHeap esta vacio, insertamos sin problema:
            if (maxHeap.size() == minHeap.size()) {
                if(maxHeap.size() == 0) {
                    maxHeap.insert(value);
                }
                else {
                    if (value > minHeap.min_element()) {
                        auto tmp = minHeap.min_element();
                        minHeap.delete_min();
                        maxHeap.insert(tmp);
                        minHeap.insert(value);
                    }
                    // 2. Si el valor a insertar sea mayor al valor raiz del maxheap
                    else {
                        maxHeap.insert(value);
                    }
                }
                // Ahora tenemos 2 posibilidades
                // 1. El valor a insertar sea menor al valor raiz del maxheap
                // En este caso, extraemos el valor de la raiz e insertamos en el minheap
            }
            else {
                if (minHeap.size() == 0) {
                    minHeap.insert(value);
                }
                else {
                    if (value < maxHeap.max_element()) {
                        auto tmp = maxHeap.max_element();
                        maxHeap.delete_max();
                        maxHeap.insert(value);
                        minHeap.insert(tmp);
                    }
                    else {
                        minHeap.insert(value);
                    }
                }
            }
        }
        double get_median() {
            if (minHeap.size() == maxHeap.size()) {
                return (minHeap.min_element() + maxHeap.max_element()) / 2;
            }
            else return maxHeap.max_element();
        }
        void print() {
            maxHeap.print();
            minHeap.print();
        }
};
int main () {
    MedianHeap median;
    // 'Insertando 1, 5, 2, 4, 18, -4, 7, 9'
    median.insert(1);
    median.print();
    std::cout << median.get_median() << '\n';
    assert(median.get_median() == 1);
    median.insert(5);
    median.print();
    std::cout << median.get_median() << '\n';
    assert(median.get_median() == 3);
    median.insert(2);
    median.print();
    std::cout << median.get_median() << '\n';
    assert(median.get_median() == 2);
    median.insert(4);
    median.print();
    std::cout << median.get_median() << '\n';
    assert(median.get_median() == 3);
    median.insert(18);
    median.print();
    std::cout << median.get_median() << '\n';
    assert(median.get_median() == 4);
    median.insert(-4);
    median.print();
    std::cout << median.get_median() << '\n';
    assert(median.get_median() == 3);
    median.insert(7);
    median.print();
    std::cout << median.get_median() << '\n';
    assert(median.get_median() == 4);
    median.insert(9);
    median.print();
    std::cout << median.get_median() << '\n';
    assert((fabs(median.get_median() - 4.5) <= 1e-9));
    std::cout << "Todas las pruebas pasaron\n"; 
}