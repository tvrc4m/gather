#include <stdlib.h>
#include <string.h>
#include "request.h"
#include "common.h"
#include "phone.h"

size_t write_callback(void *buffer,size_t size,size_t nmemb,void * stream){
	size_t result_len=size*nmemb;
	strncat(stream,buffer,result_len);
	// strcat(stream,buffer);
	return result_len;
}

int fetch(const char *url,char *result,char *error){
	curl=curl_easy_init();
	curl_easy_setopt(curl,CURLOPT_URL,url);
	curl_easy_setopt(curl,CURLOPT_TIMEOUT,180);
	curl_easy_setopt(curl,CURLOPT_ERRORBUFFER,error);
	curl_easy_setopt(curl,CURLOPT_WRITEDATA,(void*)result);
	curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,write_callback);
	// curl_easy_setopt(curl,CURLOPT_VERBOSE,1);
	CURLcode code=curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	return code;
}

int req_foreach(node top){
	node next=top->next;
	while(next!=top){
		if(next->data){
			req_match(next->data);
		}
		next=next->next;
	}
	return 1;
}

int req_match(const char *url){
	char error[100];
	char *content=(char*)calloc(sizeof(char),FETCH_DATA_MAX_SIZE);
	CURLcode code=fetch(url,content,error);
	if(code!=CURLE_OK){
		printf("%s\n", error);
	}

	match(content, PHONE_REG_EXP,1,phone_top,phone_callback);
	match(content, URL_REG_EXP,2,url_top,url_callback);
	free(content);
	return 1;
}