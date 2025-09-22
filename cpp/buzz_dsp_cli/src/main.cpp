#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << "buzz_dsp_cli: Hello World!" << std::endl;

    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <input.wav> [options]" << std::endl;
        return 1;
    }

    std::string input_file = argv[1];
    std::cout << "Input file: " << input_file << std::endl;

    // TODO: parse options, call DSP functions

    return 0;
}
