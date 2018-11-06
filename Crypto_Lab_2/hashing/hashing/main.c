//
//  main.c
//  hashing
//
//  Created by Ifunanya Nnoka on 12/2/16.
//  Copyright © 2016 Ifunanya Nnoka. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#if defined(__APPLE__)
#define COMMON_DIGEST_FOR_OPENSSL
#include <CommonCrypto/CommonDigest.h>
#define SHA1 CC_SHA1
#define SHA512 CC_SHA512
#define MD5 CC_MD5
#else
#include <openssl/sha.h>
#include <openssl/ripemd.h>
#include <openssl/md5.h>
#endif

unsigned char ibuf[BUFSIZ]; // ibuf is used to store the plain text
unsigned char obuf[BUFSIZ]; // obuf is used to store the hashed value of plain text
unsigned char dictbuf[BUFSIZ]; // used to store hashed word from dictionary
unsigned char word[BUFSIZ]; // stores the current word from dictionary
//#define BUFSIZ 512
void chop(char *word){ //this function is used to chop the \n after the word, if any.
    int lenword;
    lenword = strlen(word);
    if(word[lenword-1] == '\n')
        word[lenword-1] = '\0';
}
int main()
{
    char hash_type[BUFSIZ];
    char n_mactch_bytes[BUFSIZ];
    int result,bytes,y,n,i=0;
    char *hash = (char*)malloc(33);
    char *dict_hash = (char*)malloc(33);

    FILE *words; // this is the default dictionary in Ubuntu in the location "/usr/share/dict/words"
    words=fopen("/usr/share/dict/words","r");
    printf("Enter the word to hash \n");
    printf(":::: >>>>  ");
    fgets(ibuf,2701,stdin);
    chop(ibuf); // save this in variable ibuf
    printf("Select the Hashing algorithm: \n Enter 1 for MD5 \n "\
        "Enter 2 for SHA512 \n Enter 3 for RMD160 \n"); // save this in variable hash_type
    printf(":::: >>>>  ");
    fgets(hash_type,2701,stdin);
    chop(hash_type); // save this in variable ibuf
    printf("Enter the no of bytes to match \n");//save this in variable bytes
    printf(":::: >>>>  ");
    fgets(n_mactch_bytes,2701,stdin);
    chop(n_mactch_bytes); // save this in variable ibuf
    bytes = atoi(n_mactch_bytes);
    
    //depending on the hash_type use appropriate hashing algorithm
   switch(hash_type[0]) {
    case '1': // for MD5
        MD5(ibuf, strlen(ibuf), obuf); // with the help of this function, the word stored in variabe ibuf is hashed and stored in variable obuf
           for (n = 0; n < MD5_DIGEST_LENGTH; ++n) {
               snprintf(&(hash[n*2]), 16*2, "%02x", (unsigned int)obuf[n]);
           }
        //print user input word
        printf("User input: %s\n",ibuf);
        //print hash of input word (hint: the hash is in hex)
        printf(" \n \n start of result \n");
           printf("Hash of Input:\n");
           printf("%s",hash);
        y=1; // variable y is used to give a serial number
           
        /*traverse through dictionary until the end*/
        while (fgets(word, sizeof(word), words)){
            chop(word);
           // printf("current dictionary word: %s\n",word);
            MD5(word, strlen(word), dictbuf); //hash dictionary word
            for (n = 0; n < MD5_DIGEST_LENGTH; ++n) {
                snprintf(&(dict_hash[n*2]), 16*2, "%02x", (unsigned int)dictbuf[n]);
            }
            result = memcmp(hash, dict_hash, bytes);
        //if match is found, print the sr. no. and the word
            if (result == 0){
                //match found
                printf("\nMatch Found!\n");
                printf("serial no.: %d\n",y);
                printf("dictionary word: %s\n",word);
                printf("Hash of dictionary word:\n");
                printf("%s",dict_hash);
                i++;
            }
        y++;//increase sr. no.
        //print the hash of the match found
           }
           if (i == 0) {
               printf("\nMatch not found\n");
           }else printf("\nNo of Matches found: %d\n",i);
        break;
        // similarly code for sha512 and rmd160
    case '2':
           SHA512(ibuf, strlen(ibuf), obuf); // with the help of this function, the word stored in variabe ibuf is hashed and stored in variable obuf
           for (n = 0; n < SHA512_DIGEST_LENGTH; ++n) {
               snprintf(&(hash[n*2]), SHA512_DIGEST_LENGTH*2, "%02x", (unsigned int)obuf[n]);
           }
           //print user input word
           printf("User input: %s\n",ibuf);
           //print hash of input word (hint: the hash is in hex)
           printf(" \n \n start of result \n");
           printf("Hash of Input:\n");
           printf("%s",hash);
           y=1; // variable y is used to give a serial number
           
           /*traverse through dictionary until the end*/
           while (fgets(word, sizeof(word), words)){
               chop(word);
               // printf("current dictionary word: %s\n",word);
               SHA512(word, strlen(word), dictbuf); //hash dictionary word
               for (n = 0; n < SHA512_DIGEST_LENGTH; ++n) {
                   snprintf(&(dict_hash[n*2]), SHA512_DIGEST_LENGTH*2, "%02x", (unsigned int)dictbuf[n]);
               }
               result = memcmp(hash, dict_hash, bytes);
               //if match is found, print the sr. no. and the word
               if (result == 0){
                   //match found
                   printf("\nMatch Found!\n");
                   printf("serial no.: %d\n",y);
                   printf("dictionary word: %s\n",word);
                   printf("Hash of dictionary word:\n");
                   printf("%s",dict_hash);
                   i++;
               }
               y++;//increase sr. no.
               //print the hash of the match found
           }
           if (i == 0) {
               printf("\nMatch not found\n");
           }else printf("\nNo of Matches found: %d\n",i);
        break;
    case '3':
           SHA1(ibuf, strlen(ibuf), obuf); // with the help of this function, the word stored in variabe ibuf is hashed and stored in variable obuf
           for (n = 0; n < SHA_DIGEST_LENGTH; ++n) {
               snprintf(&(hash[n*2]), SHA_DIGEST_LENGTH*2, "%02x", (unsigned int)obuf[n]);
           }
           //print user input word
           printf("User input: %s\n",ibuf);
           //print hash of input word (hint: the hash is in hex)
           printf(" \n \n start of result \n");
           printf("Hash of Input:\n");
           printf("%s",hash);
           y=1; // variable y is used to give a serial number
           
           /*traverse through dictionary until the end*/
           while (fgets(word, sizeof(word), words)){
               chop(word);
               // printf("current dictionary word: %s\n",word);
               SHA1(word, strlen(word), dictbuf); //hash dictionary word
               for (n = 0; n < SHA_DIGEST_LENGTH; ++n) {
                   snprintf(&(dict_hash[n*2]), SHA_DIGEST_LENGTH*2, "%02x", (unsigned int)dictbuf[n]);
               }
               result = memcmp(hash, dict_hash, bytes);
               //if match is found, print the sr. no. and the word
               if (result == 0){
                   //match found
                   printf("\nMatch Found!\n");
                   printf("serial no.: %d\n",y);
                   printf("dictionary word: %s\n",word);
                   printf("Hash of dictionary word:\n");
                   printf("%s",dict_hash);
                   i++;
               }
               y++;//increase sr. no.
               //print the hash of the match found
           }
           if (i == 0) {
               printf("\nMatch not found\n");
           }else printf("\nNo of Matches found: %d\n",i);
        break;
    }
    
}