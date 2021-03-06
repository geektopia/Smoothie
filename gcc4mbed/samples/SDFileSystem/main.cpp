/* Copyright 2011 Adam Green (http://mbed.org/users/AdamGreen/)

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
/* LocalFileSystem test modified to use SD cards instead. */
#include "mbed.h"
#include "SDFileSystem.h"


SDFileSystem sd(p5, p6, p7, p8, "sd"); // the pinout on the mbed Cool Components workshop board


int main() 
{
    int  Result = -1;
    char Buffer[32];
    
    printf("\r\n\r\nGCC4MBED Test Suite\r\n");
    printf("sdFileSystem Unit Tests\r\n");

    printf("Test 1: fopen() for write\r\n");
    FILE *fp = fopen("/sd/out.txt", "w");  // Open "out.txt" on the sd file system for writing
    if (NULL == fp)
    {
        error("%s(%d) fopen() failed\r\n", __FILE__, __LINE__);
    }

    printf("Test 2: fprintf()\r\n");
    Result = fprintf(fp, "Hello World!");
    if (Result < 0)
    {
        error("%s(%d) fprintf() failed\r\n", __FILE__, __LINE__);
    }

    printf("Test 3: fclose() on written file\r\n");
    Result = fclose(fp);
    if (0 != Result)
    {
        error("%s(%d) fclose() failed\r\n", __FILE__, __LINE__);
    }
    


    printf("Test 4: fopen() for read\r\n");
    fp = fopen("/sd/out.txt", "r");
    if (NULL == fp)
    {
        error("%s(%d) fopen() failed\r\n", __FILE__, __LINE__);
    }

    printf("Test 5: fscanf()\r\n");
    Result = fscanf(fp, "%31s", Buffer);
    if (EOF == Result)
    {
        error("%s(%d) fscanf() failed\r\n", __FILE__, __LINE__);
    }
    printf("Contents of /sd/out.txt: %s\r\n", Buffer);

    printf("Test 6: fclose() on read file\r\n");
    Result = fclose(fp);
    if (0 != Result)
    {
        error("%s(%d) fclose() failed\r\n", __FILE__, __LINE__);
    }
    


    printf("Test 7: remove()\r\n");
    Result = remove("/sd/out.txt");                 // Removes the file "out.txt" from the sd file system
    if (0 != Result)
    {
        error("%s(%d) remove() failed\r\n", __FILE__, __LINE__);
    }
    

    printf("Test 8: opendir()\r\n");
    DIR *d = opendir("/sd");               // Opens the root directory of the sd file system
    printf("test\r\n"); 
    if (NULL == d)
    {
        error("%s(%d) opendir() failed\r\n", __FILE__, __LINE__);
    }
    struct dirent *p;

    printf("Test 9: readir() for all entries\r\n");
    while((p = readdir(d)) != NULL) 
    {                                         // Print the names of the files in the sd file system
      printf("%s\r\n", p->d_name);              // to stdout.
    }

    printf("Test 10: closedir\r\n");
    closedir(d);
  
    printf("\r\nTest completed\r\n");
}   
