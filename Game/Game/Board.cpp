
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

void Board::initializeBoard() {
    for (int i = 0; i < 2; i++) {
        initializeTiles(i); 
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

bool Board::isPlayerOnTile(int player_index, int pos)
{
if (_player_lane[pos] == player_index){
    return true;
}
return false;
}

void Board::displayTile(int player_index, int pos, int lane) {
    string color = "";
    string playersOnTile = ""; // Collect all players on this tile
    bool player = false;
    
    // Determine color to display
    if (_tiles[player_index][pos].getColor() == "R") {
        color = RED;
    } else if (_tiles[player_index][pos].getColor() == "G") {
        color = GREEN;
    } else if (_tiles[player_index][pos].getColor() == "B") {
        color = BLUE;
    } else if (_tiles[player_index][pos].getColor() == "U") {
        color = PURPLE;
    } else if (_tiles[player_index][pos].getColor() == "N") {
        color = BROWN;
    } else if (_tiles[player_index][pos].getColor() == "P") {
        color = PINK;
    } else if (_tiles[player_index][pos].getColor() == "O") {
        color = ORANGE;
    } else if (_tiles[player_index][pos].getColor() == "Y") {
        color = GREY;
    }

    for (int i = 0; i < _player_count; i++) {
        if (getPlayerPosition(i) == pos && (_player_lane[i] - 1) == player_index) {
            if (!playersOnTile.empty()) {
                playersOnTile += " & "; // Add separator for multiple players
            }
            playersOnTile += to_string(i + 1); // Add player index
        }
    }

    // Display the tile
    if (!playersOnTile.empty()) {
        cout << color << "|" << playersOnTile << "|" << RESET;
    } else {
        cout << color << "| |" << RESET; // Empty tile
    }
}

void Board::displayTrack(int player_index)
    {
        if (player_index > 2)
        {
            cout << getBoardType(_player_lane[player_index]) << endl;
        } else {
            cout << getBoardType(player_index) << endl;
        }
    for (int i = 0; i < _BOARD_SIZE; i++)
    {
        if (player_index > 2)
        {
            displayTile(_player_lane[player_index] - 1, i, _player_lane[player_index]);
        } else {
            displayTile(player_index, i, _player_lane[player_index]);
        }
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

        if (currentPosition > 51)
        {
            _player_position[player_index] = 51;
        } else {
            _player_position[player_index] = currentPosition;
        }

    // Add a check for a winning condition
    if (currentPosition >= _BOARD_SIZE - 1) {
        return true; // Player has won
    }


    return false;
}
    
    
int Board::getPlayerPosition(int player_index) const{
    if (player_index >= 0 && player_index <= _player_count + 1){
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
    _player_position[player_index] = moveAmt;
}

string Board::currentTileColor(int player_index, int POS) {
    return _tiles[player_index][POS].getColor();
}

int Board::getPlayerCount() {
    return _player_count;
}

string Board::getBoardType(int player_index) {
    if (player_index == 0)
    {
       return "Club Training";
    } else {
        return "Straight to the Pride Lands";
    }
    
}