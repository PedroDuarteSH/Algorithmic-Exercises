#include <iostream>
#include <algorithm>

using namespace std;

int guards(int n_pieces, const int *pieces, int range){
    int n_guards = 1;
    int last_g_pos = pieces[0] + range;

    for (int i = 1; i < n_pieces; ++i) {
        if(last_g_pos + range < pieces[i]){
            last_g_pos = pieces[i] + range;
            n_guards++;
        }
    }

    return n_guards;
}
int main() {
    int n_pieces, n_cases, range;
    int *pieces;
    cin >> n_cases;
    for (int i = 0; i < n_cases; ++i) {
        cin >> n_pieces >> range;
        pieces = new int[n_pieces];
        for (int j = 0; j < n_pieces; ++j) {
            cin >> pieces[j];
        }
        sort(pieces, pieces + n_pieces);
        cout << guards(n_pieces, pieces, range) << "\n";

        delete pieces;
    }
    return 0;
}