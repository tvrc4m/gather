#include <stdlib.h>
#include <stdio.h>
#include <regex.h>
#include "common.h"
#include "node.h"

#define URL_REG_EXP "href=\"([^\"]+)\""
#define PHONE_REG_EXP "[0-9]{6,11}"
#define HOST_REG_EXP "http://([^/]+)"

char *url_except="javascript|css|js|jpg|png|ttf|gif|ico";

extern char *host;

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
	printf("%s\n", phone);
	node_push(top,phone);
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
			printf("%s\n", url);
			node_push(top,url);
		}
		// free(url);
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

void *check_compare(char *url){
	regex_t reg;
	regcomp(&reg,host,REG_ICASE | REG_NOSUB);
	if(regexec(&reg, url, 1, NULL, 0)==REG_NOMATCH){
		if(start_with(url,"/")){
			int len=count("http://")+count(host)+count(url);
			char *latest=(char*)calloc(sizeof(char),len+1);
			sprintf(latest,"%s%s%s","http://",host,url);
			regfree(&reg);
			return latest;
		}
	}
	regfree(&reg);
	return NULL;

}

