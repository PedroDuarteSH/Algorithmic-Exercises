#include <iostream>

using namespace std;
int n_levels;

int search(int level, int pos, int **number, int **output){
    if(pos > level){
        return 0;
    }

    if(output[level][pos] != -1){
        return output[level][pos];
    }

    if(level == n_levels -1){
        output[level][pos] = number[level][pos];
        return output[level][pos];
    }

    int max = search(level + 1, pos, number, output);
    int i = search(level + 1, pos + 1, number, output);
    if(i > max){
        max = i;
    }

    output[level][pos] = max + number[level][pos];
    return output[level][pos];
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n_cases;

    cin >> n_cases;
    for (int i = 0; i < n_cases; ++i) {
        cin >> n_levels;
        int **array = new int *[n_levels];
        int **save_out = new int *[n_levels];
        for (int j = 0; j < n_levels; ++j) {
            array[j] = new int [j+1];
            save_out[j] = new int [j+1];
            for (int k = 0; k < j + 1; ++k) {
                cin >> array[j][k];
                save_out[j][k] = -1;
            }
        }
        cout << search(0, 0, array, save_out) << "\n";
    }

    return 0;
}






