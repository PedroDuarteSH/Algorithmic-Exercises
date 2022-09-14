// A - Party icebreaker

#include <iostream>
#include <vector>
#include <algorithm>
// 3 sort algorithm

using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int num;
    //While there is numbers to read
    while (cin >> num) {
        vector<int> listNumbers;
        while(num != 0){
            listNumbers.push_back(num);
            cin >> num;
        }
        sort(listNumbers.begin(), listNumbers.end());
        //Find middle value

        bool found = false;
        for (int i = 0; i < (int)listNumbers.size() - 2; ++i) {
            int next_index = i+1;
            int end_index = (int)listNumbers.size() - 1;
            while(next_index != end_index){
                int result = listNumbers[i] + listNumbers[next_index] + listNumbers[end_index];
                if(result == 0){
                    found = true;
                    break;
                }
                else if(result < 0){
                    next_index++;
                }
                else{
                    end_index--;
                }
            }
        }
        if(found){
            std::cout << "Fair\n";
        }
        else{
            std::cout << "Rigged\n";
        }



    }




    return 0;
}