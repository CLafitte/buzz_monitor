#pragma once
#include <string>
#include <vector>
#include <cstdint>

struct WavData {
    uint16_t num_channels;
    uint32_t sample_rate;
    std::vector<int16_t> samples; // mono interleaved
};

class WavReader {
public:
    static WavData read(const std::string& filename);
};
