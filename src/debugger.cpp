#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cstdint>

#include "disassembler.h"
#include "symbol_table.h"
#include "opcode_table.h"

// Constants
constexpr size_t MEMORY_SIZE = 32768; // 32K words
uint8_t memory[MEMORY_SIZE] = {0};

// Registers
uint16_t PC = 0x0000;
uint16_t startAddress = 0; // ← NEW
uint16_t A = 0x0000;
uint16_t X = 0x0000;
uint16_t L = 0x0000;
uint16_t SW = 0x0000;

// Breakpoints
std::set<uint16_t> breakpoints;

// Symbol table
std::map<uint16_t, std::string> symbolTable;

// Utility
std::string toHex(uint16_t value, int width = 4) {
    std::ostringstream oss;
    oss << std::uppercase << std::setfill('0') << std::hex << std::setw(width) << value;
    return oss.str();
}

// Load object file into memory
bool loadObjectFile(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        std::cerr << "Error: Could not open object file.\n";
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        char recordType = line[0];
        if (recordType == 'H') {
            if (line.length() < 19) {
        	std::cerr << "Warning: Malformed H record: " << line << "\n";
        	continue;
	    }

    	    try {
       		//programName = line.substr(1, 6);
        	startAddress = static_cast<uint16_t>(std::stoul(line.substr(7, 6), nullptr, 16));
        	//programLength = static_cast<uint16_t>(std::stoul(line.substr(13, 6), nullptr, 16));
		PC = startAddress;
	    } catch (...) {
		std::cerr << "Warning: Failed to parse H record: " << line << "\n";
	    }
 
            continue;
        } else if (recordType == 'T') {
            // Text record
            uint16_t startAddr = std::stoul(line.substr(1, 6), nullptr, 16);
            size_t length = std::stoul(line.substr(7, 2), nullptr, 16);
            std::string bytes = line.substr(9);

            for (size_t i = 0; i < length * 2; i += 2) {
                std::string byteStr = bytes.substr(i, 2);
                uint8_t byte = std::stoul(byteStr, nullptr, 16);
                if (startAddr < MEMORY_SIZE) {
                    memory[startAddr++] = byte;
                }
            }
        } else if (recordType == 'E') {
            // End record: set PC
            PC = std::stoul(line.substr(1, 6), nullptr, 16);
        }
    }

    std::cout << "Loaded object file.\n";
    return true;
}

// Dump register values
void printRegisters() {
    std::cout << "PC=" << toHex(PC)
              << " A=" << toHex(A)
              << " X=" << toHex(X)
              << " L=" << toHex(L)
              << " SW=" << toHex(SW) << "\n";
}

// Execute one instruction
void step() {
    if (PC > MEMORY_SIZE - 3) {
        std::cerr << "Error: PC out of bounds." << std::endl;
        return;
    }
    
    uint8_t opcode = memory[PC] & 0xFC;
    uint8_t byte2 = memory[PC + 1];
    uint8_t byte3 = memory[PC + 2];
    uint16_t operand = ((byte2 << 8) | byte3) & 0x0FFF;

    std::string mnemonic = getMnemonic(opcode);
    std::cout << toHex(PC) << ": " << mnemonic << " " << toHex(operand) << std::endl;

    PC += 3;
}

// Continue execution until breakpoint
void continueExecution() {
    while (true) {
        if (breakpoints.count(PC)) {
            std::cout << "Hit breakpoint at " << toHex(PC) << "\n";
            break;
        }
        step();
    }
}

// Set a breakpoint
void setBreakpoint(uint16_t addr) {
    breakpoints.insert(addr);
    std::cout << "Breakpoint set at " << toHex(addr) << "\n";
}

// Clear a breakpoint
void clearBreakpoint(uint16_t addr) {
    if (breakpoints.erase(addr)) {
        std::cout << "Breakpoint cleared at " << toHex(addr) << "\n";
    } else {
        std::cout << "No breakpoint at " << toHex(addr) << "\n";
    }
}

// List breakpoints
void listBreakpoints() {
    std::cout << "Breakpoints:\n";
    for (uint16_t addr : breakpoints) {
        std::cout << "  " << toHex(addr) << "\n";
    }
}

// Show help
void printHelp() {
    std::cout << "Commands:\n"
              << "  load <file.obj>         Load object file\n"
              << "  symbols <file.sym>      Load symbol table\n"
              << "  break <addr>            Set breakpoint\n"
              << "  clear <addr>            Clear breakpoint\n"
              << "  breaks                  List breakpoints\n"
              << "  step                    Execute one instruction\n"
              << "  continue                Run until breakpoint\n"
              << "  regs                    Show register values\n"
              << "  disasm <addr>           Disassemble at address\n"
              << "  help                    Show this help\n"
              << "  exit                    Quit debugger\n";
}

// Command loop
void debuggerLoop() {
    std::string line;
    while (true) {
        std::cout << "dbg> ";
        if (!std::getline(std::cin, line)) break;

        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        if (cmd == "exit" || cmd == "quit") {
            break;
        } else if (cmd == "load") {
            std::string file;
            iss >> file;
            if (!loadObjectFile(file)) {
                std::cerr << "Failed to load file.\n";
            }
        } else if (cmd == "symbols") {
            std::string file;
            iss >> file;
            symbolTable = loadSymbolTable(file);
            std::cout << "Loaded symbol table.\n";
        } else if (cmd == "break") {
            std::string addrStr;
            iss >> addrStr;
            uint16_t addr = std::stoul(addrStr, nullptr, 16);
            setBreakpoint(addr);
        } else if (cmd == "clear") {
            std::string addrStr;
            iss >> addrStr;
            uint16_t addr = std::stoul(addrStr, nullptr, 16);
            clearBreakpoint(addr);
        } else if (cmd == "breaks") {
            listBreakpoints();
        } else if (cmd == "step") {
            step();
        } else if (cmd == "continue") {
            continueExecution();
        } else if (cmd == "regs") {
            printRegisters();
        } else if (cmd == "disasm") {
            std::string addrStr;
            iss >> addrStr;
            uint16_t addr = std::stoul(addrStr, nullptr, 16);
            std::string dis = disassembleInstruction(memory, addr, symbolTable);
            std::cout << toHex(addr) << ": " << dis << "\n";
        } else if (cmd == "help") {
            printHelp();
        } else {
            std::cout << "Unknown command. Type 'help' for a list.\n";
        }
    }
}

// Entry point
int main(int argc, char* argv[]) {
    if (argc < 4) {
    	std::cerr << "Usage: " << argv[0] << " <object file> <symbol file> <opcode file>\n";
    	return 1;
    }

    if (!loadOpcodeTable(argv[3])) {
	return 1;
    }
    std::cout << "SIC Debugger\n";
    printHelp();
    debuggerLoop();
    return 0;
}

