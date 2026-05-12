#pragma once

struct userList {
  char username[80];
  char password[80];
  int isAdmin;
};

extern struct userList users[10];
extern int userCount;
extern char currentUser[80];
extern int loggedIn;