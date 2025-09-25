#include "dsp.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <complex>

using cpx = std::complex<double>;

// Recursive FFT
void DSP::fft(std::vector<cpx>& x) {
    size_t N = x.size();
    if (N <= 1) return;

    // Split into even and odd
    std::vector<cpx> even(N/2), odd(N/2);
    for (size_t i=0; i<N/2; ++i) {
        even[i] = x[i*2];
        odd[i] = x[i*2 + 1];
    }

    // Recursive calls
    fft(even);
    fft(odd);

    // Combine
    for (size_t k=0; k<N/2; ++k) {
        cpx t = std::polar(1.0, -2 * M_PI * k / N) * odd[k];
        x[k] = even[k] + t;
        x[k + N/2] = even[k] - t;
    }
}

// Simple PSD using FFT
PSDResult DSP::welch_psd(const WavData& data, double band_start_hz, double band_end_hz) {
    size_t N = data.samples.size();
    if (N == 0) return PSDResult{0.0, 0.0};

    // Convert samples to complex
    std::vector<cpx> x(N);
    for (size_t i=0; i<N; ++i)
        x[i] = cpx(static_cast<double>(data.samples[i]), 0.0);

    // Compute FFT
    fft(x);

    double df = static_cast<double>(data.sample_rate) / N;
    double band_power = 0.0;
    double peak_val = 0.0;
    size_t peak_index = 0;

    for (size_t k = 0; k < N/2; ++k) {  // only positive frequencies
        double freq = k * df;
        double mag = std::abs(x[k]);

        if (freq >= band_start_hz && freq <= band_end_hz)
            band_power += mag * mag;

        if (mag > peak_val) {
            peak_val = mag;
            peak_index = k;
        }
    }

    double peak_frequency = peak_index * df;
    return PSDResult{peak_frequency, band_power};
}
