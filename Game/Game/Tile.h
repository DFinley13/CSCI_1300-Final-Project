#ifndef TILE_H
#define TILE_H
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Player.h"

using namespace std;


class Tile{

    public:
    Tile();
    void setColor(string _color);
    void setTileType(string _tile_type);
    string getColor() const;
    void setEventTrigger(string _event_trigger);
    string getEventTrigger() const;

    void randomizeTileType(bool isCubTraining, bool isFirstHalf);
    void handleEvent(int player_index, Player player, const string playerAdvisor, bool isCubTraining);

    bool playRockPaperScissors();


    private:
    string color;
    string tile_type;
    bool rockPaperScissorsResult;
    string event_trigger;


};


#endif