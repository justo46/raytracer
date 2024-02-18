//
// Created by Julius Stotz on 10.01.24.
//

#ifndef RAY_TRACING_OUTPUTFILE_H
#define RAY_TRACING_OUTPUTFILE_H

#include <fstream>
#include "Image.h"

class OutputFile {
public:
    OutputFile() = delete;

    OutputFile(const std::string &filename)
            : outFile(filename){
        if (!outFile.is_open()) {
            std::cerr << "Failed to open file for writing." << std::endl;
        }
        write_header();
    }

    OutputFile(const std::string &filename, Image _image)
            : outFile(filename),
              image(_image) {
        if (!outFile.is_open()) {
            std::cerr << "Failed to open file for writing." << std::endl;
        }
        write_header();
    }

    // move constructor
    OutputFile(OutputFile &&other) noexcept {
        outFile = std::move(other.outFile);
        image = std::move(other.image);
    }

    // I should implement/delete the other constructors too

    ~OutputFile() {
        if (outFile.is_open()) {
            outFile.close();
        }
    }

    // Overload the << operator to write data to the file
    template<typename T>
    OutputFile &operator<<(const T &data) {
        if (!outFile.is_open()) {
            std::cerr << "Attempted to write to a closed file." << std::endl;
            return *this;
        }
        outFile << data;
        return *this;
    }

    void write_header() {
        outFile << "P3\n" << image.width << ' ' << image.height << "\n255\n";
    }

private:
    std::ofstream outFile;
    Image image = Image(1000, 16.0 / 9.0);
};

#endif //RAY_TRACING_OUTPUTFILE_H
