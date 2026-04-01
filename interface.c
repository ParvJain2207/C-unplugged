#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct song {
    int id;
    char name[100];
    char artist[100];
    int time;
    struct song *next;
}song;
typedef struct album {
    int id;
    char name[100];
    song *songs;
    struct album *next;
}album;
typedef struct playlist {
    char name[100];
    char artist[100];
    int time;
    struct playlist *next;
    struct playlist *prev;
}playlist;
void viewlogs();
void viewallsongs(song *library);
void browsesong();
void playalbum(album *headalbum);
album* deletealbum(album *headalbum, char name[]);
album* createnewalbum(album *head, char name[]);
void addSongToAlbum(album *head);
void viewalbumsongs(album *head);
void deletesong(album *head);
void log1(int func);
void playplaylist(playlist *head);
void addsongToplaylist(playlist **head);
void addalbumToplaylist();
void viewplaylist(playlist *head);
void savealbumstofile(album *head);
extern song *library;
extern album *headalbum;
extern playlist *headplaylist;
int mainscreen() {
    printf("\nWelcome to C-Unplugged!\nType out the function you wanna perform!\n");
    printf("Dont put spaces in songs and album names!\n");
    printf("1. View Logs\n");
    printf("2. View songs\n");
    printf("3. Browse a song & Play it\n");
    printf("4. Functions for playlist\n");
    printf("5. View albums & play them\n");
    printf("6. Modify album (add song , view album etc) \n");
    printf("7. Exit the program!\n");
    int x;
    printf("Enter your choice: ");
    scanf("%d", &x);
    switch (x) {

        case 1: {
            viewlogs();
            log1(2);
            printf("Do you want to go back to Main screen? (y/n): ");
            char a;
            scanf(" %c", &a);
            if (a=='y') {
                log1(12);
                mainscreen();
            } else {
                log1(11);
                savealbumstofile(headalbum);
                exit(0);
            }
            break;
        }

        case 2: {
            viewallsongs(library);
            log1(3);
            printf("Do you wish to go to main menu? (y/n): ");
            char u;
            scanf(" %c", &u);
            if (u=='y') {
                log1(12);
                mainscreen();
            } else {
                log1(11);
                savealbumstofile(headalbum);
                exit(0);
            }
            break;
        }
        case 3: {
            browsesong();
            printf("Do you wish to go to main menu? (y/n): ");
            char u;
            scanf(" %c", &u);
            if (u=='y') {
                log1(12);
                mainscreen();
            } else {
                log1(11);
                savealbumstofile(headalbum);
                exit(0);
            }
            break;
        }

        case 4:{
            printf("Type the function you want to perform!\n");
            printf("1. Play a playlist\n");
            printf("2. Add songs to a playlist\n");
            printf("3. Add Album to a playlist\n");
            printf("4. View all things in the playlist\n");
            int i;
            scanf("%d",&i);

            switch(i) {
                case 1: { 
                    playplaylist(headplaylist);
                    break; }
                case 2:{ 
                    addsongToplaylist(&headplaylist);
                    break; }
                case 3:{ 
                    addalbumToplaylist(); 
                    break; }
                case 4:{
                    viewplaylist(headplaylist);
                    break; }
                default:{ 
                    printf("Please type correct number!\n"); 
                    
                break; }
            }

            printf("Do you wish to go to main menu? (y/n): ");
            char u;
            scanf(" %c", &u);
            if (u=='y') {
                log1(12);
                mainscreen();
            } else {
                log1(11);
                savealbumstofile(headalbum);
                exit(0);
            }
            break;
        }
        case 5: {
            playalbum(headalbum);
            break;
        }
        case 6: {
            printf("What function do you want to apply?\n");
            printf("1. Delete specific album\n");
            printf("2. Add album\n");
            printf("3. Add song to album\n");
            printf("4. View all songs of an album\n");
            printf("5. Delete a song from an album\n");
            int r;
            scanf("%d",&r);
            switch (r) {
                case 1: {
                    char trash[5];
                    fgets(trash,5,stdin);
                    char dummy[100]="x";
                    headalbum = deletealbum(headalbum, dummy);
                    mainscreen();
                    break;
                }
                case 2: {
                    printf("What do you wanna name the album?\n");
                    char name101[100];
                    fgets(name101, 100, stdin);
                    if (name101[0]=='\n') fgets(name101,100,stdin);
                    int f=0;
                    while(name101[f]!='\0') {
                        if (name101[f]=='\n') {
                            name101[f]='\0';
                            break;
                        }
                        f++;
                    }
                    headalbum = createnewalbum(headalbum, name101);
                    mainscreen();
                    break;
                }
                case 3: {
                    addSongToAlbum(headalbum);
                    mainscreen();
                    break;
                }
                case 4: {
                    viewalbumsongs(headalbum);
                    break;
                }
                case 5: {
                    deletesong(headalbum);
                    break;
                }
                default:
                    printf("Please type correct number!\n");
                    mainscreen();
                    break;
            }
            break;
        }
        case 7: {
            log1(11);
            savealbumstofile(headalbum);
            exit(0);
        }
        default:
            printf("Please type correct number!\n");
            mainscreen();
            break;
    }
    return 0;
}
