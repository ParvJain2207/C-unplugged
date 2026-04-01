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
void case5(char name[], char artist[], int time);
void case9(char name[]);
void case13(char name[]);
void log1(int func);
int mainscreen();
album* loadalbumsfromfile();
void savealbumstofile(album *head);
album* getAlbumByIndex(album *head, int index) {
    int c = 1;
    while (head != NULL) {
        if (c == index) 
        return head;
        head = head->next;
        c++;
    }
    return NULL;
}
song* getSongByIndex(song *head, int index) {
    int c = 1;
    while (head != NULL) {
        if (c == index) 
        return head;
        head = head->next;
        c++;
    }
    return NULL;
}
album* createnewalbum(album *head, char name[]) {
    album *temp = head;
    int newID = 1;  //done
    if (head != NULL) {
        album *x = head;
        while (x->next != NULL) x = x->next;
        newID = x->id + 1;
    }
    if (temp == NULL) {
        temp = malloc(sizeof(album));
        strcpy(temp->name, name);
        temp->songs = NULL;
        temp->next = NULL;
        temp->id = newID;
        printf("Created a new Album!\n");
        case9(temp->name);
        return temp;
    }
    while (temp->next != NULL) 
    temp = temp->next;
    album *newAlbum = malloc(sizeof(album));
    strcpy(newAlbum->name, name);
    newAlbum->songs = NULL;
    newAlbum->next = NULL;
    newAlbum->id = newID;
    temp->next = newAlbum;
    printf("Created a new Album!\n");
    case9(newAlbum->name);
    return head;
}
void addsongtoalbum(album *albumNode, song *newsong) {

    if (albumNode == NULL) {
        return;
    }
    if (newsong == NULL) {
        return;
    }

    if (albumNode->songs == NULL) {
        albumNode->songs = newsong;
        return;
    }

    song *temp = albumNode->songs;

    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newsong;
}

