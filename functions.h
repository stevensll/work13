#define CHAR_SIZE 10

struct pop_entry{
	int year;
	int pop;
	char boro[CHAR_SIZE];
};

struct pop_entry * create_entry(int year, int pop, char * boro);

void print_pop_entry(struct pop_entry * entry);

int read_csv(char *PATH, char * OUT);

struct pop_entry * read_data(char *PATH);

void add_data(char *PATH);

void update_data(char *PATH);
