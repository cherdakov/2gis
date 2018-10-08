#include <string>
#include <iostream>
#include <vector>
#include <cctype>
#include <algorithm>

class InputParser{
public:
    InputParser (int argc, char **argv){
        for (int i=1; i < argc; ++i)
            this->tokens.push_back(std::string(argv[i]));
    }
    const std::string& getOption(const std::string &option) const{
        std::vector<std::string>::const_iterator it = std::find(this->tokens.begin(), this->tokens.end(), option);
        if (it != this->tokens.end() && ++it != this->tokens.end()){
            return *it;
        }
        static const std::string empty_string("");
        return empty_string;
    }
    bool optionExists(const std::string &option) const{
        return std::find(this->tokens.begin(), this->tokens.end(), option) != this->tokens.end();
    }
private:
    std::vector <std::string> tokens;
};

uint32_t getCountWordsInFile(const std::string& filename, const std::string& word){
    return 0;
}

uint32_t getFileCheckSum(const std::string& filename){
    return 0;
}

int main(int argc, char **argv){
    InputParser input(argc, argv);
    if(input.optionExists("-h")){
        std::cout<<"2GIS test task help message"<<std::endl;
        return 0;
    }
    std::string mode = "", filename = "";
    if(input.optionExists("-m")){
        mode = input.getOption("-m");
    } else{
        std::cout<<"Mode option does not exists"<<std::endl;
        return -1;
    }
    if(input.optionExists("-f")){
        filename = input.getOption("-f");
    } else{
        std::cout<<"Filename option does not exists"<<std::endl;
        return -1;
    }
    if("words" != mode && "checksum" != mode){
        std::cout<<"Incorrect mode"<<std::endl;
        return -1;
    }
    if("words" == mode){
        if(!input.optionExists("-v")){
            std::cout<<"-v required for this mode"<<std::endl;
            return -1;
        }
        std::string word = input.getOption("-v");
        if(word.empty()){
            std::cout<<"word is empty"<<std::endl;
            return -1;
        }
        uint32_t countWords = getCountWordsInFile(filename, word);
        std::cout<<"countWords: "<<countWords<<std::endl;
    } else if("checksum" == mode){
        uint32_t checksum = getFileCheckSum(filename);
        std::cout<<"checksum:"<<checksum<<std::endl;
    }
    return 0;
}