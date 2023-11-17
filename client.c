#include "heads.h"

// void read_handler();
// void display_handler();

int main(int argc, char * argv[]) {
    int sockfd;
    struct sockaddr_in server_add;
    pthread_t output_thread, input_thread;
    int id,t;
    info_t *info = (info_t*)malloc(sizeof(info_t));
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
        write(sockfd,info,sizeof(info_t));
    
    while(1){
        // if (pthread_create(&input_thread, NULL, (void *) read_handler, &sockfd) != 0) {
        //     perror("no sender thread creation");
        //     return -1;
        // }

        // if (pthread_create(&output_thread, NULL, (void *) display_handler, &sockfd) != 0) {
        //     perror("no receiver thread creation");
        //     return -1;
        // }
   
        // pthread_join(input_thread, NULL);
        // pthread_join(output_thread, NULL);
        // pthread_detach(input_thread);
        // pthread_detach(output_thread);
        buf[0]=0;
        read(sockfd,buf,sizeof(buf));
        if(buf<=0){
            close(sockfd);
        }
        if(strcmp(buf,"Close")==0)
        break;
        printf("%s\n",buf);
    }
    return 0;
}

// void read_handler(int * sockfd_ptr){
//     int sockfd=*sockfd_ptr;
//     int id,t;
//     info_t *info = (info_t*)malloc(sizeof(info_t));
//     while(1){
//         printf("Enter flight details:\n");
//         printf("ID: ");
//         if(id==-1){
//             printf("Shutting Down\n");
//             break;
//         }
//         printf("Type \n1:chatered\n2:commercial\n3:cargo\n");
//         scanf("%d",&t);
//         info->id=id;
//         info->type=t;
//         info->in_time=time(NULL);
//         write(sockfd,info,sizeof(info_t));
//     }
// }

// void display_handler(int * sockfd_ptr){
//     int sockfd=*sockfd_ptr;
//     char buf[256];
//     while(1){
//         read(sockfd,buf,sizeof(buf));
//         if(strcmp(buf,"Close")==0)
//         break;
//         printf("%s\n",buf);
//     }

// }
