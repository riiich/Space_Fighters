//
// Created by horic on 11/20/2020.
//

#include "Leaderboard.h"

namespace LeaderboardNamespace
{

    Leaderboard::Leaderboard()
    {}

    void Leaderboard::loadFromFile(std::ifstream& scoreFile)
    {
        //load the scores from the file into a heap
        int score;

        if(!scoreFile)
        {
            std::cout << "ERROR: High Score Tracker text file is not found!\n";
        }

        while(!scoreFile.eof()) //read the scores until the end of the file
        {
            scoreFile >> score;
            this->scores.push(score);   //put the score into heap
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
        return this->leaderboard.front(); //returns the highest score in the queue
    }

    Queue<int> Leaderboard::getQueueLeaderBoard() const
    {
        return this->leaderboard;
    }

}