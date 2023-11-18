#include "heads.h"

int main(int argc, char * argv[]) {
    int sockfd,n;
    struct sockaddr_in server_add;
    pthread_t output_thread, input_thread;
    int id,t;
    info_t *info = (info_t*)malloc(sizeof(info_t));
    memset(info,0,sizeof(info_t));
    char *srv_ip, buf[256];

    if (argc != 2) {
      printf("Usage: ./progname <ip_addr>\n");
      exit(0);
    }

    srv_ip = argv[1];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket not created\n");
        exit(EXIT_FAILURE);
    }

    server_add.sin_family = AF_INET;
    server_add.sin_addr.s_addr = inet_addr(srv_ip);
    server_add.sin_port = htons(PORT);
    int len = sizeof(server_add);
    int res=connect(sockfd,(struct sockaddr *)&server_add,len);
    if (res==-1) {
        perror("Socket not connected");
        exit(1);
    }
    printf("Enter flight details:\n");
    printf("ID: ");
    scanf("%d",&id);
    printf("Type \n1:chatered\n2:commercial\n3:cargo\n");
    scanf("%d",&t);
    info->id=id;
    info->type=t;
    info->in_time=time(NULL);
    printf("Flight %d waiting for runway\n",id);
    write(sockfd,info,sizeof(info_t));
    
    while(1){
        memset(buf,0,256);
        n=recv(sockfd,buf,sizeof(buf),MSG_WAITALL);
        if(n<0){
            close(sockfd);
        }
        if(strcmp(buf,"Close")==0){
            break;
        }
        printf("%s\n",buf);
    }
    return 0;
}


