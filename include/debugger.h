#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <string>
#include <vector>
#include "symbols.h" // Include necessary header files

// Forward declarations of other necessary classes
class Execution;
class Memory;
class Disassembler;

class Debugger {
public:
    // Constructor and Destructor
    Debugger();
    ~Debugger();

    // Main debugging interface
    void run();                  // Start the debugging process
    void step();                 // Step through the program
    void setBreakpoint(int address); // Set a breakpoint at a specific address
    void continueExecution();    // Continue execution after a breakpoint

    void start();
    void displayMenu();
    void handleCommand(const std::string& command);
    bool loadSymbols(const std::string& filename);
    void inspectMemory(uint32_t address);
    void displaySymbols() const;

    // Command parsing and interaction
    void showHelp() const;        // Show available commands
    void loadProgram(const std::string& programPath); // Load SIC program
    void displayMemory(int start, int end); // Display memory from a range
    void displayRegisters();      // Display registers

private:
    Execution* execution;       // Handles execution control
    Memory* memory;             // Handles memory inspection and management
    Disassembler* disassembler; // Handles disassembly of the program
    Symbols symbols;           // Handles the symbol table
    bool isRunning;             // Flag to track the debugger status
};

#endif // DEBUGGER_H

