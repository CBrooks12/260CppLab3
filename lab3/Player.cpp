#include "Player.h"
#include <iostream>
#include <iomanip>
using namespace std;
#pragma warning(disable:4996)		// allow call to strcpy
/*************************
private:
	char* user;
	enum gender;
	int level;
*************************/
Player::Player():user(NULL), gender(UNKNOWN), level(0)
{
}

Player::Player(char* user, Gender gender):user(NULL), gender(UNKNOWN), level(0)

{	
	setUName(user);
	setGender(gender);
	setLevel(level);
}
	
Player::Player(Player& aPlayer) : user(NULL), gender(UNKNOWN)
{
	setUName(aPlayer.user);
	setGender(aPlayer.gender);
	setLevel(aPlayer.level);
}

const Player& Player::operator=(const Player& aPlayer)
{
	//if it is a self copy, don't do anything
	if(this == &aPlayer)
		return *this;
	//make current object *this a copy of the passed in user
	else
	{
		setUName(aPlayer.user);
		setGender(aPlayer.gender);
		setLevel(aPlayer.level);
		return *this;
	}
}

Player::~Player()
{
	if(user)
		delete[] user;
}

void Player::getUName(char * user) const
{
	strcpy(user, this->user);
}

Gender Player::getGender()
{
	return gender;
}

int Player::getLevel() const
{
	return level;
}

void Player::setUName(char * user)
{
	//release the exisisting memory if there is any
	if(this->user)
		delete [] this->user;

	//set new UName
	this->user = new char[strlen(user)+1];
	strcpy(this->user, user);
}

void Player::setGender(Gender type)
{
	gender = type;
}

void Player::setLevel(int level)
{
	this->level= level;
}
void Player::LevelUp()
{
	//Player * player = &Player();
	int level = this->getLevel();
	level++;
	setLevel(level);
}

bool operator<(const Player& d1, const Player& d2)
{
	char UName1[100];
	char UName2[100];

	d1.getUName(UName1);
	d2.getUName(UName2);

	if(strcmp(UName1, UName2) < 0)
		return true;
	else
		return false;
}

bool operator==(Player& d1,Player& d2)
{
	char id1[500];
	char id2[500];

	d1.getUName(id1);
	d2.getUName(id2);

	if(strcmp(id1, id2) == 0)
		return true;
	else
		return false;
}

ostream& operator<<(ostream& out, const Player& aPlayer)
{
	out << setw(20) << aPlayer.user
		<< setw(15) << aPlayer.gender
		<< setw(8) << fixed << setprecision(2) << aPlayer.level;
	return out;
}