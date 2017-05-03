#include <iostream>
#include <vector>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include "RPGDisplay.h"
#include "Hero.h"
#include "Enemy.h"
#include "Warrior.h"
#include "Mage.h"
#include "Cleric.h"
#include "Dragon.h"
#include "Ogre.h"
#include "Bandit.h"

using namespace std;

void numParty(int&);
void turn(vector<Hero>&, vector<Enemy>&, bool&, RPGDisplay&);
void computerTurn(vector<Hero>&, vector<Enemy>&, bool&, RPGDisplay&);
void checkPartyHealth(vector<Hero>&, bool&);
void checkEnemyHealth(vector<Enemy>&, bool&);
void game(int&, int&, int&, int&);
void createLevel(vector<Hero>&, vector<Enemy>&);
void createLevel(vector<Enemy>&);
void selectParty(vector<Hero>&);
void generateEnemy(vector<Enemy>&);
int rng();
void partyFactor(int&, int&, int&);
int getInt(int, int);
void printRules();
void save(int&);
void load(int&);

int main() {
	int losses = 0;
	int wins = 0;
	int levelsBeaten = 0;
	int highestLevelBeaten;
	printRules();
	load(highestLevelBeaten);
	game(wins, losses, levelsBeaten, highestLevelBeaten);
	save(highestLevelBeaten);
	return 0;
}

// main game loop
void game(int &wins, int &losses, int &levelsBeaten, int &highestLevelBeaten) {
	vector<Hero> heroes;
	vector<Enemy> enemies;
	bool isPlayerDead = false;
	bool isComputerDead = false;
	bool finished = false;
	int choice = 0;

	createLevel(heroes, enemies);
	do { // until finished
		do { // until heroes or enemies are dead
			RPGDisplay board(heroes, enemies);
			board.display();
			turn(heroes, enemies, isComputerDead, board);
			//board.refresh();
			//board.display();
			computerTurn(heroes, enemies, isPlayerDead, board);
			//board.display();
			//board.refresh();
		} while (!isPlayerDead && !isComputerDead);
		if (isPlayerDead) {
			cout << "You lose!" << endl;
			losses++;
			cout << "Current Stats" << endl;
			cout << "_____________" << endl;
			cout << "Wins: " << wins << endl;
			cout << "Losses: " << losses << endl;
			cout << "Ratio: " << wins / (levelsBeaten + losses) << endl;
		}
		if (isComputerDead) {
			cout << "You win!" << endl;
			wins++;
			levelsBeaten++;
			cout << "Current Stats" << endl;
			cout << "_____________" << endl;
			cout << "Wins: " << wins << endl;
			cout << "Losses: " << losses << endl;
			cout << "Ratio: " << wins / (levelsBeaten) << endl;
			if (levelsBeaten > highestLevelBeaten) {
				highestLevelBeaten = levelsBeaten;
				cout << "Congratulations! New highest level!" << endl;
			}
		}
		cout << "Would you like to play again?" << endl;
		cout << "1 to play again, 2 to quit: ";
		cin >> choice;
		if (choice == 2)
			finished = true;
		else {
			isPlayerDead = false;
			createLevel(heroes, enemies);
		}
	} while (!finished);
}

// used to set up initial hero and enemy parties
void createLevel(vector<Hero> &heroes, vector<Enemy> &enemies) {
	heroes.clear();
	enemies.clear();
	selectParty(heroes);
	generateEnemy(enemies);
}

// if player wishes to continue, will generate new enemy party
void createLevel(vector<Enemy> &enemies) {
	enemies.clear();
	generateEnemy(enemies);
}

// allows player to select up to three total heroes of Warriors, Mages, and Clerics
void selectParty(vector<Hero> &heroes) {
	int numberOfHeroes;
	int numberOfWarriors = 0;
	int numberOfMages = 0;
	int numberOfClerics = 0;
	cout << "How many heroes would you like in your party?" << endl;
	cout << "You may have up to 3: ";
	cin >> numberOfHeroes;
	if (numberOfHeroes != 1 && numberOfHeroes != 2 && numberOfHeroes != 3)
		getInt(1, 3);

	// choose how many of each class
	for (int i = 0; i < numberOfHeroes; i++) {
		int choice;
		cout << "For hero " << i + 1 << " would you like a Warrior, Mage, or Cleric?" << endl;
		cout << "1 for Warrior, 2 for Mage, 3 for Cleric: ";
		cin >> choice;
		switch (choice) {
		case 1:
			numberOfWarriors++;
			break;
		case 2:
			numberOfMages++;
			break;
		case 3:
			numberOfClerics++;
			break;
		}
	}
	// create each hero
	for (int i = 0; i < numberOfWarriors; i++)
		heroes.push_back(Warrior());
	for (int i = 0; i < numberOfMages; i++)
		heroes.push_back(Mage());
	for (int i = 0; i < numberOfClerics; i++)
		heroes.push_back(Cleric());
}

