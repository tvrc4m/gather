#include <stdlib.h>
#include <stdio.h>
#include <regex.h>
#include "common.h"
#include "node.h"

char *url_except="javascript|css|js|jpg|png|ttf|gif|ico";

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
		node_push(top,url);
	}
	regfree(&reg);
	return NULL;
}



