#ifndef dictionary_h 
#define dictionary_h

#include "../tree/binaryTree.h"
#include "../nodes/entry/entry.h"

struct Dictionary 
{
	struct Tree tree;
	void (*insert)(struct Dictionary * dic, void *key, int sizeKey, void *value, int sizeValue);
	void * (*get)(struct Dictionary *dic, void *key, int keySize);
};

struct Dictionary dictionaryConstructor(int (*compare)(void *keyone, void *keytwo));
void dictionaryDestructor(struct Dictionary *dic);
void insert(struct Dictionary *dictionary, void *key, int keySize, void *value, int valueSize);
void * search(struct Dictionary *dic, void *key, int keySize);
int compareStringKeys(void *keyone, void *keytwo);
#endif 
