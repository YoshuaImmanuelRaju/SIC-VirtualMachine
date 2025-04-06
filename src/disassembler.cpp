
// === src/disassembler.cpp ===
#include "disassembler.h"
#include "utils.h"
#include "opcode_table.h"

#include <sstream>
#include <string>
#include <cstdint>

std::string disassembleInstruction(const uint8_t* memory, uint16_t addr,
                                   const std::map<uint16_t, std::string>& symbolTable) {
    if (addr > 0x7FFD) return "??";

    uint8_t byte1 = memory[addr];
    uint8_t byte2 = memory[addr + 1];
    uint8_t byte3 = memory[addr + 2];

    uint8_t opcode = byte1 & 0xFC;
    std::string mnemonic = getMnemonic(opcode);

    if (opcode == 0x4C) {
        return mnemonic; // RSUB has no operand
    }

    uint16_t target = ((byte2 << 8) | byte3) & 0x0FFF;

    std::string operand;
    auto symIt = symbolTable.find(target);
    if (symIt != symbolTable.end()) {
        operand = symIt->second;
    } else {
        operand = toHex(target, 4);
    }

    return mnemonic + " " + operand;
}
