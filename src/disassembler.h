#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include <cstdint>
#include <string>
#include <map>

std::string disassembleInstruction(const uint8_t* memory, uint16_t addr,
                                   const std::map<uint16_t, std::string>& symbolTable);

#endif

