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

struct Request requestConstructor(int clientSocket) 
{
	struct Request request;
	request.buffer[30000];
	request.fieldsList = linkedListConstructor();
	request.setHeader = setHeader;
	request.fields = dictionaryConstructor(compareStringKeys);
	request.readClientSocket = readClientSocket;

	request.readClientSocket(&request, clientSocket);
	
	int nextIsBody = 0;

	char * line = strtok(request.buffer, "\n");
	unsigned int count = 0;
	while(line != NULL)
	{
		printf("\n");
		printf("line: %s\n", line);
		if(count == 0) {
			setHttpMethodAndRouteFromBuffer(&request, line);
			line = strtok(NULL, "\n");
			count++;
			continue;
		}

		if(nextIsBody == 1) {
			request.body = line;
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
		char *key, *value;
		char *lineCopy = strdup(line);
		char *lineCopyTwo = strdup(line);
		printf("copia: %s, %lu\n", lineCopyTwo, strlen(lineCopyTwo));
		request.fieldsList.push(&request.fieldsList, &lineCopyTwo, sizeof(lineCopyTwo));

		key = strsep(&lineCopy, ":");
		value = lineCopy;	

		printf("key: %s, value: %s \n", key, value);

		if(strlen(key) == 0 || value == NULL) {
			printf("pulando chave\n");
			line = strtok(NULL, "\n");
			continue;
		}

		request.fields.insert(&request.fields, key, sizeof(key), value, sizeof(value));

		line = strtok(NULL, "\n");
	}

	char routeKey[] = "Route";
	char MethodKey[] = "Method";
	char HostKey[] = "Host";
	char UserAgentKey[] = "User-Agent";
	char ContenttypeKey[] = "Content-type";
	char AuthorizationKey[] = "Authorization";

	void * httpMethodVoid = request.fields.get(&request.fields, &MethodKey, sizeof(MethodKey));
	void * routeVoid = request.fields.get(&request.fields, &routeKey, sizeof(routeKey));
	void * hostVoid = request.fields.get(&request.fields, &HostKey, sizeof(HostKey));
	void * userAgentVoid = request.fields.get(&request.fields, &UserAgentKey, sizeof(UserAgentKey));
	void * contentTypeVoid = request.fields.get(&request.fields, &ContenttypeKey, sizeof(ContenttypeKey));
	void * authorizationVoid = request.fields.get(&request.fields, &AuthorizationKey, sizeof(AuthorizationKey));

	printf("Method: %s\n", (char*) httpMethodVoid); 
	printf("Route: %s\n", (char*) routeVoid);
	printf("Host: %s\n", (char*) hostVoid);
//	printf("User-Agent: %s\n", (char*) userAgentVoid); 
	//printf("Content-type: %s\n", (char*) contentTypeVoid);
	//printf("Authorization: %s\n", (char*) authorizationVoid);
	
	request.fieldsList.print(&request.fieldsList);

	return request;
}

void setHttpMethodAndRouteFromBuffer(struct Request * request, char * line)
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


struct Entry setHeader(struct Request *req, char *line) 
{
	char *lineCopy;
	strcpy(lineCopy, line);

	char *token = strsep(&lineCopy, ": ");
	char *value = lineCopy;

	struct Entry entry = entryConstructor(token, sizeof(token), value, sizeof(value)); 

	printf("Key: %s\n", (char*)entry.key);
	printf("Value: %s\n", (char*)entry.value);

	return entry;
}
