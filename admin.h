#ifndef ADMIN_H
#define ADMIN_H
#include "user.h"
#include <iostream>
using namespace std;

class Admin : public User {
public:
    Admin(string u, string p) : User(u, p) {}

    void menu() override {
        cout << "\n[ADMIN PANEL]\n";
        cout << "1. View All Tasks\n";
    }
};

#endif