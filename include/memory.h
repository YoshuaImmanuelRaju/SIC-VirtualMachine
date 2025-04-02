#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include <cstdint>

class Memory {
public:
    // Constructor and Destructor
    Memory(size_t size = 32768);    // Default size: 32 KB (SIC memory)
    ~Memory();

    // Memory Management
    void load(const std::vector<uint8_t>& data, size_t startAddress);  // Load program into memory
    uint8_t readByte(size_t address) const;        // Read a byte from memory
    void writeByte(size_t address, uint8_t value); // Write a byte to memory

    // Memory Inspection
    void display(size_t start, size_t end) const;  // Display memory content

private:
    std::vector<uint8_t> memory;   // SIC memory array
};

#endif // MEMORY_H
