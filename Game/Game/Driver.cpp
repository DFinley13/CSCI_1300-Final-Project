
#include "game.h"
#include "Board.h"
#include "player.h"
#include <cstdlib>
#include <ctime>
using namespace std;

//Anthony
int main() {
    Tile _tile;
    srand(time(0)); // Seed random number generator
    Game game;
    Board _board;


    // Load characters from the file
    game.loadCharacters("characters.txt");

    // Ask how many players will play
    cout << "Enter the number of players (2 to 5): ";
    int playerCount;
    cin >> playerCount;

    if (playerCount < 1 || playerCount > 5) {
        cerr << "Invalid number of players. Exiting game.\n";
        return 1;
    }

    // Players select their characters
    game.selectCharacters(playerCount);

    game.startGame();

    

    bool playerWon = false;
    while (playerWon == false)
    {
        playerWon = game.mainMenu();
    }
    
    
    return 0;
}