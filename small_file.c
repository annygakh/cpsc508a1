#include <stdio.h>
#include <time.h>

#define NUM_FILES 10000
#define FILE_SIZE 1024
static char data[FILE_SIZE];

int main(int argc, char ** argv)
{
  // printf("Creating files\n");
  /*
                       _
  ___ _ __ ___  __ _| |_ ___
 / __| '__/ _ \/ _` | __/ _ \
| (__| | |  __/ (_| | ||  __/
 \___|_|  \___|\__,_|\__\___|

  */
  char filename[50];
  // Start a timer here
  clock_t start_create;
  start_create = clock();
  // Create files
  for (int i = 0; i < NUM_FILES; i++)
  {
    sprintf(filename, "./test%d", i);
    FILE * fp = fopen(filename, "w+");
    if (!fp) {
      printf("could not open a file\n");
      return 2;
    }
    fwrite(data, sizeof(char), sizeof(data), fp);
    fclose(fp);
  }
  // End a timer here
  start_create = clock() - start_create;
  double time_taken_create = ((double)start_create)/CLOCKS_PER_SEC; // in seconds
  // printf("create, nilfs, %f\n", time_taken_create);

  /*
                      _
 _ __ ___  __ _  __| |
| '__/ _ \/ _` |/ _` |
| | |  __/ (_| | (_| |
|_|  \___|\__,_|\__,_|

  */
  // Start a timer here
  clock_t start_read;
  start_read = clock();
  // printf("Reading files\n");
  // Read files
  char read_buf[FILE_SIZE];
  for (int i = 0; i < NUM_FILES; i++)
  {
    sprintf(filename, "./test%d", i);
    FILE * fp = fopen(filename, "w+");
    if (!fp) {
      printf("could not open a file\n");
      return 2;
    }

    if (fread(read_buf, 1, sizeof(read_buf), fp) != 0)
      printf("Failed to read data from file\n");
    fclose(fp);
  }
  // End a timer here
  start_read = clock() - start_read;
  double time_taken_read = ((double)start_read)/CLOCKS_PER_SEC; // in seconds
  // printf("read, nilfs, %f\n", time_taken_read);
  /*
       _      _      _
  __| | ___| | ___| |_ ___
 / _` |/ _ \ |/ _ \ __/ _ \
| (_| |  __/ |  __/ ||  __/
 \__,_|\___|_|\___|\__\___|

  */
  // Start a timer here
  clock_t start_delete;
  start_delete = clock();
  // printf("Deleting files\n");
  // Delete files
  for (int i = 0; i < NUM_FILES; i++)
  {
    sprintf(filename, "./test%d", i);
    if (remove(filename) != 0)
      printf("Did not delete %s successfully\n", filename);
  }
  // End a timer
  start_delete = clock() - start_delete;
  double time_taken_delete = ((double)start_delete)/CLOCKS_PER_SEC; // in seconds
  // printf("delete, nilfs, %f\n", time_taken_delete);

  // Write out results of the benchmarks
  FILE * b_fp = fopen("benchmarks.csv", "a");
  if (!b_fp) {
      printf("could not open a file\n");
      return 2;
    }
  fprintf(b_fp, "create, nilfs, %f\n", time_taken_create);
  fprintf(b_fp, "read, nilfs, %f\n", time_taken_read);
  fprintf(b_fp, "delete, nilfs, %f\n", time_taken_delete);
  fclose(b_fp);

  return 0;
}
