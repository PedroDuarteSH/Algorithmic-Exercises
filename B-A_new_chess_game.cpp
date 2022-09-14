#include <iostream>
#define POS_LIMIT 200
#define NEG_LIMIT -200
using namespace std;


int chess(int x, int y, int moves, bool **table);
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    bool **table;
    table = new bool *[400];
    for (int i = 0; i < 400; ++i) {
        table[i] = new bool[400];
    }
    int count = 0;
    int n_knigths, initial_x, initial_y, n_moves;
    cin >> n_knigths;
    for (int i = 0; i < n_knigths; ++i) {
        cin >> initial_x >> initial_y >> n_moves;
        count += chess(initial_x, initial_y, n_moves, table);
    }
    cout << count << "\n";
    return 0;
}


int chess(int x, int y, int moves, bool **table){

    int count = 0;
    if(!table[x+200][y + 200]){
        count++;
        table[x+200][y + 200] = true;
    }
    if(moves == 0){
        return count;
    }

    count += chess(x - 1, y + 2, moves-1, table);
    count += chess(x - 1, y - 2, moves-1, table);
    count += chess(x + 1, y - 2, moves-1, table);
    count += chess(x + 1, y + 2, moves-1, table);
    count += chess(x - 2, y + 1, moves-1, table);
    count += chess(x - 2, y - 1, moves-1, table);
    count += chess(x + 2, y + 1, moves-1, table);
    count += chess(x + 2, y - 1, moves-1, table);

    return count;


}