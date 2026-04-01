#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct playlist {
    char name[100];
    char artist[100];
    int time;
    struct playlist *next;
    struct playlist *prev;
} playlist;
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
void log1(int func);
int mainscreen();
extern playlist *headplaylist;
extern album *headalbum;
void playplaylist(playlist *head) {
    if (head == NULL) {
        printf("Playlist is empty!\n");
        FILE *yo = fopen("log.txt", "a");
        if (yo) { 
            fprintf(yo, "\nPlaylist empty"); 
            fclose(yo); }
        return;
    }
    playlist *temp = head;
    int p;
    printf("\nNow Playing Playlist\n");
    while (1) {
        printf("\nNow playing: %s by %s (%d sec)\n",
               temp->name, temp->artist, temp->time);
        FILE *yo = fopen("log.txt", "a");
        if (yo) { 
            fprintf(yo, "\nPlaying %s from playlist", temp->name); 
            fclose(yo);
         }
        printf("\nOptions:\n");
        printf("1. Next song\n");
        printf("2. Previous song\n");
        printf("3. Exit playlist\n");
        printf("Enter your choice: ");
        scanf("%d", &p);
        if (p == 1) temp = temp->next;
        else if (p == 2) temp = temp->prev;
        else if (p == 3) {
            printf("Exiting playlist...\n");
            FILE *yo2 = fopen("log.txt", "a");
            if (yo2) { fprintf(yo2, "\nExited playlist"); fclose(yo2); }
            log1(12);
            mainscreen();
            return;
        }}}
void addsongToplaylist(playlist **head) {
    FILE *fp = fopen("library.txt", "r");
    int idArr[1000];
    int timeArr[1000];
    char nameArr[1000][100];
    char artistArr[1000][100];
    int id, time;
    char name[100], artist[100];
    int count = 0;
    printf("\nSongs in Library:\n");
    while (fscanf(fp, "%d %s %s %d", &id, name, artist, &time) == 4) {
        count++;
        idArr[count] = id;
        timeArr[count] = time;
        strcpy(nameArr[count], name);
        strcpy(artistArr[count], artist);
        printf("%d. %s by %s (%d sec)\n", count, name, artist, time);
    }
    fclose(fp);
    int choice;
    printf("Which song index to add? ");
    scanf("%d", &choice);
    playlist *newSong = malloc(sizeof(playlist));
    strcpy(newSong->name, nameArr[choice]);
    strcpy(newSong->artist, artistArr[choice]);
    newSong->time = timeArr[choice];
    if (*head == NULL) {
        *head = newSong;
        newSong->next = newSong;
        newSong->prev = newSong;
    } else {
        playlist *last = (*head)->prev;
        last->next = newSong;
        newSong->prev = last;
        newSong->next = *head;
        (*head)->prev = newSong;
    }
    printf("Song '%s' added to playlist!\n", nameArr[choice]);
}
playlist* addAlbumSongsToPlaylist(playlist *head, album *source) {
    song *s = source->songs;
    while (s != NULL) {
        playlist *node = malloc(sizeof(playlist));
        strcpy(node->name, s->name);
        strcpy(node->artist, s->artist);
        node->time = s->time;
        if (head == NULL) {
            head = node;
            node->next = node;
            node->prev = node;
        } else {
            playlist *last = head->prev;
            last->next = node;
            node->prev = last;
            node->next = head;
            head->prev = node;
        }
        s = s->next;
    }
    return head;
}
void addalbumToplaylist() {
    printf("\nAlbums:\n");
    album *a = headalbum;
    int i = 1;
    while (a != NULL) {
        printf("%d. %s\n", i++, a->name);
        a = a->next;
    }
    if (i == 1) {
         printf("No albums available.\n"); 
        return; }

    printf("Which album index to add to playlist? ");
    int choice;
    scanf("%d", &choice);
    a = headalbum;
    int c = 1;
    while (a && c < choice) { 
        a = a->next;
         c++; }
    headplaylist = addAlbumSongsToPlaylist(headplaylist, a);
    printf("Album '%s' added to playlist!\n", a->name);
}
void viewplaylist(playlist *head) {
    if (!head) {
        printf("Playlist empty.\n");
        return;
    }
    playlist *t = head;
    int i = 1;
    printf("\nPLAYLIST CONTENT\n");
    do {
        printf("%d. %s by %s (%d sec)\n",
               i++, t->name, t->artist, t->time);
        t = t->next;
    } while (t != head);
}

