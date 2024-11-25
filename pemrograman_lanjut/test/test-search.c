#include <stdio.h>

int main()
{
  int data;
  printf("Berapa banyak data yang ingin di input:");
  scanf("%d", &data);

  int arr[data];

  for (int i = 0; i < data; i++)
  {
    /* code */
    int isiData;
    printf("Masukkan isi data ke-%d:", i+1);
    scanf("%d", &isiData);
    arr[i] = isiData;
  }
  
  int input;
  int found = 0;

  printf("Masukkan angka yang ingin dicari:\n");
  scanf("%d", &input);

  for (int i = 0; i < data; i++)
  {
    if (arr[i] == input)
    {
      found = 1;
      return 1;
    }
  }

  if (found == 1)
  {
    printf("ADA\n");
  } else {
    printf("TIDAK ADA\n");
  }
  

  return 0;
}