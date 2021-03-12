#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>
#include <error.h>
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;


void *ThreadFunc(void *arg){
    pthread_mutex_lock(&mtx);
    char *buff=(char*) arg;
    FILE * file;
    file=fopen("server.txt","a");
    fputs(buff,file);
    fclose(file);
    if(strlen(buff)>0){
    printf("_____________________________________________________________________\n");
    printf("Le contenu du fichier reçu a bien était rajouté au fichier server.txt\n");
    }
    pthread_mutex_unlock(&mtx);
    pthread_exit(NULL);
}


int main(){
    int fd;
    char buff[5000];
    FILE * file;
    pthread_t th;
    mkfifo("../fifo2/pipe1",S_IRWXU|S_IRWXG|S_IRWXO);    
    fd=open("../fifo2/pipe1",O_RDONLY);
    
    while(1){
    if(read(fd,buff,sizeof(buff))){
        if(pthread_create(&th,NULL,ThreadFunc,&buff)==-1){
            perror("erreur lors de la création");
            return EXIT_FAILURE;
        }
        if(pthread_join(th,NULL)){
            perror("erreur de join");
            return EXIT_FAILURE;
        }
        
        pthread_mutex_destroy(&mtx);
        }
    }
    
    
    close(fd);
  

    return 0;
}
