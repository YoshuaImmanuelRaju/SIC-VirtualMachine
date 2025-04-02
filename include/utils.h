#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <cstdint>

class Utils {
public:
    // Hexadecimal conversion
    static uint32_t hexStringToInt(const std::string& hexStr);  // Convert hex string to int
    static std::string intToHexString(uint32_t value, size_t width = 4);  // Convert int to hex string

    // Logging functions
    static void printError(const std::string& message);    // Print error message
    static void printWarning(const std::string& message);  // Print warning message
    static void printInfo(const std::string& message);     // Print info message
};

#endif // UTILS_H
