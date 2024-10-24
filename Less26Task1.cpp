#pragma warning(disable : 4996)
#include <string>
#include <iostream>
#include <ctime>
#include <vector>
#include <ctime>

class Track {
private:
    std::string title{""};
    std::tm creationDate{};
    int duration{0};

public:
    void setTrack( std::string setTitle, std::tm& setCreationDate, int setDuration){
        title = { setTitle };
        creationDate = { setCreationDate };
        duration = { setDuration };
    }

    std::string getTitle() { return title; }

    std::tm getCreationDate()  { return creationDate; }

    int getDuration()  { return duration; }

    void printInfo() {
        std::time_t t = std::mktime(&creationDate);
        std::tm local = *std::localtime(&t);

        std::cout << "Title: " << title << ", Duration: " << duration << " sec, Created on: "
            << std::asctime(&local) << std::endl;
    }
};

class Player {
private:
    std::vector<Track> trackList;
    bool isPlaying{false};
    bool isPaused{false};
    int currentTrackIndex{-1};

public:

    void addTrack(Track& track) {
        trackList.push_back(track);
    }

    void setPlay(bool bPlay) {
        isPlaying = { bPlay };
    }

    void setPause(bool bPause) {
        isPaused = { bPause };
    }

    bool getPlay() { return isPlaying; }

    bool getPause() { return isPaused; }

    void play(std::string& title) {

        if (isPlaying && !isPaused) {
            std::cout << "Track is already playing.\n";
            return;
        } 

        for (int i = 0; i < trackList.size(); ++i) {
            if (trackList[i].getTitle() == title) {
                currentTrackIndex = i;
                isPlaying = true;
                isPaused = false;
                std::cout << "Playing ";
                trackList[currentTrackIndex].printInfo();
                return;
            }
        }
        std::cout << "Track not found.\n";
    }

    void pause() {
        if (!isPlaying && isPaused) {
            std::cout << "Cannot pause. Track is already paused.\n";
            return;
        }
        if (!isPlaying && !isPaused) {
            std::cout << "Cannot pause. Track is already stoped.\n";
            return;
        }
        isPlaying = { false };
        isPaused = { true };
        std::cout << "Track is paused.\n";
    }

    void next() {
        if (!isPlaying) {
            std::cout << "No track is currently playing.\n";
            return;
        }
        currentTrackIndex = std::rand() % trackList.size();
        isPaused = { false };
        isPlaying = { true };
        std::cout << "Playing next track: ";
        trackList[currentTrackIndex].printInfo();
    }

    void stop() {
        if (!isPlaying) {
            std::cout << "No track is currently playing.\n";
            return;
        }
        isPlaying = { false };
        isPaused = { false };
        currentTrackIndex = -1;
        std::cout << "Track stopped.\n";
    }
};

int main() {
    Player* player = new Player;

    std::tm creationDate {};
    creationDate.tm_year = 124; 
    creationDate.tm_mon = 9;    
    creationDate.tm_mday = 21; 


    // Добавляем несколько треков
    Track* track1 = new Track;
    Track* track2 = new Track;
    Track* track3 = new Track;

    track1->setTrack("Beautiful Day", creationDate, 240);
    track2->setTrack("Lose Yourself", creationDate, 320);
    track3->setTrack("Imagine", creationDate, 180);

    player->addTrack(*track1);
    player->addTrack(*track2);
    player->addTrack(*track3);

    std::string command{""};

    while (command != "exit") {
        std::cout << "Enter command (play, pause, next, stop, exit): ";
        std::cin >> command;

        if (command == "play") {
            bool isPlaying{ player->getPlay() }, isPaused{ player->getPause() };
            
            if (!isPlaying && isPaused) {
                player->setPlay(true);
                player->setPause(false);
                std::cout << "Track is played.\n";
                continue;
            }
            std::cout << "Enter track title: ";
            std::string title;
            std::cin.ignore();
            std::getline(std::cin, title);
            player->play(title);
        }
        else if (command == "pause") {
            player->pause();
        }
        else if (command == "next") {
            player->next();
        }
        else if (command == "stop") {
            player->stop();
        }
        else if (command == "exit") {
            break;
        }
        else {
            std::cout << "Unknown command.\n";
        }
    }

    delete track1, track2, track3, player;
    track1 = track2 = track3 = nullptr;
    player = nullptr;

    return 0;
}
