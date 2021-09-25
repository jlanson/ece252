#include "findpng.h"

#pragma once 
/*takes in a directory and searches everywhere under for valid png files*/

int findpng( char *path) {
     //take in directory name
    DIR *p_dir;
    struct dirent *p_dirent;
    char str[64];
    char arg[sizeof(path)] ;

    strcpy(arg,path);

    char *ptr;
    struct stat buf;

    if ((p_dir = opendir(path)) == NULL) {
        sprintf(str, "opendir(%s)", path);
        perror(str);
        exit(2);
    }

    int foundPNG = 0;

    // int counter = 0;
    //for everuyfile under directory, test if it is a regular type or a direcrtory
   

    while ((p_dirent = readdir(p_dir)) != NULL) {        
        char *str_path = p_dirent->d_name;  /* relative path name! */

        FILE* test = fopen("test.txt", "w+");
        fprintf(test, "%s", path);
        fprintf(test,"%s", "/");
        fprintf(test, "%s", str_path);
        fseek(test, 0L, SEEK_END);
        int size = ftell(test);
        fseek(test, 0L, SEEK_SET);
        char pathName [size];
        memset(pathName, '\0', size);
        fread(pathName, sizeof(char), size, test);
        pathName[size] = '\0';

        if (str_path == NULL) {
            fprintf(stderr,"Null pointer found!"); 
            exit(3);
        } else {
            char actualpath [PATH_MAX+1];

            ptr = realpath(pathName, actualpath);
        
            if (lstat(ptr, &buf) < 0) {
                perror("lstat error");
                continue;
            }   

            if (S_ISREG(buf.st_mode)){
                if (strcmp(str_path,"Lab1.out") == 0 || strcmp(str_path,"Lab1.exe") == 0 || strcmp(str_path,"a.exe") == 0){
                    continue;
                }
                FILE* pngFile = fopen(pathName, "rb+");
                fseek(pngFile, 0L, SEEK_END);
                int size = ftell(pngFile);
                fseek(pngFile, 0L, SEEK_SET);
                U8 buffer[size];
                for(int i = 0; i < size; i++) {
                fread(buffer+i, 1, 1, pngFile); 
                }
                
                if(is_png(buffer, size) == 0){
                    printf("%s\n", pathName ); //Prints pngs
                    foundPNG = 1;
                }

                fclose(pngFile);
            }else if (S_ISDIR(buf.st_mode)){
                //this is case of directory
                if (strcmp(str_path, "..") != 0 && strcmp(str_path, ".") != 0){
                    if (foundPNG == 0){
                        foundPNG = findpng(pathName);
                    }else{
                        findpng(pathName);
                    }
                }
            }else{
                continue;
            }
        }
        fclose(test);
    }
    if ( closedir(p_dir) != 0 ) {
        perror("closedir");
        exit(3);
    }
    return foundPNG;
}

int main(int argc, char *argv[]){
    if (argc == 1) {
        fprintf(stderr, "Usage: %s <directory name>\n", argv[0]);
        exit(1);
    }
   if (findpng(argv[1]) == 0){
       printf("%s: No PNG file found", argv[1]);
   }
}

int is_png(U8 *buf, size_t n){
    if (n<8){
        return 1;
    }
    unsigned int headerCheck[8] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
    for(int i = 0; i < 8; i++){
        if(buf[i] != headerCheck[i]){
            return 1;
        }
    }
    return 0;
}