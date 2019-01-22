#include <stdio.h>
#include <time.h>
#include <stdlib.h>     /* atoi */

#define FILE_SIZE 104900000
static char data[FILE_SIZE];

int main(int argc, char** argv)
{
  const char * sysname = argv[1];
  const char * fname = "large.txt";
  // Create a file using sequential writes
  FILE *fp = fopen(fname, "w+");

  clock_t t;
  t = clock();
  if (fwrite(data, sizeof(char), sizeof(data), fp) < FILE_SIZE) {
    printf("Error writing to file\n");
    return 2;
  }

  t = clock() - t;
  double time_seq_write = ((double)t) / CLOCKS_PER_SEC; // sec

  // Seek to beginning of the file
  fseek(fp, 0, SEEK_SET);

  // Sequential read from the beginning of the file
  t = clock();
  fread(data, sizeof(char), sizeof(data), fp);
  t = clock() - t;
  double time_seq_read = ((double)t) / CLOCKS_PER_SEC; // sec

  // Random 100Mbytes write
  t = clock();
  fseek(fp, 20000, SEEK_SET);
  if (fwrite(data, sizeof(char), sizeof(data), fp) < FILE_SIZE)
  {
    printf("Error writing to file\n");
    return 2;
  }
  t = clock() - t;
  double time_random_write = ((double)t) / CLOCKS_PER_SEC; // sec

  // Random 100Mbytes read
  t = clock();
  fseek(fp, 200000, SEEK_SET);
  fread(data, sizeof(char), sizeof(data), fp);
  t = clock() - t;
  double time_random_read = ((double)t) / CLOCKS_PER_SEC; // sec

  // Seek to beginning of the file
  fseek(fp, 0, SEEK_SET);

  // Reread the file sequentially
  t = clock();
  fread(data, sizeof(char), sizeof(data), fp);
  t = clock() - t;
  double time_seq_reread = ((double)t) / CLOCKS_PER_SEC; // sec
  fclose(fp);

  if (remove(fname) != 0)
      printf("Did not delete %s successfully\n", fname);



  FILE * b_fp = fopen("benchmarks_large.csv", "a");
  fprintf(b_fp, "time_seq_write, %s, %f\n", sysname, time_seq_write);
  fprintf(b_fp, "time_seq_read, %s, %f\n", sysname, time_seq_read);
  fprintf(b_fp, "time_random_write, %s, %f\n", sysname, time_random_write);
  fprintf(b_fp, "time_random_read, %s, %f\n", sysname, time_random_read);
  fprintf(b_fp, "time_seq_reread, %s, %f\n", sysname, time_seq_reread);
  fclose(b_fp);
  return 0;
}