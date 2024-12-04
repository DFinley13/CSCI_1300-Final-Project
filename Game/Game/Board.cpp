
#include "Board.h"
#include "game.h"
#include "player.h"
#include <cstdlib> // For rand() and srand()
#include <ctime> // For time()
#define RED "\033[48;2;230;10;10m"
#define GREEN "\033[48;2;34;139;34m" /* Grassy Green (34,139,34) */
#define BLUE "\033[48;2;10;10;230m"
#define PINK "\033[48;2;255;105;180m"
#define BROWN "\033[48;2;139;69;19m"
#define PURPLE "\033[48;2;128;0;128m"
#define ORANGE "\033[48;2;230;115;0m" /* Orange (230,115,0) */
#define GREY "\033[48;2;128;128;128m" /* Grey (128,128,128) */
#define RESET "\033[0m"
void Board::initializeBoard()
{
// Seed random number generator in your main function once
for (int i = 0; i < 2; i++)
{
    initializeTiles(i); // This ensures each lane has a unique tile distribution
}
}

void Board::initializeTiles(int player_index)
{
Tile temp;
int green_count = 0;
int total_tiles = _BOARD_SIZE;
// Keep track of green tile positions to ensure we place exactly 30 greens
    for (int i = 0; i < total_tiles; i++){
        if (i == total_tiles - 1) {
    // Set the last tile as Orange for "Pride Rock"
            temp.setColor("O");
    }
        else if (i == 0) {
    // Set the last tile as Orange for "Pride Rock"
        temp.setColor("Y");
    }
    else if (green_count < 30 && (rand() % (total_tiles - i) < 30 - green_count)) {
        temp.setColor("G");
        green_count++;
    }
        else
    {
    // Randomly assign one of the other colors: Blue, Pink, Brown, Red, Purple
        int color_choice = rand() % 5;
        switch (color_choice){
            case 0:
            temp.setColor("B"); // Blue
            break;
            case 1:
            temp.setColor("P"); // Pink
            break;
            case 2:
            temp.setColor("N"); // Brown
            break;
            case 3:
            temp.setColor("R"); // Red
            break;
            case 4:
            temp.setColor("U"); // Purple
            break;
    }
}
// Assign the tile to the board for the specified lane
    _tiles[player_index][i] = temp;
}
}

Board::Board()
{
_player_count = 0;
// Initialize player position
_player_position[_player_count] = 0;
// Initialize tiles
initializeTiles(_player_count);
}

Board::Board(int player_count)
{
    if (player_count > _MAX_PLAYERS){
        _player_count = _MAX_PLAYERS;
    }
    else
    {
        _player_count = player_count;
    }
    // Initialize player position
    for (int i = 0; i < _player_count; i++){
        _player_position[i] = 0;
    }
    // Initialize tiles
    initializeBoard();
}

bool Board::isPlayerOnTile(int player_index, int pos, int lane) {
    if (player_index == pos && lane == 0)
    {
        return true;
    }
    return false;
}


void Board::displayTile(int player_index, int pos, int lane) {
    string color = "";
    bool player1_on_tile = (_player_position[0] == pos && _player_lane[0] == lane);
    bool player2_on_tile = (_player_position[1] == pos && _player_lane[1] == lane);

    bool onLaneOne = isPlayerOnTile(player_index, pos, lane);

    // Determine color for the tile
    string tileColor = _tiles[player_index][pos].getColor();
    if (tileColor == "R") {
    color = RED;
    } else if (tileColor == "G") {
    color = GREEN;
    } else if (tileColor == "B") {
    color = BLUE;
    } else if (tileColor == "U") {
    color = PURPLE;
    } else if (tileColor == "N") {
    color = BROWN;
    } else if (tileColor == "P")  {
    color = PINK;
    } else if (tileColor == "O") {
    color = ORANGE;
    } else if (tileColor == "Y") {
    color = GREY;
    }

    // Display logic
    cout << color << "|";
    if (player1_on_tile && player2_on_tile) {
        cout << "1&2";  // Both players on the same tile
    } else if (player1_on_tile) {
        cout << "1";  // Only player 1 on this tile
    } else if (player2_on_tile) {
        cout << "2";  // Only player 2 on this tile
    } else {
        cout << " ";  // Empty tile
    }
    cout << "|" << RESET;
}


void Board::displayTrack(int player_index)
    {
    // cout << getBoardType(player_index) << endl;
    for (int i = 0; i < _BOARD_SIZE; i++)
    {
    displayTile(player_index, i, _player_lane[player_index]);
    }
    cout << endl;
    }

    void Board::displayBoard()
    {
    for (int i = 0; i < 2; i++)
    {
    displayTrack(i);
    if (i == 0) {
    cout << endl; // Add an extra line between the two lanes
    }
    }
}

bool Board::movePlayer(int player_index, int moveamount) {
    int currentPosition = _player_position[player_index];
    currentPosition += moveamount; // Move the player by the spinner value
    _player_position[player_index] = currentPosition;

    // Add a check for a winning condition
    if (currentPosition >= _BOARD_SIZE - 1) {
        return true; // Player has won
    }

    return false;
}
    
    
int Board::getPlayerPosition(int player_index) const{
    if (player_index >= 0 && player_index <= _player_count){
         return _player_position[player_index];
    } 
    return -1;
}

void Board::setPlayer_count(int newplayerCount) {
    _player_count = newplayerCount;
}

void Board::setPlayerLane(int playerlane, int player_index) {
    _player_lane[player_index] = playerlane;
}

int Board::getPlayerLane(int player_index) {
    return _player_lane[player_index];
}

void Board::setPlayerPosition(int player_index, int moveAmt) {
    _player_position[player_index] += moveAmt;
}
