#include "dictionary.h" 
#include "../tree/binaryTree.h"
#include "../nodes/entry/entry.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Dictionary dictionaryConstructor(int (*compare)(void *keyone, void *keytwo))
{
	struct Dictionary dictionary;
	dictionary.tree = treeConstructor(compare);
	dictionary.insert = insert;
	dictionary.get = search;
	return dictionary;
}

/*
 * Compara duas strings 
 * @param1 void *key (Entry)
 * @param2 void *key (Entry)
 *
 * @return 1,-1,0
 */
int compareStringKeys(void *keyone, void *keytwo)
{
	struct Entry *firstEntry = (struct Entry*)keyone;
	char * firstKey = (char*) firstEntry->key;

	struct Entry *targetEntry = (struct Entry*)keytwo;
	char * targetKey = (char*) targetEntry->key;

	//printf("comparing '%s' and '%s'\n", firstKey, targetKey);

	int compareResult = strcmp(firstKey, targetKey);
	int result;

	if(compareResult > 0){
		// keyone é maior que a keytwo
		return -1;
	}

	if(compareResult < 0) {
		//keyone é menor que a keytwo
		return 1;
	}

	//compareresult == 0
	//as keys sao iguais
	return 0;
}

void insert(struct Dictionary *dictionary, void *key, int keySize, void *value, int valueSize)
{
	struct Entry entry = entryConstructor(key, keySize, value, valueSize);
	dictionary->tree.insert(&dictionary->tree, &entry, sizeof(entry));
}

void * search(struct Dictionary *dic, void *key, int keySize)
{
	int value = 0;
	void * cpyKey = malloc(keySize);
	memcpy(cpyKey, key, keySize);
	struct Entry dummyEntry = entryConstructor(cpyKey, keySize, &value, keySize);
	void * result = dic->tree.search(&dic->tree, &dummyEntry);
	if(result == NULL) {
		printf("Value doesnt exists on dictionary\n");
		return NULL;
	}

	return ((struct Entry *)result)->value;
}
