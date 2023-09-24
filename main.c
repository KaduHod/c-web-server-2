#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include "server.h"

void launch(struct Server *server)
{
	int addressLength = sizeof(server->address);
	char buffer[30000];
	int newSocket = accept(server->socket, (struct sockaddr*) &server->address, (socklen_t *) &addressLength);
	char *hello = "HTTP/1.1 200 OK\nDate: Mon, 27 Jul 2009 12:28:53 GMT\nServer: Apache/2.2.14(Win32)\nLast-Modified: Wed, 22 Jul 2009 19:15:56 GMT\nContent-Length:88\nContent-type:text/html\nConnection: Closed\n<html><body><h1>Meu primeiro servidor!</h1></body></html>";

	while(0) {
		printf("Waiting for connection\n");
		read(newSocket, buffer, 30000);
		printf("Buffer: %s\n", buffer);
		write(newSocket, hello, strlen(hello));
		close(newSocket);
	}
}

int main()
{
	printf("1\n");
	struct Server server = serverConstructor(
		AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8080, 10, launch
	);
	printf("domain: %i\n",server.domain);
	printf("service: %i\n",server.service);
	printf("protocol: %i\n",server.protocol);
	printf("port: %i\n",server.port);
	printf("backlog: %i\n",server.backlog);
	printf("interface: %lu\n",server.interface);
	printf("%i\n",server.domain);
		printf("2\n");
	server.launch(&server);
		printf("3\n");
	return 0;
}
