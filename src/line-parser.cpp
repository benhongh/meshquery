#include <sstream>
#include "line-parser.hpp"

namespace hongbin {
    void readLines(std::istream& stream, std::function<void(const std::string&)> lineReader) {
        while (stream) {
            std::string line{};
            getline(stream, line);
            if (line == "#")
                break;
            
            lineReader(line);
        }
    }

    void parseLines(std::istream& stream, std::function<void(double, double, double)> lineProcessor) {
        readLines(stream, [&](const std::string& line){
            std::istringstream iss {line};
            double x, y, z;
            iss >> x >> y >> z;
            lineProcessor(x, y, z); 
        });
    }

    void parseLines(std::istream& stream, std::function<void(double, double, double, double)> lineProcessor) {
        readLines(stream, [&](const std::string& line){
            std::istringstream iss {line};
            double i, j, k, l;
            iss >> i >> j >> k >> l;
            lineProcessor(i, j, k, l); 
        });
    }
}