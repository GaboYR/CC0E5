#include<iostream>
#include<vector>
#include<cassert>
#define len(v) (int)v.size()
/*
    Encuentra el índice de cruce entre dos vectores x e y.
    El índice de cruce es el índice i tal que x[i] > y[i] y x[i+1] < y[i+1].
    Se asume que x[0] > y[0] y x[n-1] < y[n-1].
    Se asume que los vectores son estrictamente crecientes.
    Se asume que los vectores tienen la misma longitud.
    Se asume que el índice de cruce existe.

*/
/*
    Funcion findCrossoverIndexHelper
    Parametros:
    - x: vector de enteros
    - y: vector de enteros
    - left: indice izquierdo
    - right: indice derecho
*/
int findCrossoverIndexHelper (const std::vector<float> &x,const std::vector<float> &y,int left, int right) {
    assert(len(x) == len(y));
    assert(left >= 0);
    assert(left < right);
    assert(right < len(x));
    assert(x[left] > y[left]);
    assert(x[right] < y[right]);
    // Caso base
    if (left + 1 == right)  return left;

    // Caso recursivo
    int mid = left + (right - left) / 2;
    
    if (x[mid] >= y[mid]) {
        if (x[mid + 1] < y[mid + 1]) {
            return mid;
        }
        else {
            return findCrossoverIndexHelper(x, y, mid + 1, right);
        }    
    }
    return findCrossoverIndexHelper(x, y, left, mid);

}
int findCrossoverIndex (const std::vector<float> &x,const std::vector<float> &y) {
    assert(len(x) == len(y));
    assert(x[0] > y[0]);
    int n = len(x);
    assert(x[n-1] < y[n-1]);
    return findCrossoverIndexHelper(x,y,0,len(x)-1);
}

int main () {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::vector<float> x = {0,2,4,5,6,7,8,10};
    std::vector<float> y = {-2,0,2,4,7,8,10,12};

    int res = findCrossoverIndex(x,y);

    std::cout << res << "\n";

    // Caso de prueba #1
    int j1 = findCrossoverIndex({0, 1, 2, 3, 4, 5, 6, 7}, {-2, 0, 4, 5, 6, 7, 8, 9});
    std::cout << "j1 = " << j1 << "\n";
    assert((j1 == 1) && "Caso de prueba #1 fallido");
    // Caso de prueba #2
    int j2 = findCrossoverIndex({0, 1, 2, 3, 4, 5, 6, 7}, {-2, 0, 4, 4.2, 4.3, 4.5, 8, 9});
    std::cout << "j2 = " << j2 << "\n";
    assert((j2 == 1 || j2 == 5) && "Caso de prueba #2 fallido");
    // Caso de prueba #3
    int j3 = findCrossoverIndex({0, 1}, {-10, 10});
    std::cout << "j3 = " << j3 << "\n";
    assert((j3 == 0) && "Caso de prueba #3 fallido");
    // Caso de prueba #4
    int j4 = findCrossoverIndex({0, 1, 2, 3}, {-10, -9, -8, 5});
    std::cout << "j4 = " << j4 << "\n";
    assert((j4 == 2) && "Caso de prueba #4 fallido");
    std::cout << "¡Felicidades: Todos los tests pasaron! (10 puntos)\n";
    
    return 0;
}