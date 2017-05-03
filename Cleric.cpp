#include "Cleric.h"

/*
 * low attack, medium defense, can heal party members
 */

Cleric::Cleric() {
	setName("Cleric");
	setStrength(LOW);
	setIntelligence(HIGH);
	setDefense(MED);
	setSpeed(HIGH);
	setAttack(getStrength(), getIntelligence());
	setType(3);
}

Cleric::~Cleric() {
}

