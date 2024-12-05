//Anthony and David
#include "Tile.h"
#include <cstdlib>
#include <ctime>
using namespace std;


Tile::Tile(){
    color = "";
    tile_type = "";

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


bool Tile::randomeRiddle() {
    vector<string> riddles;
    vector<string> answers;
    int idx = 0;

    ifstream riddleList("riddles.txt");
    if (!riddleList.is_open()) {
        cerr << "Error: Could not open file " << "riddles.txt" << endl;
        return false;
    }

    string line;
    string firstLine;
    getline(riddleList, firstLine);


    while (getline(riddleList, line))
    {
    string riddle;

    stringstream stream(line);
    getline(stream, riddle, '|');

    string answer;
    getline(stream, answer);
    
    riddles.push_back(riddle);
    answers.push_back(answer);
    idx++;
    }

    int selcetion = randomGenerator(0, idx);

    string playerAnswer;
    bool giveUp = false;
    do
    {
    cout << "Your riddle is: " << riddles[selcetion];
    cin >> playerAnswer;

    if (playerAnswer == answers[selcetion])
    {
        return true;
    } else {
        char incorrectChoice;
        cout << "Incorrect! Try again! \n";
        cout << "If you give up press 'N' or press anything to continue" << endl;
        cin >> incorrectChoice;

        if (incorrectChoice == 'n' || incorrectChoice == 'N')
        {
            giveUp = true;
            break;
            return false;
        }  else {
            giveUp = false;
        }

    }
    } while (giveUp == false);
    
    
    return false;
}