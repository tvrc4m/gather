#ifndef COMMON_H
#define COMMON_H

#include <regex.h>
#include "node.h"

#define count(x) (sizeof(x)/sizeof(x[0]))

#define URL_REG_EXP "href=\"([^\"]+)\""
#define PHONE_REG_EXP "[0-9]{6,11}"

typedef void *match_callback(char *content,node top,int nmatch,regmatch_t *matches);

char *substr(char *content,char *dest,int start,int end);

void match(char *content,char *pattern,int nmatch,node top,match_callback callback);

void *phone_callback(char *content,node top,int nmatch,regmatch_t *matches);

void *url_callback(char *content,node top,int nmatch,regmatch_t *matches);

#endif