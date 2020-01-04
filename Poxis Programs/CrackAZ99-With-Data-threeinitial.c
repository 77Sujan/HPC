#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>

int n_passwords = 4;

char *encrypted_passwords[] = {

  "$6$KB$v6ysdjEBnVLSYIXWWwynKoepGtyxg5Yi9oK0IoDZYgVx5QxtwtRDH1tcwN2I9X8PMhGKMPU48qJaaoTnnh9.r.",
  "$6$KB$fi7wRBkOWq/kKRsGIqynQ/C7FnNFehbxj0RTJ/w1q2S7mT7.n9X9ssK0WdUyPRIX29rVCDPuoOh17JZS8q0Aj0",
  "$6$KB$jv4qzKJ4NX4v6rod1VRkd7tPy1xnJYskUWwIN8oW6emMKXMJPEsKlBDheZntWh9GPZtubpg2ElBnmGoCsJCWr.",
  "$6$KB$IgPcZ0.YRpVdHqI2iXeder5OmEYbdu6HHjnV657eCWkiFBkiC83u2Qe6PIziqvoQ4FtlfWZiQSM1jCNhR9Dn3/"
};


void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}



void crack(char *salt_and_encrypted){
  int a, b,d, c;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(a='A'; a<='Z'; a++){
    for(b='A'; b<='Z'; b++){
      for(d='A'; d<='Z'; d++){
      for(c=0; c<=99; c++){
        sprintf(plain, "%c%c%c%02d", a, b,d, c); 
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
