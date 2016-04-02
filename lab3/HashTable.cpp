#include "hashtable.h"
#include <iostream>
#include <fstream>
using namespace std;

/************************
private:
	node ** table;
	int capacity;
	int size;
	const static int DEFAULT_CAPACITY = 3;
************************/
hashTable::hashTable() :
	size(0),
	capacity(DEFAULT_CAPACITY),
	table(new node*[DEFAULT_CAPACITY])
{
	//initialize each head of the individual linked list
	for(int i=0; i<capacity; i++)
		table[i] = NULL;
}

hashTable::hashTable(const hashTable& aTable):capacity(aTable.capacity), size(aTable.size)
{
	table = new node*[capacity];

	//copy the array of linked list
	int i;	
	for(i=0; i<capacity; i++)
	{
		//copy each linked list in the array
		if (aTable.table[i] == NULL)
			table[i] = NULL;
		else
		{
			//copy the first node in current chain
			table[i] = new node(aTable.table[i]->item);

			//copy the rest of the chain
			node * srcNode = aTable.table[i]->next;
			node * destNode = table[i];
			while(srcNode)
			{
				destNode->next = new node(srcNode->item);
				destNode = destNode->next;
				srcNode = srcNode->next;
			}
			destNode->next = NULL;
		}
	}
}

const hashTable& hashTable::operator= (const hashTable& aTable)
{
	if(this == &aTable)
		return *this;
	else
	{
		//release dynamically allocated memory held by current object
		destroyTable(); 

		//make *this a deep copy of "aTable"
		table = new node*[capacity];
		capacity = aTable.capacity;
		size = aTable.size;

		//copy the array of linked list
		int i;	
		for(i=0; i<capacity; i++)
		{
			//copy each linked list in the array
			if (aTable.table[i] == NULL)
				table[i] = NULL;
			else
			{
				//copy the first node in current chain
				table[i] = new node(aTable.table[i]->item);

				//copy the rest of the chain
				node * srcNode = aTable.table[i]->next;
				node * destNode = table[i];
				while(srcNode)
				{
					destNode->next = new node(srcNode->item);
					destNode = destNode->next;
					srcNode = srcNode->next;
				}
				destNode->next = NULL;
			}
		}		
		return *this;
	}
}

void hashTable::destroyTable ()
{
	//delete each chain
	int i;
	for(i=0; i<capacity; i++)
	{
		node * head = table[i];
		node * curr;
		while(head)
		{
			curr = head->next;
			head->next = NULL;
			delete head;
			head = curr;
		}
	}

	//delete the array
	delete [] table;
}
hashTable::~hashTable()
{
	destroyTable(); 
}

bool hashTable::insert (/*char * key, */Player& aPlayer)
{
	char key[500];
	aPlayer.getUName(key);
	Player * RePlayer = &aPlayer;
	if(retrieve(key, &RePlayer))
	{
		return false;
	}
	//calculate the insertion position (the index of the array)
	size_t index = calculateIndex(key);

	//create a new node to hold data
	node * newNode = new node(aPlayer);

	//insert the new node at the beginning of the linked list
	newNode->next = table[index];
	table[index] = newNode;
	size++;
	return true;
}

bool hashTable::remove (char const * const key)
{
	//calculate the removal position (the index of the array)
	size_t index = calculateIndex(key);	

	//search for the data to be removed in the chain (linked list)
	node * curr = table[index];
	node * prev = NULL;
	char id[100];
	while (curr)
	{
		curr->item.getUName(id);
		if(strcmp(key, id) == 0)
		{
			//find match and remove the node
			if(!prev)
				table[index] = curr->next;
			else
				prev->next = curr->next;

			curr->next = NULL;
			delete curr;
			size--;
			return true;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
	return false;
}

bool hashTable::retrieve(char * key, Player ** aPlayer)
{
	//calculate the retrieval position (the index of the array)
	size_t index = calculateIndex(key);

	//search for the data in the chain (linked list)
	node * curr = table[index];
	char id[100];
	while (curr)
	{
		curr->item.getUName(id);
		if(strcmp(key, id) == 0)
		{
			//find match and return the data
			*aPlayer = &curr->item;
			return true;
		}
		else
			curr = curr->next;
	}

	//data is not in the table
	return false;
}

ostream& operator<<(ostream& cout, hashTable& ht)
{
	int i;
	
	hashTable::node * curr;
	cout << "====================" << endl;
	cout << "Hash Table Diagnostics" << endl << endl;
	cout << "Table Size: " << ht.capacity << endl;
	cout << "Number of Entries: " << ht.getSize() <<endl;
	for(i=0; i < ht.capacity; i++)
	{
		cout<< "Slot["<<i<<"]:"<<endl;
		bool isEmpty = true;
		for(curr = ht.table[i]; curr; curr = curr->next)		
		{
			isEmpty = false;
			char name[500];
			curr->item.getUName(name);
			cout <<"  "<< name << " ["<< curr->item.getLevel() << "]"<< endl;
		}
		if(isEmpty)
		{
			cout<<"  EMPTY"<<endl;
		}
			
	}
	cout << "====================" << endl;

	return cout;
}

int hashTable::getSize (void) const
{
	return size;
}

size_t hashTable::calculateIndex (char const * const key)
{
	unsigned i = 0;
	unsigned value = 0;
	size_t length = strlen(key);
	value = key[i] *32 +key[i+1];
	for(size_t i=2; i<length; i++)
	{
		value = value*32 + key[i];
	}
	return value % capacity;

}