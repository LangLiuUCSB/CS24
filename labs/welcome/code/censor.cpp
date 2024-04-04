#include <iostream>
#include <string>

int main(int argc, char* argv[]){
    if(argc != 2){
        std::cout << "USAGE: censor [length]" << std::endl;
        return 1;
    }

    int censor = std::stoi(argv[1]);

    std::string userSentence;
    std::getline(std::cin, userSentence);

    int wordStart = 0;
    int wordSize = 0;
    bool isPrevSpace = false;
    for(unsigned int i = 0; i != userSentence.size(); i++){
        if(userSentence[i] != ' ' && userSentence[i] != '\t'){
            wordSize++;
            isPrevSpace = false;
        }
        else{
            if(wordSize != censor && !isPrevSpace){
                std::cout << userSentence.substr(wordStart, wordSize) << ' ';
            }
            wordSize = 0;
            wordStart = i + 1;
            isPrevSpace = true;
        }
    }
    if(wordSize != censor && !isPrevSpace){
        std::cout << userSentence.substr(wordStart);
    }
    std::cout << std::endl;
    return 0;
}