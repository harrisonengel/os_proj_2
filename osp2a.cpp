#include <pthread.h>
#include <iostream>
#include <string>
#include <limits.h>

using namespace std;

void *average(void *args);
void *maximum(void *args);
void *minimum(void *args);

struct pass_arr{
  char **array;
  int size;
};

int glob_min, glob_max;
double avg;

int main(int size, char* args[])
{
  pthread_t avg_thread, min_thread, max_thread;
  int t;
  pass_arr to_pass;
  
  to_pass.array = &args[1];
  to_pass.size = size-1;
  
  pthread_create(&avg_thread, NULL, average, &to_pass);
  pthread_create(&min_thread, NULL, minimum, &to_pass);
  pthread_create(&max_thread, NULL, maximum, &to_pass);
  pthread_join(avg_thread, NULL);
  pthread_join(min_thread, NULL);
  pthread_join(max_thread, NULL);
  
  cout << "MEAN : " << to_string(avg) << endl;
  cout << "MAX : " << to_string(glob_max) << endl;
  cout << "MIN : " << to_string(glob_min) << endl;
  pthread_exit(NULL);
}


void *run_thread(void *args)
{
  cout << "Hello from the thread" << endl;
  pthread_exit(NULL);
}

/***************************
 *   Average
 ************************* */
void *average(void *args)
{
  struct pass_arr *p = (struct pass_arr*)args;
  int ii, sum;

  sum = 0;
  for(ii=0; ii<p->size; ii++)
    {
      sum += atoi(p->array[ii]);
    }
  avg = sum/(double)(p->size);
  pthread_exit(&avg);
  
}
  
/***************************
 *   Minimum
 ************************* */
void *minimum(void *args)
{
  struct pass_arr *p = (struct pass_arr*)args;
  int ii, min, temp;
  min = INT_MAX;

  for(ii=0; ii < p->size; ii++)
    {
      temp = atoi(p->array[ii]);
      if(temp < min)
	min = temp;
    }
  glob_min = min;
  pthread_exit(&glob_min);

}

/***************************
 *   Maximum
 ************************* */
void *maximum(void *args)
{
  struct pass_arr *p = (struct pass_arr*)args;
  int ii, max, temp;
  max = INT_MIN;

  for(ii=0; ii < p->size; ii++)
    {
      temp = atoi(p->array[ii]);
      if(temp > max)
	max = temp;
    }

  glob_max = max;
  pthread_exit(&glob_max);
}
