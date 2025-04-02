#include "memory.h"
#include <iostream>
#include <iomanip>

Memory::Memory(size_t size) : memory(size, 0) {}

Memory::~Memory() {}

void Memory::load(const std::vector<uint8_t>& data, size_t startAddress) {
    if (startAddress + data.size() > memory.size()) {
        std::cerr << "[ERROR] Program size exceeds memory limit!" << std::endl;
        return;
    }

    // Load the data into memory
    std::copy(data.begin(), data.end(), memory.begin() + startAddress);
    std::cout << "[INFO] Program loaded into memory at address 0x"
              << std::hex << startAddress << std::dec << std::endl;
}

uint8_t Memory::readByte(size_t address) const {
    if (address >= memory.size()) {
        std::cerr << "[ERROR] Invalid memory read at address 0x"
                  << std::hex << address << std::dec << std::endl;
        return 0xFF;  // Return an invalid value on error
    }
    return memory[address];
}

void Memory::writeByte(size_t address, uint8_t value) {
    if (address >= memory.size()) {
        std::cerr << "[ERROR] Invalid memory write at address 0x"
                  << std::hex << address << std::dec << std::endl;
        return;
    }

    memory[address] = value;
    std::cout << "[INFO] Memory updated at address 0x"
              << std::hex << address << std::dec
              << " with value 0x" << std::hex << (int)value << std::dec << std::endl;
}

void Memory::display(size_t start, size_t end) const {
    if (start >= memory.size() || end >= memory.size() || start > end) {
        std::cerr << "[ERROR] Invalid memory range!" << std::endl;
        return;
    }

    std::cout << std::hex << std::setfill('0');

    for (size_t addr = start; addr <= end; addr += 16) {
        std::cout << "0x" << std::setw(4) << addr << ": ";

        for (size_t offset = 0; offset < 16 && (addr + offset) <= end; ++offset) {
            std::cout << std::setw(2) << (int)memory[addr + offset] << " ";
        }

        std::cout << std::dec << std::endl;
    }
}
