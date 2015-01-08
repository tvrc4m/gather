#ifndef COMMON_H
#define COMMON_H

#include <regex.h>
#include "node.h"

#define count(x) (sizeof(x)/sizeof(x[0]))


typedef void *match_callback(char *content,node top,int nmatch,regmatch_t *matches);

char *substr(char *content,char *dest,int start,int end);

int start_with(const char *src,char *start);

int end_with(const char *src,const char *end);

void match(char *content,char *pattern,int nmatch,node top,match_callback callback);

void *phone_callback(char *content,node top,int nmatch,regmatch_t *matches);

void *url_callback(char *content,node top,int nmatch,regmatch_t *matches);

void match_phone(char *content,node top);

void match_url(char *content,node top);

char *get_host(char *url);

void *check_compare(char *url);



#endif