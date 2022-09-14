#include <iostream>
#include <array>
#include <vector>
using  namespace  std;
#define MAXSIZE 20
#define MAXREC 100000
#define MAXSONS 10

int split_string(string *line, int *line_parsed);
class Node{

public:
    int index;
    int cost = 0;
    Node *parent = nullptr;
    bool painted = false;
    array<int, 2> best_paint{-1,-1};
    array<int, 2> best_dont_paint{-1,-1};
    int number_recruitments = 0;
    array<Node *, MAXSONS> recruited{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};


    explicit Node(int index){
        this->index = index;
    }

    void setParent(Node *parent_node){
        parent = parent_node;
    }

    bool checkNotPainted(){
        for (int i = 0; i < number_recruitments; ++i) {
            if(!recruited[i]->painted){
                return false;
            }
        }
        if(parent != nullptr){
            if(!parent->painted){
                return false;
            }
        }

        return true;
    }

    array<int,2> *getBest(){

        if(best_paint[0] == -1){
            return nullptr;
        }
        //cout << "Checking node " << index << "\n";
        if(!checkNotPainted()){
            painted = true;
            return &best_paint;
        }
        //cout << "Can be not painted\n";
        if(best_paint[0] < best_dont_paint[0]){
            painted = true;
            return &best_paint;
        }
        else if(best_paint[0] > best_dont_paint[0]){
            painted = false;
            return &best_dont_paint;
        }
        else{
            if(best_paint[1] > best_dont_paint[1]){
                painted = true;
                return &best_paint;
            }
            else{
                painted = false;
                return &best_dont_paint;
            }
        }

    }
};

Node *tree[MAXREC];

array<int,2> *algorithm(Node *current_node){
    array<int,2> *best = current_node->getBest();
    if(best != nullptr){
        return best;
    }
    array<int, 2> temp{};
    //no caso de estar pintado
    current_node->painted = true;
    current_node->best_paint[0] = 1;
    current_node->best_paint[1] = current_node->cost;
    for (int i = 0; i < current_node->number_recruitments; ++i) {
        //cout << "Testing " << current_node->recruited[i]->index << " from " << current_node->index << "painted\n";
        // TEST NOT PAINTED
        temp = *algorithm(current_node->recruited[i]);
        current_node->best_paint[0] += temp[0];
        current_node->best_paint[1] += temp[1];
    }
    //cout << "Results of " << current_node->index << " painted: " << current_node->best_paint[0] << " " << current_node->best_paint[1] << "\n";
    current_node->painted = false;
    current_node->best_dont_paint[0] = 0;
    current_node->best_dont_paint[1] = 0;
    int count_last = 0;
    for (int i = 0; i < current_node->number_recruitments; ++i) {
        //cout << "Testing " << current_node->recruited[i]->index << " from " << current_node->index << " not painted\n";
        // TEST NOT PAINTED
        temp = *algorithm(current_node->recruited[i]);
        current_node->best_dont_paint[0] += temp[0];
        current_node->best_dont_paint[1] += temp[1];

        if(current_node->recruited[i]->number_recruitments == 0){
            count_last++;
        }
    }

   // cout << "Results of " << current_node->index << " dont painted: " << current_node->best_dont_paint[0] << " " << current_node->best_dont_paint[1] << "\n";



    return current_node->getBest();
}

void print_tree(Node *node){
    if(node->parent != nullptr)
        cout << node->index << "-" << node->cost;
    else  cout << node->cost << "-" << node->index << "\n";

    for (int i = 0; i < node->number_recruitments; ++i) {
        cout << "-";
        print_tree(node->recruited[i]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    auto *line = new string;
    int *line_parsed = new int [MAXSIZE];
    for (int i = 0; i < MAXSIZE; ++i)
        line_parsed[i] = -1;

    vector<int> indexes;
    while (getline(cin, *line)){
        int count = split_string(line, line_parsed);
        if(count){
            indexes.push_back(line_parsed[0]);
            Node *parent = nullptr;
            for (int i = 0; i < count-1; ++i) {
                int node_pos = line_parsed[i];
                if(tree[node_pos] == nullptr)
                    tree[node_pos] = new Node(node_pos);
                if(i == 0)
                    parent = tree[node_pos];
                else{
                    tree[node_pos]->setParent(parent);
                    parent->recruited[i-1] = tree[node_pos];
                    parent->number_recruitments++;
                }
            }
            parent->cost = line_parsed[count-1];
        }
        else{
            //Execute verification
            //print_tree(tree[0]);
            array<int,2> temp = *algorithm(tree[0]);
            cout << temp[0] << " " << temp[1] << "\n";
            //Clear
            for (const auto &item : indexes){
                delete tree[item];
                tree[item] = nullptr;
            }
            indexes.clear();
        }
    }
    return 0;
}

int split_string(string *line, int *line_parsed){
    int index = 0;
    int count = 0;
    uint start = 0;
    uint end = line->find(" ");
    while (end != (uint) string::npos){
        if((line_parsed[index++] = stoi(line->substr(start, end - start))) != -1)
            count++;
        start = end + 1;
        end = line->find(" ", start);
    }
    if((line_parsed[index++] = stoi(line->substr(start, end))) != -1)
        count++;
    while (line_parsed[index] != -1 && index < MAXSIZE){
        line_parsed[index++] = -1;
    }
    return count;
}