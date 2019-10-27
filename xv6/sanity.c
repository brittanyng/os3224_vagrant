#include "types.h"
#include "stat.h"
#include "user.h"

int totalWait, totalRun, totalTat = 0;

int main(void) {
   int i, j, k;
   int pid;
   int total;
   for(i = 0; i < 20; i++) {
      pid = fork();
      if (pid == 0) {
         if(i % 2 == 0) {
            j, k, total = 0;
            for(j = 0; j < 5000; j++) {
               for(k = 0; k < 5000; k++) {
                  total = j + k - j - k + total;
               }
            }
         } else {
            j, k, total = 0;
            for(j = 0; j < 8000; j++) {
               for(k = 0; k < 8000; k++) {
                  total = j - j + k - k + total;
               }
            }
         }
         exit();
      } else if (pid == -1) {
         printf(2, "Fork Failed!\n");
         break;
      }
   }

   int wtime, rtime, iotime, status, count = 0;
   while(wait_stat(&wtime, &rtime, &iotime, &status) != -1) {
      totalWait += wtime;
      totalRun += rtime;
      totalTat += (wtime + rtime + iotime);
      printf(0, "Child pid %d has wait=%d, run=%d, tat=%d\n", status, wtime, rtime, wtime + rtime + iotime);
      count++;
   }
   printf(0, "Parent finished...\n");
   printf(0, "Average Wait Time = %d\n", totalWait / 20);
   printf(0, "Average Run Time  = %d\n", totalRun / 20);
   printf(0, "Average TAT Time  = %d\n", totalTat / 20);
   exit();
}