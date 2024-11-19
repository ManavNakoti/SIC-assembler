//pass 1 assembler
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<iomanip>
#include<sstream>
#include<unordered_map>
#include "structure.cpp"
#include "reader.cpp"

//Pass 1 of SIC assembler

class SIC{
    private:
        Optable optab;
        Symtable symtab;
        reader read;
        uint16_t locctr;
        uint16_t startAddress;
        uint16_t programLength;
        std::string programName;
        std::vector<reader::Instruction> instructions;

    
    public:
        bool runPassOne(const std::string &inputFile, const std::string &intermediateFile){
            if(!read.readFilePassOne(inputFile)){
                std::cerr<<"Error: Unable to open file\n";
                return false;
            }
            auto instructions = read.getInstructions();
            std::ofstream intermediate(intermediateFile);
            if(!intermediate.is_open()){
                std::cerr<<"Error: Unable to open file\n";
                return false;
            }
            locctr = 0;
            bool firstLine = true;

            for(const auto & inst : instructions){

                if(firstLine && inst.opcode == "START"){
                    programName = inst.label;
                    locctr = startAddress = std::stoi(inst.operand,nullptr,16);
                    intermediate<<std::hex<<locctr<<" "<<inst.label<<" "<<inst.opcode<<" "<<inst.operand<<std::endl;
                    firstLine = false;
                    continue;
                }
                intermediate<<std::hex<<locctr<<" "<<inst.label<<" "<<inst.opcode<<" "<<inst.operand<<std::endl;

                if(!inst.label.empty() && !symtab.exists(inst.label)){
                    symtab.insert(inst.label,locctr);
                }

                if(optab.isOpcode(inst.opcode))
                    locctr += 3;
                else if(inst.opcode == "WORD")
                    locctr += 3;
                else if(inst.opcode == "RESW")
                    locctr += 3*std::stoi(inst.operand);
                else if(inst.opcode == "RESB")
                    locctr += std::stoi(inst.operand);
                else if(inst.opcode == "BYTE"){
                    if(inst.operand.front() == 'X'){
                        locctr += (inst.operand.size()-3)/2;
                    }
                    else if(inst.operand.front() == 'C'){
                        locctr += inst.operand.size()-3;
                    }
                }
                else if(inst.opcode == "END"){
                    programLength = locctr - startAddress;
                    intermediate<<std::hex<<locctr<<" "<<inst.label<<" "<<inst.opcode<<" "<<inst.operand<<std::endl;
                    break;
                }
                
            }
            intermediate.close();
            read.clear();
                return true;
        }

        bool runPassTwo(const std::string &intermediateFile, const std::string &outputFile){
            if(!read.readFilePassTwo(intermediateFile)){
                std::cerr<<"Error: Unable to open file\n";
                return false;
            }
            std::ofstream output(outputFile);
            if(!output.is_open()){
                std::cerr<<"Error: Unable to open file\n";
                return false;
            }
            std::string line;
            
            auto instructions=read.getInstructions();
            output << "H^" << programName << "^" << std::hex << std::setw(6) << std::setfill('0') << startAddress << "^" << std::setw(6) << programLength << std::endl;
            
            uint8_t opcode;
            uint16_t address;
            for(const auto & inst : instructions){
                /*if(inst.opcode == "START")
                    continue;
                if(inst.opcode == "END")
                    break;
                if(optab.isOpcode(inst.opcode)){
                    opcode = optab.getOpcode(inst.opcode);
                    address = symtab.getAddress(inst.operand);*/
                    std::cout<<inst.opcode<<" "<<std::endl;
                    
                    
            }
            return true;


        }  


};

int main(){
    SIC assembler;
    const std::string inputFile = "code1.txt";
    const std::string intermediateFile = "inter.txt";
    if(assembler.runPassOne(inputFile, intermediateFile))
        std::cout<<"Pass 1 completed successfully\n";
    else
        std::cerr<<"Error: Pass 1 failed\n";
    const std::string outputFile = "output.txt";
    if(assembler.runPassTwo(intermediateFile, outputFile))
        std::cout<<"Pass 2 completed\n";
        return 0;
}