#ifndef LD_PRELOAD__H
#define LD_PRELOAD__H

#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<dlfcn.h>
#include<unistd.h>
#include<string.h>
#include<dirent.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<fcntl.h>

int sig_check();
int load();

#endif