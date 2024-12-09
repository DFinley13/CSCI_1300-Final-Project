
#ifndef BOARD_H
#define BOARD_H
#include "Tile.h"
class Board
{
    private:
        static const int _BOARD_SIZE = 52;
        Tile _tiles[2][_BOARD_SIZE];
        static const int _MAX_PLAYERS = 5;
        int _player_count = 0;
        int _player_position[_MAX_PLAYERS];
        int _player_lane[_MAX_PLAYERS];
        void displayTile(int player_index, int pos, int lane);
        void initializeTiles(int player_index);
        bool isPlayerOnTile(int player_index, int pos);
        string boardTypes[2] = {"Cub Training", "Straight to the Pride Lands"};
    public:
        Board();
        Board(int player_count);
        void displayTrack(int player_index);
        void initializeBoard();
        void displayBoard();
        bool movePlayer(int player_index, int moveamount);
        int getPlayerPosition(int player_index) const;
        void setPlayerPosition(int player_index, int moveAmt);
        void setPlayer_count(int newPlayercount);
        void setPlayerLane(int playerLane, int player_index);
        int getPlayerLane(int player_index);
        string getBoardType(int player_index);
        string currentTileColor(int player_index, int POS);
        int getPlayerCount();
        
};

#endif