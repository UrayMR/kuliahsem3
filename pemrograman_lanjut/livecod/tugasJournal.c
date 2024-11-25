// 23081010029
// Uray Muhammad Rajsyafiq

#include <stdio.h>
#include <string.h>

typedef struct journal
{
  /* data */
  char judul[100];
  char namaPenulis[100];
  char afiliasi[100];
  char email[100];
  char abstrak[500];
  char kataKunci[100];
} jurnal;

int hitungKata(const char *str)
{
  int count = 0;
  int prevChar = ' ';

  while (*str)
  {
    /* code */
    if (*str != ' ' && prevChar == ' ')
    {
      /* code */
      count++;
    }

    prevChar = *str;
    str++;
  }
  return count;
}

int validasiEmail(const char *email)
{
  const char *domain = ".ac.id";
  const char *search = strstr(email, domain);

  if (search != NULL && strcmp(search, domain) == 0 && (search[strlen(domain)] == '\0' || search[strlen(domain)] == '\n'))
  {
    // Valid
    return 1;
  }

  // Tidak valid
  return 0;
}

int validasiKataKunci(const char *kataKunci)
{
  int count = 1;
  for (int i = 0; i < strlen(kataKunci); i++)
  {
    /* code */
    if (kataKunci[i] == ',')
    {
      /* code */
      count++;
    }
  }

  return count >= 3 && count <= 5;
}

int main()
{
  int jurnalCount;

  printf("Berapa banyak jurnal yang ingin di input?");
  scanf("%d", &jurnalCount);
  getchar();

  jurnal jurnals[jurnalCount];
  char output[1000];

  for (int j = 0; j < jurnalCount; j++)
  {
    /* code */
    system("cls");
    printf("\n ------ Input Jurnal ke-%d ------ \n", j + 1);

    // Input Judul Jurnal
    do
    {
      /* code */
      printf("Masukkan judul jurnal (5-14 kata): \n");
      fgets(jurnals[j].judul, sizeof(jurnals[j].judul), stdin);

      jurnals[j].judul[strcspn(jurnals[j].judul, "\n")] = 0;

      if (hitungKata(jurnals[j].judul) < 5 || hitungKata(jurnals[j].judul) > 14)
      {
        /* code */
        printf("Judul harus terdiri dari 5-14 kata!\n");
      }

    } while (hitungKata(jurnals[j].judul) < 5 || hitungKata(jurnals[j].judul) > 14);

    // Input nama penulis
    do
    {
      /* code */
      printf("Masukkan nama penulis (maksimal 3 penulis, dipisahkan dengan koma): \n");
      fgets(jurnals[j].namaPenulis, sizeof(jurnals[j].namaPenulis), stdin);

      jurnals[j].namaPenulis[strcspn(jurnals[j].namaPenulis, "\n")] = 0;

      int penulisCount = 1; // min 1 orang
      for (int i = 0; i < strlen(jurnals[j].namaPenulis); i++)
      {
        /* code */
        if (jurnals[j].namaPenulis[i] == ',')
        {
          /* code */
          penulisCount++;
        }

        if (penulisCount > 3)
        {
          /* code */
          printf("Penulis maksimal 3 saja!\n");
        }
      }
    } while (hitungKata(jurnals[j].namaPenulis) < 1 || hitungKata(jurnals[j].namaPenulis) > 3);

    // Input afiliasi
    printf("Masukkan afiliasi jurnal: \n");
    fgets(jurnals[j].afiliasi, sizeof(jurnals[j].afiliasi), stdin);

    jurnals[j].afiliasi[strcspn(jurnals[j].afiliasi, "\n")] = 0;

    // Input email
    do
    {
      /* code */
      printf("Masukkan email penulis (harus berdomain .ac.id): \n");
      fgets(jurnals[j].email, sizeof(jurnals[j].email), stdin);
      jurnals[j].email[strcspn(jurnals[j].email, "\n")] = 0;

      if (!validasiEmail(jurnals[j].email))
      {
        /* code */
        printf("Email harus berdomain .ac.id\n");
      }

    } while (!validasiEmail(jurnals[j].email));

    // Input abstrak
    do
    {
      /* code */
      printf("Masukkan abstrak jurnal:\n");
      fgets(jurnals[j].abstrak, sizeof(jurnals[j].abstrak), stdin);

      jurnals[j].abstrak[strcspn(jurnals[j].abstrak, "\n")] = 0;

      if (hitungKata(jurnals[j].abstrak) > 200)
      {
        /* code */
        printf("Abstrak tidak boleh lebih dari 200 kata!\n");
      }
    } while (hitungKata(jurnals[j].abstrak) > 200);

    // Input kataKunci
    do
    {
      /* code */
      printf("Masukkan kata kunci (3-5 kata, dipisahkan dengan koma): \n");
      fgets(jurnals[j].kataKunci, sizeof(jurnals[j].kataKunci), stdin);
      jurnals[j].kataKunci[strcspn(jurnals[j].kataKunci, "\n")] = 0;

      if (!validasiKataKunci(jurnals[j].kataKunci))
      {
        /* code */
        printf("Kata Kunci harus terdiri dari 3-5 kata!\n");
      }

    } while (!validasiKataKunci(jurnals[j].kataKunci));
  }

  printf("\n ------ Menampilkan hasil input ------ \n");
  for (int i = 0; i < jurnalCount; i++)
  {
    /* code */
    printf("\nJurnal ke-%d:\n", i + 1);
    sprintf(output, "Judul: %s\nNama Penulis: %s\nAfiliasi: %s\nEmail: %s\nAbstrak: %s\nKata Kunci: %s\n", jurnals[i].judul, jurnals[i].namaPenulis, jurnals[i].afiliasi, jurnals[i].email, jurnals[i].abstrak, jurnals[i].kataKunci);
    printf("%s\n", &output);
  }

  return 0;
}
