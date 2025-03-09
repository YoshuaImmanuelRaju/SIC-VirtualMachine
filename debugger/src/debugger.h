#ifndef DEBUGGER_H
#define DEBUGGER_H

#include "sic_vm.h"
#include <set>

void debugLoop(SICMachine& vm);
void setBreakpoint(uint32_t address);
bool checkBreakpoint(uint32_t pc);
void step(SICMachine& vm);
void printMemory(SICMachine& vm, uint32_t address);
void modifyMemory(SICMachine& vm, uint32_t address, uint8_t value);

#endif
