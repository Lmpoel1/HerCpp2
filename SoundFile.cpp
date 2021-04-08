//
// Created by Laurens De Poel on 07/04/2021.
//


#include "SoundFile.hpp"

void SoundFile::readChunkInfo() {
    std::vector<int> pattern {0x66, 0x6d, 0x74, 0x20};

    auto res = std::search(std::begin(fileBuffer), std::end(fileBuffer), std::begin(pattern), std::end(pattern));
    if(res == std::end(fileBuffer)) {
        std::cout << "Couldn't find FMT.\n";
    } else {
        std::cout << "Found FMT Index: " <<  res - fileBuffer.begin()<< std::endl;

        // get chunksize
        int SubChunkOffset = 4;
        this->subChunkSize = (res + SubChunkOffset)->to_ulong();
        std::cout << "File ChunkSize is: " <<  this->subChunkSize<< std::endl;


        // get bitsPerSample
        int bitsOffset = 22; // refactor
        this->bitsPerSample = (res + bitsOffset)->to_ulong();
        std::cout << "File bits per sample is: " <<  this->bitsPerSample<< std::endl;
    }
}

void SoundFile::findDataStartIndex() {
    std::vector<int> pattern {0x64, 0x61, 0x74, 0x61};

    auto res = std::search(std::begin(fileBuffer), std::end(fileBuffer), std::begin(pattern), std::end(pattern));
    if(res == std::end(fileBuffer)) {
        std::cout << "Couldn't find DATA.\n";
    } else {

        this->dataStartIndex = res - fileBuffer.begin() + 8; // 8 = two bytes
        std::cout << "Found data Start Index: " << this->dataStartIndex << std::endl;
    }
}


