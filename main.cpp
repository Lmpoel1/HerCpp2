#include <iostream>
#include <fstream>
#include <ios>
#include <vector>
#include <bitset>

#include "WaveFormat.hpp"

/*#define WAVFILE "/Users/laurensdepoel/Development/HerCpp2/file1.wav"
#define WAVFILEW "/Users/laurensdepoel/Development/HerCpp2/hiddenW.wav"*/


std::bitset<8> writeHiddenByte(std::vector<std::bitset<8>>& buffer){
    std::bitset<8> byte = 0;
    for (int i = 0; i < 8; i++) {
        std::bitset<8> var = buffer.front();
        buffer.erase(buffer.begin());
        buffer.erase(buffer.begin());

        byte = byte | var << 7 >> i;

        //std::cout << var << " | " << (var << 7 >> i) << " | " << byte << std::endl;
    }
    return byte;
}
/*
 * 1. lezen van fileBuffer
 * 2. vertalen van message
 * 3. per byte data in fileBuffer zetten
 * 4. fileBuffer schrijven
 * */


void writeFile() {
    std::ifstream input(WAVFILE, std::ios::binary);

    // copies all data into fileBuffer
    std::vector<std::bitset<8>> buffer(std::istreambuf_iterator<char>(input), {});
    std::vector<std::bitset<8>> messageBytes;

    // message to bits
    std::string message = "Dit werkt jaja";
    for (char ch : message) {
        messageBytes.emplace_back(ch);
    }
    // add stopByte
    messageBytes.emplace_back(00000000);

/*    for (auto var : messageBytes) {
        std::cout << var << " | " << char(var.to_ulong()) << std::endl;
    }*/
    //start adress

    int bufferIndex = 0;
    std::vector<int> pattern {0x64, 0x61, 0x74, 0x61};
    auto res = std::search(std::begin(buffer), std::end(buffer), std::begin(pattern), std::end(pattern));
    if(res == std::end(buffer)) {
        std::cout << "Couldn't find it.\n";
    } else {

        bufferIndex = res - buffer.begin() + 8;
        std::cout << "Found it at: " << bufferIndex << std::endl;
    }
    // as long as there is a message to be send keep replacing sound
    for (auto messageByte : messageBytes) {
        std::cout << messageByte << std::endl;
        // for each bit in message byte replace byte in fileBuffer
        for (int i = 7; i >= 0; i--) {
            // load byte from index
            std::bitset<8> soundByte = buffer.at(bufferIndex);

            std::cout << soundByte << " insert " << messageByte[i] << std::endl;
            soundByte[0] = messageByte[i];
            // add 2 for for index
            std::cout << soundByte << std::endl;
            buffer[bufferIndex] = soundByte;

            bufferIndex +=2;
        }
    }

    std::ofstream ofs;
    ofs.open(WAVFILEW, std::ofstream::out | std::ofstream::trunc | std::ofstream::binary);

    for (std::bitset<8> byte : buffer)
    {
        char c = char(byte.to_ulong());
        ofs << c;
    }

    ofs.close();

}
void ReadMessage() {
    WaveFormat wave;
    wave.ReadHiddenMassage();
}

void WriteMessage() {
    WaveFormat wave;
    std::string message;
    std::cout << "Enter hidden message" << std::endl;
    std::cin >> message;
    wave.WriteHiddenMassage(message);
}



bool PrintMenu()
{
    int myChoice = 0;

    std::cout << "********** Main Menu **********" << std::endl;
    std::cout << "1): Read Message From Sound File" << std::endl;
    std::cout << "2): Hide Message In Sound File" << std::endl;
    std::cout << "3): Exit" << std::endl;
    std::cin >> myChoice;
    std::string waitOnInput;
    switch(myChoice)
    {

        case 1:

            ReadMessage();
            return true;
        case 2:
            WriteMessage();
            return true;
        case 3:
            std::cout << "Close application." << std::endl;
            return false;
        default:
            std::cout << "ERROR! You have selected an invalid choice." << std::endl;

            return true;
    }
}

int main()
{
    /*bool status = true;
    while(status) {
        status = PrintMenu();
    }*/
    bool status = PrintMenu();
    return 0;
}
