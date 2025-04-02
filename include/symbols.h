#ifndef SYMBOLS_H
#define SYMBOLS_H

#include <string>
#include <unordered_map>
#include <cstdint>

class Symbols {
public:
    // Constructor and Destructor
    Symbols();
    ~Symbols();

    // Symbol Table Management
    bool loadSymbols(const std::string& filename);      // Load symbols from a file
    std::string resolveAddress(uint32_t address) const; // Resolve address to symbol name
    void displaySymbols() const;                        // Display the symbol table

private:
    std::unordered_map<uint32_t, std::string> symbolTable;  // Map: Address -> Symbol name
};

#endif // SYMBOLS_H
