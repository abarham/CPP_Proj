#include "Hero.h"
#include "Enemy.h"

Hero::Hero()
{
	hitPoints = 2500;
	skillPoints = 200;
}


Hero::~Hero()
{
}

bool Hero::blocked(int speed) {
	int block = speed / 2;
	std::random_device rd; //obtains seed from hw
	std::mt19937 eng(rd()); // seed
	std::uniform_int_distribution<> distr(1,100);
	return (block > distr(eng));
}
void Hero::heal(Hero &hero) {
	hero.setHitPoints(hero.getHitPoints() + 100);
}
void Hero::magicAttack(std::vector<Enemy> &enemies) {
	int sp = Hero::getSkillPoints();
	if (sp < 10) {
		std::cout << "No SP left!" << std::endl;
		return;
	}
	std::string choose = "Which enemy would you like to cast a spell at?";
	int choice;
	switch (enemies.size()) {
	case 1:
		std::cout << "Casting spell on the " << enemies[0].getName() << ".";
		Hero::magicDamage(enemies[0]);
		Hero::setSkillPoints(Hero::getSkillPoints() - 10);
		break;
	case 2:
		std::cout << choose << std::endl;
		std::cout << "1 for left, 2 for right: ";
		std::cin >> choice;
		if (choice == 1 || choice == 2) {
			Hero::magicDamage(enemies[choice - 1]);
			Hero::setSkillPoints(Hero::getSkillPoints() - 10);
		}
		else
			std::cout << "Invalid choice, attack missed!" << std::endl;
		break;
	case 3:
		std::cout << choose << std::endl;
		std::cout << "1 for left, 2 for middle, 3 for right: ";
		std::cin >> choice;
		if (choice == 1 || choice == 2 || choice == 3) {
			Hero::magicDamage(enemies[choice - 1]);
			Hero::setSkillPoints(Hero::getSkillPoints() - 10);
		}
		else
			std::cout << "Invaid choice, attack missed!" << std::endl;
		break;
	}
}
void Hero::clericHeal(std::vector<Hero> &heroes) {
	std::string choose = "Which member would you like to heal?";
	int choice;
	switch (heroes.size()) {
	case 1:
		std::cout << "Healing self";
		Hero::heal(heroes[0]);
		break;
	case 2:
		std::cout << choose << std::endl << "1 for left, 2 for right: ";
		std::cin >> choice;
		if (choice != 1 && choice != 2) {
			std::cout << "Invalid choice, heal missed!" << std::endl;
			return;
		}
		Hero::heal(heroes[choice - 1]);
		Hero::setSkillPoints(Hero::getSkillPoints() - 10);
		break;
	case 3:
		std::cout << choose << std::endl << "1 for right, 2 for middle, 3 for right: ";
		std::cin >> choice;
		if (choice != 1 && choice != 2 && choice != 3) {
			std::cout << "Invalid choice, heal missed!" << std::endl;
			return;
		}
		Hero::heal(heroes[choice - 1]);
		Hero::setSkillPoints(Hero::getSkillPoints() - 10);
		break;
	}
}
void Hero::physicalAttack(std::vector<Enemy> &enemies) {
	std::string choose = "Which enemy would you like to attack?";
	int choice;
	char wait;
	switch (enemies.size()) {
	case 1:
		std::cout << "Attacking only enemy. Press enter to continue." << std::endl;
		std::cin.get(wait);
		Hero::damage(enemies[0]);
		break;
	case 2:
		std::cout << choose << std::endl;
		std::cout << "1 for left, 2 for right: ";
		std::cin >> choice;
		std::cout << "Attacking " << enemies[choice - 1].getName() << "." << std::endl;
		Hero::damage(enemies[choice - 1]);
		break;
	case 3:
		std::cout << choose << std::endl;
		std::cout << "1 for left, 2 for middle, 3 for right: ";
		std::cin >> choice;
		std::cout << "Attacking " << enemies[choice - 1].getName() << "." << std::endl;
		Hero::damage(enemies[choice - 1]);
	}

}

void Hero::damage(Enemy &enemy) {
	enemy.takeDamage(this->getAttack());
}

void Hero::magicDamage(Enemy &enemy) {
	enemy.takeMagicDamage(Hero::getIntelligence());
}

void Hero::takeDamage(int damage) {
	bool block = Hero::blocked(Hero::getSpeed());
	if (block) {
		std::cout << "Attack blocked! No damage!" << std::endl;
		return;
	}
	else
		std::cout << "Attack lands!" << std::endl;
	int damageTotal = damage - (Hero::getDefense());
	std::cout << "tot: " << damageTotal << std::endl;
	std::cout << damageTotal << " dmg to " << Hero::getName() << std::endl;
	if (this->hitPoints > damageTotal)
		this->setHitPoints(this->hitPoints - damageTotal);
	else
		this->setHitPoints(0);
}

std::string Hero::getName() {
	return name;
}

int Hero::getHitPoints() {
	return hitPoints;
}

int Hero::getSkillPoints() {
	return skillPoints;
}

int Hero::getStrength() {
	return strength;
}

int Hero::getIntelligence() {
	return intelligence;
}

int Hero::getDefense() {
	return defence;
}

int Hero::getAttack() {
	return attack;
}

void Hero::setHitPoints(int hp) {
	this->hitPoints = hp;
}

void Hero::setSkillPoints(int sp) {
	this->skillPoints = sp;
}

void Hero::setName(std::string str) {
	this->name = str;
}

void Hero::setStrength(int str) {
	this->strength = str;
}

void Hero::setIntelligence(int intel) {
	this->intelligence = intel;
}

void Hero::setDefense(int def) {
	this->defence = def;
}

void Hero::setSpeed(int spd) {
	this->speed = spd;
}

int Hero::getSpeed() {
	return speed;
}

void Hero::setAttack(int str, int intel) {
	this->attack = (str * intel) / 15;
}

int Hero::getType() {
	return type;
}

void Hero::setType(int type) {
	this->type = type;
}

int Hero::chooseActionCleric() {
	int choice;
	std::cout << "1 for attack, 2 for heal: ";
	std::cin >> choice;
	if (choice == 1 || choice == 2)
		return choice;
	else
		return Hero::chooseActionCleric();
}

void Hero::printStats() {
	std::cout << "Name: " << Hero::getName() << std::endl;
	std::cout << "hp: " << Hero::getHitPoints() << std::endl;
	std::cout << "sp: " << Hero::getSkillPoints() << std::endl;
	std::cout << "atk: " << Hero::getAttack() << std::endl;
	std::cout << "def: " << Hero::getDefense() << std::endl;
	std::cout << "spd: " << Hero::getSpeed() << std::endl;
}
