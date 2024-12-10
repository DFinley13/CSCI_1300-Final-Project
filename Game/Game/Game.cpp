
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

    // Ensure valid player count
    while (playerCount < 2 || playerCount > n) {
        cerr << "Error: Invalid number of players. You must select between 2 and " << n << " players.\n";
        cout << "Enter the number of players: ";
        cin >> playerCount;
    }

    _board.setPlayer_count(playerCount);

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

        // Ensure the choice is valid and the character isn't already chosen
        while (choice < 1 || choice > n || selected[choice - 1]) {
            cerr << "Invalid choice or character already chosen. Try again: ";
            cin >> choice;
        }

        // Add the selected character to the players list
        _players.push_back(_characters[choice - 1]);
        selected[choice - 1] = true; // Mark the character as chosen
        
        // Apply path effects
        int playerPath = _players[i].choosePath();
        if (playerPath == 1)
        {
            _board.setPlayerLane(playerPath, i);
            selectAdvisor(i);
        } else {
            _board.setPlayerLane(playerPath, i);
        }

    }

    // Confirm selections
    int k = _players.size();
    cout << "\nPlayers have chosen their characters and paths:\n";
    for (int i = 0; i < k; ++i) {
        cout << "Player " << i + 1 << ":\n";
        _players[i].printStats();
        cout << endl;
        _board.setPlayerPosition(i, 0);
    }
}

void Game::selectAdvisor(int player_index) {
    // Advisor options
    vector<string> advisorNames = {"Rafiki", "Nala", "Sarabi", "Zazu", "Sarafina"};
    vector<string> advisorAbilities = {"Invisibility", "Night Vision", "Energy Manipulation", "Weather Control", "Super Speed"};

    int l = advisorNames.size();
    bool validChoice = false;  // Flag to control the loop

    // The player selects an advisor
    while (!validChoice) {
        cout << "Player " << player_index + 1 << ", choose an advisor:\n";
        for (int j = 0; j < l; ++j) {
            cout << j + 1 << ". " << advisorNames[j] << " - " << advisorAbilities[j] << endl;
        }

        int advisorChoice;
        cin >> advisorChoice;

        // Check if the choice is valid
        if (advisorChoice >= 1 && advisorChoice <= l) {
            // Assign the chosen advisor to the player
            _players[player_index].setAdvisor(advisorNames[advisorChoice - 1], advisorAbilities[advisorChoice - 1]);
            
            // Ask for confirmation
            char userInput;
            cout << "You have chosen " << _players[player_index].getAdvisor() << " with the ability " << _players[player_index].getAdvisorAbility() << "\n";
            cout << "Is this correct? Enter 'N' if incorrect, 'Y' if correct.\n";
            cin >> userInput;

            if (userInput == 'Y' || userInput == 'y') {
                validChoice = true;  // Exit the loop if confirmed
            } else {
                cout << "Please choose again.\n";  // Allow retrying if incorrect
            }
        } else {
            cout << "Invalid choice. Please choose a valid advisor number.\n";
        }
    }

    // Apply the advisor's effect (this is just a placeholder function)
    applyAdvisorEffect(player_index);
}


