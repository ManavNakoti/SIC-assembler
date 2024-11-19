//Data Structures for SIC Assembler
#include<iostream>
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
        {"STCH", 0x54}, {"TIX", 0x2C},{"STL", 0x14},
        {"STX", 0x10}, {"TD", 0xE0}, {"RD", 0xD8},
        {"WD", 0xDC},{"LDL", 0x08}
    };
    public:
        std::uint8_t getOpcode(const std::string& mnemonic){
            if(opcodeTable.find(mnemonic) != opcodeTable.end())
                return opcodeTable[mnemonic];
            else{
                throw std::invalid_argument("Invalid Opcode");
            }
        }

        bool isOpcode(const std::string& mnemonic){
            return opcodeTable.find(mnemonic) != opcodeTable.end();
        }
        void displayOptable(){
            for(auto& x: opcodeTable){
                std::cout << x.first << " " << std::hex << (int)x.second << std::endl;
            }
        }
};

//Symbol Table
class Symtable {
    std::unordered_map<std::string, std::uint16_t> symbolTable;
    public:
        void insert(std::string symbol, std::uint16_t address) {
            symbolTable[symbol] = address;
        }
        std::uint16_t getAddress(std::string symbol) {
            if(symbolTable.find(symbol) != symbolTable.end())
                return symbolTable[symbol];
            else{
                throw std::invalid_argument("Invalid Symbol");
            }
        }
        std::uint16_t exists(std::string symbol) {
            return symbolTable.find(symbol) != symbolTable.end();
        }
        void displaySymtab(){
            for(auto& x: symbolTable){
              
              std::cout << x.first << " " << std::hex << x.second << std::endl;
            }
        }
};  //End of Symtab