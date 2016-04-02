#include "PlayerDB.h"
#include "HashTable.h"
#include <iostream>
#include <fstream>
using namespace std;

PlayerDB::PlayerDB(): outStream(0)
{
}

PlayerDB::PlayerDB(std::ostream& outStm)
{
	outStream = &outStm;
	database = hashTable();
};
PlayerDB::~PlayerDB()
{
}
void PlayerDB::AddPlayer(Player player)			
{
	char name[500];
	player.getUName(name);
	cout<<"Attempting to add player \""<< name <<"\"  to the database";
	if(database.insert(player))
		cout<<" -- Success!"<<endl;
	else
		cout<<" -- Failed."<<endl;
}

void PlayerDB::RemovePlayer(char * user)			
{
	cout<<"Removing player \""<< user <<"\"  to the database";
	if(database.remove(user))
		cout<<" -- Success!"<<endl;
	else
		cout<<" -- Failed."<<endl;
}

Player* PlayerDB::FetchPlayer(char* user)
{
	cout<<"Fetching player \""<<user<<"\"";
	Player * RePlayer = &Player();
	if(database.retrieve(user, &RePlayer))
	{
		cout<<" -- Success!"<<endl;
		return RePlayer;
	}
	else
	{
		cout<<" -- Failed."<<endl;
		return NULL;
	}
}
void PlayerDB::PrintDiagnostics()
{
	*outStream << database;
}