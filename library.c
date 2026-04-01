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
song* createSong(char *name, char *artist, int duration);
song* makelibsongll() {                   
    FILE *fp = fopen("library.txt", "r");
    char name[100], artist[100];
    int time, id;                         
    song* head = NULL;
    song* tail = NULL;
    while (fscanf(fp, "%d %s %s %d", &id, name, artist, &time) == 4) { 
        song* newSong = createSong(name, artist, time);
        if (newSong == NULL)
         continue;
        newSong->id = id;          
        if (head == NULL) {
            head = newSong;
            tail = newSong;
        } 
        else {
            tail->next = newSong;
            tail = newSong;
        }
    }
    fclose(fp);
    return head;
}
