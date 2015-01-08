#ifndef REQUEST_H
#define REQUEST_H

#include <curl/curl.h>

CURL *curl;

int fetch(char *url,char *result,char *error);


#endif