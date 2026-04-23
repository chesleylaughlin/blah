#ifndef TASK_H
#define TASK_H
#include <iostream>
using namespace std;

class Task {
private:
    string title;
    bool completed;

public:
    Task() {
        title = "";
        completed = false;
    }

    Task(string t) {
        title = t;
        completed = false;
    }

    void markDone() {
        completed = true;
    }

    string getTask() {
        if (completed)
            return title + " [Done]";
        else
            return title + " [Pending]";
    }
};

#endif