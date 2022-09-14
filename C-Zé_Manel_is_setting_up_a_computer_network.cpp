#include <iostream>
#include <unordered_map>
using namespace std;

class Node{
public:
    unordered_map<int, int> link_cost;
    int degree = 0;
    bool visited = false;
};


int n_nodes, max_degree, best = -1;
void tree(int number, int c, Node *nodes){
    if (best != -1 && c >= best){
        return;
    }

    if(number == n_nodes-1){
        if(best == -1){
            best = c;
        }
        if(c < best){
            best = c;
        }
        return;
    }

    for (int i = 0; i < n_nodes; ++i) {
        if(!nodes[i].visited){
            for (const auto &item : nodes[i].link_cost){
                int dest = item.first;
                if(nodes[dest].visited){
                    int cost = item.second;
                    if(cost && nodes[dest].degree < max_degree){
                        nodes[i].degree = nodes[i].degree + 1;
                        nodes[dest].degree = nodes[dest].degree + 1;
                        nodes[i].visited = true;
                        tree(number + 1, c + cost, nodes);
                        nodes[i].visited = false;
                        nodes[i].degree = nodes[i].degree - 1;
                        nodes[dest].degree = nodes[dest].degree - 1;
                    }
                }

            }

            }
        }


}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int m;
    while(cin >> n_nodes){
        cin >> m >> max_degree;
        Node *nodes = new Node[n_nodes];
        int origin, destination, cost;
        for (int i = 0; i < m; ++i) {
            cin >> origin >> destination >> cost;
            nodes[origin - 1].link_cost.insert(make_pair(destination-1, cost));
            nodes[destination-1].link_cost.insert(make_pair(origin - 1, cost));
        }
        nodes[0].visited = true;
        tree(0, 0, nodes);
        if(best != -1){
            cout << best << "\n";
        }
        else{
            cout  << "NO WAY!\n";
        }
        best = -1;
    }

    return 0;
}