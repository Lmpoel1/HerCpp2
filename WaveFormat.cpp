//
// Created by Laurens De Poel on 07/04/2021.
//

#include "WaveFormat.hpp"

WaveFormat::WaveFormat() {
    std::ifstream input(WAVFILEW, std::ios::binary);

    // copies all data into fileBuffer
    std::vector<std::bitset<8>> temp(std::istreambuf_iterator<char>(input), {});
    this->fileBuffer = std::move(temp);

    readChunkInfo();
    findDataStartIndex();
}


void WaveFormat::ReadHiddenMassage() {

    //fileBuffer.erase(fileBuffer.begin(), fileBuffer.begin() + this->dataStartIndex);

    bool endOfMessage = false;
    while(!endOfMessage) {
        std::bitset<8> tmp = getHiddenByte();
        std::cout <<char(tmp.to_ulong());

        if(tmp == 0x00) {
            endOfMessage = true;
        }

    }

}

void WaveFormat::WriteHiddenMassage(std::string message) {
    std::cout << message << std::endl;
}



std::bitset<8> WaveFormat::getHiddenByte() {
    std::bitset<8> byte = 0;
    int bufferIndex = this->dataStartIndex;

    for (int i = 0; i < 8; i++) {
        std::bitset<8> soundByte = this->fileBuffer.at(bufferIndex);
        //bufferIndex += 2;
        bufferIndex += this->bitsPerSample / 8;

        byte = byte | soundByte << 7 >> i;
        //std::cout << soundByte << " | " << (soundByte << 7 >> i) << " | " << byte << std::endl;
    }
    this->dataStartIndex = bufferIndex;
    //std::cout <<char(byte.to_ulong());
    return byte;
}
