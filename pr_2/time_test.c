#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <limits.h>
int main() {
 printf("Size of time_t: %lu bites (%lu bit)\n",(unsigned long)sizeof(time_t),(unsigned long)sizeof(time_t) * 8);
 const long long max_time_val = (long long)(((unsigned long long)1 << (sizeof(time_t) * 8 - 1))-1);
 printf("Max counter value(unix timestamp): %lld\n", max_time_val);
 time_t max_t =  (time_t)max_time_val;
 struct tm *ts = gmtime(&max_t);
 char buf[80];
 if(ts != NULL) {
   strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S UTC",ts);
   printf("Overflow date: %s\n", buf);
  } else {
   printf("Time conversion error(number is too large)");
 }
 return 0;
}

