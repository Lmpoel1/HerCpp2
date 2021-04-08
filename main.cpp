#include <iostream>
#include <fstream>
#include <ios>
#include <vector>
#include <bitset>

#include <filesystem>
#include "WaveFormat.hpp"

namespace fs = std::__fs::filesystem;

#define AUDIOFILES "/Users/laurensdepoel/Development/HerCpp2/audiofiles/"


std::string ReadLine(const std::string& messageToUser) {
    std::string inputFromUser;
    std::cout << messageToUser << std::endl;
    while(inputFromUser.empty()) {
        getline(std::cin >> std::noskipws, inputFromUser);
    }
    return inputFromUser;
}

void ReadMessage() {
    std::cout << "List of audio files:" << std::endl;
    for (const auto & fileIt : fs::directory_iterator(AUDIOFILES)) {
        std::cout << fileIt.path().filename() << std::endl;
    }
    // select wav file
    std::string filePath = ReadLine("Enter filename.");
    WaveFormat wave(AUDIOFILES + filePath);

    wave.ReadHiddenMassage();
}

void WriteMessage() {
    std::cout << "List of audio files:" << std::endl;
    for (const auto & fileIt : fs::directory_iterator(AUDIOFILES)) {
        std::cout << fileIt.path().filename() << std::endl;
    }

    // select wav file
    std::string filePath = ReadLine("Enter filename.");
    WaveFormat wave(AUDIOFILES + filePath);
    // enter message
    std::string message = ReadLine("Enter message.");
    // write message
    wave.WriteHiddenMassage(message);
}

bool PrintMenu()
{
    std::cout << "********** Main Menu **********" << std::endl;
    std::cout << "1): Read Message From Sound File" << std::endl;
    std::cout << "2): Hide Message In Sound File" << std::endl;
    std::cout << "3): Exit" << std::endl;

    std::string myChoice = ReadLine("Select option.");

    if (myChoice == "1") {
        ReadMessage();
        std::string wait = ReadLine("Enter a key to continue!");
        return true;
    }
    else if (myChoice == "2") {
        WriteMessage();
        std::string wait = ReadLine("Enter a key to continue!");
        return true;
    }
    else if (myChoice == "3") {
        std::cout << "Close application." << std::endl;
        return false;
    }
    else {
        std::cout << "ERROR! You have selected an invalid choice." << std::endl;
        return true;
    }
}

int main()
{
    bool status = true;
    while(status) {
        status = PrintMenu();
    }
    return 0;
}
