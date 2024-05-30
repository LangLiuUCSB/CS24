#include "WordList.h"

#include <iostream>

WordList::WordList(std::istream &stream)
{
    std::string word;
    bool allLower;
    while (stream >> word)
    {
        if (!word.size() || word[0] == '#')
        {
            continue;
        }
        allLower = true;
        for (char ch : word)
        {
            if (!islower(ch))
            {
                allLower = false;
                break;
            }
        }
        if (allLower)
        {
            mWords.push_back(word);
        }
    }
}

Heap WordList::correct(const std::vector<Point> &points, size_t maxcount, float cutoff) const
{
    Heap probableWords(maxcount);
    size_t i;
    double dx;
    double dy;
    double score;
    double heapmin = 0;
    for (std::string word : mWords)
    {
        if (word.size() != points.size())
        {
            continue;
        }
        score = 0;
        i = 0;
        for (char ch : word)
        {
            dx = points[i].x - QWERTY[ch - 97].x;
            dy = points[i].y - QWERTY[ch - 97].y;
            score += 1 / (10 * (dx * dx + dy * dy) + 1);
            ++i;
        }
        score /= i;
        if (score < cutoff || score < heapmin)
        {
            continue;
        }
        if (probableWords.count() != maxcount)
        {
            probableWords.push(word, score);
        }
        else
        {
            probableWords.pushpop(word, score);
            heapmin = score;
        }
    }
    return probableWords;
}
