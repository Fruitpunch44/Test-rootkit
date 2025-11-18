#include"rkconstant.h"
#include"ld_preload.h"

int sig_check(){
    if(access(SIGNATURE_PATH,F_OK)== 0){
        fprintf(stdout,"Path %s exists continue whatever",SIGNATURE_PATH);
        return 1;
    }
    else {
        fprintf(stderr,"Path %s does not exist ,exiting now",SIGNATURE_PATH);
<<<<<<< HEAD
        return -1;
=======
        //compile backdoor first
        //might have to use make for this damn thing
        return 0;
>>>>>>> ad67d173960c85505564d929eaa660236a6a904d
    }
}



