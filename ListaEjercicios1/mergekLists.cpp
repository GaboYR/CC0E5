#include<iostream>
#include<vector>
#include<cassert>

#define len(x) (int)x.size()
std::vector<int> twoWayMerge(const std::vector<int> &x, const std::vector<int> &y) {
    int n = len(x);
    int m = len(y);
    std::vector<int> res(n + m);
    int i = 0, j = 0, k = 0;
    while (i < n && j < m) {
        if (x[i] < y[j]) {
            res[k++] = x[i++];
        } else {
            res[k++] = y[j++];
        }
    }
    while (i < n) {
        res[k++] = x[i++];
    }
    while (j < m) {
        res[k++] = y[j++];
    }
    return res;
}

std::vector<std::vector<int>> oneStepKWayMerge(const std::vector<std::vector<int>> &x) {
    int n = len(x);
    std::vector<std::vector<int>> res;
    while (n > 1) {
        res.push_back(twoWayMerge(x[n - 1],x[n - 2]));
        n -= 2;
    }
    if (n == 1) res.push_back(x[0]);
    return res;
}

std::vector<int> KWayMerge(const std::vector<std::vector<int>> &x) {
    int n = len(x);
    if (n <= 1) return x[0];
    auto res = oneStepKWayMerge(x);
    return KWayMerge(res);
}

int main () {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::vector<std::vector<int>> list1 = {
        {1,2,3},
        {4,5,7},
        {-2,0,6},
        {5}
    };
    
    auto res1 = KWayMerge(list1);
    assert((res1 == std::vector<int>{-2,0,1,2,3,4,5,5,6,7}) && "Prueba 1 fallida");

    std::vector<std::vector<int>> list2 = {
        {-2,4,5,8},
        {0,1,2},
        {-1,3,6,7}
    };
    auto res2 = KWayMerge(list2);
    
    assert((res2 == std::vector<int>{-2,-1,0,1,2,3,4,5,6,7,8}) && "Prueba 2 fallida");

    std::vector<std::vector<int>> lst3 = {
        {-1,1,2,3,4,5}
    };
    auto res3 = KWayMerge(lst3);

    assert((res3 == std::vector<int>{-1,1,2,3,4,5}) && "Prueba 3 fallida");    
    std::cout << "Todas las pruebas pasaron\n";
    
    return 0;
}