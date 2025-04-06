#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <map>
#include <string>
#include <cstdint>

std::map<uint16_t, std::string> loadSymbolTable(const std::string& path);

#endif

