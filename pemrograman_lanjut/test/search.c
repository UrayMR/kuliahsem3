#include <stdio.h>

int main()
{
  int n = 9;
  int data[] = {3, 4, 200, 23, 1, 24, 1, 42, 3, 2, 25, 3, 436, 36, 99};
  int cari = 3;
  int found = 0;
  int count = 0;

  for (int i = 0; i < n; i++)
  {
    if (data[i] == cari)
    {
      found = 1;
      break;
    }
    count++;
  }

  if (found)
  {
    printf("Data ditemukan : %d\n", cari);
  }
  else
  {
    printf("Data tidak ditemukan : %d\n", cari);
  }

  printf("Jumlah loop : %d", count);

  return 0;
}