#include "heads.h"

flight_t *chartered=NULL;
flight_t *commercial=NULL;
flight_t *cargo=NULL;

int check_aged(flight_t* head,time_t now){
    if(head!=NULL){
        if(now-head->in_time>=head->aged_time) 
        return 1;
    }
    
    return 0;
}

void delete_f(flight_t* temp){ 
    pthread_mutex_unlock(&delete);
    char buf1[256],buf2[256],buf3[256];
    memset(buf1,0,256);
    memset(buf2,0,256);
    memset(buf3,0,256);
    printf("Flight %d getting ready for take off\n",temp->id);
    sprintf(buf1,"Runway assigned. Get ready for take off\n");
    write(temp->sockfd,buf1,sizeof(buf1));
    sleep(temp->takeoff_time);
    printf("Flight %d has taken off succesfully\n",temp->id);
    sprintf(buf2,"Flight has taken off successfully. Have a safe journey\n");
    write(temp->sockfd,buf2,sizeof(buf2));
    sprintf(buf3,"Close");
    write(temp->sockfd,buf3,sizeof(buf3));
    free(temp);
    //sem_post(&delete);
    //peep();
    pthread_mutex_unlock(&delete);
    
}

flight_t* deque(int n){
    pthread_mutex_lock(&mutex);
    flight_t* node=(flight_t*)malloc(sizeof(flight_t*));
    memset(node,0,sizeof(node));
    switch(n){
        case 1: node=chartered;
            chartered=chartered->next;
            break;
        case 2: node=commercial;
            commercial=commercial->next;
            break;
        case 3: node=cargo;
            cargo=cargo->next;
            break;
    }
    pthread_mutex_unlock(&mutex);
    return node;
}

void runway_handler(){
    while(1){
        time_t now=time(NULL);
        flight_t* node;
        if(chartered!=NULL){
            if(check_aged(commercial,now)==0){
                if(check_aged(cargo,now)==0){
                    node=deque(1);
                    delete_f(node);
                    continue;
                }
                else{
                    node=deque(3);
                    delete_f(node);
                    continue;
                }
            }
            else{
                node=deque(2);
                delete_f(node);
                continue;
            }
        }
        else if(commercial!=NULL){
            if(check_aged(cargo,now)==0){
                node=deque(2);
                delete_f(node);
                continue;
            }
            else{
                node=deque(3);
                delete_f(node);
                continue;
            }
        }
        else if(cargo!=NULL){
            node=deque(3);
            delete_f(node);
            continue;
        }
        sleep(1);
    }
}
void peep(){
    flight_t * temp=chartered;
    if(temp==NULL){
        printf("empty");
    }
    while(temp!=NULL){
        printf("%d ",temp->id);
        temp=temp->next;
    }
    printf("\n");
    temp=commercial;
    if(temp==NULL){
        printf("empty");
    }
    while(temp!=NULL){
        printf("%d ",temp->id);
        temp=temp->next;
    }
    printf("\n");
    temp=cargo;
    if(temp==NULL){
        printf("empty");
    }
    while(temp!=NULL){
        printf("%d ",temp->id);
        temp=temp->next;
    }
    printf("\n");
}

void create(info_t *info,int sockfd, struct sockaddr_in addr){
    pthread_mutex_lock(&mutex);
    flight_t* node = (flight_t*)malloc(sizeof(flight_t));
    memset(node,0,sizeof(node)); 
    flight_t* temp,*head;
    char buf[256];
    memset(buf,0,256);
   
    switch(info->type){
        case(1):
        node->aged_time=A_TIME_CH;
        node->takeoff_time=T_TIME_CH;
        head = chartered;
        break;
        case(2):
        node->aged_time=A_TIME_COMM;
        node->takeoff_time=T_TIME_COM;
        head = commercial;
        break;
        case(3):
        node->aged_time=A_TIME_CAR;
        node->takeoff_time=T_TIME_CAR;
        head = cargo;
        break;
    }
    node->type=info->type;
    node->id=info->id;
    node->in_time=info->in_time;
    node->sockfd=sockfd;
    node->addr=addr;
    node->next=NULL;
    printf("Node created\n");
    if(head==NULL){
        head=node;
    }
    else{
        temp=head;
        while(temp->next!=NULL){
            temp=temp->next;
        }
        temp->next=node;
    }
    switch(node->type){
        case(1): 
        chartered=head;
        break;
        case(2):
        commercial=head;
        break;
        case(3):
        cargo=head;
        break;
    }
    
    peep();
    sprintf(buf,"Flight %d added in queue\n",node->id);
    write(node->sockfd,buf,sizeof(buf));
    printf(buf,"Flight %d added in queue\n",node->id);
    pthread_mutex_unlock(&mutex);

}

int main(){
    int mainsockfd, clisockfd,n;
    struct sockaddr_in servadd, cliadd;
    pthread_t tid,rtid;
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
    pthread_create(&tid, NULL, (void *) runway_handler, NULL);
    while(1)
    {   
        int clilen=sizeof(cliadd);
        info_t * info=(info_t*)malloc(sizeof(info_t));
        flight_t* node;
        clisockfd = accept(mainsockfd,(struct sockaddr*)&cliadd, &clilen);
        if(clisockfd<0){
            perror("Accept error\n");
        }  
        n=recv(clisockfd,info,sizeof(info_t),MSG_WAITALL);
        if(n<0){
            close(clisockfd);
        }
        create(info, clisockfd, cliadd);
        //node=create(info, clisockfd, cliadd);
        //pthread_create(&rtid, NULL, (void *) insert_b , (void *)node); 
        pthread_join(rtid, NULL);
        pthread_detach(rtid); 

    }
}