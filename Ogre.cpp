#include "Ogre.h"

/*
 * powerful physical attack, medium hp
 */

Ogre::Ogre() {
	setName("Ogre");
	setStrength(HIGH);
	setIntelligence(MED);
	setDefense(HIGH);
	setAttack(getStrength(), getIntelligence());
	setType(2);
	setHitPoints(1000);
}

Ogre::~Ogre() {
	// TODO Auto-generated destructor stub
}