// allows player to select between 1 and 3 heroes to fight with
void numParty(int &numHeroes) {
	cout << "How many heroes would you like in your party? ";
	cin >> numHeroes;
	if (numHeroes < 1 || numHeroes > 3) {
		cout << "Please enter a party number between 1 and 3: ";
		cin >> numHeroes;
	}
}

// iterates over hero party and allows player to select which enemy each member attacks
// then gives computer turn
void turn(vector<Hero> &heroes, vector<Enemy> &enemies, bool &isComputerDead, RPGDisplay &board) {
	// player turn
	for (int i = 0; i < heroes.size(); i++) {
		int type = heroes[i].getType();
		cout << "It is the " << heroes[i].getName() << "'s turn." << endl;
		if (type == 1) { // Warrior
			heroes[i].physicalAttack(enemies);
			checkEnemyHealth(enemies, isComputerDead);
			board.display();
		} else if (type == 2) { // Mage
			int choice;
			cout << "Would you like the Mage to use a magic or physical attack?" << endl;
			cout << "1 for magic, 2 for physical: ";
			cin >> choice;
			if (choice != 1 && choice != 2)
				cout << "Invalid choice, attack missed!" << endl;
			else {
				if (choice == 1) {
					heroes[i].magicAttack(enemies);
					checkEnemyHealth(enemies, isComputerDead);
					board.display();
				}
				else {
					heroes[i].physicalAttack(enemies);
					checkEnemyHealth(enemies, isComputerDead);
					board.display();
				}
			}
		} else if (type == 3) { // Cleric
			int choice;
			cout << "Would you like to heal or attack?" << endl;
			cout << "1 for heal, 2 for attack: ";
			cin >> choice;
			if (choice != 1 && choice != 2) {
				cout << "Invalid choice, turn missed." << endl;
			} else {
				switch (choice) {
				case 1:
					heroes[i].clericHeal(heroes);
					checkEnemyHealth(enemies, isComputerDead);
					board.display();
					break;
				case 2:
					heroes[i].physicalAttack(enemies);
					checkEnemyHealth(enemies, isComputerDead);
					board.display();
					break;
				}
			}
		}
	}
	checkEnemyHealth(enemies, isComputerDead);
}

// computer's turn
void computerTurn(vector<Hero> &heroes, vector<Enemy> &enemies, bool &isPlayerDead, RPGDisplay &board) {
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i].chooseAttack(heroes);
		checkPartyHealth(heroes, isPlayerDead);
	}
}

// iterates over hero party and checks each member's health, removing them from the vector if needed
void checkPartyHealth(vector<Hero> &heroes, bool &isPlayerDead) {
	for (int i = 0; i < heroes.size(); i++)
		if (heroes[i].getHitPoints() == 0)
			heroes.erase(heroes.begin() + i);
	if (heroes.size() == 0)
		isPlayerDead = true;
	else
		isPlayerDead = false;
}

// iterates over enemy party and checks each member's health, removing them from the vector if needed
void checkEnemyHealth(vector<Enemy> &enemies, bool &isComputerDead) {
	for (int i = 0; i < enemies.size(); i++)
		if (enemies[i].getHitPoints() == 0) {
			enemies.erase(enemies.begin() + i);
		}

	if (enemies.size() == 0)
		isComputerDead = true;
	else
		isComputerDead = false;
}

// returns randmon int between 1 and 3
int rng() {
	std::random_device rd; // obtains random number from hardware
	std::mt19937 eng(rd()); // seed the rng
	std::uniform_int_distribution<> distr(1, 3);
	return distr(eng);
}
int rng(int min, int max) {
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(min, max);
	return distr(eng);
}

void generateEnemy(vector<Enemy> &enemies) {
	int numberOfDragons = 0;
	int numberOfBandits = 0;
	int numberOfOgres = 0;

	partyFactor(numberOfDragons, numberOfBandits, numberOfOgres);
	for (int i = 0; i < numberOfDragons; i++)
		enemies.push_back(Dragon());
	for (int i = 0; i < numberOfBandits; i++)
		enemies.push_back(Bandit());
	for (int i = 0; i < numberOfOgres; i++)
		enemies.push_back(Ogre());
}

