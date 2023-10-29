#ifndef REQUEST_H
#define REQUEST_H

#include "../ds/dictionary/dictionary.h"
#include "../ds/lists/linkedList.h"

struct Request {
	char * body;
	char buffer[30000];
	char rawRequest[30000];
	struct LinkedList fieldsList;
	struct Dictionary fields;
	struct Entry (*setHeader)(struct Request *req, char *line);
	void (*readClientSocket)(struct Request *req, int clientSocket);
};

struct Request requestConstructor(int  clientSocket);

void setHttpMethodAndRouteFromBuffer(struct Request * request, char * line);

void getRequestInfo(int clientSocket, char * buffer);

struct Entry setHeader(struct Request *req, char *line);

struct Entry getHeader(char str); 
#endif
