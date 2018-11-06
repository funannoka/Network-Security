//
//  main.c
//  btc_hashing
//
//  Created by Ifunanya Nnoka on 12/2/16.
//  Copyright © 2016 Ifunanya Nnoka. All rights reserved.
//

#include <stdio.h>
#include <sys/types.h>
#include <sys/signal.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include<time.h>
#if defined(__APPLE__)
#define COMMON_DIGEST_FOR_OPENSSL
#include <CommonCrypto/CommonDigest.h>
#define SHA1 CC_SHA1
#define SHA512 CC_SHA512
#define MD5 CC_MD5
#define SHA256 CC_SHA256
#else
#include <openssl/sha.h>
#include <openssl/ripemd.h>
#include <openssl/md5.h>
#endif

char *hash_gen_sha256(const char *field, int len){
    int i;
    SHA256_CTX p;
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char *hash = (char*)malloc(65);
    
    SHA256_Init(&p);
    while (len > 0) {
        if (len > 512) {
            SHA256_Update(&p, field, 512);
        } else {
            SHA256_Update(&p, field, len);
        }
        len -= 512;
        field += 512;
    }
    SHA256_Final(digest, &p);
    for (i = 0; i < sizeof(digest); ++i) {
        snprintf(&(hash[i*2]), SHA256_DIGEST_LENGTH*2,"%02x",(unsigned int)digest[i]);
    }
    return hash;
}


int main(int argc, const char * argv[]){
   // char previousTx[] = "The Times 03/Jan/2009 Chancellor on brink of second bailout for banks";
    char nextTx[] = "I, Ifunanya Nnoka, and Rahul Dileep Jadhav began hashing, at 11:11AM December 3, 2016";
///  unsigned char previousHeader[BUFSIZ];
    unsigned char digest[BUFSIZ];
    unsigned char finaldigest[BUFSIZ];
    char *hash;//= (char*)malloc(256);
   // char *point;
    char hex_hash[70];
   // char *hex_hash;
    char *hexPreviousHeader = "15ad44909d7c00d05384e5a613fd6f132f7441a0";
    char prev_next_nonce[BUFSIZ];
    char str_nonce[64];
    clock_t end;
    clock_t start;
    clock_t elapsed_time,total_t;
    double maxNonce = pow(2,66);
    printf("maxNonce: %f\n",maxNonce);
    long double difficulty;
  long double hash_i;
    long long nonce; //=15606388348;
    //9469105958;
    long double target;
    int n;
    long i=1;
    int NMax = 100;
    float NM,num;
    
    //SHA256(previousTx, strlen(previousTx), previousHeader);
   // for (n = 0; n < SHA256_DIGEST_LENGTH; ++n) {
  //      snprintf(&(hexPreviousHeader[n*2]),SHA256_DIGEST_LENGTH*2,"%02x",(unsigned int)previousHeader[n]);
   // }
        printf("Enter number of bits to match\n");
        printf(":::: >>>>  ");
        scanf("%f",&NM);
        //printf("NM: %d\n",NM);
begin:  num = 256 - NM;
        target = pow(2,num);
        printf("Target: %Lf\n",target);
        difficulty = pow(2,NM);
        //srand(time(NULL));
        //nonce = rand();
    start = clock();
    while (0 <= nonce < maxNonce){
        // bzero(str_nonce, sizeof(str_nonce));
        sprintf(str_nonce,"%lld",nonce);
        // printf("nonce: %s\n",str_nonce);
        strcpy(prev_next_nonce,hexPreviousHeader);
        strcat(prev_next_nonce,nextTx);
        strcat(prev_next_nonce,str_nonce);
        SHA256(prev_next_nonce,strlen(prev_next_nonce),digest);
        for (n = 0; n < SHA256_DIGEST_LENGTH; ++n){
            snprintf(&(hex_hash[n*2]),SHA256_DIGEST_LENGTH*2,"%02x",(unsigned int)digest[n]);
        }
        SHA256(hex_hash,strlen(hex_hash),finaldigest);
        for (n = 0; n < SHA256_DIGEST_LENGTH; ++n){
            snprintf(&(hex_hash[n*2]),SHA256_DIGEST_LENGTH*2,"%02x",(unsigned int)finaldigest[n]);
        }
        asprintf(&hash,"%Lf",(unsigned long long)hex_hash);
        // printf("hex_hash: %s\n",hex_hash);
        //printf("hash: %s\n",hash);
        hash_i = atof(hash);//(hash);
        free(hash);
        //  sscanf(hash, "%Lf", &hash_i);
        //hash_i = strtod(hex_hash, &point);
        //hash_i = (double)strtoll(hex_hash, &point,16);
        //  hash_i = sscanf(hash, "%Lf", &hash_i);
       //  printf("hash_i: %Lf\n",hash_i);
        if(hash_i < target)
        {
            end = clock();
            elapsed_time = end-start;
            total_t = ((double)elapsed_time/CLOCKS_PER_SEC);
            printf("\nFor number: %f diffuculty: %Lf",NM,difficulty);
            printf("\nMatching Found: %s",hex_hash);
            printf("\nFor Previous Header: %s",hexPreviousHeader);
            printf("\nFor Next Tx: %s",nextTx);
            printf("\nFor Nonce Value: %lld",nonce);
            printf("\nElapsed Time: %lu",elapsed_time);
            printf("\nElapsed Time secs: %lu",total_t);
            printf("\nCPU Hash Speed: %f",(nonce/(double)elapsed_time));
            nonce++;
            break;
        }else{
            nonce++;
            if (nonce == maxNonce) {
                printf("\nFailed after %ld tries\n",i);
            }
        }
        i++;
    }
    printf("\n============\n");
    NM = NM + 1;
    if (NM <NMax)
        goto begin;
    return 0;
}
