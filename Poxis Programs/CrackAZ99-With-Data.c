#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>

int n_passwords = 4;

char *encrypted_passwords[] = {

  "$6$KB$GBVaKSTtLZW0JdGUtA3Not7zfm.y3TVu4794tItHazIldslHZ8jyaNfulL2j3lfwZ6UJ5quOjm7S1PIPgcR9Z/",
  "$6$KB$hZ.CC7zI1bt9cPr7Z4cdMH0Hc7pvWb4NywkydXlUM3GWSGaQQAWA7qkHoiXLtH.xusB9kFs0NHZWl3kFxfgQi/",
  "$6$KB$J3m7A6YF43jN.rIbG8Awh6mNUw7WArtgZ1qN39ijK8NWs0.0dpFmD0RRktXQLqrBJMV3z3BYCt24JnG23bfGy.",
  "$6$KB$d5TFYVYcXhnzUaB3o.JQ0MytgBkcwb66OTtAmt/PgjJMmEqH4QjKBlrVHIzTuxAMJEzO/h7ASM.xQxlhBio330"
};

/**
 Required by lack of standard function in C.   
*/

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}


void crack(char *salt_and_encrypted){
  int a, b, c;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(a='A'; a<='Z'; a++){
    for(b='A'; b<='Z'; b++){
      for(c=0; c<=99; c++){
        sprintf(plain, "%c%c%02d", a, b, c); 
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        } else {
          printf(" %-8d%s %s\n", count, plain, enc);
        }
      }
    }
  }
  printf("%d solutions explored\n", count);
}
 int time_difference(struct timespec *start, struct timespec *finish, 
                              long long int *difference) {
  long long int ds =  finish->tv_sec - start->tv_sec; 
  long long int dn =  finish->tv_nsec - start->tv_nsec; 

  if(dn < 0 ) {
    ds--;
    dn += 1000000000; 
  } 
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}


int main(int argc, char *argv[]){
  int i;
  struct timespec start, finish;   
  long long int time_elapsed;

  clock_gettime(CLOCK_MONOTONIC, &start);
 
  for(i=0;i<n_passwords;i<i++) {
    crack(encrypted_passwords[i]);
  }

 clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed, 
         (time_elapsed/1.0e9));

  return 0;
}
