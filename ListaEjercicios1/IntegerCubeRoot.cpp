#include<iostream>
#include<cassert>
int integerCubeRootHelper(int64_t n, int64_t left, int64_t right) {
    auto cube = [](int64_t n) -> int64_t {
        return n * n * n;
    };
    assert(n >= 1);
    assert(left <= right);
    assert(left >= 0);
    assert(right <= n);
    assert(cube(left) <= n);
    assert(cube(right) >= n);
    int64_t l = 0,r = 1<<21;
    while (l < r) {
        int64_t m = l + (r - l) / 2;
        if (m * m * m < n) l = m + 1;
        else r = m;
    }
    return l * l * l <= n ? l : l - 1;
}
int integerCubeRoot(int64_t n) {
    assert(n > 0);
    if (n == 1) return 1;
    if (n == 2) return 1;
    return integerCubeRootHelper(n, 0, n - 1);
}

int main () {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int64_t n[] = {1, 8, 27, 64, 125, 216, 343, 512, 729, 1000,1001,1330};
    int nSize = sizeof(n) / sizeof(n[0]);
    
    assert(integerCubeRoot(1) == 1);
    assert(integerCubeRoot(2) == 1);
    assert(integerCubeRoot(4) == 1);
    assert(integerCubeRoot(8) == 2);
    assert(integerCubeRoot(20) == 2);
    assert(integerCubeRoot(26) == 2);

    for (int i = 27; i < 64; i++) {
        assert(integerCubeRoot(i) == 3);
    }
    for (int i = 64; i < 125; i++) {
        assert(integerCubeRoot(i) == 4);
    }
    for (int i = 125; i < 216; i++) {
        assert(integerCubeRoot(i) == 5);
    }
    for (int i = 216; i < 343; i++) {
        assert(integerCubeRoot(i) == 6);
    }
    for (int i = 343; i < 512; i++) {
        assert(integerCubeRoot(i) == 7);
    }
    std::cout << "Felicidades, todas las pruebas han pasado =) \n";
    return 0;
}