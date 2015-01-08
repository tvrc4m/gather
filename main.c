#include <stdio.h>
#include "common.h"
#include "node.h"
#include "request.h"

char *host;

int main(int argc,char **argv){

	char *url=argv[1];

	host=get_host(url);

	url_top=node_init(url);

	phone_top=node_init("15763951212");

	curl_global_init(CURL_GLOBAL_ALL);

	req_match(url);

	req_foreach(url_top);
	
	node next=url_top->next;
	while(next->next!=url_top){
		printf("%s\n", next->data);
		next=next->next;
	}

	// node_free(url_top);
	// node_free(phone_top);

	curl_global_cleanup();

	return 0;
}