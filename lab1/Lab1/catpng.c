#include "pnginfo.h"

#pragma once 

int is_png(U8 *buf, size_t n){
    if (n<8){
        return 1;
    }
    unsigned int headerCheck[8] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
    for(int i = 0; i < 8; i++){
        if(buf[i] != headerCheck[i]){
            printf("%X & %X\n", buf[i], headerCheck[i]);
            return 1;
        }
    }
    //printf("this is a png");
    return 0;
}

int find_data_size(){

}


int main(int argc, char *argv[]) 
{   
    //Open all the png files passed in and save them to pngFiles
    FILE* pngFiles[argc-1];
    for(int i = 1; i < argc; i++){
        pngFiles[i-1] = fopen(argv[i], "rb+");
        printf("opened -> %s\n", argv[i]);
    }
    FILE* allPng = fopen("all.png", "wb+");
    
    int sizes[argc-1];

    //Find the file sizes for all the pngs
    for(int i = 0; i < argc-1; i++){
        fseek(pngFiles[i], 0L, SEEK_END);
        int size = ftell(pngFiles[i]);
        printf("%d\n", size);
        fseek(pngFiles[i], 0L, SEEK_SET);
        sizes[i] = size;
    }
    int largestSize = 0;
    int current;
    for(int i = 0; i < argc-1; i++){
        current = sizes[i];
        if(current>largestSize){
            largestSize = current;
        }
    }

    U8 buffers[argc-1][largestSize];
    
    for(int i = 0; i < argc-1; i++) {
        for(int j = 0; j < sizes[i]; j++ ){
            fread(buffers[i]+j, 1, 1, pngFiles[i]); 
        }
    }
    is_png(buffers[0], sizes[0]);
    is_png(buffers[1], sizes[1]);
    
    char bob[] = "asd;k;kajsdkja";
    char jerry = buffers[0][0];

    printf("%X\n", jerry);
    for(int i = 0; i < 30; i++){
        //printf("%X\n", buffers[0][i]);
    }
    //fwrite(jerry, sizeof(char), 8 , allPng);
    putc(0x77, allPng);
    U8 test[10];
    for(int i = 0; i < 100; i ++){
        fread(test+i, 1, 1, allPng); 
        printf("%X\n",test[i]);
    }

    is_png(test, 10);

    fclose(allPng);


}