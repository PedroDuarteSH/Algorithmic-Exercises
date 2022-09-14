#include <iostream>
#include <array>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
//
// BRAIN STORM
// MAP POSSIBLE SEQUENCES IN HASH MAP ON THE BEGINNING

//g++ -std=c++17 -Wall -Wextra -O2 -pg main.cpp -lm
//./a.out < texz.txt
//gprof a.out gmon.out > analysis.txt
//

typedef unordered_map<int, vector<int>> hashMap;

int n_pieces, rows, cols;

class Piece {
public:
    /*
     * 0 -> Top Left
     * 1 -> Top Right
     * 2 -> Bottom Right
     * 3 -> Bottom Left
     */
    array<int, 4> corners{};
    bool placed = false;


    Piece rotate(){
        std::rotate(corners.begin(),corners.begin()+1,corners.end());
        return *this;
    }

    int seq_in(int a, int b){
        int count = 0;
        if(corners[0] == a && corners[3] == b){
            count++;
        }
        for (int i = 1; i < 4; ++i){
            if(corners[i] == a && corners[i - 1] == b)
                count++;
        }

        return count;
    }

    static vector<int> *find_seq(int a, int b, hashMap &map, Piece *pieces){
        int num = a * 1000 + b;
        auto search = map.find(num);
        if(search != map.end())
            return &search->second;
        else{
            vector<int> possibilities;

            for (int i = 0; i < n_pieces; ++i) {
                int count = pieces[i].seq_in(a, b);
                for (int j = 0; j < count; ++j) {
                    possibilities.push_back(i);
                }
            }
            map.insert(make_pair(num, possibilities));
            return &map.find(num)->second;
        }
    }


    Piece set_left(int a, int b){
        this->rotate();
        while(corners[0] != a || corners[3] != b){
            this->rotate();
        }
        return *this;
    }

    Piece set_up(int a, int b){
        this->rotate();
        while(corners[1] != a || corners[0] != b){
            this->rotate();
        }
        return *this;
    }
};


bool processTable(Piece *pieces, Piece **table, hashMap& current_map);
bool put_down(int to_add, Piece **table, Piece *pieces,int current_row, int current_col, hashMap& current_map);
bool put_right(int to_add, Piece **table, Piece *pieces,int current_row, int current_col, hashMap& current_map);
void print_table(Piece **table);



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int cases;
    cin >> cases;
    for (int i = 0; i < cases; ++i) {
        cin >> n_pieces >> rows >> cols;
        Piece allPieces[n_pieces];
        unordered_map<int, bool> is_even;
        for (int j = 0; j < n_pieces; ++j) {
            cin >> allPieces[j].corners[0] >> allPieces[j].corners[1] >> allPieces[j].corners[2] >> allPieces[j].corners[3];
            is_even[allPieces[j].corners[0]] = !is_even[allPieces[j].corners[0]];
            is_even[allPieces[j].corners[1]] = !is_even[allPieces[j].corners[1]];
            is_even[allPieces[j].corners[2]] = !is_even[allPieces[j].corners[2]];
            is_even[allPieces[j].corners[3]] = !is_even[allPieces[j].corners[3]];
        }
        int count = 0;
        for (const auto &item : is_even){
            if(item.second){
                count++;
            }
        }

        if(count > 4){
            // cout << "impossible puzzle!\n";
        }
        else{
            Piece **table;
            table = new Piece *[rows];
            for(int j = 0; j < rows; j++)
                table[j] = new Piece[cols];
            hashMap current_map;
            if(processTable(allPieces, table, current_map)){

            }
                // print_table(table);
            else{

            }
                //cout << "impossible puzzle!\n";

            delete table;
            current_map.clear();
        }
    }
    return 0;
}

vector<int> *intercept(vector<int> *a, vector<int> *b){
    auto *result = new vector<int>;
    int count_b;
    int count_a;
    int last_item = -1;
    for (const auto &item : *a){
        if(item != last_item){
            count_b = (int) count(b->begin(), b->end(), item);
            if(count_b == 0){
                last_item = item;
                continue;
            }
            count_a = (int) count(a->begin(), a->end(), item);
            if(count_b > count_a){
                count_a = count_b;
            }
            for (int i = 0; i < count_a; ++i) {
                result->push_back(item);
            }
        }
        last_item = item;
    }
    return result;
}


