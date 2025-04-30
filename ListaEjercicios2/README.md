# Lista 2

## Ejercicio 1(Estructura de datos para los k-elementos menores)

### 1. Diseño de insercion

Ahora explicaremos un pseudocodigo sobre el funcionamiento del algoritmo

```txt
INSERTAR(valor):
    // Si el tamaño del arreglo A es menor que k, se inserta el valor en A
    // y se reordena A para mantener el orden
    SI len(TopKHeap) < k:
        TopKHeap.A.insertar(valor) // Considerando que A tiene su metodo 
        insertar
        TopKHeap.A.reordenar()
    // Ahora, si el tamaño de A es k, debemos usar el heap, por lo que realizaremos comparaciones
    SINO:
        // Si el valor a insertar es menor que el último elemento de A,pasamos el ultimo elemento de A al heap 
        /// y el valor a insertar se inserta en A, finalmente se reordena A para mantener el orden
        SI valor < TopKHeap.A[len(TopKHeap.A) - 1]:
            tmp = TopKHeap.A[len(TopKHeap.A) - 1]
            TopKHeap.A[len(TopKHeap.A) - 1] = valor
            TopKHeap.A.reordenar() // Considerando que A tiene su metodo reordenar
        TopKHeap.H.insertar(tmp) // Considerando que H tiene su metodo insertar
        // De lo contrario,lo insertamos directamente en el heap
        SINO:
            TopKHeap.H.insertar(valor) // Considerando que H tiene su metodo insertar
```

¿Cuál es la complejidad de la operación de inserción en el peor caso en términos de $n$ y $k$?

Sabemos que $n\gt k$, entonces nuestro arreglo $A$ esta lleno.

El peor caso ocurre cuando el valor a insertar cuando el valor a insertar sea menor al ultimo elemento de $A$(incluso que el menor elemento de $A$), lo cual al reordenar ira recorriendo el arreglo en complejidad $O(k)$, y al insertar el elemento en el heap, la complejidad es $O(log(n - k))$, por lo que la complejidad total es: $$O(k + log(n - k))$$.

### 2. Diseño de eliminacion

Ahora explicaremos un pseudocodigo sobre el funcionamiento del algoritmo $(n \gt k)$

```txt
// Eliminamos el valor del valor de indice j del arreglo A (j < k)
ELIMINAR(j):
    // REalizamos un barrido desde el indice j hasta el final del arreglo A
    // y movemos los elementos hacia la izquierda
    MIENTRAS j < k - 1:
        TopKHeap.A[j] = TopKHeap.A[j + 1]
        j = j + 1
    // El ultimo elemento de A toma el valor de la raiz del heap
    TopKHeap.A[k - 1] = TopKHeap.H[1]
    // Eliminamos la raiz del heap
    delete(H,1)
```

¿Cuál es la complejidad de la operación de eliminacion en el peor caso en términos de $n$ y $k$?

El peor caso se da cuando eliminamos el primer elemento de $A$, lo cual implica recorrer todo el arreglo $A$ para mover los elementos hacia la izquierda, lo cual tiene una complejidad de $O(k)$, y al eliminar la raiz del heap, la complejidad es $O(log(n - k))$, por lo que la complejidad total es: $$O(k + log(n - k))$$.

### 3.Programacion de la solucion

El codigo ha sido migrado a C++, se creo un archivo `minHeap.hpp` que contiene la clase `MinHeap`, la cual contiene los metodos necesarios para el funcionamiento del algoritmo, y un archivo `TopKHeap.hpp` que contiene la clase `TopKHeap`, la cual incluye al arreglo `A` y al heap `H`, y los metodos de insercion y eliminacion.

Clase `minHeap.hpp`:

```cpp
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
```

Clase `TopKHeap.hpp`:

```cpp
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
```

Clase `main.cpp`:

```cpp
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
```

Veamos la ejecucion del programa:

![ejecucion](/ListaEjercicios2/images/Ejecucion.png)

## Ejercicio 2 (Estructura de heap para mantener/extrayer la mediana)

