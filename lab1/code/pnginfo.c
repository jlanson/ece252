#include "pnginfo.h"

#pragma once 

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
    int startingIndex = 8;
    int size;
    int crc; 
    //the following is waste for checking corrupted files
    
    // for(int i = 0; i < 1; i++ ){
    //     size = (buf[startingIndex] << 8) + buf[startingIndex+3];
    //     printf("%d", size);
    //     make_crc_table();
    //     crc = crc(&buf[8], 4);
    //     printf("%d", crc);
    //     startingIndex += size;
    // }
}


int main(int argc, char *argv[]) 
{   
    // Creates the byte by pointer for the file
    FILE* pngFile = fopen(argv[1], "rb+");
    fseek(pngFile, 0L, SEEK_END);
    int size = ftell(pngFile);
    fseek(pngFile, 0L, SEEK_SET);
    U8 buffer[size];
    for(int i = 0; i < size; i++) {
       fread(buffer+i, 1, 1, pngFile); 
    }
    

    //Checks if the file is a png
    if(is_png(buffer, size) == 1){
        printf("%s: Not a PNG", argv[1] );
        return 0;
    }

    unsigned int width = (buffer[16] << 24 )+ (buffer[17] << 16)+(buffer[18] << 8) + buffer[19];
    unsigned int length = (buffer[20] << 24 )+ (buffer[21] << 16)+(buffer[22] << 8) + buffer[23];
    printf("%s: %d x %d", argv[1], width, length );

    fclose(pngFile);
}