void Game::applyAdvisorEffect(int player_index) {
    string ability = _players[player_index].getAdvisorAbility();
    if (ability == "Invisibility") {
        // Rafiki: Invisibility - Hide position, no effect on stats, just a narrative effect
        cout << "You are now invisible, your position is hidden from others for this turn.\n";
    }
    else if (ability == "Night Vision") {
        // Nala: Night Vision - Increase Wisdom
        _players[player_index].addWisdom(100); // Example: Boost wisdom by 100
        cout << "Night Vision: Wisdom increased by 100!\n";
    }
    else if (ability == "Energy Manipulation") {
        // Sarabi: Energy Manipulation - Boost Stamina
        _players[player_index].addStamina(100); // Example: Boost stamina by 100
        cout << "Energy Manipulation: Stamina increased by 100!\n";
    }
    else if (ability == "Weather Control") {
        // Zazu: Weather Control - Boost Strength
        _players[player_index].addStrength(100); // Example: Boost strength by 100
        cout << "Weather Control: Strength increased by 100!\n";
    }
    else if (ability == "Super Speed") {
        // Sarafina: Super Speed - Allow extra movement
        cout << "Super Speed: You can move an extra 2 spaces this turn!\n";

        if (_board.getPlayerPosition(player_index) > 0 && _board.getPlayerPosition(player_index) < 51)
        {  
            int moveamt = randomGenerator(1, 7);
            _board.movePlayer(player_index, moveamt);
            _board.displayTrack(player_index);
            moveamt = randomGenerator(1, 7);
            _board.movePlayer(player_index, moveamt);
            _board.displayTrack(player_index);
        }
    }
    else {
        cout << "Unknown advisor ability!\n";
    }
}
    

void Game::startGame() {
    cout << "Starting the game...\n";

    int k = _players.size();
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

//The menu that displays the actions the players can do on there turn
bool Game::mainMenu() {
 // For each players turn
    int playersize;
    playersize = _players.size();
    
   

    for (int i = 0; i < playersize; i++)
    {

        // if (_board.getPlayerPosition(0) == 51 && _board.getPlayerPosition(1) == 51, _board.getPlayerPosition(2) == 51, _board.getPlayerPosition(3) == 51, _board.getPlayerPosition(4) == 51)
        // {
        //     return true;
        // }
        

        if (_board.getPlayerPosition(i) >= 51)
        {
            continue;
        }

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

            // Call movePlayer with the current player index
            _board.movePlayer(i, moveAmount); // Move the player i

                cout << "Player " << i + 1 << " moved forward: " << moveAmount << " spaces." << endl;
                _board.displayTrack(_board.getPlayerLane(i) - 1); // Display the updated track
                playerLastMove[i] = moveAmount;

                string color = _board.currentTileColor(_board.getPlayerLane(i) - 1, _board.getPlayerPosition(i));
                tileAffect(color, i);



            validchoice = true;
    } else {
        cout << "Invalid Choice" << endl;
    }
        }
         cout << "----------" << "\n" << endl;
    }
    return false;
}

