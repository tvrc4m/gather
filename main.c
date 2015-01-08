#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "common.h"
#include "node.h"
#include "request.h"

#define FETCH_DATA_MAX_SIZE 1024*100

char *host;

node url_top;
node phone_top;

int main(int argc,char **argv){
	char *url=argv[1];

	url_top=node_init(url);
	phone_top=node_init("2222");

	printf("%s\n", url_top->data);

	curl_global_init(CURL_GLOBAL_ALL);
	char error[100];
	char *result=(char*)calloc(sizeof(char),FETCH_DATA_MAX_SIZE);
	CURLcode code=fetch(url,result,error);
	if(code!=CURLE_OK){
		printf("%s\n", error);
	}

	match(result, PHONE_REG_EXP,1,phone_top,phone_callback);
	match(result, URL_REG_EXP,2,url_top,url_callback);

	node next=url_top->next;
	while(next->next!=url_top){
		printf("%s\n", next->data);
		next=next->next;
	}

	free(result);
	curl_global_cleanup();
	return 0;
}