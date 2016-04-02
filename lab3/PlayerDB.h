#ifndef PlayerDB_H
#define PlayerDB_H
#include <iostream>
#include "HashTable.h"
#include "Player.h"
using namespace std;
class PlayerDB
{
public:
	PlayerDB();
	PlayerDB(std::ostream& outStm);
	~PlayerDB();						//destructor: release the dynamically allocated memory
	void AddPlayer(Player player);
	void PrintDiagnostics();
	void RemovePlayer(char* user);
	Player* FetchPlayer(char* user);
	

	void setUName(char* user);
	void setgender(Gender gender);

	const Player& operator=(const Player& user);	 //overloading assignment operator
	friend ostream& operator<<(ostream& out, const Player& user);

private:
	std::ostream* outStream;
	hashTable database;
};

#endif