//What the tiles do
void Game::tileAffect(string tilesColor, int player_index) {
    Tile _tile;
   if (tilesColor == "G")
   {
       int random = rand() % 100 + 1;

       if (random <= 50)
       {
           cout << "Nothing happens. Take a rest." << endl;
        } else if (random > 50) {
            cout << "Green" << endl;
            // randomEvent(player_index);
       } else {
           cout << "ERROR in green tile affect" << endl;
           return;
       }
       
    } else if (tilesColor == "B") 
    {
        cout << "You found a peaceful oasis! \n";
        cout << "You get a extra turn to move forward!" << endl; 

        _players[player_index].addStamina(200);
        cout << "You gained +200 Stamina" << endl;
       
        _players[player_index].addStrength(200);
         cout << "You gained +200 Strength" << endl;

        _players[player_index].addWisdom(200);
         cout << "You gained +200 Wisdom" << endl;


        char ready;
        cout << "Ready to move? Press 'Y' to continue" << endl;
        cin >> ready;
        if (ready == 'y' || ready == 'Y')
        {
            int moveamount = randomGenerator(1,7);
            _board.movePlayer(player_index, moveamount);    
            cout << "You moved " << moveamount << " Spaces" << endl;
            _board.displayTrack(player_index);
            string color = _board.currentTileColor(_board.getPlayerLane(player_index) - 1, _board.getPlayerPosition(player_index));
            tileAffect(color, player_index);
        }
        

    } 
    else if (tilesColor == "P") 
    {
        cout << "Player " << player_index + 1 << " Welcome to the land of enrichment - when landing on this tile, your Stamina, Strength, and Wisdom \n";
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
            selectAdvisor(player_index);
        } else {
            char change;
            cout << "Would you like to from chagne Advisors?" << endl;
            cout << "You currently have " << currentAdvisor << " with the abillity " << currentAdvisorAbillity << endl;
            cout << "Press Y for yes and N for no" << endl;
            cin >> change;
            if (change == 'y' || change == 'Y')
            {
                cout << "Great!" << endl;
                selectAdvisor(player_index);
            } else {
                cout << "Good choice! " << currentAdvisor << " will treat you well" << endl;
            }
        }
    }
    else if (tilesColor == "R") 
    {
        cout << "Oh-oh, you’ve stumbled into the Graveyard! \n";
        cout << "This forces the player to move back 10 tiles and lose 100 Stamina, Strength, and Wisdom Points." << endl;

        _players[player_index].addStamina(-100);
        _players[player_index].addStrength(-100);
        _players[player_index].addWisdom(-100);

        if (_board.getPlayerPosition(player_index) - 10 < 0){
            _board.setPlayerPosition(player_index, 0);
        } else {
            _board.movePlayer(player_index, -10);
        }
        _board.displayTrack(player_index);
    } 
    else if (tilesColor == "N") 
    {
        cout << "The Hyenas are on the prowl! They drag you back to where you were last, and the journey comes at a cost. \n";
        cout << "This returns the player to their previous position. \n"; 
        cout << "In addition, the player’s Stamina Points decrease by 300 Points" << endl;


        _players[player_index].addStamina(-300);
        _board.movePlayer(player_index, -playerLastMove[player_index]);
        _board.displayTrack(player_index);

    } 
    else if (tilesColor == "U") 
    {
        cout << "Time for a test of wits! Land here, and you face a Rock, Paper, Scissors challenge!\n";
        cout << "Choose your move:\n";
        cout << "1. Rock\n2. Paper\n3. Scissors\n";
        
        int playerMove;
        cin >> playerMove;

        while (playerMove < 1 || playerMove > 3) {
            cout << "Invalid choice. Please choose 1 (Rock), 2 (Paper), or 3 (Scissors): ";
            cin >> playerMove;
        }

        // Computer randomly selects a move
        srand(time(0));
        int computerMove = rand() % 3 + 1;
        string moves[] = {"Rock", "Paper", "Scissors"};

        cout << "You chose: " << moves[playerMove - 1] << endl;
        cout << "The computer chose: " << moves[computerMove - 1] << endl;

        // Determine winner
        if (playerMove == computerMove) {
            cout << "It's a tie! No changes to your stats.\n";
        } 
        else if ((playerMove == 1 && computerMove == 3) || (playerMove == 2 && computerMove == 1) || (playerMove == 3 && computerMove == 2)) {
            cout << "You win! Your Wisdom increases by 500 points.\n";
            _players[player_index].addWisdom(500);
        } 
        else {
            cout << "You lose! Your Wisdom decreases by 200 points.\n";
            _players[player_index].addWisdom(-200);
        }
    } 
    else {
        cout << "ERROR!!!" << endl;
        return;
    }
    
}

//Gives a random number
int Game::randomGenerator(int min, int max)
{
    return (rand() % (max - min + 1) + min);
}

