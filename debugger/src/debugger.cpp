#include "debugger.h"
#include <iostream>
#include <set>

std::set<uint32_t> breakpoints;

void setBreakpoint(uint32_t address) {
    breakpoints.insert(address);
    std::cout << "Breakpoint set at address: " << std::hex << address << "\n";
}

bool checkBreakpoint(uint32_t pc) {
    return breakpoints.find(pc) != breakpoints.end();
}

void step(SICMachine& vm) {
    executeInstruction(vm);
    std::cout << "Stepped to PC: " << std::hex << vm.PC << "\n";
}

void printMemory(SICMachine& vm, uint32_t address) {
    std::cout << "Memory[" << std::hex << address << "] = " 
              << std::hex << (int)vm.memory[address] << "\n";
}

void modifyMemory(SICMachine& vm, uint32_t address, uint8_t value) {
    vm.memory[address] = value;
    std::cout << "Modified Memory[" << std::hex << address << "] = " 
              << std::hex << (int)value << "\n";
}

void debugLoop(SICMachine& vm) {
    std::string command;
    while (true) {
        std::cout << "(debugger) ";
        std::cin >> command;

        if (command == "run") {
            while (vm.PC < sizeof(vm.memory)) {
                if (checkBreakpoint(vm.PC)) {
                    std::cout << "Breakpoint hit at PC: " << std::hex << vm.PC << "\n";
                    break;
                }
                executeInstruction(vm);
            }
        } else if (command == "step") {
            step(vm);
        } else if (command == "break") {
            uint32_t addr;
            std::cin >> std::hex >> addr;
            setBreakpoint(addr);
        } else if (command == "print") {
            uint32_t addr;
            std::cin >> std::hex >> addr;
            printMemory(vm, addr);
        } else if (command == "modify") {
            uint32_t addr;
            uint8_t value;
            std::cin >> std::hex >> addr >> value;
            modifyMemory(vm, addr, value);
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "Unknown command. Available commands: run, step, break, print, modify, exit\n";
        }
    }
}
