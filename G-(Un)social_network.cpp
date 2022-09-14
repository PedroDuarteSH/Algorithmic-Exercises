
#include <iostream>


using namespace std;
bool **links;
int *visited;
int n_nodes, n_links;
int best;
int remaining(int current_node){
    int c = 0;
    for (int i = current_node; i < n_nodes; ++i) {
        if(visited[i] == 0){
            c+=1;
        }
    }
    return c;
}

void choosePerson(int current_node, int current_best){
    int b = current_best + remaining(current_node);
    if(b <= best)
        return;
    if(current_best > best)
        best = current_best;
    if(current_node == n_nodes)
        return;

    if(visited[current_node] == 0){
        visited[current_node] = 1;
        for (int i = 0; i < n_nodes; ++i) {
            if(links[current_node][i]){
                visited[i] += 1;
            }
        }
        choosePerson(current_node + 1, current_best + 1);
        for (int i = 0; i < n_nodes; ++i) {
            if(links[current_node][i]){
                visited[i] -= 1;
            }
        }
        visited[current_node] = 0;
    }
    choosePerson(current_node + 1, current_best);

}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);


    while (cin >> n_nodes){
        best = 0;
        links = new bool*[n_nodes];
        visited = new int[n_nodes];
        for (int i = 0; i < n_nodes; ++i){
            links[i] = new bool [n_nodes];
            visited[i] = 0;
            for (int j = 0; j < n_nodes; ++j) {
                links[i][j] = false;
            }
        }


        cin >> n_links;

        for (int i = 0; i < n_links; ++i) {
            int n1, n2;
            cin >> n1 >> n2;
            links[n1][n2] = true;
            links[n2][n1] = true;
        }
        choosePerson(0, 0);
        cout << best << "\n";
    }

    return 0;
}