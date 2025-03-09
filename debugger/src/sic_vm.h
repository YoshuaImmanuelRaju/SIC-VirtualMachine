#ifndef SIC_VM_H
#define SIC_VM_H

#include <iostream>
#include <fstream>
#include <cstdint>

struct SICMachine {
    uint8_t memory[32768] = {0}; // SIC memory
    uint32_t A = 0, X = 0, L = 0, PC = 0, SW = 0; // SIC Registers
};

bool loadSICProgram(SICMachine& vm, const std::string& filename);
void executeInstruction(SICMachine& vm);

#endif
