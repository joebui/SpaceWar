#ifndef COSC2131_PROJECT_S3445846_S3372771_DATABASE_HPP
#define COSC2131_PROJECT_S3445846_S3372771_DATABASE_HPP

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>

using namespace sf;

class HighScore {
private:
    sqlite3 *db;
    int rc;
    char *errorMsg;

    Text title, name, line, info;
    Font font, font1;

public:
    static vector<string> scores;

public:
    HighScore() {
        rc = sqlite3_open("scores.db", &db);
        if (rc) {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
            exit(0);
        }else{
            fprintf(stdout, "Opened database successfully\n");
        }

        font.loadFromFile("fonts/OpenSans-Bold.ttf");
        font1.loadFromFile("fonts/Starjedi.ttf");
        title.setString("Hall of Fame");
    }

    void saveResult(int level, int score) {
        string sql = "INSERT INTO achievement (level, score) VALUES (" + to_string(level) + "," + to_string(score) + ");";
        rc = sqlite3_exec(db, sql.c_str(), callback, 0, &errorMsg);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", errorMsg);
            sqlite3_free(errorMsg);
        } else {
            fprintf(stdout, "Records created successfully\n");
        }
    }

    void listTopTenScores() {
        scores.clear();
        string sql = "SELECT * FROM achievement ORDER BY level DESC LIMIT 10";
        rc = sqlite3_exec(db, sql.c_str(), callback, 0, &errorMsg);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", errorMsg);
            sqlite3_free(errorMsg);
        } else {
            fprintf(stdout, "Successful query\n");
        }
    }

    static int callback(void *NotUsed, int argc, char **argv, char **azColName){
        string row;
        row.append(argv[1]);
        row.append("\t\t\t\t\t\t\t");
        row.append(argv[2]);
        scores.push_back(row);

        return 0;
    }

    void print(RenderWindow &window) {
        title.setFont(font1);
        title.setCharacterSize(60); // in pixels, not points!
        title.setColor(sf::Color::Yellow);
        title.setStyle(sf::Text::Bold);
        sf::FloatRect textRect = title.getLocalBounds();
        title.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        title.setPosition(sf::Vector2f(1024/2.0f,720/8.0f));

        name.setFont(font);
        name.setString("Level\t\tScore");
        name.setCharacterSize(30); // in pixels, not points!
        textRect = name.getLocalBounds();
        name.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        name.setPosition(sf::Vector2f(1024/2.0f,720/4.0f));

        line.setFont(font);
        string result;
        for (unsigned int i = 0; i < scores.size(); ++i) {
            result.append(scores[i]);
            result.append("\n");
        }
        line.setString(result);
        line.setCharacterSize(20); // in pixels, not points!
//        textRect = line.getLocalBounds();
        line.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        line.setPosition(sf::Vector2f(1024/2.0f,720/3.0f));

        info.setFont(font);
        info.setString("Press Esc to return");
        info.setCharacterSize(30); // in pixels, not points!
        info.setColor(Color::Green);
        textRect = info.getLocalBounds();
        info.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        info.setPosition(sf::Vector2f(1024/2.0f,720/1.2f));

        window.draw(title);
        window.draw(name);
        window.draw(line);
        window.draw(info);
    }
};

vector<string> HighScore::scores;

#endif //COSC2131_PROJECT_S3445846_S3372771_DATABASE_HPP
