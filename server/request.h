#ifndef REQUEST_H
#define REQUEST_H

struct Request {
	char * httpMethod;
	char * route;
	char * body;
	char rawRequest[30000];
};

struct Request requestConstructor(int  clientSocket);

void setHttpMethodAndRouteFromBuffer(struct Request * request, char * line);

void getRequestInfo(int clientSocket, char * buffer);

#endif
