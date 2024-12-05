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