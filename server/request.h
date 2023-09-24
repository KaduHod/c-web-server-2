#ifndef REQUEST_H
#define REQUEST_H

struct Request {
	char url;
	char headers;
	char body;
};

struct Request requestConstructor(int clientSocket);

void setHttpMethodAndRouteFromBuffer(struct Request * request, char * line);

int getRequestInfo(int clientSocket, char * buffer);

#endif
