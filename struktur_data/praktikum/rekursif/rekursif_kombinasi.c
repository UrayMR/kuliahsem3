#include <stdio.h>
#include <string.h>

// 23081010029
// Uray Muhammad Rajsyafiq

// Fungsi rekursif untuk mencetak semua kombinasi karakter
void kombinasi(char *set, char *prefix, int n, int k)
{
  // Basis rekursi: Jika panjang kombinasi sudah mencapai k
  if (k == 0)
  {
    printf("%s\n", prefix);
    return;
  }

  // Iterasi melalui setiap karakter dalam set
  for (int i = 0; i < n; i++)
  {
    // Menambahkan karakter ke prefix
    int len = strlen(prefix);
    prefix[len] = set[i];
    prefix[len + 1] = '\0';

    // Rekursi dengan mengurangi panjang kombinasi yang tersisa
    kombinasi(set, prefix, n, k - 1);

    // Menghapus delimiter
    prefix[len] = '\0';
  }
}

int main()
{
  int n;
  char set[100];

  printf("Masukkan set karakter (tanpa spasi): ");
  scanf("%s", set);

  printf("Masukkan panjang kombinasi: ");
  scanf("%d", &n);

  if (n <= 0)
  {
    printf("Panjang kombinasi harus lebih dari 0.\n");
    return 1;
  }

  int set_len = strlen(set);
  char prefix[100] = ""; // Buffer untuk menyimpan kombinasi saat ini

  // Memulai proses rekursif
  printf("Kombinasi dengan panjang %d:\n", n);
  kombinasi(set, prefix, set_len, n);

  return 0;
}
