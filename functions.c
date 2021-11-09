#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>
#include "functions.h"

struct pop_entry * create_entry(int year, int pop, char * boro){
	struct pop_entry * e = malloc(sizeof(struct pop_entry));
	e->year = year;
	e->pop = pop;
    strcpy(e->boro, boro);
	return e;
}
void print_pop_entry(struct pop_entry * entry){
	printf("Year: %d | Boro: %s | Pop: %d\n", entry->year, entry->boro, entry-> pop);
}


int read_csv(char * PATH, char * OUT){
	//opening csv file
	int in_fd = open(PATH, O_RDONLY);
	//opening out file
	int out_fd = open(OUT, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// get size
	struct stat info;
	stat(PATH, &info);
	
	char data[info.st_size];
	read(in_fd, data, info.st_size);
	close(in_fd);

	char * boros[5] = {"Manhattan", "Brooklyn", "Queens", "Bronx", "Staten Island"};
	
	char * curr = data;
	int lines = 0;
	while(curr = strchr(curr, '\n')){
		curr++;
		lines++;
	}
	curr = data;
	curr = strchr(curr, '\n')+1;

	int i = 0;
	for(i = 0; i < lines; i++){
		int line[6];
		sscanf(curr, "%d,%d,%d,%d,%d,%d", line, line+1, line+2, line+3, line+4, line+5);
		int j;
		for(j = 0; j < 5; j++){
			struct pop_entry * e =  create_entry(line[0], line[j+1], boros[j]);
			print_pop_entry(e);
			write(out_fd, e, sizeof(struct pop_entry));
		}
		curr = strchr(curr, '\n')+1;
	}
	close(out_fd);
	printf("Wrote %ld bytes into %s\n", lines*sizeof(struct pop_entry), OUT);
	return 0;

}

struct pop_entry * read_data(char * PATH){
	//opening data file
	int in_fd = open(PATH, O_RDONLY);

	//get size
	struct stat info;
	stat(PATH, &info);
	struct pop_entry * e_arr = calloc(info.st_size / sizeof(struct pop_entry), sizeof(struct pop_entry));
	
	//reading file
	int read_in = read(in_fd, e_arr, info.st_size);
	close(in_fd);
	int i = 0;
	for (i = 0; i < info.st_size / sizeof(struct pop_entry); i++) {
		printf("%d: ", i);
		print_pop_entry(e_arr + i);
	}
	return e_arr;
}

void add_data (char * PATH){
	char DATA[256];
	printf("Enter in data entry in the format of year, borough, population (please include commas)\n");
	
	struct pop_entry e;
	fgets(DATA, 256, stdin);
	sscanf(DATA, "%d, %[^,], %d", &e.year, e.boro, &e.pop);
	int in_fd = open(PATH, O_WRONLY || O_APPEND | O_CREAT, 0644);
	lseek(in_fd, 0, SEEK_END);
	write(in_fd, &e, sizeof(struct pop_entry));
	close(in_fd);
	printf("Appended data [%d %s %d] to file %s\n",  e.year, e.boro, e.pop, PATH);
}

void update_data(char * PATH){
	struct pop_entry *entries = read_data(PATH);
	
	struct pop_entry temp;

	char ENTRY[10];
	printf("\nEnter data entry number to update\n");
	
	fgets(ENTRY, 10, stdin);
	int entry;
	sscanf(ENTRY, "%d", &entry);

	printf("\nEnter in data entry in the format of year, borough, population (please include commas)\n");
	char DATA [256];
	fgets(DATA, 256, stdin);
	sscanf(DATA, "%d, %[^,], %d", &temp.year, temp.boro, &temp.pop);
	
	int fd = open(PATH, O_WRONLY);
	lseek(fd, entry * sizeof(struct pop_entry),  SEEK_SET);
	int w = write(fd, &temp, sizeof(struct pop_entry));
	close(fd);
	printf("Updated entry %d with [%d %s %d] to file %s\n", entry, temp.year, temp.boro, temp.pop, PATH);
	
}
