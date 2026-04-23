#ifndef UTILS_H
#define UTILS_H
#include <iostream>
using namespace std;

class Utils {
public:
    void show(string msg) {
        cout << msg << endl;
    }

    void show(string msg, int num) {
        cout << msg << " " << num << endl;
    }
};

#endif