#include <iostream>
#include <iomanip>
#include "list/XArrayList.h"
#include "util/Point.h"
using namespace std;

void array1() {
  XArrayList<int> list;
  for (int i = 0; i < list.size(); i++) list.add(i);

  string output = list.toString() + "\nsize=" + to_string(list.size()) +
                  "\nempty=" + to_string(list.empty());

  cout << "Output:" << output << endl;
}

void array2() {
  XArrayList<int> list;
  list.add(0);
  list.add(1);
  list.add(2);
  list.removeAt(1);
  list.add(1, 1);
  list.removeAt(2);

  string output = list.toString() + ";size=" + to_string(list.size()) +
                  ";empty=" + to_string(list.empty());

  cout << "Output:" << output << endl;
}

void array3() {
  XArrayList<Point> list(0, &Point::pointEQ);
  list.add(Point(3.f, 4.f));
  list.add(Point(4.f, 3.f));

  int index1 = list.indexOf(Point(3.f, 5.f));
  string output1 = "Index of item 1: " + to_string(index1);
  int index2 = list.indexOf(Point(4.f, 3.f));
  string output2 = "Index of item 2: " + to_string(index2);

  cout << "Output1:" << output1 << endl;
  cout << "Output2:" << output2 << endl;
}

void array4() {
  XArrayList<Point *> list(&XArrayList<Point *>::free, &Point::pointEQ);
  list.add(new Point(23.2f, 25.4f));
  list.add(new Point(24.6f, 23.1f));
  list.add(new Point(12.5f, 22.3f));

  stringstream output;
  output << "[";
  for (auto it = list.begin(); it != list.end(); ++it) {
    if (it != list.begin()) output << ", ";
    output << **it;
  }
  output << "]";

  list.clear();

  cout << "Output:" << output.str() << endl;
}

void array5() {
  XArrayList<Point *> list(&XArrayList<Point *>::free, &Point::pointEQ);
  list.add(new Point(23.2f, 25.4f));
  list.add(new Point(24.6f, 23.1f));
  list.add(new Point(12.5f, 22.3f));

  auto interator = list.begin();
  interator.remove(&Point::pointRemove);
  interator++;
  interator.remove(&Point::pointRemove);

  stringstream output;
  output << "[";
  for (auto it = list.begin(); it != list.end(); ++it) {
    if (it != list.begin()) output << ", ";
    output << **it;
  }
  output << "]";

  list.clear();

  cout << "Output:" << output.str() << endl;
}