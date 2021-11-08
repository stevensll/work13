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
#define PATH_IN "nyc_pop.csv"
#define PATH_OUT "nyc_pop.data"

int main(int argc, char* argv[]){

	if (argc != 2){
		printf("Expected exactly one of the command line arguments with ./reader.out:\n -read_csv, -read_data, -add_data, or -update_data\n");
		return 0;
	}

	if (strcmp(argv[1], "-read_csv") == 0) {
		printf("Reading in csv\n");
		read_csv(PATH_IN, PATH_OUT);
	} 
	else if (strcmp(argv[1], "-read_data") == 0) {
		printf("\nReading in data\n");
		read_data(PATH_OUT);
	} 
	else if (strcmp(argv[1], "-add_data") == 0) {
		printf("\nAdding in data\n");
		add_data(PATH_OUT);
	} 
	else if (strcmp(argv[1], "-update_data") == 0) {
		printf("\nUpdating data\n");
		update_data(PATH_OUT);
	} 
	else {
		printf("Invalid command.\n");
	}
	return 0;
}
