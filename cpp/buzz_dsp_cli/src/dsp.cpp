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

