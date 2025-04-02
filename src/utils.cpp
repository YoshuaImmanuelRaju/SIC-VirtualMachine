#include "utils.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cctype>

// Convert hex string to integer
uint32_t Utils::hexStringToInt(const std::string& hexStr) {
    uint32_t value = 0;
    std::istringstream iss(hexStr);
    
    if (hexStr.find("0x") == 0 || hexStr.find("0X") == 0) {
        iss >> std::hex >> value;
    } else {
        iss >> std::hex >> value;
    }

    if (iss.fail()) {
        std::cerr << "[ERROR] Invalid hex string: " << hexStr << std::endl;
        return 0;
    }

    return value;
}

// Convert integer to hex string with optional width
std::string Utils::intToHexString(uint32_t value, size_t width) {
    std::ostringstream oss;
    oss << "0x" << std::hex << std::setfill('0') << std::setw(width) << value;
    return oss.str();
}

// Print error message
void Utils::printError(const std::string& message) {
    std::cerr << "\033[1;31m[ERROR]\033[0m " << message << std::endl;
}

// Print warning message
void Utils::printWarning(const std::string& message) {
    std::cerr << "\033[1;33m[WARNING]\033[0m " << message << std::endl;
}

// Print info message
void Utils::printInfo(const std::string& message) {
    std::cout << "\033[1;32m[INFO]\033[0m " << message << std::endl;
}
