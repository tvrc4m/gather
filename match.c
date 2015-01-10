#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include "common.h"
#include "node.h"

#define URL_REG_EXP "href=\"([^\"]+)\""
#define PHONE_REG_EXP "[0-9]{7,11}"
#define HOST_REG_EXP "http://([^/]+)"

#define PHONE_NO_VALID_DATE_EXP "20[0-2][0-9][0-9][0-2][0-3][0-9]{1,6}"

char *url_except="javascript|css|js|jpg|png|ttf|gif|ico|rss";

extern char *host;

char *check_phone(char *phone){
	regex_t reg;	regcomp(&reg, PHONE_NO_VALID_DATE_EXP, REG_EXTENDED | REG_NOSUB);
	if(regexec(&reg, phone, 1, NULL, 0)==REG_NOMATCH){
		return phone;
	}
	return NULL;
}

void match(char *content,char *pattern,int nmatch,node top,match_callback callback){
	regex_t reg;
	regcomp(&reg, pattern, REG_EXTENDED | REG_ICASE | REG_NEWLINE);
	regmatch_t matches[nmatch];
	while(regexec(&reg, content, nmatch, matches,REG_NOTEOL)!=REG_NOMATCH){
		callback(content,top,nmatch,matches);
		content=content+matches[0].rm_eo;
	}
	regfree(&reg);
}

void *phone_callback(char *content,node top,int nmatch,regmatch_t *matches){
	int start=matches[0].rm_so;
	int end=matches[0].rm_eo;
	char *phone=(char*)calloc(sizeof(char*),end-start);
	substr(content,phone,start,end);
	if(check_phone(phone)!=NULL){
		log_info(phone);
		node_push(top,phone);
	}
	return NULL;
}

void *url_callback(char *content,node top,int nmatch,regmatch_t *matches){
	int start=matches[1].rm_so;
	int end=matches[1].rm_eo;
	char *url=(char*)calloc(sizeof(char*),end-start);
	substr(content,url,start,end);
	regex_t reg;
	regcomp(&reg,url_except,REG_EXTENDED | REG_NOSUB | REG_ICASE);
	if(regexec(&reg,url,1,NULL,0)==REG_NOMATCH){
		url=check_compare(url);
		if(url!=NULL){
			node_push(top,url);
		}
	}
	regfree(&reg);
	return NULL;
}

void match_phone(char *content,node top){
	match(content, PHONE_REG_EXP,1,top,phone_callback);
}

void match_url(char *content,node top){
	match(content, URL_REG_EXP,2,top,url_callback);
}

char *get_host(char *url){
	regex_t reg;
	regcomp(&reg, HOST_REG_EXP, REG_EXTENDED | REG_ICASE | REG_NEWLINE);
	regmatch_t matches[2];
	if(regexec(&reg, url, 2, matches,REG_NOTEOL)!=REG_NOMATCH){
		int start=matches[1].rm_so;
		int end=matches[1].rm_eo;
		char *host=(char*)calloc(sizeof(char*),end-start);
		substr(url,host,start,end);
		regfree(&reg);
		return host;
	}
	return NULL;
}

char *check_compare(char *url){
	
	char *domain=host;
	if(start_with(host,"www")){
		domain=strchr(host,'.')+1;
	}
	extern char *request;
	char *current=get_host(request);
	if(start_with(url,"/")){
		int len=strlen("http://")+strlen(current)+strlen(url);
		char *latest=(char*)calloc(sizeof(char),len);
		sprintf(latest,"%s%s%s","http://",current,url);
		// printf("%s\n", latest);
		return latest;
	}else{
		if(strstr(url, domain)!=NULL){
			printf("%s\n", url);
			return url;
		}
	}
	return NULL;
}


