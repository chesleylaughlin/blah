#ifndef USER_H
#define USER_H
#include <iostream>
using namespace std;

class User {
protected:
    string username;
    string password;

public:
    User() {}

    User(string u, string p) {
        username = u;
        password = p;
    }

    virtual void menu() = 0; // pure virtual

    string getUsername() {
        return username;
    }

    virtual ~User() {}
};

#endif