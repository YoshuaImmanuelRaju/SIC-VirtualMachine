#include "opcode_table.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cctype>
#include <algorithm>

static std::map<uint8_t, std::string> opcodeMap;

bool loadOpcodeTable(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        std::cerr << "Error: Could not open opcode file: " << path << "\n";
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        std::string mnemonic, hexStr;
        iss >> mnemonic >> hexStr;

        // Remove trailing/leading spaces from hexStr just in case
        hexStr.erase(std::remove_if(hexStr.begin(), hexStr.end(), ::isspace), hexStr.end());

        try {
            uint8_t opcode = static_cast<uint8_t>(std::stoul(hexStr, nullptr, 16));
            opcodeMap[opcode] = mnemonic;
        } catch (...) {
            std::cerr << "Warning: Skipping invalid opcode line: " << line << "\n";
        }
    }

    return true;
}

std::string getMnemonic(uint8_t opcode) {
    auto it = opcodeMap.find(opcode);
    return (it != opcodeMap.end()) ? it->second : "???";
}

