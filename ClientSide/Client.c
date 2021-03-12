#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[]){
    int fd,loop=0;
    char filename[255],path[255],fullpath[255]="",buff[5000]="",aff[255],choice[2];
    FILE * file;
    mkfifo("../fifo2/pipe1",S_IRWXU|S_IRWXG|S_IRWXO);
    fd=open("../fifo2/pipe1",O_WRONLY);
 
    while(loop==0){
        printf("Veuillez choisir un des choix suivant:\n");
        printf("- 1 Envoyer un fichier \n");
        printf("- 2 Quitter\n");
        scanf("%s",&choice);
        
        if(strcmp(choice,"1")==0){
            printf("Veuillez saisir le nom du fichier\n");
            scanf(" %[^\n]",&filename);
            printf("Veuillez saisir le chemin du fichier\n");
            scanf(" %[^\n]",&path);
            strcat(fullpath,path);
            strcat(fullpath,filename);
            printf("Chemin complet : %s\n",fullpath);
            file=fopen(fullpath,"r");
            if(file==NULL){
                printf("le nom du fichier ou le chemin sont incorrecte\nle programme va se fermé...\n");
                close(fd);
                return 1;
            }else{
                while((fscanf(file,"%[^\n]\n",aff))!=EOF){
                    strcat(buff,aff);
                    strcat(buff,"\n");
                    }
                }
                fclose(file);
                write(fd,buff,sizeof(buff));
                close(fd);
                printf("_______________________________________________\n");
                printf("Le Contenu du fichier a été envoyer au serveur \nle programme va se fermé...\n");
                printf("________________________________________________\n");
                loop=1;
            
            }else  if(strcmp(choice,"2")==0){
                printf("________________________________________________________________________\n");
                printf("Le programme va se fermé...\n");
                printf("________________________________________________________________________\n");
                close(fd);
                loop=1;
            }else{
                printf("Choix erroné\n");
            }
        }

return 0;
}


