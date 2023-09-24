#include <request.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

struct Request requestConstructor(int clientSocket) {
	char route;
	char httpMethod;
	char body;	
	char buffer[30000];
	struct Request request;
	
	memset(buffer, 0, sizeof(buffer));
	
	int readBytes = read(clientSocket, buffer, sizeof(buffer) - 1);
	
	strcpy(request.rawRequest, buffer);

	if(readBytes < 0)
	{
		perror("Erro lendo o requet: ");
		close(clientSocket);
	}

	if(readBytes == 0)
	{
		printf("Cliente fechou a conexão");
		close(clientSocket);
	}


	int count = 0;

	char * line = strtok(buffer, "\n");
	int nextIsBody = 0;

	while(line != NULL)
	{
		if(count == 0)
		{
			setHttpMethodAndRouteFromBuffer(&request, line);
		}
		if(nextIsBody == 1) {
			request.body = line;	
		}  

		if(strcmp(line, "\0")){
			nextIsBody = 1;
		}

		line = strtok(NULL, "\n");
		count++;
	
	}

	printf("Method: %s\n", request.httpMethod);
	printf("Route: %s\n", request.route);
	printf("Body: %s\n", request.body);
	printf("Raw request: %s\n", request.rawRequest);
	return request;
}


void setHttpMethodAndRouteFromBuffer(struct Request * request, char * line)
{
	char httpMethod[64]; // Tamanho máximo para o método HTTP (ajuste conforme necessário)
    	char route[256]; // Tamanho máximo para a rota (ajuste conforme necessário)

 	// Use sscanf para analisar a linha de solicitação HTTP
    	if (sscanf(line, "%s %s ", httpMethod, route) != 2) {
        // A linha de solicitação não está no formato esperado
        	printf("Erro ao analisar a linha de solicitação HTTP\n");
        	return;
    	}

	request->httpMethod = httpMethod;
	request->route = route;
}

void getRequestInfo(int clientSocket, char * buffer)
{
	int readBytes = read(clientSocket, buffer, sizeof(buffer) - 1);
	if(readBytes < 0)
	{
		perror("Erro lendo o requet: ");
		close(clientSocket);
	}

	if(readBytes == 0)
	{
		printf("Cliente fechou a conexão");
		close(clientSocket);
	}

	return;
}

