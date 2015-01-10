#ifndef REQUEST_H
#define REQUEST_H

#include <curl/curl.h>
#include "node.h"

#define FETCH_DATA_MAX_SIZE 1024*100

CURL *curl;

char *request;

int fetch(const char *url,char *result,char *error);

int req_foreach(node top);

int req_match(const char *url);

#endif