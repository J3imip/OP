#include <iostream>
#include <math.h>

using namespace std;

struct Point {
    int x, y, z;
};

int calcDistance(Point p1, Point p2) {
    return sqrt(
        pow((p2.x - p1.x), 2) + 
        pow((p2.y - p1.y), 2) + 
        pow((p2.z - p1.z), 2)
    );
}

int main() {
    Point p1 = {1, 2, 3};
    Point p2 = {6, 2, 3};

    cout << "Distance between points: " << calcDistance(p1, p2) << endl;
}
