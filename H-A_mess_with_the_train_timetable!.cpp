#include <iostream>
#include <queue>
#include <vector>
#include <array>
using namespace std;

class Node{
public:
    int index;
    int color = -1;
    vector<Node *> connects_to{};
    Node(int index){
        this->index = index;
    }
};

Node **graph;

bool BFS(){
    queue<Node *> node_queue;
    graph[0]->color = 1;
    node_queue.push(graph[0]);
    while(!node_queue.empty()){
        Node *current_node = node_queue.front();
        node_queue.pop();
        for (const auto &item : current_node->connects_to){
            if(item->color == -1){
                item->color = 1 - current_node->color;
                node_queue.push(item);
            }else if(item->color == current_node->color){
                return false;
            }
        }
    }
    return true;
}



int main() {

    int n_trains, pairs;
    while (cin >> n_trains){
        cin >> pairs;
        graph = new Node*[n_trains];
        for (int i = 0; i < n_trains; ++i)
            graph[i] = nullptr;

        for (int i = 0; i < pairs; ++i) {
            int start, end;
            cin >> start >> end;
            start--;
            end--;
            if(graph[start] == nullptr)
                graph[start] = new Node(start);
            if(graph[end] == nullptr)
                graph[end] = new Node(end);
            graph[start]->connects_to.push_back(graph[end]);
            graph[end]->connects_to.push_back(graph[start]);
        }
        bool result = BFS();
        if(result){
            cout << "NOT SURE\n";
        }else{
            cout << "NO\n";
        }
    }
    return 0;
}
