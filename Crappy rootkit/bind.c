#include "ld_preload.h"
#include "rkconstant.h"

//create socket object
void create(){
int sockfd,newsock_fd,status;


struct sockaddr_in *socket_config;
socket_config->sin_family =AF_INET;
socket_config->sin_port = htons(PORT);
socket_config ->sin_addr.s_addr=INADDR_ANY;

char buff[256];
sockfd=socket(AF_INET,SOCK_STREAM,0);
//check if socket is created
if(sockfd < 0){
    fprintf(stderr,"ERROR in creating socket object ");
    exit(EXIT_FAILURE);
}
status = bind(sockfd,(struct sockaddr *)socket_config,sizeof(socket_config));
if(status != 0){
    fprintf(stderr,"ERROR in binding socket ");
    exit(EXIT_FAILURE);
}
status = listen(sockfd,5);
if(status != 0){
    fprintf(stderr,"ERROR in listening to socket ");
    exit(EXIT_FAILURE);
}
newsock_fd=accept(sockfd,NULL,NULL);
if(newsock_fd !=0){
    fprintf(stderr,"ERROR in accepting connections");
    exit(EXIT_FAILURE);
}
//bind socket to port
//listen for connections
//accept connections