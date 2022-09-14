#define MAX_N 200
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Place{
public:
    vector<Place *> connects_to;
    vector<int> connection_cost;
    int current_cost = INT32_MAX;

};
Place *places[MAX_N];

void algorithm(Place* current_node, int current_cost){
    if(current_cost >= current_node->current_cost)
        return;
    current_node->current_cost = current_cost;
    for (int i = 0; i < (int)current_node->connects_to.size(); ++i) 
        algorithm(current_node->connects_to.at(i), current_node->current_cost + current_node->connection_cost.at(i));
}



int main() {
    int n_places, finish_id = 0, place, cost, temp;
    cin >> n_places >> temp;
    for (int i = 0; i < n_places; ++i) {
        cin >> place;
        if(places[i] == nullptr)
            places[i] = new Place();

        for (int j = 0; j < n_places;++j) {
            cin >> cost;
            if(cost > -1){
                if(places[j] == nullptr)
                    places[j] = new Place();
                places[i]->connects_to.push_back(places[j]);
                places[i]->connection_cost.push_back(cost);
            }
        }
        if(place == temp){
            finish_id = i;
        }
    }
    algorithm(places[0], 0);
    cout << places[finish_id]->current_cost << "\n";

    return 0;
}