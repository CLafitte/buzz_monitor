#pragma once
#include <vector>
#include <complex>
#include "wav_io.hpp"

struct PSDResult {
    double peak_frequency;
    double band_power;
};

class DSP {
public:
    // Compute simple Welch-style PSD using our own FFT
    static PSDResult welch_psd(const WavData& data, double band_start_hz, double band_end_hz);

private:
    // Recursive FFT
    static void fft(std::vector<std::complex<double>>& x);
};
