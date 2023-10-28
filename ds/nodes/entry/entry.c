#include "entry.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Entry entryConstructor(void *key, int keySize, void *value, int valueSize) 
{
	struct Entry entry;
	entry.key = malloc(keySize);
	entry.value = malloc(valueSize);
	memcpy(entry.key, key, keySize);
	memcpy(entry.value, value, valueSize);
	return entry;
};

void entryDeconstructor(struct Entry *entry)
{
	free(entry->key);
	free(entry->value);
	if(entry == NULL) {
		return;
	}
	//free(entry);
}
