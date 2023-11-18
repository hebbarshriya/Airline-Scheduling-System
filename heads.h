#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <signal.h>
#include <zlib.h>
#define PORT 13505
#define MAX 50
#define T_TIME_CH 5
#define T_TIME_COM 7
#define T_TIME_CAR 10
#define A_TIME_CH 15
#define A_TIME_COMM 20
#define A_TIME_CAR 25

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t delete = PTHREAD_MUTEX_INITIALIZER;

typedef struct flight{
    int sockfd;
    struct sockaddr_in addr;
    int id;
    int type;
    int aged_time;
    int takeoff_time;
    time_t in_time;
    struct flight *next;
}flight_t;

typedef struct{
    int id;
    int type;
    time_t in_time;
}info_t;



/*void peep(){
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
}*/


/*void* insert_b(void* arg){
    pthread_mutex_lock(&mutex);
    //sem_wait(&ins);
    flight_t* node=(flight_t*)arg;
    char buf[256];
    memset(buf,0,256);
    flight_t* temp,*head=(flight_t*)malloc(sizeof(flight_t*));
    memset(head,0,sizeof(head));
    switch(node->type){
        case(1): 
        head = chartered;
        break;
        case(2):
        head = commercial;
        break;
        case(3):
        head = cargo;
        break;
    }
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
    

    sprintf(buf,"Flight %d added in queue\n",node->id);
    write(node->sockfd,buf,sizeof(buf));
    printf(buf,"Flight %d added in queue\n",node->id);
    pthread_mutex_unlock(&mutex);
    //sem_post(&ins);
}*/