//The random events when a player lands on the green tiles
void Game::randomEvent(int player_index) {
    Player _player;
    vector<string> descriptions;
    vector<int> paths;
    vector<int> toAdvisors;
    vector<int> pridePointChanges;
    int idx = 0;

    ifstream file("random_events.txt");
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << "random_events.txt" << endl;
        return;
    }

    string line, firstline;
    getline(file, firstline); // Skip the header line

    // Parse the file
    while (getline(file, line)) {
        string description, path, toAdvisor, pridePointChange;
        stringstream stream(line);

        getline(stream, description, '|');
        getline(stream, path, '|');
        getline(stream, toAdvisor, '|');
        getline(stream, pridePointChange, '|');

        descriptions.push_back(description);
        paths.push_back(stoi(path));
        toAdvisors.push_back(stoi(toAdvisor));
        pridePointChanges.push_back(stoi(pridePointChange));
        idx++;
    }

    // Create a 2D vector to store events for each path and advisor combination
    vector<vector<vector<int>>> eventGroups(2, vector<vector<int>>(6)); 
    // `2` paths (0 = club, 1 = pride), `6` advisors (0 = no advisor, 1-5 = others)

    for (int i = 0; i < idx; ++i) {
        int path = paths[i];
        int advisor = toAdvisors[i];
        if (path >= 0 && path < 2 && advisor >= 0 && advisor < 6) {
            eventGroups[path][advisor].push_back(i);
        } else {
            cerr << "Error: Invalid path or advisor value in random events file." << endl;
            return;
        }
    }

    // Determine the player's path and advisor
    int playerLane = _board.getPlayerLane(player_index);
    string playerAdvisor = _players[player_index].getAdvisor();

    // Map advisor names to numerical indices
    int advisorIndex = 0;
    if (playerAdvisor == "Rafiki") advisorIndex = 1;
    else if (playerAdvisor == "Nala") advisorIndex = 2;
    else if (playerAdvisor == "Sarabi") advisorIndex = 3;
    else if (playerAdvisor == "Zazu") advisorIndex = 4;
    else if (playerAdvisor == "Sarafina") advisorIndex = 5;

    // Check if events exist for the player's group
    if (!eventGroups[playerLane][advisorIndex].empty()) {
        const auto& events = eventGroups[playerLane][advisorIndex];
        int randomIndex = randomGenerator(0, events.size());
        int selectedEvent = events[randomIndex];

        // Output the event and update pride points
        cout << descriptions[selectedEvent] << endl;
        _players[player_index].addPridePoints(pridePointChanges[selectedEvent]);
        cout << "Pride Points: " << pridePointChanges[selectedEvent] << endl;
    } else {
        cout << "No events available for the player's path and advisor." << endl;
    }
}

//The end win screen 
void Game::winscreen() {
    cout << "-----------------------------" << endl;
    cout << "Congratulations players you have all completed your journey!" << endl; 

    const int maxPlayers = 5; // Assuming max 5 players
    int totalPridepoints[maxPlayers] = {0, 0, 0, 0, 0};
    int playerIndices[maxPlayers] = {0, 1, 2, 3, 4};

    int totalPlayers = amountOfPlayers();
    for (int i = 0; i < totalPlayers; i++)
    {
        int totalPoints = _players[i].getPridePoints();
        int testStamina = _players[i].getStamina();
        int testStrength = _players[i].getStrength();
        int testWisdom = _players[i].getWisdom();
                while (testStamina > 100)
                {
                    testStamina -= 100;
                    totalPoints += 1000;
                }
                while (testStrength > 100) {
                    testStrength -= 100;
                    totalPoints += 1000;
                } 
                while (testWisdom > 100) {
                    testWisdom -= 100;
                    totalPoints += 1000;
                }
        totalPridepoints[i] = totalPoints;
    }

    int n = amountOfPlayers();


    //Bubble sort
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (totalPridepoints[j] < totalPridepoints[j + 1]) // Reverse the comparison
            {
                cout << "swapping numbers: " << j << " and " << j + 1 << endl;
                int temp = totalPridepoints[j + 1];
                totalPridepoints[j + 1] = totalPridepoints[j];
                totalPridepoints[j] = temp;

                int tempIndex = playerIndices[j + 1];
                playerIndices[j + 1] = playerIndices[j];
                playerIndices[j] = tempIndex;
            }

            
        }
        
    }
    
    cout << "The pride points leader board is: " << endl;

    for (int i = 0; i < n; i++)
    {
       cout << "Player: " << playerIndices[i] + 1 << ": " <<totalPridepoints[i] <<  endl;
    }
    

}