// generates a random number 1-3 for number of enemies, and then uses another random number to decided how many of each enemy
void partyFactor(int &numberOfDragons, int &numberOfBandits, int &numberOfOgres) {
	int numEnemies = rng(1, 3);
	int partyFactorOne = rng(1, 3);
	int partyFactorTwo = rng(1, 6);
	int partyFactorThree = rng(1, 10);
	switch (numEnemies) {
	case 1:
		switch (partyFactorOne) {
		case 1:
			numberOfDragons = 1;
			numberOfOgres = 0;
			numberOfBandits = 0;
			break;
		case 2:
			numberOfDragons = 0;
			numberOfOgres = 1;
			numberOfBandits = 0;
			break;
		case 3:
			numberOfDragons = 0;
			numberOfOgres = 0;
			numberOfBandits = 1;
			break;
		}
		break;
		case 2:
			switch (partyFactorTwo) {
			case 1:
				numberOfDragons = 2;
				numberOfOgres = 0;
				numberOfBandits = 0;
				break;
			case 2:
				numberOfDragons = 0;
				numberOfOgres = 2;
				numberOfBandits = 0;
				break;
			case 3:
				numberOfDragons = 0;
				numberOfOgres = 0;
				numberOfBandits = 2;
				break;
			case 4:
				numberOfDragons = 1;
				numberOfOgres = 1;
				numberOfBandits = 0;
				break;
			case 5:
				numberOfDragons = 1;
				numberOfOgres = 0;
				numberOfBandits = 1;
				break;
			case 6:
				numberOfDragons = 0;
				numberOfOgres = 1;
				numberOfBandits = 1;
				break;
			}
			break;

			case 3:
				switch (partyFactorThree) {
				case 1:
					numberOfDragons = 3;
					numberOfOgres = 0;
					numberOfBandits = 0;
					break;
				case 2:
					numberOfDragons = 0;
					numberOfOgres = 0;
					numberOfBandits = 3;
					break;
				case 3:
					numberOfDragons = 0;
					numberOfOgres = 3;
					numberOfBandits = 0;
					break;
				case 4:
					numberOfDragons = 2;
					numberOfOgres = 0;
					numberOfBandits = 1;
					break;
				case 5:
					numberOfDragons = 2;
					numberOfOgres = 1;
					numberOfBandits = 0;
					break;
				case 6:
					numberOfBandits = 2;
					numberOfDragons = 1;
					numberOfOgres = 0;
					break;
				case 7:
					numberOfDragons = 0;
					numberOfBandits = 2;
					numberOfOgres = 1;
					break;
				case 8:
					numberOfOgres = 2;
					numberOfDragons = 1;
					numberOfBandits = 0;
					break;
				case 9:
					numberOfDragons = 0;
					numberOfOgres = 2;
					numberOfBandits = 1;
					break;
				case 10:
					numberOfDragons = 1;
					numberOfOgres = 1;
					numberOfBandits = 1;
					break;
				}
				break;
	}
}

// prompts user for int between min and max until a valid answer is given
int getInt(int min, int max) {
	int input;
	cout << "Enter a number between " << min << " and " << max << ":";
	cin >> input;
	if (input >= min && input <= max)
		return input;
	else
		return getInt(min, max);
}

// prints basic info about the game
void printRules() {
	cout << "The \'attack\' stat is a function of \'strength\' and intelligence." << endl;
	cout << "\'speed\' is taken into account everytime the character takes damage as a chance to block." << endl;
	cout << "Healing and Magic attacks drain \'sp\'." << endl;
}

void save(int &highestLevelBeaten) {
	cout << "Saving data..." << endl;
	FILE* f = fopen("data.txt", "w");
	if (f == NULL) {
		printf("File does not exist, can't save");
		return;
	}
	// write data
	fprintf(f, "%d\n", highestLevelBeaten);
	fclose(f);
}

void load(int &highestLevelBeaten) {
	cout << "Loading data..." << endl;
	FILE* f = fopen("data.txt", "r");
	if(f == NULL) {
		printf("File does not exist.");
		return;
	}

	// load
	while(fscanf(f, "%d", &highestLevelBeaten) == 1) {
		printf("Highest level beaten is level %d.\n", highestLevelBeaten);
	}
	fclose(f);
}
