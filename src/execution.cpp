#include "execution.h"
#include <iostream>
#include <unordered_set>

Execution::Execution() : programCounter(0), isRunning(false) {}

Execution::~Execution() {}

void Execution::loadProgram(const std::vector<uint8_t>& program) {
    memory = program;  // Load program into memory
    programCounter = 0;
    isRunning = true;

    std::cout << "[INFO] Program loaded. Starting at address 0x"
              << std::hex << programCounter << std::dec << std::endl;
}

void Execution::run() {
    std::cout << "[INFO] Running program..." << std::endl;

    while (isRunning && programCounter < memory.size()) {
        if (breakpoints.find(programCounter) != breakpoints.end()) {
            std::cout << "[BREAK] Hit breakpoint at 0x" 
                      << std::hex << programCounter << std::dec << std::endl;
            isRunning = false;
            break;
        }

        // Simulate instruction execution (placeholder)
        std::cout << "[EXEC] Executing instruction at 0x"
                  << std::hex << programCounter << std::dec << std::endl;

        // Advance program counter (simulate SIC instruction size of 3 bytes)
        programCounter += 3;

        // Simulate hitting end of memory
        if (programCounter >= memory.size()) {
            std::cout << "[INFO] Reached end of program." << std::endl;
            isRunning = false;
        }
    }
}

void Execution::step() {
    std::cout << "[STEP] Executing instruction at 0x"
              << std::hex << programCounter << std::dec << std::endl;

    // Simulate instruction execution
    programCounter += 3;  // SIC instructions are 3 bytes long

    // Stop execution if the end of memory is reached
    if (programCounter >= memory.size()) {
        std::cout << "[INFO] Reached end of program." << std::endl;
        isRunning = false;
    }
}

void Execution::setBreakpoint(int address) {
    breakpoints.insert(address);
    std::cout << "[INFO] Breakpoint set at 0x" 
              << std::hex << address << std::dec << std::endl;
}

void Execution::removeBreakpoint(int address) {
    if (breakpoints.erase(address)) {
        std::cout << "[INFO] Breakpoint removed at 0x" 
                  << std::hex << address << std::dec << std::endl;
    } else {
        std::cout << "[WARN] No breakpoint found at 0x" 
                  << std::hex << address << std::dec << std::endl;
    }
}

bool Execution::isAtBreakpoint() const {
    return breakpoints.find(programCounter) != breakpoints.end();
}

void Execution::stop() {
    std::cout << "[INFO] Stopping execution." << std::endl;
    isRunning = false;
}
