/************************************************************************
	Excersize 17 from Learn C the Hard Way
	The goal is to learn the difference between stack and heap memory 
	allocation. 
	
	First I followed the code and wrote comments on what it should do on
	a large scale. Then I rewrote the code trying to look at the textbook 
	as little as possible. 
	
	Author: kj01a
************************************************************************/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

//define max_data and max_rows
#define MAX_DATA 512
#define MAX_ROWS 100

//create structs for address, database and connection
//Address hols the values of the entries into the db
struct Address{
	int id;
	int set; 
	char name[MAX_DATA];
	char email[MAX_DATA];
};

//The Database struct is an array of rows that is defined as an Address datatype. 
struct Database{
	struct Address rows[MAX_ROWS]; 
};

//Connection is a struct that links the database struct in memory with the db file on disk.
struct Connection{
	FILE *file;
	struct Database *db;
};

//First things first, error exceptions. 
//Kill program on error and send tailored error message
void die(const char *message){
	if (errno){
		perror(message);
	}
	else{
		printf("ERROR: %s\n", message);
	}
	
	exit(1);
}

//We need a function to print out elements of an address variable.
void Address_print(struct Address *addr){
	printf("%d, %s, %s\n", addr->id, addr->name, addr->email);
}

//Program needs to read db
//research fread function and it's arguments
//Allows the user to interact with the db file
void Database_load(struct Connection (*conn)){
	int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
	if (rc != 1){
		die("Failed to load database");
	}
}

//Open a connction to the db file created by the Database_create() function
//So, the database is basically just a dat file. This function opens that file in either
//a read-only or writable way.  
struct Connection *Database_open(const char *filename, char mode){
	struct Connection *conn = malloc(sizeof(struct Connection));
	if (!conn){
		die("Memory error");
	}
	
	conn->db = malloc(sizeof(struct Database));
	if (!conn->db){
		die("Memory error");
	}
	
	if (mode == 'c'){
		conn->file = fopen(filename, "w");
	}
	else{
		conn->file = fopen(filename, "r+");
		
		if (conn->file){
			Database_load(conn);
		}
	}
	
	if (!conn->file){
		die("Failed to load file");
	}
	
	return conn;
}

//Close the db safely
void Database_close(struct Connection *conn){
	if (conn){
		if (conn->file)
			fclose(conn->file);
		if (conn->db)
			free(conn->db);
		free(conn);
	}
}

//Create the db file
void Database_write(struct Connection *conn){
	rewind(conn->file);
	
	int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
	
	if (rc != 1)
		die("Failed to write to database.");
	
	rc = fflush(conn->file); //clears output buffer for when new output is needed
	
	if (rc == -1)
		die("Cannot not flush database");
}

//Instantiate db prototype
//This is basically the skeleton of the db.
//A db of empty rows
void Database_create(struct Connection *conn){
	int i = 0;
	
	for(i = 0; i < MAX_ROWS; i++){
		struct Address addr = {.id = i, .set = 0};
		conn->db->rows[i] = addr;
	}
}

//Allow the user to insert data into db
//This is a weird one for me, I guess. It's basically an insert in sql, but the built in
//function have me confused. Will need to research more. 
void Database_set(struct Connection *conn, int id, const char *name, const char *email){
	struct Address *addr = &conn->db->rows[id];
	if (addr->set)
		die("Address already set.");
	
	addr->set = 1;
	
	//apparently there is a bug here
	//must study strcpy
	char *res = strncpy(addr->name, name, MAX_DATA);
	
	if (!res)
		die("Name copy failed.");
	
	res = strncpy(addr->email, email, MAX_DATA);
	
	if (!res)
		die("Email copy faild.");
}

//Allow user to query db
//select statment
void Database_get(struct Connection *conn, int id){
	struct Address *addr = &conn->db->rows[id];
	
	if (addr->set){
		Address_print(addr);
	}
	else{
		die("ID is not set.");
	}
}

//Delete db entry
void Database_delete(struct Connection *conn, int id){
	struct Address addr = {.id = id, .set = 0};
	conn->db->rows[id] = addr;
}

//List all entries in db
//select * from file;
void Database_list(struct Connection *conn){
	int i = 0;
	struct Database *db = conn->db;
	
	for (i = 0; i < MAX_ROWS; i++){
		struct Address *cur = &db->rows[i];
		
		if (cur->set){
			Address_print(cur);
		}
	}
}

int main(int argc, char *argv[]){
	if (argc < 3)
		die("USAGE: ex17 <dbfile> <action> [action params]");
	
	//The second cl arg is the db file
	char *filename = argv[1];
	//the first letter of the third cl arg is the action
	char action = argv[2][0];
	//open the db
	//all of those params in the funcs above, this is where we define the arg for them
	struct Connection *conn = Database_open(filename, action);
	//init id to 0
	int id = 0;
	
	if (argc > 3) id = atoi(argv[3]);
	if (id >= MAX_ROWS) die("There are not that many records.");
	
	//switch statment defines what each action does
	switch (action){
		case 'c':
			Database_create(conn);
			Database_write(conn);
			break;
		
		case 'g':
			if (argc != 4)
				die("Need an ID to get");
			
			Database_get(conn, id);
			break;
			
		case 's':
			if (argc != 6)
				die("Need id, name, and email to set");
			
			Database_set(conn, id, argv[4], argv[5]);
			Database_write(conn);
			break;
			
		case 'd':
			if (argc != 4)
				die("Need id to delete");
			
			Database_delete(conn, id);
			Database_write(conn);
			break;
			
		case 'l':
			Database_list(conn);
			break;
			
		default:
			die("Invalid action: c=create, g=get, s=set, d=delete, l=list.");
			
	}
	
	Database_close(conn);
	
	return 0;
}
