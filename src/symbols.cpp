#include "symbols.h"
#include "utils.h"
#include <fstream>
#include <sstream>
#include <iostream>

Symbols::Symbols() {}

Symbols::~Symbols() {}

bool Symbols::loadSymbols(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        Utils::printError("Failed to open symbol table file: " + filename);
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string symbol;
        uint32_t address;

        if (iss >> symbol >> std::hex >> address) {
            symbolTable[address] = symbol; // Store symbol at given address
        } else {
            Utils::printWarning("Invalid line in symbol table: " + line);
        }
    }

    file.close();
    Utils::printInfo("Symbol table loaded successfully.");
    return true;
}

std::string Symbols::resolveAddress(uint32_t address) const {
    auto it = symbolTable.find(address);
    if (it != symbolTable.end()) {
        return it->second; // Return the symbol at this address
    } else {
        return "[UNKNOWN]"; // No symbol found for this address
    }
}

void Symbols::displaySymbols() const {
    std::cout << "\nSymbol Table:\n";
    for (const auto& entry : symbolTable) {
        std::cout << Utils::intToHexString(entry.first, 6) << " : " << entry.second << std::endl;
    }
}
