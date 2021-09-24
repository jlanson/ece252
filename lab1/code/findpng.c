#include "findpng.h"

#pragma once 
/*takes in a directory and searches everywhere under for valid png files*/

int main(int argc, char *argv[]){

    //take in directory name
    DIR *p_dir;
    struct dirent *p_dirent;
    char str[64];
    char *arg ;

    int i;
    char *ptr;
    struct stat buf;

    if (argc == 1) {
        fprintf(stderr, "Usage: %s <directory name>\n", argv[0]);
        exit(1);
    }

    if ((p_dir = opendir(argv[1])) == NULL) {
        sprintf(str, "opendir(%s)", argv[1]);
        perror(str);
        exit(2);
    }


    //printf("%s\n",argv[1]);
    //for everuyfile under directory, test if it is a regular type or a direcrtory

    while ((p_dirent = readdir(p_dir)) != NULL) {
        char *str_path = p_dirent->d_name;  /* relative path name! */

        arg = NULL;

        strcat(arg,argv[1]);
        //char *name = strcat(arg,str_path);

        //needs to be able to take absolute path

        if (str_path == NULL) {
            fprintf(stderr,"Null pointer found!"); 
            exit(3);
        } else {
            //str_path has the name of the path

            // argv[] = "c:users/angel"
            // strname= "info.png"


            // buf= "c:users/angel/info.png"

            char *symlinkpath = strcat(arg,str_path);
            char actualpath [PATH_MAX+1];

            


            ptr = realpath(symlinkpath, actualpath);
            printf("%s\n",symlinkpath);
            printf("%s\n",actualpath);
        
            // //printf("%s: ", str_path);
            if (lstat(ptr, &buf) < 0) {
                
                
                perror("lstat error");

                
                continue;
            }   

            if (S_ISREG(buf.st_mode)){
                //run is_png on this
                printf("hello");
            }
            else if (S_ISDIR(buf.st_mode)){
                //this is case of directory
                //recursive? 
                 printf("this is a directory");
                printf("%s\n",ptr);
            }

            

        }
    }

    if ( closedir(p_dir) != 0 ) {
        perror("closedir");
        exit(3);
    }


}