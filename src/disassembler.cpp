#include "disassembler.h"
#include <iostream>
#include <iomanip>
#include <unordered_map>

Disassembler::Disassembler() {}

Disassembler::~Disassembler() {}

void Disassembler::disassemble(const std::vector<uint8_t>& memory, size_t start, size_t end) {
    if (start >= memory.size() || end >= memory.size() || start > end) {
        std::cerr << "[ERROR] Invalid memory range!" << std::endl;
        return;
    }

    std::cout << std::hex << std::setfill('0');

    // Loop through memory in 3-byte chunks (SIC instruction size)
    for (size_t addr = start; addr <= end; addr += 3) {
        if (addr + 2 >= memory.size()) {
            std::cerr << "[WARN] Incomplete instruction at 0x"
                      << std::setw(4) << addr << std::endl;
            break;
        }

        // Read the 3-byte instruction
        uint8_t byte1 = memory[addr];
        uint8_t byte2 = memory[addr + 1];
        uint8_t byte3 = memory[addr + 2];

        uint32_t instruction = (byte1 << 16) | (byte2 << 8) | byte3;

        // Print memory address
        std::cout << "0x" << std::setw(4) << addr << ": ";

        // Print raw instruction bytes
        std::cout << std::setw(2) << (int)byte1 << " "
                  << std::setw(2) << (int)byte2 << " "
                  << std::setw(2) << (int)byte3 << "  ";

        // Placeholder disassembly logic
        disassembleInstruction(instruction);

        std::cout << std::endl;
    }

    std::cout << std::dec;  // Reset formatting
}

void Disassembler::disassembleInstruction(uint32_t instruction) {
    // Extract opcode (first 8 bits)
    uint8_t opcode = (instruction >> 16) & 0xFF;
    uint16_t address = instruction & 0xFFFF;

    // Placeholder opcode map
    std::unordered_map<uint8_t, std::string> opcodeMap = {
        {0x18, "ADD"},
        {0x58, "ADDF"},
        {0x40, "AND"},
        {0x28, "COMP"},
        {0x24, "DIV"},
        {0x3C, "J"},
        {0x30, "JEQ"},
        {0x34, "JGT"},
        {0x38, "JLT"},
        {0x48, "JSUB"},
        {0x00, "LDA"},
        {0x68, "LDB"},
        {0x74, "LDT"},
        {0x50, "LDCH"},
        {0x08, "LDL"},
        {0x04, "LDX"},
        {0x20, "MUL"},
        {0x44, "OR"},
        {0x4C, "RSUB"},
        {0x0C, "STA"},
        {0x54, "STCH"},
        {0x14, "STL"},
        {0x10, "STX"},
        {0x1C, "SUB"},
        {0xE0, "TD"},
        {0x2C, "TIX"},
        {0xDC, "WD"}
    };

    // Print disassembled instruction
    if (opcodeMap.find(opcode) != opcodeMap.end()) {
        std::cout << opcodeMap[opcode] << " 0x" << std::hex << address;
    } else {
        std::cout << "[UNK] Opcode: 0x" << std::hex << (int)opcode
                  << " Addr: 0x" << address;
    }
}
