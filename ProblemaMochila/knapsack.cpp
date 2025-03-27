#include<iostream>
#include<vector>
// Problema de la mochila con numero ilimitado de objetos
// W: Peso maximo que puede soportar la mochila
// w: Vector de pesos de los objetos
// v: Vector de valores de los objetos
double knapsackIlimited(int W,const std::vector<int> &w,const std::vector<double> &v) {
    int n = (int)w.size();
    std::vector<double> dp(W+1,0.0);
    for (int i = 0; i <= W; i ++) {
        for (int j = 0; j < n; j ++) {
            if (w[j] <= i) {
                dp[i] = std::max(dp[i],dp[i-w[j]]+v[j]);
                //std::cout << "dp[" << i << "] = " << dp[i] << "\n";
            }
        }
    }
    return dp[W];
}
// Problema pde la mochila para 0-1 objeto
double knapsack01(int W,const std::vector<int> &w,const std::vector<double> v) {
    int n = (int)w.size();
    std::vector<std::vector<double>> dp(n+1,std::vector<double>(W+1,0.0));
    for (int i = 1; i <= n; i ++) {
        for (int j = 0; j <= W; j ++) {
            dp[i][j] = dp[i-1][j];
            if (w[i-1] <= j) {
                dp[i][j] = std::max(dp[i][j],dp[i-1][j-w[i-1]]+v[i-1]);
            }
        }
    }
    // Recuperar la solucion encontrada
    int tmpW = W;
    std::vector<int> sol(n,0);
    for (int i = n; i > 0; i --) {
        if (dp[i][tmpW] != dp[i-1][tmpW]) {
            sol[i-1] = 1;
            tmpW -= w[i-1];
        }
    }
    double check = 0;
    for (int i = 0; i < n; i ++) {
        std::cout << "\nSe tomo el item " << i+1 << " con peso "<< w[i] << " y valor " << v[i] << " : " << sol[i] << "\n";
        check += sol[i]*v[i];
        std::cout << "Peso hasta el momento : " << check << "\n";
    }
    return dp[n][W];
}
int main () {
    int W[] = {50,100,200};
    std::vector<int> pesos = {1,5,20,35,80};
    std::vector<double> valores = {15,14.5,19.2,19.8,195.2};
    
    for (int i = 0; i < 3; i ++) {
        std::cout << "Para W = " << W[i] << " la respuesta es: " << knapsack01(W[i],pesos,valores) << std::endl;
    }
    return 0;
}