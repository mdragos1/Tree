//PROBLEMA D1 - ietud.txt

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

int tree(char * dirName, int k){
    DIR  *dir = opendir(dirName);
    if(dir==NULL){
        perror("Error while opening directory.\n");
        return errno;
    }
    char* dirNameCopy = malloc(sizeof(char)*strlen(dirName));
    strcpy(dirNameCopy,dirName);
    char * p = strtok(dirNameCopy, "/");
    char vector[50][50];int c=0;
    while(p != NULL )
    {       
        strcpy(vector[c],p);
            c++;
            p = strtok(NULL, "/");
    }
    free(dirNameCopy);
    for(int i=0;i<k;i++){
        printf(" ");
    }
    printf("%s: \n",vector[c-1]);
    struct dirent *dirContent;
    while ((dirContent=readdir(dir)) != NULL  )
    {
       if(dirContent->d_name[0]!= '.'){
        if(dirContent->d_type == DT_DIR){
            ssize_t size= sizeof(dirName) + sizeof(dirContent->d_name) + sizeof("/");
            char *dirCopy = malloc(sizeof(char) * size);
            strcpy(dirCopy, dirName);
            strcat(dirCopy,"/");
            strcat(dirCopy,dirContent->d_name);
            tree(dirCopy,(k+strlen(vector[c-1])+1));
            free (dirCopy);
        }
        else {
            for(int i=0;i<k+strlen(vector[c-1])+1;i++){
                printf(" ");
            }
            printf("%s\n",dirContent->d_name);
        }
       }
        
    }
    closedir(dir);
}

int main (int argc, char* argv[]){
    if(argc !=2){
        printf("Incorect format, please use ./tree2 <dirName>\n");
        return -1;
    }
    tree(argv[1],0);
    return 0;
}