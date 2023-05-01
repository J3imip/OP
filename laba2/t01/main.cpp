#include <iostream>
#include <math.h>

using namespace std;

class Point3D {
  friend double operator-(const Point3D &p1, const Point3D &p2) {
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    double dz = p2.z - p1.z;

    return sqrt(dx * dx + dy * dy + dz * dz);
  }
private:
  double x, y, z;
public:
  Point3D(): Point3D(0, 0, 0) {}
  Point3D(double x, double y, double z): x(x), y(y), z(z) {}

  //setters
  void setX(double x) { this->x = x; }
  void setY(double y) { this->y = y; }
  void setZ(double z) { this->z = z; }

  //getters
  double getX() { return this->x; }
  double getY() { return this->y; }
  double getZ() { return this->z; }
};

void printPoints(Point3D &p1, Point3D &p2) {
  cout << "Coordinates of points:" << endl;
  cout << "p1:\t" << p1.getX() << " " << p1.getY() << " " << p1.getZ() << endl;
  cout << "p2:\t" << p2.getX() << " " << p2.getY() << " " << p2.getZ() << "\n";
}

int main() {
  Point3D p1;
  Point3D p2(2, 4, 6);

  printPoints(p1, p2);

  //using operator- function
  cout << "Distance between two points: " << p1-p2 << "\n\n";

  //setting new values
  p1.setX(20);
  p1.setY(40);
  p1.setZ(60);

  printPoints(p1, p2);

  cout << "Distance between two points: " << operator-(p1, p2) << endl;
}
