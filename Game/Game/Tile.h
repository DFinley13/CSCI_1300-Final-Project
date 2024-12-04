#ifndef TILE_H
#define TILE_H
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;


class Tile{

    public:
    Tile();
    void setColor(string _color);
    void setTileType(string _tile_type);
    string getColor() const;

    void randomizeTileType(bool isCubTraining, bool isFirstHalf);

    bool randomeRiddle();


    private:
    string color;
    string tile_type;


};


#endif