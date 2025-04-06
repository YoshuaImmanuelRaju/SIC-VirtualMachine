// === include/utils.h ===
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>
#include <iomanip>
#include <cstdint>

inline std::string toHex(uint16_t value, int width = 4) {
    std::ostringstream oss;
    oss << std::uppercase << std::hex << std::setfill('0') << std::setw(width) << value;
    return oss.str();
}

#endif
