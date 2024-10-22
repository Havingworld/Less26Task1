#include <string>
#include <iostream>
#include <ctime>

class Track {
private:
    std::string title;
    std::tm creationDate;
    int duration; // в секундах

public:
    Track(const std::string& title, const std::tm& creationDate, int duration)
        : title(title), creationDate(creationDate), duration(duration) {}

    std::string getTitle() const { return title; }
    std::tm getCreationDate() const { return creationDate; }
    int getDuration() const { return duration; }

    void printInfo() const {
        std::cout << "Title: " << title << ", Duration: " << duration << " sec, Created on: "
            << std::asctime(&creationDate);
    }
};
