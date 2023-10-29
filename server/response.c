#include "response.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct Response responseConstructor(int clientSocket)
{	
	struct Response res;
	res.clientSocket = clientSocket;
	res.send = writeReponse;
	return res;
}

void writeReponse(struct Response *res)
{
	char *body = "HTTP/1.1 200 OK\nDate: Mon, 27 Jul 2009 12:28:53 GMT\nServer: Apache/2.2.14(Win32)\nLast-Modified: Wed, 22 Jul 2009 19:15:56 GMT\nContent-type:text/html\nConnection: Closed\n\n<html><body><h1>Hello,World!</h1></body></html>";
	write(res->clientSocket, body, strlen(body));
	close(res->clientSocket);
}
