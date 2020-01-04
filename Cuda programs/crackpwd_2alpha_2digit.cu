#include <stdio.h>
#include <cuda_runtime_api.h>
#include <time.h>

__device__ int is_a_match(char *attempt) {
  char password1[] = "AV70";
  char password2[] = "ES07";
  char password3[] = "HT12";
  char password4[] = "RB23";

  char *s = attempt;
  char *u = attempt;
  char *j = attempt;
  char *n = attempt;
  char *pwd1 = password1;
  char *pwd2 = password2;
  char *pwd3 = password3;
  char *pwd4 = password4;

  while(*s == *pwd1) {
   if(*s == '\0')
    {
    printf("Found password: %s\n",password1);
      break;
    }

    s++;
    pwd1++;
  }
    
  while(*u == *pwd2) {
   if(*u == '\0')
    {
    printf("Found password: %s\n",password2);
      break;
}

    u++;
    pwd2++;
  }

  while(*j == *pwd3) {
   if(*j == '\0')
    {
    printf("Found password: %s\n",password3);
      break;
    }

    j++;
    pwd3++;
  }

  while(*n == *pwd4) {
   if(*n == '\0')
    {
    printf("Found password: %s\n",password4);
      return 1;
    }

    n++;
    pwd4++;
  }
  return 0;

}


__global__ void  kernel() {
char t,k;
 
  char password[5];
  password[4] = '\0';

int i = blockIdx.x+65;
int j = threadIdx.x+65;
char firstValue = i;
char secondValue = j;
    
password[0] = firstValue;
password[1] = secondValue;
    for(t='0'; t<='9'; t++){
      for(k='0'; k<='9'; k++){
            password[2] = t;
            password[3] = k;
          if(is_a_match(password)) {
        //printf("Success");
          }
             else {
         //printf("tried: %s\n", password);          
            }
          }
        } 
      
}
int time_difference(struct timespec *start,
                    struct timespec *finish,
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


int main() {

  struct  timespec start, finish;
  long long int time_elapsed;
  clock_gettime(CLOCK_MONOTONIC, &start);

kernel <<<26,26>>>();
  cudaThreadSynchronize();

  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed, (time_elapsed/1.0e9));
  return 0;
}




