#include <stdio.h>

// Uray Muhammad Rajsyafiq
// 23081010029

int pascalValue(int i, int j)
{
  if (j == 0 || j == i)
  {
    return 1; // Nilai di ujung baris adalah 1
  }
  return pascalValue(i - 1, j - 1) + pascalValue(i - 1, j);
}

int main()
{
  int n;

  printf("Masukkan jumlah baris segitiga Pascal: ");
  scanf("%d", &n);

  if (n <= 0)
  {
    printf("Input tidak valid. Program hanya menerima angka positif.\n");
    return 1;
  }

  for (int i = 0; i < n; i++)
  {
    // Cetak spasi untuk membuat segitiga terlihat rapi
    for (int j = 0; j < n - i - 1; j++)
    {
      printf(" ");
    }

    // Cetak elemen dalam baris ke-i
    for (int j = 0; j <= i; j++)
    {
      printf("%d ", pascalValue(i, j));
    }
    printf("\n");
  }
  return 0;
}