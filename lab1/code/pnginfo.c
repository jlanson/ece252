#include "pnginfo.h"


#pragma once 

int is_png(U8 *buf){
    if(!buf){
        return 1;
    }
    char png[8] = {0,0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
    for (int i = 1; i < 8; i++){
        if(buf[i] != png[i]){
            return 1;
        }
    }
    return 0;
}

int main(int argc, char *argv[]) 
{   
    // Checks if the file exists
    FILE* pngFile = fopen(argv[1], "rb+");
    if (!pngFile){
        printf("%s: Not a PNG file", argv[1]);
        return 0;
    }

    //Checks if the file is a valid png
    char header[2000];
    fread(&header, sizeof(char), 8, pngFile);
    if(is_png(header)){
        printf("%s: Not a PNG file", argv[1]);
        return 0;
    }
    for(int i = 0; i< 8; i++){
        printf("%0X\n",header[i] );
    }
    printf("end of header\n");
    unsigned int IHDR; 
    fread(&IHDR, sizeof(char), 4, pngFile);
    printf("yess");
    ntohl(IHDR);
    printf("%d\n",IHDR );
    // }
    // for(int i = 0; i< 15; i++){
    //     printf("%X\n",IHDR[i] );
    // }
    fclose(pngFile);

    
}


