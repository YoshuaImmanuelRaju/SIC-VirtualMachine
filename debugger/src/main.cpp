#include "sic_vm.h"
#include "debugger.h"

int main() {
    SICMachine vm;
    
    // Load SIC machine program from file
    if (!loadSICProgram(vm, "programs/program.sic")) {
        return 1;
    }

    std::cout << "SIC Debugger Started. Type 'help' for commands.\n";
    debugLoop(vm); // Enter debugger mode

    return 0;
}
