//
// Created by Laurens De Poel on 07/04/2021.
//
#include <vector>
#include <bitset>
#include <iostream>
#include <fstream>
#include <ios>

#ifndef HERCPP2_SOUNDFILE_HPP
#define HERCPP2_SOUNDFILE_HPP

#define WAVFILE "/Users/laurensdepoel/Development/HerCpp2/file1.wav"
#define WAVFILEW "/Users/laurensdepoel/Development/HerCpp2/hiddenW.wav"

class SoundFile {
protected:
    int subChunkSize = 16; // default chunk size
    int bitsPerSample = 16; // default bits per sample
    int dataStartIndex = 0; // default start index
    std::vector<std::bitset<8>> fileBuffer; // store bytes of file
public:
    virtual void ReadHiddenMassage() = 0;
    virtual void WriteHiddenMassage(std::string message) = 0;
    virtual void readChunkInfo();
    virtual void findDataStartIndex();


};


#endif //HERCPP2_SOUNDFILE_HPP
