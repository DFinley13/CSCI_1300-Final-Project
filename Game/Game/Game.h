
//Anthony
#ifndef GAME_H
#define Game_H

#include "player.h"
#include <vector>
#include "Board.h"
#include "Tile.h"

using namespace std;

class Game{

    private:
    vector<Player> _characters;
    vector<Player> _players;
    Board _board;
    int playerLastMove[5]= {0};

    public:
    Game();
    void loadCharacters(const string filename);
    void selectCharacters(int playerCount);
    void selectAdvisor(int player_index);
    void startGame();
    int randomGenerator(int min, int max);
    void applyAdvisorEffect(int player_index);

    //David
    int spinner();
    int amountOfPlayers();
    bool mainMenu();
    void tileAffect(string tilesColor, int player_index);
    void randomEvent(int player_index);
    void winscreen();
};




#endif