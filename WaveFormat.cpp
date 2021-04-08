//
// Created by Laurens De Poel on 07/04/2021.
//

#include "WaveFormat.hpp"

WaveFormat::WaveFormat(const std::string& filePath) {
    std::ifstream input(filePath, std::ios::binary);

    // copies all data into fileBuffer
    std::vector<std::bitset<8>> temp(std::istreambuf_iterator<char>(input), {});
    this->fileBuffer = std::move(temp);

    readChunkInfo();
    findDataStartIndex();
}

void WaveFormat::ReadHiddenMassage() {

    if (!CheckFile()) {
        return;
    }

    bool endOfMessage = false;
    while(!endOfMessage) {
        std::bitset<8> tmp = getHiddenByte();
        std::cout <<char(tmp.to_ulong());

        if(tmp == 0x00) {
            endOfMessage = true;
            std::cout << std::endl;
        }
    }
}

void WaveFormat::WriteHiddenMassage(std::string message) {

    if (CheckFile()) {
        return;
    }
    std::vector<std::bitset<8>> messageBytes;

    for (char ch : message) {
        messageBytes.emplace_back(ch);
    }
    // add stopByte
    messageBytes.emplace_back(00000000);

    // checks if message fits in file
    if (messageBytes.size() * 8  > this->fileBuffer.size() - (this->dataStartIndex + 4)) {
        std::cerr << "ERROR Message doesn't fit" << std::endl;
        return;
    }

    int bufferIndex = this->dataStartIndex;

    // as long as there is a message to be send keep replacing sound
    for (auto messageByte : messageBytes) {
        //std::cout << messageByte << std::endl;
        // for each bit in message byte replace byte in fileBuffer
        for (int i = 7; i >= 0; i--) {
            // load byte from index
            std::bitset<8> soundByte = this->fileBuffer.at(bufferIndex);

            //std::cout << soundByte << " insert " << messageByte[i] << std::endl;
            soundByte[0] = messageByte[i];
            // add 2 for for index
            //std::cout << soundByte << std::endl;
            this->fileBuffer[bufferIndex] = soundByte;

            bufferIndex += this->bitsPerSample/8;
        }
    }

    std::ofstream ofs;
    ofs.open(WAVFILEW, std::ofstream::out | std::ofstream::trunc | std::ofstream::binary);

    for (std::bitset<8> byte : this->fileBuffer)
    {
        char c = char(byte.to_ulong());
        ofs << c;
    }
    ofs.close();
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

bool WaveFormat::CheckFile() {
    if (this->subChunkSize == -1) {
        std::cerr << "File not a .WAV!" << std::flush;
        return false;
    } else if (this->dataStartIndex == -1) {
        std::cerr << "Data not found" << std::flush;
        return false;
    }
    return true;
}
