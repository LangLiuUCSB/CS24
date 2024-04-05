#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "USAGE: censor [length]" << std::endl;
        return 1;
    }
    size_t censor = std::stoi(argv[1]);
    std::string inSentence, outSentence;
    std::getline(std::cin, inSentence);
    bool prevNotSpace = inSentence[0] != ' ' || inSentence[0] != '\t';
    size_t WordStart = 0;
    while (inSentence[WordStart] == ' ' || inSentence[WordStart] == '\t')
    {
        WordStart++;
    }
    size_t wordSize = 0;
    for (size_t i = WordStart; i != inSentence.size(); i++)
    {
        if (inSentence[i] == ' ' || inSentence[i] == '\t')
        {
            if (prevNotSpace)
            {
                if (wordSize != censor)
                {
                    outSentence.append(inSentence.substr(WordStart, wordSize));
                    outSentence.push_back(' ');
                }
                wordSize = 0;
                prevNotSpace = false;
            }
            WordStart = i + 1;
        }
        else
        {
            wordSize++;
            prevNotSpace = true;
        }
    }
    if (prevNotSpace && wordSize != censor)
    {
        outSentence.append(inSentence.substr(WordStart, wordSize));
        outSentence.push_back(' ');
    }
    outSentence.pop_back();
    std::cout << outSentence << std::endl;
    return 0;
}