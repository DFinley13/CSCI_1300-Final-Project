
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

using namespace std;

class Player{

    private:
    string _name;
    int _strength, _stamina, _wisdom, _pride_points, _age;
    string advisorName;
    string advisorAbility;

    public:
    //Default Constructor
    Player();
    //Parameterized Constructor
    Player(string name, int strength, int stamina, int wisdom);
    
    //Getters
    string getName();
    int getStrength();
    int getStamina();
    int getWisdom();
    int getPridePoints();
    int getAge();
    string getAdvisor();
    string getAdvisorAbility();

    //Setters
    void setName(string name);
    void setStrength(int strength);
    void setStamina(int stamina);
    void setWisdom(int wisdom);
    void setPridePoints(int pride_points);
    void setAge(int age);

    //Funcitons
    void addStrength(int strength);
    void addStamina(int stamina);
    void addWisdom(int wisdom);
    void addPridePoints(int pride_points);
    void addAge(int age);

    //Anthony
    void setAdvisor(string name, string ability);
    void traincub(int strength, int stamina, int wisdom);
    void choosePath();
    void toPrideLands(); 
    void printStats();

};




#endif