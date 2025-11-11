#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "test/test_DLinkedList.h"
#include "test/test_XArrayList.h"
#include "test/test_Data.h"

using namespace std;

void (*func_ptr[14])() = {
    array1,
    array2,
    array3,
    array4,
    array5,
    linkedList1,
    linkedList2,
    linkedList3,
    linkedList4,
    data1,
    data2,
    data3,
    data4,
    data5
};

void run(int func_idx)
{
    func_ptr[func_idx]();
}

int main(int argc, char **argv)
{
    for (int i = 0; i < 14; i++) {
        cout << "Running test " << i + 1 << "..." << endl;
        run(i);
    }
    return 0;
}