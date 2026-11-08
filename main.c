#include <stdio.h>

int main(int argc, char *argv[]) {	
	if (argc < 2) {
        	printf("Usage: %s <query>\n", argv[0]);
	        return 1;
	}
	
	char *query;
	query = argv[1];
	printf("%s\n", query);

	return 0;
}
