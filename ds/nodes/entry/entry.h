#ifndef entry_h
#define entry_h

struct Entry 
{
	void *key;
	void *value;
};
struct Entry entryConstructor(void *key, int keySize, void *value, int valueSize); 
void entryDeconstructor(struct Entry *entry);
#endif  
