#include "wav_io.hpp"
#include "dsp.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <input.wav>\n";
        return 1;
    }

    std::string input_file = argv[1];

    try {
        WavData data = WavReader::read(input_file);
        std::cout << "Channels: " << data.num_channels
                  << ", Sample rate: " << data.sample_rate
                  << ", Num samples: " << data.samples.size() << std::endl;

        PSDResult result = DSP::welch_psd(data, 200.0, 800.0);
        std::cout << "Peak frequency: " << result.peak_frequency
                  << " Hz, Band power: " << result.band_power << std::endl;

    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
