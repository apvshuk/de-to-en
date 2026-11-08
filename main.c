#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

typedef struct {
    char german[128];
    char english[512];
} Entry;

Entry dictionary[90000];
int entry_count = 0;

int compare(const void *a, const void *b) {
    return strcasecmp(
        ((Entry *)a)->german,
        ((Entry *)b)->german
    );
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
        	printf("Usage: %s <query>\n", argv[0]);
	        return 1;
	}

	FILE *file = fopen("./german_english.tsv", "r");
	if (file == NULL) {
		perror("Unable to open file");
		return EXIT_FAILURE;
	}

	// Initialize buffer pounters to NULL/0 so getline manages allocation
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	// getline return -1 on EOF or failure
	while ((read = getline(&line, &len, file)) != -1) {
	    char *german = strtok(line, "\t");
	    char *english = strtok(NULL, "\t");

	    if (german == NULL || english == NULL) continue;

	    english[strcspn(english, "\n")] = '\0';

	    strcpy(dictionary[entry_count].german, german);
	    strcpy(dictionary[entry_count].english, english);

	    entry_count++;
	}

	free(line);
	fclose(file);

	qsort(dictionary, entry_count, sizeof(Entry), compare);
	Entry key;
	strcpy(key.german, argv[1]);

	Entry *result = bsearch(&key, dictionary, entry_count, sizeof(Entry), compare);

	if (result != NULL) {
	    printf("%s\n", result->english);
	} else {
	    printf("Not found\n");
	}

	return 0;
}
