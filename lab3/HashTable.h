#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Player.h"

class hashTable
{
public:
	hashTable();
	hashTable(const hashTable& aTable);
	~hashTable();

	const hashTable& operator= (const hashTable& aTable);

	bool insert(/*char * key,*/ Player& aPlayer);
	bool remove(char const * const key);
	bool retrieve(char * key, Player ** aPlayer);
	int getSize(void)const;

	friend ostream& operator<<(ostream& out, hashTable& ht);

private:
	struct node
	{
		Player item;
		node * next;
		node(Player& aPlayer) : item(aPlayer), next(NULL) {}
	};
	node ** table;
	int capacity;
	int size;
	const static int DEFAULT_CAPACITY = 3;

	void destroyTable();
	size_t calculateIndex(char const * const key);
};
#endif