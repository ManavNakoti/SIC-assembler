//Helper functions for SIC Assembler
#include<iostream>
#include<unordered_map>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>

class reader{
    public:
        struct Instruction{
            uint32_t address;
            std::string label;
            std::string opcode;
            std::string operand;
            
        }; 
    private:
        std::vector<Instruction> instructions;
        std::ifstream file;
        std::string line;
        std::string label;
        std::string opcode;
        std::string operand;
        uint32_t address;
    public:
       
        Instruction parseLinePassOne(const std::string& line){
            Instruction inst={0,"","",""};
            std::stringstream ss(line);
            std::string part;
            ss>>part;

            if(part.back()==':'){
                inst.label=part.substr(0,part.size()-1);
                ss>>inst.opcode>>inst.operand;
            }
            else{
                inst.label="";
                inst.opcode=part;
                ss>>inst.operand;
            }
            return inst;
        }

        Instruction parseLinePassTwo(const std::string& line){
            Instruction inst;
            std::stringstream ss(line);
            ss>>std::hex>>inst.address>>inst.label>>inst.opcode>>inst.operand;
            return inst;
        }       

        bool readFilePassOne(std::string filename){
            std::ifstream file(filename);
            if(!file.is_open())return false;

            std::string line;
            while(std::getline(file,line)){
                if(line.empty())continue;
                instructions.push_back(parseLinePassOne(line));
            }
            file.close();
            return true;
        }

        bool readFilePassTwo(std::string filename){
            std::ifstream file(filename);
            if(!file.is_open())return false;

            std::string line;
            while(std::getline(file,line)){
                if(line.empty())continue;
                instructions.push_back(parseLinePassTwo(line));
            }
            file.close();
            return true;
        }

        const std::vector<Instruction>& getInstructions(){
            return instructions;
        }

        void clear(){
            instructions.clear();
        }
};