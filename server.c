#include "heads.h"

void runway_handler(){
    peep();
    int count=0;
    while(1){
        time_t now=time(NULL);
        printf("hallo1.1\n");
        if(chartered!=NULL){
            if(count!=0) count=0;
            if(check_aged(commercial,now)==0){
                if(check_aged(cargo,now)==0){
                    delete_f(chartered);
                    continue;
                }
                else{
                    delete_f(cargo);
                    continue;
                }
            }
            else{
                delete_f(commercial);
                continue;
            }
        }
        else if(commercial!=NULL){
            if(count!=0) count=0;
            if(check_aged(cargo,now)==0){
                delete_f(commercial);
                continue;
            }
            else{
                delete_f(cargo);
                continue;
            }
        }
        else if(cargo!=NULL){
            if(count!=0) count=0;
            delete_f(cargo);
            continue;
        }
        else {
            if(count<1000000){
                printf("hallooooo\n");
                count++;
                continue;
            }
            return;
        }
        printf("hallo1.2\n");
        
    }
}

int main(){
    int mainsockfd, clisockfd;
    struct sockaddr_in servadd, cliadd;
    pthread_t tid;
    char buf[256];
     
    //creating the main socket that listens for connections.
    mainsockfd=socket(AF_INET, SOCK_STREAM,0);
    if(mainsockfd<0){
        perror("Socket not created\n");
        exit(EXIT_FAILURE);
    }
    servadd.sin_family= AF_INET;
    servadd.sin_addr.s_addr = INADDR_ANY;
    servadd.sin_port=htons(PORT);
    int opt = 1;
    setsockopt(mainsockfd, SOL_SOCKET, SO_REUSEADDR, (void *) &opt, sizeof(opt));

    int res= bind(mainsockfd,(struct sockaddr*)&servadd, sizeof(servadd));
    if(res==-1){
        perror("Bind error\n");
        exit(EXIT_FAILURE);
    }
   
    printf("Server listening on port %d\n",PORT);

    listen(mainsockfd,MAX);

    //memset(chartered,0,sizeof(chartered));
    //memset(commercial,0,sizeof(commercial));
    //memset(cargo,0,sizeof(cargo));
    pthread_create(&tid, NULL, (void *) runway_handler, NULL);
    while(1)
    {   
        int clilen=sizeof(cliadd);
        info_t * info=(info_t*)malloc(sizeof(info_t));
        clisockfd = accept(mainsockfd,(struct sockaddr*)&cliadd, &clilen);
        if(clisockfd<0){
            perror("Accept error\n");
        }  
        read(clisockfd,info,sizeof(info_t));
        printf("hallo1\n");
        insert_b(info, clisockfd, cliadd);
        printf("hallo2\n");
        
        
        // pthread_join(tid, NULL);
        // pthread_detach(tid);
        // strcpy(buf,"Close");
        // write(clisockfd,buf,sizeof(buf));
        // close(mainsockfd);

    }
}