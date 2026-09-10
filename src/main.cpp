#include "../include/Ocar.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

static void printHelp(const char* prog) {
    std::cout
        << "Ocar - OCAR Can't Allocate Registers\n"
        << "An assembly transpiler with C-inspired syntax.\n"
        << "\n"
        << "Usage:\n"
        << "  " << prog << " [options]\n"
        << "  " << prog << " <input.ocar>\n"
        << "  " << prog << " <input.ocar> <output.asm>\n"
        << "\n"
        << "Options:\n"
        << "  -h, --help       Show this help message and exit\n"
        << "  --version        Show version information and exit\n"
        << "\n"
        << "Arguments:\n"
        << "  input.ocar       Path to the source file  (default: ../code.scl)\n"
        << "  output.asm       Path to the output file  (default: ../output.sh)\n"
        << "\n"
        << "Language features:\n"
        << "  rtn <name>()     Define a routine (function)\n"
        << "  noret            Mark routine as no-return (skips 'ret')\n"
        << "  <reg> <var> = N  Declare a variable bound to a register\n"
        << "  delete <var>     Free the register held by a variable\n"
        << "  raw <reg> = N    Write directly to a register without variable binding\n"
        << "  @<asm>           Emit raw assembly directly (no checks)\n"
        << "  syscall          Emit a syscall instruction\n"
        << "  #stdlib <name>   Include a standard-library module\n"
        << "  #noheader        Suppress the auto-generated header comment\n"
        << "  if / while       Control flow (else not yet supported)\n"
        << "  goto / label     Unconditional jumps\n"
        << "  +=  -=  *=       Arithmetic assignment operators\n"
        << "\n"
        << "Examples:\n"
        << "  " << prog << " hello.ocar\n"
        << "  " << prog << " hello.ocar hello.asm\n"
        << "\n"
        << "Repository: https://github.com/Mher-DeLight/Ocar\n";
}

static void printVersion() {
    std::cout << "Ocar version 0.0.4\n";
}

int main(int argc, char* argv[]) {
    std::string read_from = "../code.scl";
    std::string write_to  = "../output.sh";

    // --- Parse flags/arguments ---
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--help") {
            printHelp(argv[0]);
            return 0;
        } else if (arg == "--version") {
            printVersion();
            return 0;
        }
    }

    if (argc == 2) {
        read_from = argv[1];
    } else if (argc > 2) {
        read_from = argv[1];
        write_to  = argv[2];
    }

    // --- Open input file ---
    std::ifstream fileStream(read_from);
    if (!fileStream.is_open()) {
        std::cerr << "cannot open input file '" << read_from << "'\n"
                  << "Tip: run '" << argv[0] << " --help' for usage.\n";
        return 1;
    }

    std::ostringstream sstr;
    sstr << fileStream.rdbuf();
    fileStream.close();

    // --- Open output file ---
    std::ofstream output(write_to);
    if (!output.is_open()) {
        std::cerr << "cannot open output file '" << write_to << "'\n";
        return 1;
    }


    Compiler compiler;
    compiler.compile(sstr.str(), output);

    output.close();

    return 0;
}
