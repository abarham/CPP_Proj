#include "Mage.h"
/*
 * The Mage is a Hero that deals magic damage and has low defense
 */

Mage::Mage() {
	setName("Mage");
	setStrength(LOW);
	setIntelligence(HIGH);
	setDefense(LOW);
	setSpeed(MED);
	setAttack(getStrength(), getIntelligence());
	setType(2);
}

Mage::~Mage() {
	// TODO Auto-generated destructor stub
}

