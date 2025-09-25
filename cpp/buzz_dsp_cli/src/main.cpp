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
        // --- Read WAV file ---
        WavData data = WavReader::read(input_file);
        std::cout << "Channels: " << data.num_channels
                  << ", Sample rate: " << data.sample_rate
                  << ", Num samples: " << data.samples.size() << std::endl;

        // --- Print first 10 samples ---
        std::cout << "First 10 samples: ";
        for (size_t i = 0; i < 10 && i < data.samples.size(); ++i)
            std::cout << data.samples[i] << " ";
        std::cout << std::endl;

        // --- Run DSP analysis ---
        PSDResult result = DSP::welch_psd(data, 200.0, 800.0);
        std::cout << "DSP Results:\n";
        std::cout << "  Peak frequency: " << result.peak_frequency << " Hz\n";
        std::cout << "  Band power: " << result.band_power << std::endl;

    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
