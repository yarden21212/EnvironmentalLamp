#include "Music.h"
#include <fstream>   // required for std::ifstream
#include <string_view>
#include <iostream>
#include <windows.h>


/* How to check suffix: https://stackoverflow.com/questions/874134/find-out-if-string-ends-with-another-string-in-c */
bool testSuffix(std::string const& fullString, std::string const& suffix) {
    if (fullString.length() >= suffix.length()) {
        return (0 == fullString.compare(fullString.length() - suffix.length(), suffix.length(), suffix));
    }
    else {
        return false;
    }
}


Music::Music() : path(""), isPlaying(false) {}

void Music::setSoundPath(const std::string& path) {
    this->path = path;
}

/* How to use PlaySound https://stackoverflow.com/questions/9961949/playsound-in-c-console-application */
void Music::playMusic() {
    std::string soundPath = path;      // make sure it's initialized
    std::ifstream infile(soundPath);
    if (!infile) {
        std::cerr << "Given file doesn't exist!" << std::endl;
        return;
    }
    if (!testSuffix(soundPath, ".wav"))
    {
        std::cerr << "Invalid file format. Please provide a .wav file." << std::endl;
        return;
    }
    
    PlaySoundA(path.c_str(), NULL, SND_FILENAME | SND_ASYNC);
    isPlaying = true;
}
void Music::stopMusic() {
	isPlaying = false;
	PlaySoundA(NULL, 0, 0);
}

void Music::setPlayStatus(bool newStatus) {
    isPlaying = newStatus;
}
bool Music::getPlayStatus() {
    return isPlaying;
}