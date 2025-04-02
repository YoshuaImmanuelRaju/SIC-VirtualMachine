#include "../include/debugger.h"
#include "../include/execution.h"
#include "../include/disassembler.h"
#include <iostream>
#include <string>
#include <vector>
#include "../include/symbols.h"
#include "../include/utils.h"

using namespace std;

// Constructor
Debugger::Debugger() : execution(nullptr), memory(nullptr), disassembler(nullptr), isRunning(false)	{}

Debugger::~Debugger() {
	delete execution;
	delete memory;
	delete disassembler;
}

// Display the CLI menu
void Debugger::displayMenu() {
    cout << "\n==== SIC Debugger ====\n";
    cout << "1. Load program\n";
    cout << "2. Run\n";
    cout << "3. Step\n";
    cout << "4. Add breakpoint\n";
    cout << "5. View memory\n";
    cout << "6. View registers\n";
    cout << "7. Quit\n";
    cout << "====================\n";
}

// Handle CLI commands
void Debugger::handleCommand(const string& command) {
    if (command == "1") {
        cout << "Loading program...\n";
        // TODO: Load program logic
    } else if (command == "2") {
        cout << "Running program...\n";
        // TODO: Run program logic
    } else if (command == "3") {
        cout << "Stepping...\n";
        // TODO: Step logic
    } else if (command == "4") {
        cout << "Adding breakpoint...\n";
        // TODO: Add breakpoint logic
    } else if (command == "5") {
        cout << "Viewing memory...\n";
        // TODO: Memory inspection logic
    } else if (command == "6") {
        cout << "Viewing registers...\n";
        // TODO: Register inspection logic
    } else if (command == "7") {
        cout << "Exiting debugger.\n";
        isRunning = false;
    } else {
        cout << "Invalid command. Try again.\n";
    }
}

void Debugger::inspectMemory(uint32_t address) {
    std::string symbol = symbols.resolveAddress(address);
    std::string hexAddress = Utils::intToHexString(address, 6);
    std::cout << "Memory at " << hexAddress << " (" << symbol << "): ";
    // Add more memory inspection logic here...
}

// Main debugger loop
void Debugger::start() {
    isRunning = true;
    string command;
    
    while (isRunning) {
        displayMenu();
        cout << "Enter command: ";
        getline(cin, command);
        handleCommand(command);
    }
    cout << "Debugger terminated.\n";
}

void Debugger::displaySymbols() const {
	symbolsdisplaySymbols();
}
