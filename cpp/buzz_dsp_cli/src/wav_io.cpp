#include "wav_io.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>

WavData WavReader::read(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) throw std::runtime_error("Cannot open file: " + filename);

    char riff[4];
    file.read(riff, 4);
    if (std::string(riff,4) != "RIFF") throw std::runtime_error("Not a RIFF file");

    file.seekg(22); // num channels
    uint16_t num_channels;
    file.read(reinterpret_cast<char*>(&num_channels), sizeof(num_channels));

    file.read(reinterpret_cast<char*>(&num_channels), sizeof(num_channels)); // redundant?
    
    file.seekg(24); // sample rate
    uint32_t sample_rate;
    file.read(reinterpret_cast<char*>(&sample_rate), sizeof(sample_rate));

    // skip to "data" chunk
    file.seekg(40); 
    uint32_t data_size;
    file.read(reinterpret_cast<char*>(&data_size), sizeof(data_size));

    std::vector<int16_t> samples(data_size / sizeof(int16_t));
    file.read(reinterpret_cast<char*>(samples.data()), data_size);

    return WavData{num_channels, sample_rate, samples};
