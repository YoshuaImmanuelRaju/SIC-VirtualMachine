#include "symbol_table.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <cstdint>

// Load symbol table from a .sym file
std::map<uint16_t, std::string> loadSymbolTable(const std::string& path) {
    std::map<uint16_t, std::string> table;
    std::ifstream file(path);

    if (!file) {
        std::cerr << "Error: Could not open symbol file: " << path << "\n";
        return table;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        std::string label, addrStr;
        iss >> label >> addrStr;

        if (label.empty() || addrStr.empty()) continue;

        try {
            uint16_t address = std::stoul(addrStr, nullptr, 16);
            table[address] = label;
        } catch (...) {
            std::cerr << "Warning: Skipping invalid line: " << line << "\n";
        }
    }

    return table;
}

