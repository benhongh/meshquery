#ifndef INCLUDED_LINE_PARSER_HPP
#define INCLUDED_LINE_PARSER_HPP

#include <string>
#include <istream>

namespace hongbin {
    /**
     * read from a stream and pass individual lines into lineReader callback
     * \param stream source input stream
     * \param lineReader line reader callback function
     */
    void readLines(std::istream& stream, std::function<void(const std::string&)> lineReader);
    
    /**
     * read from a stream and parse each line as three numbers, then pass these numbers into lineProcessor callback
     * \param stream source input stream
     * \param lineProcessor line processor callback function
     */
    void parseLines(std::istream& stream, std::function<void(double, double, double)> lineProcessor);
    
    /**
     * read from a stream and parse each line as four numbers, then pass these numbers into lineProcessor callback
     * \param stream source input stream
     * \param lineProcessor line processor callback function
     */
    void parseLines(std::istream& stream, std::function<void(double, double, double, double)> lineProcessor);
}

#endif // include guard