bool processTable(Piece *pieces, Piece **table, hashMap& current_map){
    table[0][0] = pieces[0];
    pieces[0].placed = true;
    if(cols == 1){
        vector<int> *possible = Piece::find_seq(table[0][0].corners[1], table[0][0].corners[2], current_map, pieces);
        for(auto & i: *possible){
            if(!pieces[i].placed){
                if(put_down(i, table, pieces, 1, 0, current_map)){
                    return true;
                }
            }
        }
    }

    else{
        vector<int> *possible = Piece::find_seq(table[0][0].corners[1], table[0][0].corners[2], current_map, pieces);
        for (auto & i : *possible) {
            if(!pieces[i].placed){
                if(put_right(i, table, pieces, 0, 1, current_map)){
                    return true;
                }
            }

        }
    }

    return false;
}

bool put_right(int to_add, Piece **table, Piece *pieces,int current_row, int current_col, hashMap& current_map){
    //Rotate piece to correct position
    pieces[to_add] = pieces[to_add].set_left(table[current_row][current_col-1].corners[1], table[current_row][current_col-1].corners[2]);
    //Verify if up sequence is correct
    if(current_row){
        if(pieces[to_add].corners[0] != table[current_row-1][current_col].corners[3] || pieces[to_add].corners[1] != table[current_row-1][current_col].corners[2]){
            return false;
        }
    }
    vector<int> *possible;
    table[current_row][current_col] = pieces[to_add];
    pieces[to_add].placed = true;

    //cout << "PUT RIGHT " <<to_add << "-" << current_col << "-" << current_row << "\n" << rows << "-" << cols << "\n";
    //print_table(table, rows, cols);
    if(current_col == cols - 1){
        if(current_row == rows - 1){
            return true;
        }
        else{
            possible = Piece::find_seq(table[current_row][0].corners[2],table[current_row][0].corners[3], current_map, pieces);
            for(auto & i : *possible){
                if(!pieces[i].placed){
                    if(put_down(i, table, pieces, current_row + 1, 0, current_map)){
                        return true;
                    }
                }
            }
        }


    }
    else{
        vector<int> *possibleRight = Piece::find_seq(table[current_row][current_col].corners[1], table[current_row][current_col].corners[2], current_map, pieces);
        if(current_row){
            vector<int> *possibleDown = Piece::find_seq(table[current_row-1][current_col+1].corners[2], table[current_row-1][current_col+1].corners[3], current_map, pieces);
            possible = intercept(possibleRight, possibleDown);
        } else{
            possible = possibleRight;
        }
        for (auto & i : *possible) {
            if(!pieces[i].placed){
                if(put_right(i, table, pieces, current_row, current_col + 1, current_map)){
                    return true;
                }
            }
        }
    }
    pieces[to_add].placed = false;
    return false;
}

bool put_down(int to_add, Piece **table, Piece *pieces,int current_row, int current_col, hashMap& current_map){
    //Rotate piece to correct position
    pieces[to_add] = pieces[to_add].set_up(table[current_row - 1][current_col].corners[2], table[current_row - 1][current_col].corners[3]);
    table[current_row][current_col] = pieces[to_add];
    pieces[to_add].placed = true;
    vector<int> *possible;
    //cout << "PUT DOWN " <<to_add << "-" << current_col << "-" << current_row  <<  "->" <<  go_left << "\n" << rows << "-" << cols << "\n";
    //print_table(table, rows, cols);
    if(cols == 1){
        if(current_row == rows-1){
            return true;
        }
        possible = Piece::find_seq(table[current_row][0].corners[2],table[current_row][0].corners[3], current_map, pieces);
        for(auto & i: *possible){
            if(!pieces[i].placed){
                if(put_down(i, table, pieces, current_row + 1, 0, current_map)){
                    return true;
                }
            }
        }
    }
    else{
        vector<int> *possibleRight = Piece::find_seq(table[current_row][current_col].corners[1], table[current_row][current_col].corners[2], current_map, pieces);
        if(current_row){
            vector<int> *possibleDown = Piece::find_seq(table[current_row-1][current_col+1].corners[2], table[current_row-1][current_col+1].corners[3], current_map, pieces);
            possible = intercept(possibleRight, possibleDown);
        }
        else{
            possible = possibleRight;
        }
        for (auto & i : *possible) {
            if(!pieces[i].placed){
                if(put_right(i, table, pieces, current_row, current_col + 1, current_map)){
                    return true;
                }
            }
        }
    }

    pieces[to_add].placed = false;
    return false;
}

void print_table(Piece **table){
    //Print table

    for (int i = 0; i < rows; ++i) {
        if(i > 0){
            cout << "\n";
        }
        for (int j = 0; j < cols; ++j) {
            if(j > 0){
                cout << "  ";
            }
            cout << table[i][j].corners[0] << " " <<  table[i][j].corners[1];
        }
        cout << "\n";
        for (int j = 0; j < cols; ++j) {
            if(j > 0){
                cout << "  ";//oss << "  ";
            }
            cout << table[i][j].corners[3] << " " <<  table[i][j].corners[2];
        }
        cout << "\n";
    }
}