#include <iostream>

using namespace std;

class Cube{
public:
    int x;
    int y;
    int z;
    int size;

    Cube(int x, int y, int z, int size){
        this->x = x;
        this->y = y;
        this->z = z;
        this->size = size;
    }

};

Cube **cubes;
int n_cubes;
int cubes3dVolume(){
    Cube *left_down = new Cube(-INT32_MAX,-INT32_MAX, -INT32_MAX, -INT32_MAX);
    Cube *right_up = new Cube(INT32_MAX,INT32_MAX, INT32_MAX, INT32_MAX);

    for (int i = 0; i < n_cubes; ++i) {
        left_down->x = max(left_down->x, cubes[i]->x);
        left_down->y = max(left_down->y, cubes[i]->y);
        left_down->z = max(left_down->z, cubes[i]->z);

        right_up->x = min(right_up->x, cubes[i]->x + cubes[i]->size);
        right_up->y = min(right_up->y, cubes[i]->y + cubes[i]->size);
        right_up->z = min(right_up->z, cubes[i]->z + cubes[i]->size);
    }
    return max(0, right_up->x - left_down->x) * max(0, right_up->y - left_down->y) * max(0, right_up->z - left_down->z);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n_cubes;
    int x, y, z, size;
    cubes = new Cube*[n_cubes];
    for (int i = 0; i < n_cubes; ++i) {
        cin >> x >> y >> z >> size;
        cubes[i] = new Cube(x, y, z, size);
    }
    cout << cubes3dVolume() << endl;
    return 0;
}