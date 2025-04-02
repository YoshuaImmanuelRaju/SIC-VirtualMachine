#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include <vector>
#include <cstdint>

class Disassembler {
public:
    // Constructor and Destructor
    Disassembler();
    ~Disassembler();

    // Disassembly Functions
    void disassemble(const std::vector<uint8_t>& memory, size_t start, size_t end);  // Disassemble memory range

private:
    void disassembleInstruction(uint32_t instruction);  // Decode and print a single instruction
};

#endif // DISASSEMBLER_H
