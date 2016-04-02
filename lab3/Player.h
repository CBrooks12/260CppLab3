#ifndef Player_H
#define Player_H
#include <iostream>
using namespace std;
enum Gender {UNKNOWN, MALE, FEMALE};
class Player
{
public:
	
	Player();
	Player(char* user, Gender gender);
	Player(Player& aPlayer);		//copy constructor: make current object a copy of "aPlayer"
	~Player();						//destructor: release the dynamically allocated memory

	void getUName(char* user) const;
	Gender getGender();
	int getLevel() const;

	void setUName(char* user);
	void setGender(Gender gender);
	void setLevel(int level);
	void LevelUp();

	const Player& operator=(const Player& user);	 //overloading assignment operator
	friend ostream& operator<<(ostream& out, const Player& user);

private:
	char*	user;
	Gender	gender;
	int		level;
};

bool operator< (const Player& d1, const Player& d2);
bool operator== (const Player& d1, const Player& d2);

#endif