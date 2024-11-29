
#include "game.h"
#include "Board.h"
#include "player.h"
#include <cstdlib>
#include <ctime>
using namespace std;

//Anthony
int main() {
    srand(time(0)); // Seed random number generator
    Game game;

    // Load characters from the file
    game.loadCharacters("characters.txt");

    // Ask how many players will play
    cout << "Enter the number of players (2 to 5): ";
    int playerCount;
    cin >> playerCount;
    Board board = Board(playerCount);

    if (playerCount < 1 || playerCount > 5) {
        cerr << "Invalid number of players. Exiting game.\n";
        return 1;
    }

    // Players select their characters
    game.selectCharacters(playerCount);

    //Load the board
    board.initializeBoard();
    board.displayBoard();

    game.mainMenu();
    // Start the game
    // game.startGame();

    // //david
    // cout << game.spinner();
    // return 0;
}