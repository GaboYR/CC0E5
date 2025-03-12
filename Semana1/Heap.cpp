#include<iostream>
#include<vector>
#include<algorithm>
#include "heap_library.hpp"
int main() {
    MaxHeap maxh;
    std::vector<int> v = {16,14,10,8,7,9,3,2,4,1};
    maxh.insert(v.begin(),v.end());
    maxh.print();
    

    MinHeap minh;
    minh.insert(v.begin(),v.end());
    minh.print();

    return 0;
}
