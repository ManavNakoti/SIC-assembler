//Data Structures for SIC Assembler
#include<unordered_map>
#include<string>

//Opcode Table
class Optable {
    std::unordered_map<std::string, std::uint8_t> opcodeTable = {
        {"LDA", 0x00}, {"STA", 0x0C}, {"LDX", 0x04},
        {"ADD", 0x18}, {"SUB", 0x1C}, {"MUL", 0x20},
        {"DIV", 0x24}, {"COMP", 0x28}, {"J", 0x3C},
        {"JEQ", 0x30}, {"JGT", 0x34}, {"JLT", 0x38},
        {"JSUB", 0x48}, {"RSUB", 0x4C}, {"LDCH", 0x50},
        {"STCH", 0x54}, {"TIX", 0x2C}
    };
    public:
        std::uint8_t getOpcode(std::string mnemonic) {
            return opcodeTable[mnemonic];
        }
};

//Symbol Table
class Symtab {
    std::unordered_map<std::string, std::uint16_t> symbolTable;
    public:
        void insert(std::string symbol, std::uint16_t address) {
            symbolTable[symbol] = address;
        }
        std::uint16_t getAddress(std::string symbol) {
            return symbolTable[symbol];
        }
};

