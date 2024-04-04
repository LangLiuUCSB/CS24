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
    bool first = true;
    for(unsigned int i = 0; i != userSentence.size(); i++){
        if(userSentence.size()-1 && userSentence[i] != ' ' && userSentence[i] != '\t'){
            wordSize++;
            isPrevSpace = false;
        }
        else{
            if(wordSize != censor && !isPrevSpace){
                if(first){
                    std::cout << userSentence.substr(wordStart, wordSize);
                    first = false;
                }else{
                    std::cout << ' ' << userSentence.substr(wordStart, wordSize);
                }
            }
            wordSize = 0;
            wordStart = i + 1;
            isPrevSpace = true;
        }
        if(i = userSentence.size()-1){
            std::cout << ' ' << userSentence.substr(wordStart, wordSize);
        }
    }
    std::cout << std::endl;
    return 0;
}