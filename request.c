#include <stdlib.h>
#include <string.h>
#include "request.h"
#include "common.h"

size_t write_callback(void *buffer,size_t size,size_t nmemb,void * stream){
	size_t result_len=size*nmemb;
	strncat(stream,buffer,result_len);
	// strcat(stream,buffer);
	return result_len;
}

int fetch(const char *url,char *result,char *error){
	printf("%s\n", "------------------------");
	printf("-- 开始采集 %s --\n", url);
	printf("%s\n", "------------------------");
	curl=curl_easy_init();
	curl_easy_setopt(curl,CURLOPT_URL,url);
	curl_easy_setopt(curl,CURLOPT_TIMEOUT,30);
	curl_easy_setopt(curl,CURLOPT_ERRORBUFFER,error);
	curl_easy_setopt(curl,CURLOPT_WRITEDATA,(void*)result);
	curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,write_callback);
	// curl_easy_setopt(curl,CURLOPT_VERBOSE,1);
	CURLcode code=curl_easy_perform(curl);

	long response_code;
	if(curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE,&response_code)==CURLE_OK){
		// printf("%ld\n", response_code);	
	}
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
	request=(char *)url;
	char error[100];
	char *content=(char*)calloc(sizeof(char),FETCH_DATA_MAX_SIZE);
	log_info(request);
	CURLcode code=fetch(url,content,error);
	if(code!=CURLE_OK){
		printf("%s\n", error);
	}

	match_phone(content,phone_top);
	match_url(content,url_top);
	free(content);
	return 1;
}