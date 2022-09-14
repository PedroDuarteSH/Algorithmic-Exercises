#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
using namespace std;

class Node{
public:
    int time = 0;
    int number = 0;
    vector<Node *> connection_out {};
    vector<Node *> connection_in {};
    int min_time_next = 0;

    //Check if is cyclic
    bool visitedInRecursion = false;
    bool visited = false;

    // Visited in statiscs
    bool visitedInTree = false;

    int in_degree = 0;
    int level = 0;
    bool operator<(Node const &p) const {
        return number > p.number;
    }
};

Node **graph;
int n_connections;
bool check_cycle(Node *currentNode){
    if (currentNode->visitedInRecursion)
        return true;
    if (currentNode->visited)
        return false;
    currentNode->visited = true;
    currentNode->visitedInRecursion = true;


    for (auto & i : currentNode->connection_out){
        if(check_cycle(i)){
            return true;
        }
    }
    currentNode->visitedInRecursion = false;
    return false;
}

vector <int> statistic1(Node *start_node){
    vector<int> path;
    priority_queue<int,vector<int>, greater<>> next_nodes;
    next_nodes.push(start_node->number-1);
    path.push_back(0);

    while (!next_nodes.empty()){
        int current_number = next_nodes.top();
        next_nodes.pop();
        Node *current_node = graph[current_number];
        path.at(0)+=current_node->time;
        path.push_back(current_node->number);
        for (const auto &item : current_node->connection_out){
            item->in_degree--;
            if(item->in_degree == 0){
                next_nodes.push(item->number-1);
            }
        }
    }
    return path;
}

// If return -1, cycle was found, end
int statistic2(Node *currentNode){
    if(currentNode->min_time_next != 0){
        return currentNode->min_time_next;
    }
    int max_time = 0;
    for (auto & i : currentNode->connection_out) {
        int son_time = statistic2(i);
        if(son_time > max_time){
            max_time = son_time;
        }
    }
    currentNode->min_time_next = max_time + currentNode->time;
    return max_time + currentNode->time;
}

vector<int> statistic3(Node *start_node){
    vector<int> path;
    queue<int> next_nodes;
    //para comecar logo no tempo 0
    // aumentoamnete vai buscar o contrutor do par
    next_nodes.push(start_node->number-1);
    //buscar o minimo numero de nos que
    // ver os niveis sozinhos
    //procurar em tds os nos uim numero menor ou ihuais aquele
    while (!next_nodes.empty()) {
        int current_number = next_nodes.front();
        next_nodes.pop();
        Node *current_node = graph[current_number];
        for (auto &i: current_node->connection_out) {
            i->in_degree--;
            if (i->in_degree == 0) {
                i->level = current_node->level + 1;
                next_nodes.push(i->number - 1);
            }
        }
    }
    next_nodes.push(start_node->number-1);
    for (int i = 0; i < n_connections; ++i) {
        graph[i]->in_degree = graph[i]->connection_in.size();
    }

    //2 bfs
    while (!next_nodes.empty()){
        int current_number = next_nodes.front();
        next_nodes.pop();
        Node *current_node = graph[current_number];
        queue<int> back_nodes;
        vector<bool> visited(n_connections, false);
        back_nodes.push(current_node->number-1);
        visited[current_node->number-1] = true;
        while (!back_nodes.empty()) {
            int back_number = back_nodes.front();
            back_nodes.pop();
            Node *back_node = graph[back_number];
            back_node->visitedInTree = true;
            for (const auto &item : back_node->connection_in){
                if (!visited[item->number-1]){
                    visited[item->number-1] = true;
                    back_nodes.push(item->number-1);
                }
            }
        }
        bool is_bottleneck = true;
        for (int i = 0; i < n_connections; ++i) {
            // se isto acontecer nao e bottleneck
            if(graph[i]->level <= current_node->level && !graph[i]->visitedInTree){
                // cout << current_node->number << " : "  << graph[i]->number << endl;
                is_bottleneck = false;
            }
            graph[i]->visitedInTree = false;
        }
        if(is_bottleneck){
            cout << current_node->number << endl;
        }
        for (auto & i : current_node->connection_out){
            i->in_degree--;
            if(i->in_degree == 0){
                i->level = current_node->level+1;
                next_nodes.push(i->number-1);
            }
        }
    }

    return path;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int mode;
    cin >> n_connections;
        graph = new Node*[n_connections];
        for (int i = 0; i < n_connections; ++i) {
            graph[i] = nullptr;
        }
        bool *start = new bool[n_connections];
        bool *end = new bool[n_connections];
        int starting_nodes = n_connections;
        int end_nodes = n_connections;

        for (int i = 0; i < n_connections; ++i){
            if(graph[i] == nullptr){
                graph[i] = new Node();
                start[i] = true;
                end[i] = true;
                graph[i]->number = i+1;
            }

            int connections, time;
            cin >> time >> connections;
            graph[i]->time = time;
            for (int j = 0; j < connections; ++j) {
                int node_num;
                cin >> node_num;
                node_num = node_num - 1;
                if(graph[node_num] == nullptr){
                    graph[node_num] = new Node();
                    start[node_num] = true;
                    end[node_num] = true;
                    graph[node_num]->number = node_num+1;
                }
                graph[i]->connection_in.push_back(graph[node_num]);
                graph[i]->in_degree++;

                graph[node_num]->connection_out.push_back(graph[i]);

                if(start[i]){
                    start[i] = false;
                    starting_nodes--;
                }
                if(end[node_num]){
                    end[node_num] = false;
                    end_nodes--;
                }
            }
        }
        cin >> mode;

        //Find starting node
        int start_index;
        for (start_index = 0; start_index < n_connections; ++start_index){
            if(start[start_index])
                break;
        }
        bool cyclic = true;
        bool invalid = starting_nodes > 1 || end_nodes > 1;
        if(start_index < n_connections){
            cyclic = check_cycle(graph[start_index]);
        }

        //Verify if is pipeline and if there are more than one ends or starts
        if(cyclic || invalid) {
            cout << "INVALID" << "\n";
        } else{
            if(mode == 0){
                cout << "VALID" << "\n";
            }
            else if(mode == 1){
                vector<int> path = statistic1(graph[start_index]);
                for (const auto &item : path){
                    cout << item << "\n";
                }
            }
            else if(mode == 2){
                cout << statistic2(graph[start_index]) << "\n";
            }
            else if(mode == 3){
                vector<int> path = statistic3(graph[start_index]);
                //for (const auto &item : path){
                //    cout << item << "\n";
                //}
            }
        }

    return 0;
}