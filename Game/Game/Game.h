#ifndef GAME_H
#define Game_H

#include "Player.h"
#include <vector>

using namespace std;

class Game{

    private:
    vector<Player> _characters;
    vector<Player> _players;

    public:
    Game();
    void loadCharacters(const string filename);
    void selectCharacters(int playerCount);
    void selectAdvisor();
    void startGame();

};




#endif