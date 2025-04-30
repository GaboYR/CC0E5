#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<assert.h>
#include<ostream>
#include "minHeap.hpp"
/*
    Estructura TopKHeap, consta de una arreglo ordenado A y un MinHeap.
    A contiene los k elementos menores del heap, y el MinHeap contiene los
    elementos restantes.
*/

class TopKHeap {
    private:
    int k;
    std::vector<int> A;
    MinHeap minHeap;
    public:
    TopKHeap(int k) {
        this->k = k;
        A.reserve(k);
        minHeap = MinHeap();
    }
    std::vector<int>& get_A() {
        return A;
    }
    MinHeap& get_minHeap() {
        return minHeap;
    }
    void set_A(std::vector<int> A) {
        this->A = A;
    }
    void set_minHeap(MinHeap minHeap) {
        this->minHeap = minHeap;
    }
    int size() {
        return A.size() + minHeap.size();
    }
    int get_jth_element(int j) {
        assert(j >= 0 && j < k);
        assert(j < size());
        return A[j];
    }
    void satisfies_assertions() {
        for (int i = 0; i < A.size() - 1;i ++) {
            assert((A[i] <= A[i + 1] && "El arreglo A no está ordenado"));
        }
        minHeap.satisfies_assertions();
        for (int i = 0; i < A.size(); i++) {
            assert(A[i] <= minHeap.min_element() && "El elemento mínimo del heap no es mayor que el máximo de A");
        }
    }
    // funciones de insercion
    void insert_into_A(int value) {
        std::cout << k << "\n";
        assert(A.size() < k);
        A.push_back(value);
        int j = A.size() - 1;
        while (j >= 1 && A[j] < A[j - 1]) {
            std::swap(A[j], A[j - 1]);
            j--;
        }
    }
    void insert(int value) {
        int sz = size();
        if (sz <= k) {
            insert_into_A(value);
            return;
        }
        else {
            if (value < A[A.size() - 1]) {
                minHeap.insert(A[A.size() - 1]);
                A[A.size() - 1] = value;
                int j = A.size() - 1;
                while (j >= 1 && A[j] < A[j - 1]) {
                    std::swap(A[j], A[j - 1]);
                    j--;
                }
                minHeap.bubble_up(minHeap.size());
            }
            else {
                minHeap.insert(value);
            }
        }
        return;
    }
    // Elimina un elemento del arreglo 
    void delete_top_k(int j) {
        int k = this->k;
        assert(size()> k);
        assert(j >= 0 && j < k);
        // Al eliminar un elemento de posicion j del arreglo A, quedara un espacio vacio
        // que sera cubierto por el elemento menor del heap 
        int root = minHeap.min_element();
        int sz = A.size() - 1;
        while (j < sz) {
            A[j] = A[j + 1];
            j++;
        }
        // Se elimina el último elemento del arreglo A
        A[sz] = root;
        // Se ordena el arreglo A
        int i = sz;
        while (i >= 1 && A[i] < A[i - 1]) {
            std::swap(A[i], A[i - 1]);
            i--;
        }
        // Se elimina el elemento menor del heap
        minHeap.delete_min();
    }
    friend std::ostream& operator<<(std::ostream& os, const TopKHeap& th) {
        os << "A = [";
        for (int i = 0; i < th.A.size(); i++) {
            os << th.A[i];
            if (i != th.A.size() - 1) {
                os << ", ";
            }
        }
        os << "]\n";
        os << "H = " << th.minHeap;
        return os;
    }
};