song* createSong(char *name, char *artist, int duration) {     
    song *newsong = malloc(sizeof(song));
    strcpy(newsong->name, name);
    strcpy(newsong->artist, artist);
    newsong->time = duration;
    newsong->next = NULL;
    newsong->id = -1;
    return newsong;
}
void viewallsongs(song *library) { 
    int i = 1;
    while (library) {
        printf("%d. %s by %s (%d sec)\n", i++, library->name, library->artist, library->time);
        library = library->next;
    }
}
void browsesong(){                     
    FILE *fp = fopen("library.txt", "r");
    int id, time;
    char name[100], artist[100];
    int ids[1000];
    int times[1000];
    char names[1000][100];
    char artists[1000][100];
    int count = 0;
    printf("\nSongs in Library:\n");
    while (fscanf(fp, "%d %s %s %d", &id, name, artist, &time) == 4) {
        count++;
        ids[count] = id;
        times[count] = time;
        strcpy(names[count], name);
        strcpy(artists[count], artist);
        printf("%d. %s by %s (%d sec)\n", count, name, artist, time);
    }
    int choice;
    printf("Enter the song index you want to play:");
    scanf("%d", &choice);
    printf("\nSong found!\n");
    printf("Now Playing song - Name: %s\nArtist: %s\nDuration: %d\n",
           names[choice], artists[choice], times[choice]);
    case5(names[choice], artists[choice], times[choice]);
    fclose(fp);
}
void playalbum(album *head) {
    printf("\nAlbums Available:\n");
    int i = 1;
    album *p = head;
    while (p) {
        printf("%d. %s\n", i++, p->name);
        p = p->next;
    }
    printf("Enter album index: ");
    int aindex;
    scanf("%d",&aindex);
    album *t = getAlbumByIndex(head, aindex);
    printf("\nNow Playing Album: %s\n", t->name);
    if (!t->songs) {
        printf("This album has no songs.\n");
        return;
    }
    song *s = t->songs;
    while (s) {
        printf("Playing: %s by %s (%d sec)\n", s->name, s->artist, s->time);
        case5(s->name, s->artist, s->time);
        s = s->next;
    }
    printf("Album finished!\n");
    printf("Back to main?(y/n): ");
    char y;
    scanf(" %c",&y);
    if (y=='y') 
    mainscreen();
    else {
        savealbumstofile(head);
        exit(0);
    }
}
void viewalbumsongs(album *head) {
    printf("\nAlbums:\n");
    int i = 1;
    album *a = head;
    while (a) {
        printf("%d. %s\n", i++, a->name);
        a = a->next;
    }
    printf("Which album index? ");
    int idx;
    scanf("%d",&idx);
    album *t = getAlbumByIndex(head, idx);
    printf("\nSongs in Album: %s\n", t->name);
    song *s = t->songs;
    if (!s) { printf("Album empty.\n"); return; }
    int c=1;
    while (s) {
        printf("%d. %s by %s (%d sec)\n", c++, s->name, s->artist, s->time);
        s = s->next;
    }
    printf("Back to main? (y/n): ");
    char e;
    scanf(" %c",&e);
    if (e=='y')
     mainscreen();
    else {
         savealbumstofile(head); 
        exit(0); }
}
void deletesong(album *head) {
    printf("\nAlbums:\n");
    int i = 1;
    album *p = head;
    while (p) {
        printf("%d. %s\n", i++, p->name);
        p = p->next;
    }
    printf("Which album index? ");
    int aindex;
    scanf("%d",&aindex);
    album *chosen = getAlbumByIndex(head, aindex);
    if (!chosen->songs) {
         printf("Album empty!\n");
         return; }
    printf("\nSongs in %s:\n", chosen->name);
    song *s = chosen->songs;
    int c = 1;
    while (s) {
        printf("%d. %s\n", c++, s->name);
        s = s->next;
    }
    printf("Which song index to delete? ");
    int sindex;
    scanf("%d",&sindex);
    song *target = getSongByIndex(chosen->songs, sindex);
    song *cur = chosen->songs, *prev = NULL;
    while (cur && cur != target) { 
         prev = cur;
         cur = cur->next; }
    if (!prev) 
    chosen->songs = cur->next;
    else 
    prev->next = cur->next;
    printf("Song '%s' deleted.\n", cur->name);
    free(cur);
    printf("Back to main? (y/n): ");
    char e; 
    scanf(" %c",&e);
    if (e=='y')
     mainscreen();
    else { 
        savealbumstofile(head); 
        exit(0); }
}
void addSongToAlbum(album *head) {
    FILE *fp = fopen("library.txt", "r");
    int idArr[1000];
    int timeArr[1000];
    char nameArr[1000][100];
    char artistArr[1000][100];
    int id, time;
    char nm[100], art[100];
    int count = 0;
    printf("\nSongs in Library:\n");
    while (fscanf(fp, "%d %s %s %d", &id, nm, art, &time) == 4) {
        count++;
        idArr[count] = id;
        timeArr[count] = time;
        strcpy(nameArr[count], nm);
        strcpy(artistArr[count], art);
        printf("%d. %s by %s (%d sec)\n", count, nm, art, time);
    }
    int sindex;
    printf("Which song index? ");
    scanf("%d", &sindex);
    fclose(fp);
    printf("\nAlbums:\n");
    album *p = head;
    int idx = 1;
    while (p != NULL) {
        printf("%d. %s\n", idx, p->name);
        idx++;
        p = p->next;
    }
    printf("Which album index? ");
    int aindex;
    scanf("%d", &aindex);
    album *chosen = getAlbumByIndex(head, aindex);
    song *ns = createSong(nameArr[sindex], artistArr[sindex], timeArr[sindex]);
    ns->id = idArr[sindex];
    addsongtoalbum(chosen, ns);
    printf("Song '%s' added to album '%s'.\n",
           nameArr[sindex], chosen->name);
}
void savealbumstofile(album *head) {
    FILE *fp = fopen("album.txt","w");
    while (head) {
        fprintf(fp,"ALBUM %d %s\n", head->id, head->name);
        song *s = head->songs;
        while (s) {
            fprintf(fp,"SONG %d %s %s %d\n", s->id, s->name, s->artist, s->time);
            s=s->next;
        }
        fprintf(fp,"END\n");
        head=head->next;
    }
    fclose(fp);
}
album* loadalbumsfromfile() {
    FILE *fp = fopen("album.txt","r");
    if (!fp) 
    return NULL;
    album *head=NULL,*curr=NULL;
    char tag[10], name[100], artist[100];
    int id,time;
    while (fscanf(fp,"%s",tag)==1) {
        if (strcmp(tag,"ALBUM")==0) {
            album *a=malloc(sizeof(album));
            fscanf(fp,"%d %s",&a->id,a->name);
            a->songs=NULL;
             a->next=NULL;
            if (!head)
             head=a;
            else
             curr->next=a;
            curr=a;
        }
        else if (strcmp(tag,"SONG")==0) {
            song *s=malloc(sizeof(song));
            fscanf(fp,"%d %s %s %d",&s->id,s->name,s->artist,&time);
            s->time = time;
s->next = NULL;

if (curr->songs == NULL) {
    curr->songs = s;
} 
else {

    song *temp = curr->songs;

    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = s;
}

            }
        }
    
    fclose(fp);
    return head;
}
album* deletealbum(album *head, char dummy[]) {
    printf("\nAlbums:\n");
    int i=1;
    album *p=head;
    while (p) {
        printf("%d. %s\n",i++, p->name);
        p=p->next;
    }
    printf("Which album index? ");
    int idx; 
    scanf("%d",&idx);
    album *target = getAlbumByIndex(head, idx);
    if (!target)
     return head;
    album *cur=head,*prev=NULL;
    while (cur && cur!=target) { 
        prev=cur;
         cur=cur->next; }
    if (!prev) 
    head=cur->next;
    else 
    prev->next=cur->next;
    song *s=cur->songs;
    while (s) { 
        song *nx=s->next;
         free(s);
          s=nx; }
    printf("Album deleted.\n");
    free(cur);
    return head;
}
