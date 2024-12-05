//Anthony and David
#include "game.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

Game::Game(){
    
}

void Game::loadCharacters(const string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        string name;
        int age, strength, stamina, wisdom, pridePoints;

        stringstream stream(line);
        getline(stream, name, '|');

        string ageStr, strengthStr, staminaStr, wisdomStr, pridePointsStr;
        getline(stream, ageStr, '|');
        getline(stream, strengthStr, '|');
        getline(stream, staminaStr, '|');
        getline(stream, wisdomStr, '|');
        getline(stream, pridePointsStr, '|');

        age = stoi(ageStr);
        strength = stoi(strengthStr);
        stamina = stoi(staminaStr);
        wisdom = stoi(wisdomStr);
        pridePoints = stoi(pridePointsStr);

        Player character(name, strength, stamina, wisdom);
        character.setAge(age);
        character.setPridePoints(pridePoints);

        _characters.push_back(character);
    }

    file.close();
}

void Game::selectCharacters(int playerCount) {
    int n = _characters.size();
    while (playerCount < 2 || playerCount > n) {
        cerr << "Error: Invalid number of players. You must select between 2 and " << n << " players.\n";
        cout << "Enter the number of players: ";
        cin >> playerCount;
    }

    // Display available characters
    cout << "Available Characters:\n";
    for (int i = 0; i < n; ++i) {
        cout << i + 1 << ": ";
        _characters[i].printStats();
        cout << endl;
    }

    vector<bool> selected(n, false);

    for (int i = 0; i < playerCount; ++i) {
        cout << "Player " << i + 1 << ", choose your character by number: ";
        int choice;
        cin >> choice;

        while (choice < 1 || choice > n || selected[choice - 1]) {
            cerr << "Invalid choice or character already chosen. Try again: ";
            cin >> choice;
        }

        // Add the selected character to the players list
        _players.push_back(_characters[choice - 1]);
        selected[choice - 1] = true; // Mark the character as chosen

        // Ask for path choice
        cout << "Player " << i + 1 << ", choose your path 1 (Cub Training) or 2 (Straight to Pride Land): ";
        int pathChoice;
        cin >> pathChoice;

        // Apply path effects
        _players[i].choosePath(pathChoice);
    }

    // Confirm selections
    int k = _players.size();
    cout << "\nPlayers have chosen their characters and paths:\n";
    for (int i = 0; i < k; ++i) {
        cout << "Player " << i + 1 << ":\n";
        _players[i].printStats();
        cout << endl;
    }
}

void Game::selectAdvisor(){
    // Advisor options
    vector<string> advisorNames = {"Rafiki", "Nala", "Sarabi", "Zazu", "Sarafina"};
    vector<string> advisorAbilities = {"Invisibility", "Night Vision", "Energy Manipulation", "Weather Control", "Super Speed"};

    int n = _players.size();
    int l = advisorNames.size();
    // Allow each player to select an advisor
    for (int i = 0; i < n; ++i) {
        cout << "Player " << i + 1 << ", choose an advisor:\n";
        for (int j = 0; j < l; ++j) {
            cout << j + 1 << ". " << advisorNames[j] << " - " << advisorAbilities[j] << endl;
        }

        int advisorChoice;
        cin >> advisorChoice;

        // Assign the chosen advisor to the player
        if (advisorChoice >= 1 && advisorChoice <= l) {
            _players[i].setAdvisor(advisorNames[advisorChoice - 1], advisorAbilities[advisorChoice - 1]);
        } else {
            cout << "Invalid choice. No advisor selected.\n";
        }
    }
}

void Game::startGame() {
    // cout << "Starting the game...\n";
    int k = _players.size();
    // Placeholder
    for (int i = 0; i < k; ++i) {
        cout << "Player " << i + 1 << " stats:\n";
        _players[i].printStats();
        cout << endl;
    }
}

int Game::spinner() {
    srand(time(0));
    int spinner_out_put = 0;

    spinner_out_put = rand() % 8;

    return spinner_out_put;
}