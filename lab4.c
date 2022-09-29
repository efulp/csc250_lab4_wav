/**
 * This program reads a WAV audio file and prints statistics about the audio samples. The file name 
 * is provided using command line arguments. If the file name is not provided or the file is not readable, 
 * the program will exit and provide an error message.
 *
 * @author Your Name Here {@literal <pluf@wfu.edu>}
 * @date Sep. 23, 2022
 * @assignment Lab 4  
 * @course CSC 250
 **/

#include <stdio.h>
#include <stdlib.h>  
#include <string.h>  
#include <math.h>  


int readWavReader(FILE* inFile, short *sampleSizePtr, int *numSamplesPtr, int *sampleRatePtr);
int readWavData(FILE* inFile, short sampleSize, int numSamples, int sampleRate);


int main(int argc, char *argv[]) {
    FILE *inFile;      /* WAV file */
    short sampleSize;  /* size of an audio sample (bits) */
    int sampleRate;    /* sample rate (samples/second) */
    int numSamples;    /* number of audio samples */ 
    int wavOK = 0;     /* 1 if the WAV file si ok, 0 otherwise */

    if(argc < 2) {
        printf("usage: %s wav_file \n", argv[0]);
        return 1;
    }

    inFile = fopen(argv[1], "rbe"); 
    if(!inFile) {
        printf("could not open wav file %s \n", argv[1]);
        return 2;
    }

    wavOK = readWavReader(inFile, &sampleSize, &numSamples, &sampleRate);
    if(!wavOK) {
       printf("wav file %s has incompatible format \n", argv[1]);   
       return 3;
    }
    else
        readWavData(inFile, sampleSize, numSamples, sampleRate);

    if(inFile) fclose(inFile);
    return 0;
}


/**
 *  function reads the RIFF, fmt, and start of the data chunk. 
 */
int readWavReader(FILE* inFile, short *sampleSizePtr, int *numSamplesPtr, int *sampleRatePtr) {
    char chunkId[] = "    ";  /* chunk id, note initialize as a C-string */
    char data[] = "    ";      /* chunk data */
    int chunkSize = 0;        /* number of bytes remaining in chunk */
    short audioFormat = 0;    /* audio format type, PCM = 1 */
    short numChannels = 0;    /* number of audio channels */ 

    /* first chunk is the RIFF chunk, let's read that info */  
    fread(chunkId, 1, 4, inFile);
    fread(&chunkSize, 1, 4, inFile);
    printf("chunk: %s, size: %d \n", chunkId, chunkSize);
    fread(data, 1, 4, inFile);
    printf("  data: %s \n", data);

    /* let's try to read the next chunk, it always starts with an id */
    fread(chunkId, 1, 4, inFile);
    /* if the next chunk is not "fmt " then let's skip over it */  
    while(strcmp(chunkId, "fmt ") != 0) {
        fread(&chunkSize, 1, 4, inFile);
        /* skip to the end of this chunk */  
        fseek(inFile, chunkSize, SEEK_CUR);
        /* read the id of the next chuck */  
        fread(chunkId, 1, 4, inFile);
    }  

    /* if we are here, then we must have the fmt chunk, now read that data */  
    fread(&chunkSize, 1, 4, inFile);
    fread(&audioFormat, 1,  sizeof(audioFormat), inFile);
    fread(&numChannels, 1,  sizeof(numChannels), inFile);
    /* you'll need more reads here, hear? */  

    printf("chunk: %s, size: %d \n", chunkId, chunkSize);
    printf(" audioFormat: %d \n", audioFormat);

    /* read the data chunk next, use another while loop (like above) */
    /* visit http://goo.gl/rxnHB1 for helpful advice */

    return (audioFormat == 1);
}


/**
 *  function reads the WAV audio data (last part of the data chunk)
 */
int readWavData(FILE* inFile, short sampleSize, int numSamples, int sampleRate) {

   return 1;
}



