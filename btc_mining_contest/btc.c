//
//  main.c
//  testing_btc_mining
//
//  Created by Ifunanya Nnoka on 12/4/16.
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

previousHeader = '15ad44909d7c00d5384e5a613fd6f132f7441a0'
nextTx = 'I, Rahul Dileep Jadhav, give Ifunanya Nnoka 10 BTC-282, on November18, 2016 2:52 am'
NMax = 100
maxNonce = 2**66
NM = int(input('Enter the number of bits to match: '))
while NM < NMax:
    start_time = time.time()
    Target = 2**(256-NM)
    difficulty = 2**NM
    nonce = random.randint(0,maxNonce)
    hash_i = hashlib.sha256(hashlib.sha256(str(previousHeader) + nextTx +str(nonce)).hexdigest()).hexdigest()
    end_time=time.time()
    elapsed_time = end_time - start_time
    if long(hash_i,16) < Target:
        print '\n\nFor number', NM, 'difficulty', difficulty
        print '\nMatching found', hash_i
        print '\nfor previousHeader=>', previousHeader
        print '\nfor => nextTx', nextTx
        print '\nFor nonce value', nonce
        print '\n Elapsed Time', elapsed_time
        print '\n CPU hash speed', nonce/elapsed_time
        NM += 1

int main(int argc, const char * argv[]){
    // char previousTx[] = "The Times 03/Jan/2009 Chancellor on brink of second bailout for banks";
    char nextTx[] = "I, Rahul Dileep Jadhav, give Ifunanya Nnoka 10 BTC-282, on November18, 2016 2:52 am";
    //"I, Ifunanya Nnoka, and Rahul Dileep Jadhav began hashing, at 11:11AM December 3, 2016";
    //  unsigned char previousHeader[BUFSIZ];
    unsigned char digest[BUFSIZ];
    unsigned char finaldigest[BUFSIZ];
    char *hash;
    //= (char*)malloc(256);
    char hex_hash[70];
    char *previousHeader = "15ad44909d7c00d5384e5a613fd6f132f7441a0";
    int NMax = 100;
    double maxNonce = pow(2,66);


   // char *hexPreviousHeader = "15ad44909d7c00d05384e5a613fd6f132f7441a0";
    char prev_next_nonce[BUFSIZ];
    char str_nonce[64];
    clock_t end;
    clock_t start;
    clock_t elapsed_time,total_t;
    //printf("maxNonce: %f\n",maxNonce);
    long double difficulty;
    long double hash_i;
    long long nonce = 712104922140203459311248264073.;
    long i;
    long double target;
    int n;
    int NM,num;
    
    
    printf("Enter number of bits to match\n");
    printf(":::: >>>>  ");
    scanf("%d",&NM);
  //  printf("NM: %d\n",NM);

while (NM < NMax){
    start = clock();//time.time()
    Target = 2**(256-NM)
    difficulty = 2**NM
    nonce = random.randint(0,maxNonce)
    hash_i = hashlib.sha256(hashlib.sha256(str(previousHeader) + nextTx +str(nonce)).hexdigest()).hexdigest()
    end_time=time.time()
    elapsed_time = end_time - start_time
    if long(hash_i,16) < Target:

begin:num = 256 - NM;
    target = 
    //        //P[i]= sqrt(((X[i].rl*X[i].rl)+(X[i].im*X[i].im)));
    printf("Target: %Lf\n",target);
    difficulty = pow(2,NM);
    //srand(time(NULL));
rand:  nonce = rand();
   // if ((nonce < 0)||(nonce>maxNonce)){
   //     goto rand;
  //  }
  //  printf("nonce: %lld\n",nonce);
    i=1;
    while (1){
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
        asprintf(&hash,"%Lf",(long long)hex_hash);
       // printf("hex_hash: %s\n",hex_hash);
        //printf("hash: %s\n",hash);
        hash_i = atof(hash);//(hash);
       //  sscanf(hash, "%Lf", &hash_i);
       //hash_i = strtod(hex_hash, &point);
       //hash_i = (double)strtoll(hex_hash, &point,16);
     //  hash_i = sscanf(hash, "%Lf", &hash_i);
        // printf("hash_i: %Lf\n",hash_i);
        free(hash);
        if(hash_i < target)
        {
            end = clock();
            elapsed_time = end-start;
            total_t = ((double)elapsed_time/CLOCKS_PER_SEC);
            printf("\nFor number: %d diffuculty: %Lf",NM,difficulty);
            printf("\nMatching Found: %s",hash);
            printf("\nFor Previous Header: %s",hexPreviousHeader);
            printf("\nFor Next Tx: %s",nextTx);
            printf("\nFor Nonce Value: %lld",nonce);
            printf("\nElapsed Time: %lu",elapsed_time);
            printf("\nElapsed Time secs: %lu",total_t);
            printf("\nCPU Hash Speed: %f",(nonce/(double)elapsed_time));
           // nonce++;
randagainw:  nonce = rand();
           // if ((nonce < 0)||(nonce>maxNonce)){
            //    goto randagainw;
         //   }
            break;
        }else{
           // nonce++;
randagain:  nonce = rand();
        //    printf("nonce: %lld\n",nonce);
          //  if ((nonce < 0)||(nonce>maxNonce)){
          //      goto randagain;
          //  }
          //  printf("\nFailed after %d tries\n",i);
            if (nonce == maxNonce){
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

