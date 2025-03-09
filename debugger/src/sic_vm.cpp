#include "sic_vm.h"

bool loadSICProgram(SICMachine& vm, const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open SIC file!\n";
        return false;
    }
    file.read(reinterpret_cast<char*>(vm.memory), sizeof(vm.memory));
    return true;
}

void executeInstruction(SICMachine& vm) {
    uint8_t opcode = vm.memory[vm.PC]; // Fetch opcode
    switch (opcode) {
        case 0x00: // LDA (Load A register)
            vm.A = vm.memory[vm.PC + 1];
            vm.PC += 3;
            break;
        case 0x18: // ADD (Add to A register)
            vm.A += vm.memory[vm.PC + 1];
            vm.PC += 3;
            break;
        default:
            std::cout << "Unknown opcode: " << std::hex << (int)opcode << "\n";
            vm.PC += 3;
            break;
    }
}
