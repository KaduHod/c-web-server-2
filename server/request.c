#include "request.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../ds/dictionary/dictionary.h"


void readClientSocket(struct Request *req ,int clientSocket)
{
	memset(req->buffer, 0, sizeof(req->buffer));
	int readBytes = read(clientSocket, req->buffer, sizeof(req->buffer) -1);

	if(readBytes < 0) {
		perror("Erro lendo o requet: ");
		close(clientSocket);
	}

	if(readBytes == 0) {
		printf("Cliente fechou a conexão");
		close(clientSocket);
	}

	strcpy(req->rawRequest, req->buffer);
}

void processRequest(struct Request *req)
{
	int nextIsBody = 0;
	int count = 0;
	char *line = strtok(req->buffer, "\n");

	while(line != NULL) {
		if(count == 0) {
			req->setMethodAndRoute(req, line);
			line = strtok(NULL, "\n");
			count++;
			continue;
		}

		if(nextIsBody == 1) {
			req->body = line;
			line = strtok(NULL, "\n");
			count++;
			nextIsBody = 0;
			continue;
		}  


		if(strlen(line) == 1){
			nextIsBody = 1;
		}

		// comecar a buscar os headers	
		if(count == 0) {
			count++;
			line = strtok(NULL, "\n");
			continue;
		}
		count++;

		if(strlen(line) > 1) {
			req->setHeader(req, line);
		}

		line = strtok(NULL, "\n");
	}
}

struct Request requestConstructor() 
{
	struct Request request;
	request.setHeader = setHeader;
	request.fields = dictionaryConstructor(compareStringKeys);
	request.readClientSocket = readClientSocket;
	request.setMethodAndRoute = setHttpMethodAndRouteFromBuffer;
	request.process = processRequest;
	return request;
}

void setHttpMethodAndRouteFromBuffer(struct Request *request, char *line)
{
	char httpMethod[64]; // Tamanho máximo para o método HTTP (ajuste conforme necessário)
    	char route[256]; // Tamanho máximo para a rota (ajuste conforme necessário)

 	// Use sscanf para analisar a linha de solicitação HTTP
    	if (sscanf(line, "%s\n %s ", httpMethod, route) != 2) {
        // A linha de solicitação não está no formato esperado
        	printf("Erro ao analisar a linha de solicitação HTTP\n");
        	return;
    	}

	// Nova forma de guardar valores
	char httpMethodKey[] = "Method";
	char routeKey[] = "Route";

	request->fields.insert(&request->fields, &httpMethodKey, sizeof(httpMethodKey), &httpMethod, sizeof(httpMethod));
	request->fields.insert(&request->fields, &routeKey, sizeof(routeKey), &route, sizeof(route));


}

void setHeader(struct Request *req, char *line) 
{
	char value[256];
	char key[256];

	if(sscanf(line, "%s %s", key, value) != 2) {
		printf("Erro ao analisar a linha!\n");
		exit(1);
	}

	// retiro o caractere ":" do header
	key[strlen(key) -1] = '\0';

	req->fields.insert(&req->fields, &key, sizeof(key), &value, sizeof(value));
}
