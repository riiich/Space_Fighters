//
// Created by horic on 11/20/2020.
//

#include "Leaderboard.h"
#include <sstream>

namespace LeaderboardNamespace
{

    Leaderboard::Leaderboard()
    {}

    void Leaderboard::loadFromFile(std::ifstream& scoreFile)
    {
        while(!this->leaderboard.empty())
            this->leaderboard.pop();

        //load the scores from the file into a heap
        if(!scoreFile)
        {
            std::cout << "ERROR: High Score Tracker text file is not found!\n";
            return;
        }

        const std::vector<LeaderboardEntry> entries = loadEntries(scoreFile);
        for(const LeaderboardEntry& entry : entries)
        {
            this->scores.push(entry.score);
        }
        scoreFile.close();

        while(!this->scores.empty())    //pop all the scores from the heap
        {
            //put the scores inside a queue from the heap (highest score should be on the top of the stack)
            this->leaderboard.push(this->scores.pop()); //put the score that was popped from the heap into the queue
        }
    }

    int Leaderboard::getHighestScore() const
    {
        if(this->leaderboard.empty())
        {
            return 0;
        }

        return this->leaderboard.front(); //returns the highest score in the queue
    }

    Queue<int> Leaderboard::getQueueLeaderBoard() const
    {
        return this->leaderboard;
    }

    std::vector<LeaderboardEntry> Leaderboard::loadEntries(std::istream& scoreFile)
    {
        std::vector<LeaderboardEntry> entries;
        std::string line;

        while(std::getline(scoreFile, line))
        {
            std::stringstream row(line);
            std::string firstValue;
            if(!(row >> firstValue))
                continue;

            LeaderboardEntry entry;
            std::stringstream legacyScore(firstValue);
            if((legacyScore >> entry.score) && legacyScore.eof())
            {
                entry.username = "PLAYER";
            }
            else
            {
                entry.username = firstValue;
                if(!(row >> entry.score))
                    continue;
            }

            entries.push_back(entry);
        }

        return entries;
    }

}
