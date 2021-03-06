#pragma once

struct bloomstr{
    unsigned char *bloom;
    unsigned int size;
};

typedef struct bloomstr *BloomFilter;

BloomFilter bloomInitialize(unsigned int); 
unsigned int bloomInsert(BloomFilter, char *);
unsigned int bloomExists(BloomFilter, char *);
void bloomDestroy(BloomFilter);
