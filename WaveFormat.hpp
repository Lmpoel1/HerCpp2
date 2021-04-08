//
// Created by Laurens De Poel on 07/04/2021.
//
#include "SoundFile.hpp"

#ifndef HERCPP2_WAVE_HPP
#define HERCPP2_WAVE_HPP

class WaveFormat: SoundFile {
public:
    WaveFormat();
    void ReadHiddenMassage() override;
    void WriteHiddenMassage(std::string message) override;

private:
    std::bitset<8> getHiddenByte();

};


#endif //HERCPP2_WAVE_HPP
