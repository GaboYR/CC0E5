#include<iostream>
#include<vector>
void insertionSort(std::vector<int> &arr) {
    int sz = (int)arr.size();
    for (int i = 0; i < sz; i ++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j --;
        }
        arr[j + 1] = key;
    }
}
int main () {
    std::vector<int> arr = {1,2,7,4,5,6,3,8,9};
    insertionSort(arr);
    for (int i = 0; i < (int)arr.size(); i ++) {
        std::cout << arr[i] << " \n"[i == (int)arr.size() - 1];
    }
    return 0;
}