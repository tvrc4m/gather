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
		callback(top,nmatch,matches);

		int start=match[0].rm_so;
		int end=match[0].rm_eo;
		char *dest=(char*)calloc(sizeof(char*),end-start);

		if(match[1].rm_so!=-1){
			printf("%lld\n", match[1].rm_so);
		}

		callback(top,substr(content,dest,start,end));
		content=content+end;
	}
	regfree(&reg);
}

void *phone_callback(node top,regmatch_t *matches){
	printf("%s\n", match);
	node_push(top,match);
	return NULL;
}

void *url_callback(node top,regmatch_t *matches){
	regex_t reg;
	regcomp(&reg,url_except,REG_EXTENDED | REG_NOSUB | REG_ICASE);
	if(regexec(&reg,match,1,NULL,0)==REG_NOMATCH){
		node_push(top,match);		
	}
	regfree(&reg);
	return NULL;
}



