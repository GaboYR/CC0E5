#include<iostream>
const int maxn = 5e3 +5;
int A[maxn],B[maxn],C[maxn];
int main () {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    std::cin >> t;
    for (int _t = 0; _t < t; _t ++) {
        int n;  std::cin >> n;
        int minA = -1, minB = -1, minC = -1;
        for (int i = 0; i < n; i ++) {
            std::cin >> A[i] >> B[i] >> C[i];
            minA = std::max(minA, A[i]);
            minB = std::max(minB, B[i]);
            minC = std::max(minC, C[i]);
        }
        int ans = 0;
        int res = 0;
        for (int x = minA; x <= 10'000; x ++) {
            for (int y = minB; y <= 10'000 - x; y ++) {
                int z = std::min(10'000 - x - y, minC);
                if (z < 0) break;
                for (int i = 0; i < n; i ++) {
                    ans += ((x >= A[i]) && y >= B[i] && z >= C[i]);
                }
                res = std::max(res, ans);
                ans = 0;
                if (res == n) break;
            }
        }
        std::cout << "Caso #" << _t + 1 << ": " << res << "\n"; 
    }
}