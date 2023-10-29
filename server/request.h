#ifndef REQUEST_H
#define REQUEST_H

#include "../ds/dictionary/dictionary.h"
#include "../ds/lists/linkedList.h"

struct Request {
	char * body;
	char buffer[30000];
	char rawRequest[30000];
	struct Dictionary fields;
	void (*setHeader)(struct Request *req, char *line);
	void (*readClientSocket)(struct Request *req, int clientSocket);
	void (*process)(struct Request *req);
	void (*setMethodAndRoute)(struct Request *req, char *requestLine);
};

struct Request requestConstructor();

void setHttpMethodAndRouteFromBuffer(struct Request *req, char *requestLine);

void getRequestInfo(int clientSocket, char * buffer);

void processRequest(struct Request *req);

void setHeader(struct Request *req, char *line);

struct Entry getHeader(char str); 
#endif
