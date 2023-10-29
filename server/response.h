#ifndef RESPONSE_H
#define RESPONSE_H  

struct Response 
{
	int clientSocket;
	void (*send)(struct Response *res);	
};

struct Response responseConstructor(int clientSocket);
void writeReponse(struct Response *res);

#endif // DEBUG
