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
    
    if(is_png(buffer, size) == 1){
        printf("%s: Not a PNG", argv[1] );
        return 0;
    }
        //Checks for corrupted file
    int startingIndex = 8;
    int dataSize;
    int expectedCrC; 
    int chunkCrc;
    int corrupted = 0;
    int corruptionType = 0;
    for (int i = 0; i < 3; i++){
        dataSize = (buffer[startingIndex] << 24) + (buffer[startingIndex+1] << 16)+ (buffer[startingIndex+2] << 8)+ buffer[startingIndex+3];
        expectedCrC = crc(&buffer[startingIndex + 4], dataSize+4);
        chunkCrc = (buffer[startingIndex + 8 + dataSize] << 24)+ (buffer[startingIndex + 8 + dataSize+1] << 16)+ (buffer[startingIndex + 8 + dataSize+2] << 8)+ buffer[startingIndex + 8 + dataSize+3];
        if(chunkCrc != expectedCrC){
            corrupted = 1;
            corruptionType = i;
            break;
        }
        startingIndex += 8 + dataSize + 4;
    }
    
    //Outputs dimensions
    unsigned int width = (buffer[16] << 24 )+ (buffer[17] << 16)+(buffer[18] << 8) + buffer[19];
    unsigned int length = (buffer[20] << 24 )+ (buffer[21] << 16)+(buffer[22] << 8) + buffer[23];
    printf("%s: %d x %d\n", argv[1], width, length );

    //Outputs if file is corrupted
    if(corrupted == 1){
        if (corruptionType == 0){
            printf("IHDR: chunk CRC error computed %x, expected %x\n", expectedCrC, chunkCrc );
        }else if(corruptionType == 1){
            printf("IDAT: chunk CRC error computed %x, expected %x\n", expectedCrC, chunkCrc );
        }else if(corruptionType =2 ){
            printf("IEND: chunk CRC error computed %x, expected %x\n", expectedCrC, chunkCrc );
        }
    }
    fclose(pngFile);
}


