//Anthony
#include "game.h"
#include "Board.h"
#include "player.h"
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

        // Apply path effects
        _players[i].choosePath();
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

//David
int Game::spinner() {
    // random seed
    srand(time(0));
    int spinner_out_put = 0;

    // Random number 1-7
    spinner_out_put = rand() % 8;

    // Give the output
    return spinner_out_put;
}

// Outputs as a public tool the amount of players
int Game::amountOfPlayers() {
    return _players.size();
}

void Game::mainMenu() {
    for (int i = 0; i < _players.size(); i++)
    {
       bool validchoice = false;
    Board b;
    Player p;
    int idx = 0;
    while (validchoice == false)
    {
    cout << "Main Menu: Select an option to continue for player: " << i + 1 <<  "\n"  
    "1. Check Player Progress \n" 
    "2. Review Character \n"
    "3. Check Position \n"
    "4. Review your Advisor \n"
    "5. Move Forward \n \n" 
    "Please choose an option using the corresponding number: \n";

    int menuChoice;
    cin >> menuChoice;

    if (menuChoice < 1 || menuChoice > 5)
    {
        cout << "Invalid Choice!" << endl;
    } else if (menuChoice == 1) {
        char choice;
        while (validchoice == false)
        {
            cout << "Do you want to convert your Leadership Traits to Pride Points? \n"
            "Y for yes N for no \n";
            cin >> choice;
            if (choice == 'Y') {
                int testStamina = _players[i].getStamina();
                int testStrength = _players[i].getStrength();
                int testWisdom = _players[i].getWisdom();
                int testPridePoints = _players[i].getPridePoints();
                while (testStamina > 100)
                {
                    testStamina -= 100;
                    testPridePoints += 1000;
                }
                while (testStrength > 100) {
                    testStrength -= 100;
                    testPridePoints += 1000;
                } 
                while (testWisdom > 100) {
                    testWisdom -= 100;
                    testPridePoints += 1000;
                }
                cout << "Player " << i + 1 << " combined Pride Points: " << testPridePoints << endl;
                break;
            } else if (choice == 'N') {
                cout << "Player " << i + 1 << " current Pride Points: " << _players[i].getPridePoints() << endl;
                break;
            } else {
                cout << "Invalid option" << endl;
            }
        }
    } else if (menuChoice == 2) {
        _players[i].printStats();
    } else if (menuChoice == 3) {
         b.displayBoard();
    } else if (menuChoice == 4) {
        char continueInput;
        bool valid = false;
        cout << "Your advisor is: " <<  _players[i].getAdvisor() << endl;
        cout << "Their ability is: " << _players[i].getAdvisorAbility() << endl;
        cout << "Press Y to continue" << endl;
        cin >> continueInput;
        while (valid == false)
        {
            if (continueInput == 'Y')
            {
                break;
            } else {
                cout << "Press 'Y' to continue" << endl;
            }
        }
        
    } else if (menuChoice == 5) {
        b.movePlayer(i);
        cout << "Player " << i + 1 << " moved foward: " << spinner() << " spaces" << endl;
        break;
    } else {
        cout << "Invalid Choice" << endl;
    }
    idx++;
         cout << "----------" << "\n" << endl;
        }
         cout << "----------" << "\n" << endl;
    }
}