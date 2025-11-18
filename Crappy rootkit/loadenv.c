#include"rkconstant.h"
#include"ld_preload.h"

/*
int load_shared_file(){

    void *shared_handle;
    const char* error = dlerror();
    
    //check if the so file exists and is readable
    if(access(Shared_Lib_Path,R_OK)==0 || access(Shared_Lib_Path,F_OK)==0){
        fprintf(stdout,"Shared file %s is avalible",Shared_Lib_Path);
        shared_handle = dlopen(Shared_Lib_Path,RTLD_GLOBAL);
        if(shared_handle == NULL){
            fprintf(stderr,"error in  loading shared object %s",error);
            return 1;
        }
        fprintf(stdout,"shared object %s loaded successfully",Shared_Lib_Path);
        return 0;
    }
    fprintf(stderr,"Shared File %s does not exists",Shared_Lib_Path);
    return -1;
}
    useless function for now stick with preload env variable
    */