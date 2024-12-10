

#include "player.h"
#include <iostream>

using namespace std;


Player::Player(){
        _name = "";
        _strength = 100;
        _stamina = 100;
        _wisdom = 100;
        _pride_points = 0;
        _age = 1;
}   

Player::Player(string name, int strength, int stamina, int wisdom){
    if(strength >= 100 && strength <= 1000){
        _strength = strength;
    }
    else{
        _strength = 100;
    }
    if(stamina >= 100 && stamina <= 1000){
        _stamina = stamina;
    }
    else{
        _stamina = 100;
    }
    if(wisdom >= 100 && wisdom <= 1000){
        _wisdom = wisdom;
    }
    else{
        _wisdom = 100;
    }
    _name = name;
    _pride_points = 0;
    _age = 1;
}

string Player::getName(){
    return _name;
}

int Player::getStrength(){
    return _strength;
}

int Player::getStamina(){
    return _stamina;
}

int Player::getWisdom(){
    return _wisdom;
}

int Player::getPridePoints(){
    return _pride_points;
}

int Player::getAge(){
    return _age;
}

void Player::setName(string name){
    _name = name;
}

void Player::setStrength(int strength){
    _strength = strength;
}

void Player::setStamina(int stamina){
    _stamina = stamina;
}

void Player::setWisdom(int wisdom){
    _wisdom = wisdom;
}

void Player::setPridePoints(int pride_points){
    _pride_points = pride_points;
}

void Player::setAge(int age){
    _age = age;
}

void Player::addStrength(int strength){
    _strength += strength;
}

void Player::addStamina(int stamina){
    _stamina += stamina;
}

void Player::addWisdom(int wisdom){
    _wisdom += wisdom;
}

void Player::addPridePoints(int pride_points){
    _pride_points += pride_points;
}

void Player::addAge(int age){
    _age += age;
}

void Player::setAdvisor(string adName, string adAbility){
    advisorName = adName;
    advisorAbility = adAbility;
}

int Player::choosePath() {
    int pathChoice;
    // Keep asking until the player chooses a valid path
    do {
        cout << "Choose your path:" << endl;
        cout << "1: Cub Training" << endl;
        cout << "2: Straight to the Pride Lands" << endl;
        cin >> pathChoice;

        if (cin.fail() || (pathChoice != 1 && pathChoice != 2)) {
            // If the input is invalid (non-integer or out of range), clear the error and discard the invalid input
            cin.clear();  // clear the error flag
            cin.ignore(99999, '\n');  // discard the invalid input
            cout << "Invalid input, please enter 1 or 2." << endl;
            continue;  // Prompt the user again
        }
        else{
            break; // if valid then break
        }
    } while (true);  // Continue asking until a valid choice is made
    
    if (pathChoice == 1){
            traincub(500, 500, 1000);  // Increase Strength, Stamina, Wisdom
    } 
    else if (pathChoice == 2){
            addStrength(200);  // Boost Strength
            addStamina(200);   // Boost Stamina
            addWisdom(200);    // Boost Wisdom
            toPrideLands();
    } 
    else{
            cout << "Invalid choice, please select 1 or 2." << endl;
    }
    return pathChoice;
}
void Player::traincub(int strength, int stamina, int wisdom){
    addStrength(strength);
    addStamina(stamina);
    addWisdom(wisdom);

    _pride_points -= 5000;
}
void Player::toPrideLands(){
    addStrength(-2000);
    addStamina(-1000);
    addWisdom(-2000);
    addPridePoints(5000);
}
void Player::printStats(){
    cout << _name << ", " << "age " << _age << endl;
    cout << "Strength: " << _strength << endl;
    cout << "Stamina: " << _stamina << endl;
    cout << "Wisdom: " << _wisdom << endl;
    cout << "Pride Points: " << _pride_points << endl;
}

string Player::getAdvisor() {
    return advisorName;
}

string Player::getAdvisorAbility() {
    return advisorAbility;
}
