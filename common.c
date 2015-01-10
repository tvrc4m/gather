#include "common.h"
#include <regex.h>
#include <string.h>
#include "request.h"

char *substr(char *content,char *dest,int start,int end){
	strncat(dest, content+start, end-start);
	return dest;
}

int start_with(const char *src,char *start){
	int len=count(src),slen=count(start);
	if(slen>len) return 0;
	for(;*start!='\0';src++,start++){
		if(*src!=*start) return 0;
	}
	return 1;
}

int end_with(const char *src,const char *end){
	int len=count(src),slen=count(end);
	if(slen>len) return 0;
	return !strcmp(src+len-slen,end);
}

char *str_replace(char *src,char *find,char *replace){
	return NULL;
}

int log_info(char *text){
	extern char *host;
	extern char *request;
	FILE *file=fopen("/tmp/phone.log","a+");
	if(fputs(text, file)==EOF){
		perror("fputs():");
		printf("%s      %s\n",request, text);
	}
	putc('\n', file);
	fclose(file);
	return 0;
}