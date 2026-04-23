#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace std;

struct Task {
    string title;
    int status;
    int priority;
    string deadline;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 700), "Task Manager Pro");
    window.setFramerateLimit(60);

    sf::Font font;
    font.loadFromFile("arial.ttf");

    // UI STATE
    bool loggedIn = false;

    // LOGIN
    string username = "", password = "";
    bool typingUser = true;

    // TASK DATA
    vector<Task> tasks = {
        {"Study", 0, 2, "25 Sep"},
        {"Gym", 0, 1, "Daily"},
        {"Project", 1, 2, "30 Sep"}
    };

    // SEARCH
    string search = "";
    bool typingSearch = false;

    while (window.isOpen()) {
        sf::Event event;
        auto mouse = sf::Mouse::getPosition(window);

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::TextEntered) {
                char ch = static_cast<char>(event.text.unicode);

                if (!loggedIn) {
                    if (typingUser) {
                        if (event.text.unicode == 8 && !username.empty())
                            username.pop_back();
                        else if (event.text.unicode >= 32 && event.text.unicode <= 126)
                            username += ch;
                    } else {
                        if (event.text.unicode == 8 && !password.empty())
                            password.pop_back();
                        else if (event.text.unicode >= 32 && event.text.unicode <= 126)
                            password += ch;
                    }
                } else if (typingSearch) {
                    if (event.text.unicode == 8 && !search.empty())
                        search.pop_back();
                    else if (event.text.unicode >= 32 && event.text.unicode <= 126)
                        search += ch;
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {

                // LOGIN SCREEN
                if (!loggedIn) {
                    if (mouse.y > 200 && mouse.y < 240)
                        typingUser = true;
                    else if (mouse.y > 260 && mouse.y < 300)
                        typingUser = false;
                    else if (mouse.y > 320 && mouse.y < 360)
                        loggedIn = true; // simple login
                }

                // DASHBOARD
                else {
                    typingSearch = (mouse.y > 630);

                    for (int i = 0; i < tasks.size(); i++) {
                        int x = 250 + tasks[i].status * 300;
                        int y = 120 + i * 70;

                        if (sf::FloatRect(x, y, 250, 60).contains(mouse.x, mouse.y))
                            tasks[i].status = (tasks[i].status + 1) % 3;
                    }
                }
            }
        }

        window.clear(sf::Color(10, 10, 25));

        if (!loggedIn) {
            // LOGIN UI
            sf::Text t("LOGIN", font, 28);
            t.setPosition(550, 100);

            sf::Text u(username, font, 18);
            u.setPosition(500, 210);

            sf::Text p(string(password.size(), '*'), font, 18);
            p.setPosition(500, 270);

            sf::Text btn("LOGIN", font, 18);
            btn.setPosition(550, 330);

            window.draw(t);
            window.draw(u);
            window.draw(p);
            window.draw(btn);
        } else {

            // SEARCH BAR
            sf::Text s("Search: " + search, font, 16);
            s.setPosition(250, 640);
            window.draw(s);

            vector<string> titles = {"TO DO", "IN PROGRESS", "DONE"};

            for (int c = 0; c < 3; c++) {
                sf::Text t(titles[c], font, 18);
                t.setPosition(250 + c * 300, 80);
                window.draw(t);
            }

            for (int i = 0; i < tasks.size(); i++) {

                if (!search.empty() &&
                    tasks[i].title.find(search) == string::npos)
                    continue;

                int x = 250 + tasks[i].status * 300;
                int y = 120 + i * 70;

                sf::RectangleShape card({250, 60});
                card.setPosition(x, y);

                if (tasks[i].priority == 2)
                    card.setFillColor(sf::Color(150, 50, 50));
                else if (tasks[i].priority == 1)
                    card.setFillColor(sf::Color(150, 150, 50));
                else
                    card.setFillColor(sf::Color(50, 100, 50));

                sf::Text txt(tasks[i].title, font, 16);
                txt.setPosition(x + 10, y + 10);

                sf::Text d(tasks[i].deadline, font, 12);
                d.setPosition(x + 10, y + 35);

                window.draw(card);
                window.draw(txt);
                window.draw(d);
            }
        }

        window.display();
    }

    return 0;
}