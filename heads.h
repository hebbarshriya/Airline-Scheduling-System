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
#include <signal.h>
#include <zlib.h>
#define PORT 13505
#define MAX 50
#define T_TIME_CH 5
#define T_TIME_COM 7
#define T_TIME_CAR 10
#define A_TIME_CH 30
#define A_TIME_COMM 40
#define A_TIME_CAR 60

pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

/*typedef enum{
    charter,
    commercial,
    cargo
}flight_type_t;

typedef enum{
    takeof,
    landing
}status_t;*/

typedef struct flight{
    int sockfd;
    struct sockaddr_in addr;
    int id;
    char type[50];
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

flight_t *chartered;
flight_t *commercial;
flight_t *cargo;

int check_aged(flight_t* head,time_t now){
    if(now-head->in_time>=head->aged_time) return 1;
    else return 0;
}

void insert_b(info_t *info,int sockfd, struct sockaddr_in addr){
    pthread_mutex_lock(&clients_mutex);
    printf("hallo3\n");
    char buf[256];
    flight_t* temp,*head;
    flight_t* node = (flight_t*)malloc(sizeof(flight_t));
    switch(info->type){
        case(1): printf("hallo1\n");
        head = chartered;
        printf("hallo2\n");
        strcpy(node->type,"Chartered");
        node->aged_time=A_TIME_CH;
        node->takeoff_time=T_TIME_CH;
        break;
        case(2):
        head = commercial;
        strcpy(node->type,"Commercial");
        node->aged_time=A_TIME_COMM;
        node->takeoff_time=T_TIME_COM;
        break;
        case(3):
        head = cargo;
        strcpy(node->type,"Cargo");
        node->aged_time=A_TIME_CAR;
        node->takeoff_time=T_TIME_CAR;
        break;
    }
    node->id=info->id;
    node->in_time=info->in_time;
    node->sockfd=sockfd;
    node->addr=addr;
    node->next=NULL;
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
    switch(info->type){
        case(1): chartered=head;
        break;
        case(2):
        commercial=head;
        break;
        case(3):
        cargo=head;
        break;
    }

    sprintf(buf,"Flight %d waiting for runway\n",info->id);
    write(sockfd,buf,sizeof(buf));
    pthread_mutex_unlock(&clients_mutex);
    peep();
}

flight_t delete_f(flight_t* head){ 
    printf("hallo9\n");
    pthread_mutex_lock(&clients_mutex);
    flight_t* temp;
    char buf[256];
    temp = head;
    head = head->next;
    printf("Flight %d getting ready for take off\n",temp->id);
    sprintf(buf,"Runway assigned. Get ready for take off\n");
    write(temp->sockfd,buf,sizeof(buf));
    sleep(temp->takeoff_time);
    printf("Flight %d has taken off succesfully\n",temp->id);
    sprintf(buf,"Flight has taken off successfully. Have a safe journey\n");
    write(temp->sockfd,buf,sizeof(buf));
    free(temp);
    printf("hallo10\n");
    pthread_mutex_unlock(&clients_mutex);
}

void peep(){
    flight_t * temp=chartered;
    if(temp==NULL){
        printf("empty\n");
    }
    while(temp!=NULL){
        printf("%d\n",temp->id);
        temp=temp->next;
    }
    temp=commercial;
    if(temp==NULL){
        printf("empty\n");
    }
    while(temp!=NULL){
        printf("%d\n",temp->id);
        temp=temp->next;
    }
    temp=cargo;
    if(temp==NULL){
        printf("empty\n");
    }
    while(temp!=NULL){
        printf("%d\n",temp->id);
        temp=temp->next;
    }
}



