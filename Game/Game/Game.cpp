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
        int playerPath = _players[i].choosePath();
        _board.setPlayerLane(playerPath, i);
        if (playerPath == 1)
        {
            selectAdvisor(i);
        }
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

void Game::selectAdvisor(int player_index){
    // Advisor options
    vector<string> advisorNames = {"Rafiki", "Nala", "Sarabi", "Zazu", "Sarafina"};
    vector<string> advisorAbilities = {"Invisibility", "Night Vision", "Energy Manipulation", "Weather Control", "Super Speed"};

    int l = advisorNames.size();
    // The player to select an advisor
        cout << "Player " << player_index + 1 << ", choose an advisor:\n";
        for (int j = 0; j < l; ++j) {
            cout << j + 1 << ". " << advisorNames[j] << " - " << advisorAbilities[j] << endl;
        }

        int advisorChoice;
        cin >> advisorChoice;

        // Assign the chosen advisor to the player
        if (advisorChoice >= 1 && advisorChoice <= l) {
            _players[player_index].setAdvisor(advisorNames[advisorChoice - 1], advisorAbilities[advisorChoice - 1]);
        } else {
            cout << "Invalid choice. No advisor selected.\n";
        }

        char userInput;
        cout << "You have choosen " << _players[player_index].getAdvisor() << " with the abillity " << _players[player_index].getAdvisorAbility() << "\n";
        cout << "Is this correct? Enter 'N' if incorrect, 'Y if correct \n";
        cin >> userInput;
            if (userInput == 'N' || userInput == 'n')
            {
              selectAdvisor(player_index);  
            } 
        cout << endl;
}
    

void Game::startGame() {
    cout << "Starting the game...\n";

    int k = _players.size();
    // Placeholder
    for (int i = 0; i < k; ++i) {
        cout << "Player " << i + 1 << " stats:\n";
        _players[i].printStats();
        cout << endl;
    }

    _board.initializeBoard();
    _board.displayBoard();
    cout << endl;
}

//David
int Game::spinner() {
    srand(time(0));
    int spinner_out_put = 0;

    // Random number 1-6
    spinner_out_put = rand() % 6 + 1;

    // Give the output
    return spinner_out_put;
}

// Outputs as a public tool the amount of players
int Game::amountOfPlayers() {
    return _players.size();
}

bool Game::mainMenu() {
    // For each players turn
    int playersize;
    if (_players.size() > 2)
    {
        playersize = 2;
    } else {
        playersize = 2; 
    }
    
    for (int i = 0; i < playersize; i++)
    {
        //To continue the while loop
       bool validchoice = false;
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
            if (choice == 'Y' || choice == 'y') {
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
            } else if (choice == 'N' || choice == 'n') {
                cout << "Player " << i + 1 << " current Pride Points: " << _players[i].getPridePoints() << endl;
                break;
            } else {
                cout << "Invalid option" << endl;
            }
        }
    } else if (menuChoice == 2) {
        _players[i].printStats();
    } else if (menuChoice == 3) {
        _board.displayTrack(_board.getPlayerLane(i) - 1);
    } else if (menuChoice == 4) {
        char continueInput;
        bool valid = false;
        cout << "Your advisor is: " <<  _players[i].getAdvisor() << endl;
        cout << "Their ability is: " << _players[i].getAdvisorAbility() << endl;
        cout << "Press Y to continue" << endl;
        while (valid == false)
        {
            cin >> continueInput;
            if (continueInput == 'Y' || continueInput == 'y')
            {
                break;
            } else {
                cout << "Press 'Y' to continue" << endl;
            }
        }
        
    } else if (menuChoice == 5) {
            // Move player forward
            int moveAmount = spinner();
            bool won = false;

            // Call movePlayer with the current player index
                won = _board.movePlayer(i, moveAmount); // Move the player i
                if (won == true) {
                    cout << "Player " << i + 1 << " has won!!!" << endl;
                    return won;
                }
            cout << "Player " << i + 1 << " moved forward: " << moveAmount << " spaces." << endl;
            _board.displayTrack(_board.getPlayerLane(i) - 1); // Display the updated track
            validchoice = true;
    } else {
        cout << "Invalid Choice" << endl;
    }
        }
         cout << "----------" << "\n" << endl;
    }
    return false;
}

void Game::tileAffect(string tilesColor, int player_index) {
    if (tilesColor == "G")
    {
        //Create the random events fucntion
    } else if (tilesColor == "B") 
    {
        cout << "You’ve found a peaceful oasis! \n";
        cout << "You get a extra turn to move forward!" << endl; 

        _players[player_index].addStamina(200);
        cout << "You gained +200 Stamina" << endl;
       
        _players[player_index].addStrength(200);
         cout << "You gained +200 Strength" << endl;

        _players[player_index].addWisdom(200);
         cout << "You gained +200 Wisdom" << endl;
    } 
    else if (tilesColor == "P") 
    {
        cout << "Welcome to the land of enrichment - when landing on this tile, your Stamina, Strength, and Wisdom \n";
        cout << "Points increase by 300, and you get to choose an advisor from the available list of advisors. \n";
        cout << "If you already have an advisor, you can switch your advisor out for a different one from the list or keep your original advisor. \n";
        cout << "Don’t forget - an advisor can protect you from random events that negatively impact your Pride Points." << endl;

        _players[player_index].addStamina(300);
        _players[player_index].addStrength(300);
        _players[player_index].addWisdom(300);

        string currentAdvisor = _players[player_index].getAdvisor();
        string currentAdvisorAbillity = _players[player_index].getAdvisorAbility();
        if (currentAdvisor == "" && currentAdvisorAbillity == "")
        {
            char change;
            cout << "Would you like to from chagne Advisors?" << endl;
            cout << "You currently have " << currentAdvisor << " with the abillity " << currentAdvisorAbillity << endl;
            cout << "Press Y for yes and N for no" << endl;
            cin >> change;
            if (change == 'y' || change == 'y')
            {
                cout << "Great!" << endl;
                selectAdvisor(player_index);
            } else {
                cout << "Good choice! " << currentAdvisor << " will treat you well" << endl;
            }

        } else {
            selectAdvisor(player_index);
        }
    }
    else if (tilesColor == "R") 
    {
        cout << "Oh-oh, you’ve stumbled into the Graveyard! \n";
        cout << "This forces the player to move back 10 tiles and lose 100 Stamina, Strength, and Wisdom Points." << endl;

        _players[player_index].addStamina(-100);
        _players[player_index].addStrength(-100);
        _players[player_index].addWisdom(-100);

        _board.setPlayerPosition(player_index, -10);
    } 
    else if (tilesColor == "N") 
    {
        cout << "The Hyenas are on the prowl! They drag you back to where you were last, and the journey comes at a cost. \n";
        cout << "This returns the player to their previous position. \n"; 
        cout << "In addition, the player’s Stamina Points decrease by 300 Points" << endl;

        //add the move back feature

    } 
    else if (tilesColor == "P") 
    {
        bool gotRight;
        cout << "Time for a test of wits! Land here, and you’ll face a riddle randomly pulled. \n";
        cout << "Answer correctly, and you’ll earn a boost of 500 Points to your Wisdom Trait—your cleverness pays off!" << endl;
        Tile _tile;
        gotRight = _tile.randomeRiddle();

        if (gotRight == true)
        {
            cout << "Congratulation!!! You got it right!" << endl;
            _players[player_index].addWisdom(500);
        } else {
            cout << "Unlucky. Hope you get it next time!" << endl;
        }
        

    } else {
        cout << "ERROR!!!" << endl;
        return;
    }
    
}