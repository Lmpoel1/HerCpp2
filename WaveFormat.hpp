//
// Created by Laurens De Poel on 07/04/2021.
//
#include "SoundFile.hpp"

#ifndef HERCPP2_WAVE_HPP
#define HERCPP2_WAVE_HPP

class WaveFormat: SoundFile {
public:
    WaveFormat(const std::string& filePath);
    void ReadHiddenMassage() override;
    void WriteHiddenMassage(std::string message) override;

private:
    std::bitset<8> getHiddenByte();
    bool CheckFile();

};


#endif //HERCPP2_WAVE_HPP
