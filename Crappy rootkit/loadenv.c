#include"rkconstant.h"
#include"ld_preload.h"
int load(){
    char *preload_path = getenv(PRELOAD_ENV);
    if(preload_path != NULL){
        #ifdef DEBUG
            fprintf(stderr,"[*] Preload path found : %s \n",preload_path);
        #endif
        return 1;
    }
    else {
        #ifdef DEBUG
            fprintf(stderr,"[!] Preload path not found , setting it now \n");
        #endif
        if(setenv(PRELOAD_ENV,Shared_Lib_Path,1) != 0){
            #ifdef DEBUG
                fprintf(stderr,"[!] Error setting preload path \n");
            #endif
            return -1;
        }
        return 0;
    }
}