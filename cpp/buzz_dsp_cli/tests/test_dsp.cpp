#include "dsp.hpp"
#include "wav_io.hpp"
#include <iostream>
#include <vector>
#include <cmath>

int main() {
    // --- Generate a synthetic sine wave ---
    double fs = 1024;          // sample rate
    double f = 50.0;           // sine frequency
    size_t N = 1024;           // number of samples
    WavData data;
    data.num_channels = 1;
    data.sample_rate = static_cast<uint32_t>(fs);
    data.samples.resize(N);

    for (size_t i = 0; i < N; ++i) {
        data.samples[i] = static_cast<int16_t>(32767.0 * std::sin(2.0 * M_PI * f * i / fs));
    }

    // --- Run DSP ---
    PSDResult result = DSP::welch_psd(data, 40.0, 60.0);

    // --- Check results ---
    std::cout << "Test DSP on sine wave:\n";
    std::cout << "  Expected peak frequency: ~50 Hz\n";
    std::cout << "  Computed peak frequency: " << result.peak_frequency << " Hz\n";
    std::cout << "  Band power: " << result.band_power << std::endl;

    return 0;
}