El problema trata de calcular la mediana mediante el uso de dos heaps, uno max y otro min, el max heap contiene los elementos menores o iguales a la mediana, y el min heap contiene los elementos mayores a la mediana. La mediana se encuentra en la raiz del max heap.
Y ademas, la raiz del maxHeap guardara la mediana, y la raiz del minHeap guardara el siguiente elemento mayor a la mediana.

### 1.Diseño de insercion

Ahora explicaremos un pseudocodigo sobre el funcionamiento del algoritmo

```txt
INSERTAR(valor):
    // Tenemos dos situaciones principales:
    // 1. Insertar en el maxHeap
    // 2. Insertar en el minHeap 
    // Si ambos heaps tienen el mismo tamaño, se inserta en el maxHeap
    SI(len(maxHeap) == len(minHeap)):
        // Si el maxHeap esta vacio, se inserta el valor en el maxHeap
        SI(len(maxHeap) == 0):
            maxHeap.insertar(valor)
        // En otro caso, si el valor a insertar es mayor que la raiz del minHeap, guardamos el valor de esta raiz, y hacemos 2 pasos
        // 1. Insertamos el valor raiz del minHeap en el maxHeap
        // 2. Removemos la raiz del minHeap e insertamos el valor
        SINO:
            SI(valor > minHeap.min_element()):
                tmp = minHeap.min_element()
                minHeap.delete_min()
                maxHeap.insertar(tmp)
                minHeap.insertar(valor)
            // En otro caso, se inserta el valor en el maxHeap
            SINO:
                maxHeap.insertar(valor)
    
    // De lo contrario, se inserta en el minHeap
    SINO:
        // Si el minHeap esta vacio, se inserta el valor en el minHeap
        SI(len(minHeap) == 0):
            minHeap.insertar(valor)
        // En otro caso, si el valor a insertar es menor al valor de la raiz del maxHeap, debemos insertar este valor en el maxHeap, y mover la raiz al minHeap
        SINO:
            SI(valor < maxHeap.min_element()):
                tmp = maxHeap.min_element()
                maxHeap.delete_min()
                minHeap.insertar(tmp)
                maxHeap.insertar(valor)
            // En otro caso, se inserta el valor en el minHeap
            SINO:
                minHeap.insertar(valor)
```

### 2.Algoritmo para encontrar la mediana

Este paso es sencillo, sabemos que la mediana es la raiz del maxHeap, por lo que simplemente retornamos el valor de la raiz del maxHeap en el caso de que **el tamaño del maxHeap sea mayor al del minHeap por una unidad**, y en el caso de que ambos heaps tengan el mismo tamaño, la mediana sera el promedio de las raices de ambos heaps.

La complejidad de este algoritmo es $O(1)$, ya que solo se accede a la raiz de ambos heaps, y no se realizan operaciones adicionales.

### 3. Programacion de la solucion

Hemos migrado el codigo a C++, omitiremos la implementacion del `minHeap` y del `maxHeap`,ya que es muy similar al del ejercicio 1, y solo cambia el orden de los elementos, por lo que solo mostraremos la clase `MedianHeap.hpp`, la cual contiene la clase `MedianHeap`, que contiene los heaps y los metodos de insercion y de obtencion de la mediana.

La clase `MedianHeap.hpp` es la siguiente, contiene 2 heaps, uno max y otro min, y los metodos de insercion y de obtencion de la mediana.

```cpp
#include<iostream>
#include<assert.h>
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
    std::cout << "Todas las pruebas pasaron"; 
}
```

Ejecucion del codigo:

![ejecucion](/ListaEjercicios2/images/Ejecucion2.png)
El resultado es el esperado, y se han pasado todas las pruebas.

### Observacion

En el ultimo problema, se modifico :

```cpp
assert(median.get_median() == 4.5);
// Por
(fabs(median.get_median() - 4.5) <= 1e-9) // 1e-9 = 10^-9
```

Debido a que el resultado de la mediana es un double, y al hacer la comparacion con un entero, puede dar error debido a la precision de los numeros decimales, por lo que se hace una comparacion entre el valor absoluto de la diferencia entre ambos numeros y un epsilon, que en este caso es $10^{-9}$.
