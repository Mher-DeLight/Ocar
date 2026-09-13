#pragma once
#include "Common.h"
#include "IrGenerator.h"

namespace ocarlang {
class IrPrinter {
private:
    std::vector<std::unique_ptr<Ir>> ir;
    int indent = 0;
    bool has_text_section = false;
    void print_indent(std::ostream& stream);
    void
    dispatch_print(Ir* instr,
                   std::ostream& stream); // yes, yes, a dispatcher function isn't the best practice
                                          // but like who really cares it's just a bunch of if
                                          // statements, way more readable than operator overloads

    void instr_print(IrMovStmt* ins, std::ostream& stream);
    void instr_print(IrLabelStmt* ins, std::ostream& stream);
    void instr_print(IrRetStmt* ins, std::ostream& stream);
    void instr_print(IrRtnCall* ins, std::ostream& stream);
    void instr_print(IrGlobal* ins, std::ostream& stream);
    void instr_print(IrSection* ins, std::ostream& stream);
    void instr_print(IrAsm* ins, std::ostream& stream);
    void instr_print(IrJmp* ins, std::ostream& stream);
    void instr_print(IrCmp* ins, std::ostream& stream);
    void instr_print(IrSyscall* ins, std::ostream& stream);
    void instr_print(IrAdd* ins, std::ostream& stream);
    void instr_print(IrSub* ins, std::ostream& stream);
    void instr_print(IrImul* ins, std::ostream& stream);
    void instr_print(IrXchg* ins, std::ostream& stream);

    void instr_print(IrIntLit* ins, std::ostream& stream);
    void instr_print(IrMemName* ins, std::ostream& stream);

public:
    bool makeHeader = true;
    void load_ir(std::vector<std::unique_ptr<Ir>> ir_);
    void print(std::ostream& stream);
};
} // namespace ocarlang
