#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class FileManager {
public:
    static void saveUser(string u, string p) {
        ofstream file("data/users.txt", ios::app);
        file << u << " " << p << endl;
        file.close();
    }

    static bool validateUser(string u, string p) {
        ifstream file("data/users.txt");
        string user, pass;

        while (file >> user >> pass) {
            if (user == u && pass == p)
                return true;
        }
        return false;
    }

    static void saveTask(string user, string task, bool done = false) {
        ofstream file("data/tasks.txt", ios::app);
        file << user << "|" << task << "|" << done << endl;
        file.close();
    }

    static vector<pair<string, bool>> loadTasks(string user) {
        ifstream file("data/tasks.txt");
        vector<pair<string, bool>> tasks;

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string u, task, status;

            getline(ss, u, '|');
            getline(ss, task, '|');
            getline(ss, status, '|');

            if (u == user) {
                tasks.push_back({task, status == "1"});
            }
        }

        return tasks;
    }

    static void overwriteTasks(string user, vector<pair<string, bool>> tasks) {
        ifstream file("data/tasks.txt");
        vector<string> allLines;
        string line;

        while (getline(file, line)) {
            if (line.find(user + "|") != 0)
                allLines.push_back(line);
        }
        file.close();

        ofstream out("data/tasks.txt");

        for (auto l : allLines)
            out << l << endl;

        for (auto t : tasks)
            out << user << "|" << t.first << "|" << t.second << endl;

        out.close();
    }
};

#endif