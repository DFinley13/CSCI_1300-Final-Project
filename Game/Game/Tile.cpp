#include "Tile.h"
#include "player.h"
#include "game.h"
#include <cstdlib>
#include <ctime>
using namespace std;


Tile::Tile(){
    color = "";
    tile_type = "";
    event_trigger = "";
    rockPaperScissorsResult = false;

}

void Tile::setColor(string _color){
    color = _color;
}
string Tile::getColor() const{
    return color;
}

void Tile::setTileType(string _tile_type){
    tile_type = _tile_type;
}

void Tile::setEventTrigger(string _event_trigger) {
    event_trigger = _event_trigger;
}

string Tile::getEventTrigger() const {
    return event_trigger;
}

void Tile::randomizeTileType(bool isCubTraining, bool isFirstHalf) {
    int random = rand() % 100 + 1;

    if (isCubTraining) {
        // Cub Training Lane
        if (random <= 80) {
            tile_type = "Grassland";
        } else if (random <= 100) {
            if (isFirstHalf) {
                if (random <= 25) {
                    tile_type = "Oasis";
                } else if (random <= 50) {
                    tile_type = "Graveyard";
                } else {
                    tile_type = "Challenge";
                }
            } else {
                if (random <= 15) {
                    tile_type = "Oasis";
                } else if (random <= 35) {
                    tile_type = "Graveyard";
                } else {
                    tile_type = "Challenge";
                }
            }
        }
    } else {
        // Straight to the Pride Lands Lane
        if (random <= 80) {
            tile_type = "Grassland";
        } else {
            if (isFirstHalf) {
                if (random <= 25) {
                    tile_type = "Graveyard";
                } else if (random <= 50) {
                    tile_type = "Hyena";
                } else {
                    tile_type = "Challenge";
                }
            } else {
                if (random <= 15) {
                    tile_type = "Graveyard";
                } else if (random <= 30) {
                    tile_type = "Hyena";
                } else {
                    tile_type = "Oasis";
                }
            }
        }
    }
}

int randomGenerator(int min, int max)
{
    return (rand() % (max - min + 1) + min);
}


// Play Rock Paper Scissors
bool Tile::playRockPaperScissors() {
    int choice;
    bool loop = true;
    cout << "Play Rock Paper Scissors to regain your turn!" << endl;
    while (loop) {
        cout << "Choose Rock(1), Paper(2), or Scissors(3)" << endl;
        while (cin >> choice) {
            if (choice > 0 && choice < 4) {
                break;
            } else {
                cout << "Invalid input! Please choose Rock(1), Paper(2), or Scissors(3)." << endl;
            }
        }
        int randomChoice = randomGenerator(1, 3);
        if (choice == 1) { // Rock
            if (randomChoice == 1) {
                cout << "Tie! Play again!" << endl;
            } else if (randomChoice == 2) {
                cout << "You lost! You do not get your turn back." << endl;
                rockPaperScissorsResult = false;
                return false;
            } else {
                cout << "You won! You get your turn back!" << endl;
                rockPaperScissorsResult = true;
                return true;
            }
        } else if (choice == 2) { // Paper
            if (randomChoice == 1) {
                cout << "You won! You get your turn back!" << endl;
                rockPaperScissorsResult = true;
                return true;
            } else if (randomChoice == 2) {
                cout << "Tie! Play again!" << endl;
            } else {
                cout << "You lost! You do not get your turn back." << endl;
                rockPaperScissorsResult = false;
                return false;
            }
        } else { // Scissors
            if (randomChoice == 1) {
                cout << "You lost! You do not get your turn back." << endl;
                rockPaperScissorsResult = false;
                return false;
            } else if (randomChoice == 2) {
                cout << "You won! You get your turn back!" << endl;
                rockPaperScissorsResult = true;
                return true;
            } else {
                cout << "Tie! Play again!" << endl;
            }
        }
    }
    return false;
}

void Tile::handleEvent(int player_index, Player player, const string playerAdvisor, bool isCubTraining) {
    if (tile_type == "Graveyard") {
        cout << "You encounter a Graveyard event!" << endl;
        // If advisor is Sarabi and player is in cub training, skip this event
        if (isCubTraining && playerAdvisor == "Sarabi") {
            cout << "Sarabi helps you avoid the danger of the Graveyard!" << endl;
        } else {
            // Apply the penalty of losing pride points in the Graveyard
            cout << "You lose some pride points in the Graveyard!" << endl;
            player.addPridePoints(-200); // Subtract 200 pride points
        }
    } else if (tile_type == "Oasis") {
        cout << "You encounter an Oasis event!" << endl;
        // If advisor is Rafiki, gain pride points
        if (playerAdvisor == "Rafiki") {
            cout << "Rafiki's wisdom restores your energy!" << endl;
            player.addPridePoints(300); // Add 300 pride points
        } else {
            cout << "You gain a small bonus from the Oasis." << endl;
            player.addPridePoints(100); // Add 100 pride points
        }
    } else if (tile_type == "Challenge") {
        cout << "You encounter a Challenge event!" << endl;
        // Play Rock Paper Scissors to regain turn
        if (playRockPaperScissors()) {
            // If won, player gets turn back (regained turn means some kind of bonus or skipping penalty)
            cout << "You successfully regained your turn!" << endl;
            player.addPridePoints(50); // Example: Player gets 50 pride points for winning
        } else {
            cout << "You lost! No turn for you this time." << endl;
        }
    } else if (tile_type == "Hyena") {
        cout << "You encounter a Hyena event!" << endl;
        // Penalty for Hyena encounter
        cout << "The Hyenas cause you to lose pride!" << endl;
        player.addPridePoints(-300); // Subtract 300 pride points
    }
}