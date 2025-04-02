#ifndef EXECUTION_H
#define EXECUTION_H

#include <vector>
#include <unordered_set>

class Execution {
public:
    // Constructor and Destructor
    Execution();
    ~Execution();

    // Program Execution Control
    void loadProgram(const std::vector<uint8_t>& program);  // Load SIC program into memory
    void run();                        // Run until completion or breakpoint
    void step();                       // Execute a single instruction
    void stop();                       // Stop execution

    // Breakpoint Management
    void setBreakpoint(int address);   // Add a breakpoint
    void removeBreakpoint(int address);// Remove a breakpoint
    bool isAtBreakpoint() const;       // Check if at a breakpoint

private:
    std::vector<uint8_t> memory;        // SIC memory space
    std::unordered_set<int> breakpoints; // Set of breakpoints
    int programCounter;                 // Current program counter
    bool isRunning;                     // Execution status flag
};

#endif // EXECUTION_H
