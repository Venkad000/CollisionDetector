/*
Space	        O(n)
Searching	    O(logn)
Traversal	    O(n)
Insertion	    O(logn)
Deletion	    O(logn)
Synchronization	O(logn)
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct node{
    char* hash;
    struct node* left;
    struct node* right;
}node;

int no_of_chunks;

int findNumberOfChunks(){
    FILE* fp;
    char path[2000]="";
    fp = popen("ls ../temp | wc -l","r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    while (fgets(path, sizeof(path), fp) != NULL) {
        
    }
    no_of_chunks = atoi(path);
    pclose(fp);
    return no_of_chunks;
}

char* findHash(char* str){
    FILE* fp;
    char path[2000]="";
    char hash[2000]="";
    char a[100] = "./md5 ";
    strcat(a,str);
    fp = popen(a,"r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    while (fgets(path, sizeof(path), fp) != NULL) {

    }
    for(int i=0;i<2000;i++){
        hash[i] = path[i];
    }
    pclose(fp);
    // printf("%s",hash);
    char* temp = hash;
    return temp;
}

void findHashOfFile(char* filename){
    char* buffer = 0;
    long length;
    FILE *f = fopen(filename,"rb");
    if (f){
        fseek(f,0,SEEK_END);
        length = ftell(f);
        fseek(f,0,SEEK_SET);
        buffer = malloc(length);
        if (buffer){
            fread(buffer,1,length,f);
        }
        fclose(f);
    }
    if (buffer){
        // printf("%s",buffer);
        FILE* fp;
        char path[2000]="";
        char hash[2000]="";
        char a[100] = "./md5 ";
        strcat(a,buffer);
        fp = popen(a,"r");
        if (fp == NULL) {
            printf("Failed to run command\n" );
            exit(1);
        }
        while (fgets(path, sizeof(path), fp) != NULL) {
            // printf("%s", path);
        }
        for(int i=0;i<2000;i++){
            hash[i] = path[i];
        }
        printf("%s",hash);
        pclose(fp);
    }
    
}

char* findHashOfTwoHashes(char* a, char* b){
    char temp[2000]="";
    strcat(temp,a);
    strcat(temp,b);
    // strcat(a,b);
    // printf("%s",temp);
    return findHash(temp);
}

char* returnHash(char* a){
    char temp[2000] = "";
    strcat(temp,a);
    return findHash(temp);
}

node* createNewNode(char* filename){
    
}

int main(){
    
    char * shit = findHashOfTwoHashes("pussy","cat");
    printf("%s",shit);

    char * shit1 = findHashOfTwoHashes("pussy","cat");
    printf("%s",shit1);
    // findHash("pussy");
    // findHash("pussy");
}


