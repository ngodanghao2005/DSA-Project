#include <iostream>
#include <iomanip>
#include "list/DLinkedList.h"
#include "util/Point.h"
using namespace std;

void linkedList1() {
  DLinkedList<int> list;
  for (int i = 0; i < list.size(); i++) list.add(i);

  string output = list.toString() + "\nsize=" + to_string(list.size()) +
                  "\nempty=" + to_string(list.empty());

  cout << "Output:" << output << endl;
}

void linkedList2() {
  DLinkedList<int> list;
  list.add(0, 0);
  list.add(0, 1);
  list.add(0, 2);

  string output = "";
  try {
    list.removeAt(3);
  } catch (const std::out_of_range &e) {
    output = "Error: Out of range exception: " + string(e.what());
  }
  cout << "Output:" << output << endl;
}

void linkedList3() {
  DLinkedList<Point *> list(&DLinkedList<Point *>::free, &Point::pointEQ);
  list.add(new Point(23.2f, 25.4f));
  list.add(new Point(24.6f, 23.1f));
  list.add(new Point(12.5f, 22.3f));

  Point* p = new Point(12.5f, 22.3f);
  cout << "IndexOf: " << *p << " at: " << list.indexOf(p) << endl;
  delete p;

  string output = list.toString(&Point::point2str);

  cout << "Output:" << output << endl;
}

void linkedList4() {
  DLinkedList<Point *> list(&DLinkedList<Point *>::free, &Point::pointEQ);
  list.add(new Point(23.2f, 25.4f));
  list.add(new Point(24.6f, 23.1f));
  list.add(new Point(12.5f, 22.3f));

  stringstream output;
  output << "[";
  for (auto it = list.bbegin(); it != list.bend(); ++it) {
    if (it != list.bbegin()) output << ", ";
    output << **it;
  }
  output << "]";

  list.clear();

  cout << "Output:" << output.str() << endl;
}