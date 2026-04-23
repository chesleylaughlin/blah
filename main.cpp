#include <iostream>
#include <vector>
#include "task.h"
#include "admin.h"
#include "fileManager.h"

using namespace std;

class NormalUser : public User {
private:
    vector<pair<string, bool>> tasks;

public:
    NormalUser(string u, string p) : User(u, p) {
        tasks = FileManager::loadTasks(username);
    }

    void addTask() {
        string t;
        cout << "Enter task: ";
        cin >> t;

        tasks.push_back({t, false});
        FileManager::saveTask(username, t);

        cout << "Task added!\n";
    }

    void viewTasks() {
        if (tasks.empty()) {
            cout << "No tasks\n";
            return;
        }

        for (int i = 0; i < tasks.size(); i++) {
            cout << i + 1 << ". " << tasks[i].first
                 << (tasks[i].second ? " [Done]" : " [Pending]") << endl;
        }
    }

    void markDone() {
        int n;
        viewTasks();
        cout << "Enter task number: ";
        cin >> n;

        if (n < 1 || n > tasks.size()) return;

        tasks[n - 1].second = true;
        FileManager::overwriteTasks(username, tasks);

        cout << "Marked as done!\n";
    }

    void deleteTask() {
        int n;
        viewTasks();
        cout << "Enter task number: ";
        cin >> n;

        if (n < 1 || n > tasks.size()) return;

        tasks.erase(tasks.begin() + (n - 1));
        FileManager::overwriteTasks(username, tasks);

        cout << "Task deleted!\n";
    }

    void menu() override {
        int ch;
        while (true) {
            cout << "\n[USER MENU]\n";
            cout << "1. Add Task\n2. View Tasks\n3. Mark Done\n4. Delete Task\n5. Logout\n";
            cin >> ch;

            if (ch == 1) addTask();
            else if (ch == 2) viewTasks();
            else if (ch == 3) markDone();
            else if (ch == 4) deleteTask();
            else if (ch == 5) break;
        }
    }
};

int main() {
    int choice;
    string username, password;

    while (true) {
        cout << "\n1. Register\n2. Login\n3. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;

            FileManager::saveUser(username, password);
            cout << "Registered!\n";
        }

        else if (choice == 2) {
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;

            if (!FileManager::validateUser(username, password)) {
                cout << "Invalid login!\n";
                continue;
            }

            User* user;

            if (username == "admin")
                user = new Admin(username, password);
            else
                user = new NormalUser(username, password);

            user->menu();
            delete user;
        }

        else if (choice == 3) break;
    }

    return 0;
}