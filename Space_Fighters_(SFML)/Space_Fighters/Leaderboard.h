//
// Created by horic on 11/20/2020.
//

#ifndef SFML_PROJECTS_CS3A_LEADERBOARD_H
#define SFML_PROJECTS_CS3A_LEADERBOARD_H
#include "../DataStructures/Heap.h"
#include "../DataStructures/Queue.h"
#include <fstream>

namespace LeaderboardNamespace
{
    class Leaderboard {
    public:
        Leaderboard();
        void loadFromFile(std::ifstream& scoreFile);    //load all the scores from the text file into a heap and push into a queue
        int getHighestScore() const;    //get the front score in the queue (at this point, it should be the highest score)
        Queue<int> getQueueLeaderBoard() const;

    private:
        Heap<int> scores;    //heap will keep popping the highest score at the top
        Queue<int> leaderboard;  //gets the scores from the heap, (queue FIFO)
    };
}


#endif //SFML_PROJECTS_CS3A_LEADERBOARD_H