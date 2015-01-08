#include <string.h>
#include "request.h"

size_t curl_write_func(void *buffer,size_t size,size_t nmemb,void * stream){
	size_t result_len=size*nmemb;
	strncat(stream,buffer,result_len);
	// strcat(stream,buffer);
	return result_len;
}

int fetch(char *url,char *result,char *error){
	curl=curl_easy_init();
	curl_easy_setopt(curl,CURLOPT_URL,url);
	curl_easy_setopt(curl,CURLOPT_TIMEOUT,180);
	curl_easy_setopt(curl,CURLOPT_ERRORBUFFER,error);
	curl_easy_setopt(curl,CURLOPT_WRITEDATA,(void*)result);
	curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,curl_write_func);
	// curl_easy_setopt(curl,CURLOPT_VERBOSE,1);
	CURLcode code=curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	return code;
}