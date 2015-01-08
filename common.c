#include "common.h"
#include <regex.h>
#include <string.h>

char *substr(char *content,char *dest,int start,int end){
	strncat(dest, content+start, end-start);
	return dest;
}


