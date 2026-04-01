#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct song {
    int id;
    char name[100];
    char artist[100];
    int time;
    struct song *next;
} song;
typedef struct album {
    int id;
    char name[100];
    song *songs;
    struct album *next;
} album;
typedef struct playlist {
    char name[100];
    char artist[100];
    int time;
    struct playlist *next;
    struct playlist *prev;
} playlist;
song *library = NULL;
album *headalbum = NULL;
playlist *headplaylist = NULL;
song* makelibsongll();
album* loadalbumsfromfile();
int mainscreen();
int main() {
    library = makelibsongll();
    headalbum = loadalbumsfromfile();
    headplaylist = NULL;
    mainscreen();
    return 0;
}
