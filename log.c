#include <stdio.h>
#include <string.h>
char name1[100];
char artist1[100];
int time1;
char name2[100];
char name3[100];
char name4[100];
char name5[100];
char artist5[100];
int time5;
char name6[100];
char name13[100];
void log1(int func);
void viewlogs();
void case5(char name[], char artist[], int time) {
    time1 = time;
    strcpy(name1, name);
    strcpy(artist1, artist);
    log1(5);
}
void case10(char name[], char artist[], int time, char album[]) {
    time5 = time;
    strcpy(name5, name);
    strcpy(artist5, artist);
    strcpy(name6, album);
    log1(10);
}
void case13(char name[]) {
    strcpy(name13, name);
    log1(13);
}
void case7(char name[]) {
    strcpy(name2, name);
    log1(7);
}
void case8(char name[]) {
    strcpy(name3, name);
    log1(8);
}
void case9(char name[]) {
    strcpy(name4, name);
    log1(9);
}
void log1(int func) {
    FILE *pt = fopen("log.txt", "a");
    switch(func) {
        case 1: fprintf(pt,"\nUser started the program!"); 
        break;
        case 2: fprintf(pt,"\nUser viewed the logs");
         break;
        case 3: fprintf(pt,"\nUser viewed all the songs");
         break;
        case 4: fprintf(pt,"\nSearched song but couldn't find it"); 
        break;
        case 5: fprintf(pt,"\nUser browsed for %s by %s (%d sec)",name1,artist1,time1); 
        break;
        case 6: fprintf(pt,"\nUser made a new playlist"); 
        break;
        case 7: fprintf(pt,"\nUser viewed %s album",name2);
         break;
        case 8: fprintf(pt,"\nUser is playing %s album",name3); 
        break;
        case 9: fprintf(pt,"\nUser is making new album %s",name4); 
        break;
        case 10: fprintf(pt,"\nUser added %s by %s to album %s",name5,artist5,name6);
         break;
        case 11: fprintf(pt,"\nUser exited the program!");
         break;
        case 12: fprintf(pt,"\nUser went back to main screen!");
         break;
        case 13: fprintf(pt,"\nViewed all songs of album %s",name13); 
        break;
        default:
         break;
    }
    fclose(pt);
}
void viewlogs() {
    FILE *fp=fopen("log.txt","r");
    char line[200];
    printf("\nUser Logs:\n");
    while(fgets(line,200,fp)) 
    printf("%s",line);
    fclose(fp);
    printf("\nEnd of logs\n");
}
