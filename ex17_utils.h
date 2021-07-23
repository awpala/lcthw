#ifndef __ex17_utils_h__
#define __ex17_utils_h__

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

typedef struct {
  int id;
  int set;
  char name[MAX_DATA];
  char email[MAX_DATA];
} Address;

typedef struct {
  Address rows[MAX_ROWS];
} Database;

typedef struct {
  FILE *file;
  Database *db;
} Connection;

// general utilities
void die(const char *);
void Database_load(Connection *);
Connection *Database_open(const char *, char);
void Database_close(Connection *);

// actions `'c'`, `'s'`, `'d'`
void Database_write(Connection *);

// actions '`g`', `'l'`
void Address_print(Address *);

// action `'c'`
void Database_create(Connection *);

// action `'g'`
void Database_get(Connection *, int);

// action `'s'`
void Database_set(Connection *, int, const char *, const char *);

// action `'d'`
void Database_delete(Connection *, int);

// action `'l'`
void Database_list(Connection *);

// function definitions
void die(const char *message) {
  if (errno) {
    perror(message);
  } else {
    printf("ERROR: %s\n", message);
  }

  exit(1);
}

void Database_load(Connection *conn) {
  int rc = fread(conn->db, sizeof(Database), 1, conn->file);
  if (rc != 1)
    die("Failed to load database.");
}

Connection *Database_open(const char *filename, char action) {
  Connection *conn = (Connection *)malloc(sizeof(Connection));
  if (!conn)
    die("Memory error");

  conn->db = (Database *)malloc(sizeof(Database));
  if (!conn->db)
    die("Memory error");

  if (action == 'c') {
    conn->file = fopen(filename, "w");
  } else {
    conn->file = fopen(filename, "r+");

    if (conn->file) {
      Database_load(conn);
    }
  }

  if (!conn->file)
    die("Failed to open the file");
  
  return conn;
}

void Database_close(Connection *conn) {
  if (conn) {
    if (conn->file)
      fclose(conn->file);
    if (conn->db)
      free(conn->db);
    free(conn);
  }
}

void Database_write(Connection *conn) {
  rewind(conn->file);

  int rc = fwrite(conn->db, sizeof(Database), 1, conn->file);
  if (rc != 1)
    die("Failed to write database.");
  
  rc = fflush(conn->file);
  if (rc == -1)
    die("Cannot flush database.");
}

void Address_print(Address *addr) {
  printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void Database_create(Connection *conn) {
  int i = 0;

  for (i = 0; i < MAX_ROWS; i++) {
    // make a prototype to initialize it
    Address addr = { .id = i, .set = 0 };
    // then just assign it
    conn->db->rows[i] = addr;
  }
}

void Database_get(Connection *conn, int id) {
  Address *addr = &conn->db->rows[id];

  if (addr->set) {
    Address_print(addr);
  } else {
    die("ID is not set");
  }
}

void Database_set(Connection *conn, int id, const char *name, const char *email) {
  Address *addr = &conn->db->rows[id];
  if (addr->set)
    die("Already set, delete it first");

  addr->set = 1;

  // WARNING: bug, read the "How to Break It" and fix this -- program will crash if name > MAX_DATA
  char *res = strncpy(addr->name, name, MAX_DATA);
  // demonstrate the `strncpy` bug -- `strncpy` does not prevent copying `name` if it is larger than `addr->name`
  if (!res)
    die("Name copy failed");

  res = strncpy(addr->email, email, MAX_DATA);
  if (!res)
    die("Email copy failed");
}

void Database_delete(Connection *conn, int id) {
  Address addr = { .id = id, .set = 0 };
  conn->db->rows[id] = addr;
}

void Database_list(Connection *conn) {
  int i = 0;
  Database *db = conn->db;

  for (i = 0; i < MAX_ROWS; i++) {
    Address *cur = &db->rows[i];

    if (cur->set) {
      Address_print(cur);
    }
  }
}

#endif
