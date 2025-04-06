#ifndef OPCODE_TABLE_H
#define OPCODE_TABLE_H

#include <map>
#include <string>
#include <cstdint>

bool loadOpcodeTable(const std::string& path);
std::string getMnemonic(uint8_t opcode);

#endif

