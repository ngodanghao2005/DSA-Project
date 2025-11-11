#ifndef POINT_H
#define POINT_H

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

#define EPSILON (1E-8)

class Point {
 private:
  float x, y, z;
  friend ostream& operator<<(ostream& os, const Point& point){
    os << "P(" << fixed << setprecision(1) << point.x << ", " << setprecision(1)
      << point.y << ", " << setprecision(1) << point.z << ")";
    return os;
  }

 public:
  Point(float x = 0.0f, float y = 0.0f, float z = 0.0f): x(x), y(y), z(z) {}
  Point(const Point& point): x(point.x), y(point.y), z(point.z) {}

  void setX(float x){ this->x = x; }
  float getX() const{ return x; }
  void setY(float y){ this->y = y; }
  float getY() const{ return y; }
  void setZ(float z){ this->z = z; }
  float getZ() const{ return z; }

  float radius() const{ return std::sqrt(x * x + y * y + z * z); }

  operator float(){ return this->radius(); }

  bool operator==(Point rhs) const{
    return std::abs(x - rhs.x) < EPSILON && std::abs(y - rhs.y) < EPSILON && std::abs(z - rhs.z) < EPSILON;
  }

  // Compare by x, y, z and radius
  static bool pointEQ_X(Point& lhs, Point& rhs){
    return std::abs(lhs.x - rhs.x) < EPSILON;
  }
  static bool pointEQ_Y(Point& lhs, Point& rhs){
    return std::abs(lhs.y - rhs.y) < EPSILON;
  }
  static bool pointEQ_Z(Point& lhs, Point& rhs){
    return std::abs(lhs.z - rhs.z) < EPSILON;
  }
  static bool pointEQ_Radius(Point& lhs, Point& rhs){
    return std::abs(lhs.radius() - rhs.radius()) < EPSILON;
  }
  static bool pointEQ(Point& lhs, Point& rhs){
    return pointEQ_X(lhs, rhs) && pointEQ_Y(lhs, rhs) && pointEQ_Z(lhs, rhs);
  }

  // Comparison functions for pointers
  static bool pointEQ_X(Point*& lhs, Point*& rhs){
    return pointEQ_X(*lhs, *rhs);
  }
  static bool pointEQ_Y(Point*& lhs, Point*& rhs){
    return pointEQ_Y(*lhs, *rhs);
  }
  static bool pointEQ_Z(Point*& lhs, Point*& rhs){
    return pointEQ_Z(*lhs, *rhs);
  }
  static bool pointEQ_Radius(Point*& lhs, Point*& rhs){
    return pointEQ_Radius(*lhs, *rhs);
  }
  static bool pointEQ(Point*& lhs, Point*& rhs){
    return pointEQ(*lhs, *rhs);
  }

  // Conversion to string
  static string point2str_X(Point& point){
    std::stringstream ss;
    ss << "X: " << point.x;
    return ss.str();
  }
  static string point2str_Y(Point& point){
    std::stringstream ss;
    ss << "Y: " << point.y;
    return ss.str();
  }
  static string point2str_Z(Point& point){
    std::stringstream ss;
    ss << "Z: " << point.z;
    return ss.str();
  }
  static string point2str_Radius(Point& point){
    std::stringstream ss;
    ss << "Radius: " << point.radius();
    return ss.str();
  }
  static string point2str(Point& point){
    std::stringstream ss;
    ss << "P(" << point.x << ", " << point.y << ", " << point.z << ")";
    return ss.str();
  }

  // Conversion to string for pointers
  static string point2str_X(Point*& point){ return point2str_X(*point); }
  static string point2str_Y(Point*& point){ return point2str_Y(*point); }
  static string point2str_Z(Point*& point){ return point2str_Z(*point); }
  static string point2str_Radius(Point*& point){
    return point2str_Radius(*point);
  }
  static string point2str(Point*& point){ return point2str(*point); }

  // Point operations
  static void pointRemove(Point* point){ delete point; }
  static Point* genPoints(int size, float minValue = 0, float maxValue = 1, bool manualSeed = false, int seedValue = 0){
    Point* points = new Point[size];
    // Implement point generation logic here
    return points;
  }
  static void println(Point* head, int size){
    stringstream os;
    os << "[";
    for (int idx = 0; idx < size - 1; idx++) {
      os << head[idx] << ", ";
    }
    if (size > 0)
      os << head[size - 1] << "]";
    else
      os << "]";
    cout << os.str() << endl;
  }
};

#endif /* POINT_H */
