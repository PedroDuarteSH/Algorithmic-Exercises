#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;


bool **DP;
int *pizza_time;
int n_pizzas;
int mean_time;
int get_medium(){
    for (int i = 0; i < n_pizzas + 1; i++)
        DP[i][0] = true;
    for (int j = 1; j < mean_time + 1; j++)
        DP[0][j] = false;

    for (int i = 1; i < n_pizzas + 1; ++i) {
        for (int j = 1; j < mean_time + 1; ++j) {
            if(pizza_time[i-1] > j){
                DP[i][j] = DP[i-1][j];
            }
            else{
                if(DP[i-1][j]){
                    DP[i][j] = DP[i-1][j];
                }
                else{
                    DP[i][j] = DP[i-1][j-pizza_time[i-1]];
                }
            }
        }
    }
    for (int i = mean_time; i > 0; i--) {
        if(DP[n_pizzas][i])
            return i;
    }
    return 0;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    while(cin >> n_pizzas){
        int sum = 0;
        pizza_time = new int[n_pizzas];
        for (int i = 0; i < n_pizzas; ++i) {
            cin >> pizza_time[i];
            sum += pizza_time[i];
        }

        mean_time = sum / 2;
        DP = new bool*[n_pizzas + 1];
        for (int i = 0; i < n_pizzas + 1; ++i) {
            DP[i] = new bool[mean_time + 1];
        }
        int result = get_medium();
        cout << abs((sum-result) - result) << "\n";
    }
    return 0;
}