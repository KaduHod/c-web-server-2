#include "date.h"
#include <time.h>
#include <stdio.h>

char* getDate() 
{
	time_t currentTime;
	time(&currentTime);
	char* dateString = ctime(&currentTime);
	return dateString;
}
