#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  int noRegistrasi;
  char namaLengkap[100];
  char alamat[100];
  int jenisKelamin; // 1 untuk laki-laki, 0 untuk perempuan
  int umur;
} pasien;

void searchPasien(pasien *dataPasien, int jumlahPasien, int noRegis, char namaLengkap[100], char alamat[100], int umur)
{
  int found = 0;
  int namaLengkap_match = strcmp(namaLengkap, "0"); // return valuenya 0 kalau comparenya sesuai
  int alamat_match = strcmp(alamat, "0");
  for (int i = 0; i < jumlahPasien; i++)
  {
    if ((noRegis == 0 || dataPasien[i].noRegistrasi == noRegis) &&
        (namaLengkap_match == 0 || strlen(namaLengkap) == 0 || strstr(dataPasien[i].namaLengkap, namaLengkap)) &&
        (alamat_match == 0 || strlen(alamat) == 0 || strstr(dataPasien[i].alamat, alamat)) &&
        (umur == 0 || dataPasien[i].umur == umur))
    {
      printf("\nPasien ditemukan:\n");
      printf("Nomor Registrasi: %d\n", dataPasien[i].noRegistrasi);
      printf("Nama Lengkap: %s", dataPasien[i].namaLengkap);
      printf("Alamat: %s", dataPasien[i].alamat);
      printf("Jenis Kelamin: %s\n", dataPasien[i].jenisKelamin ? "Laki-laki" : "Perempuan");
      printf("Umur: %d\n", dataPasien[i].umur);
      found = 1;
    }
  }
  if (!found)
  {
    printf("\nData pasien tidak ditemukan.\n");
  }
}

void menampilkanDataPasien(pasien *dataPasien, int jumlahPasien)
{
  if (jumlahPasien == 0)
  {
    printf("\nTidak ada data pasien yang tersedia.\n");
    return;
  }

  printf("\n------------------------------------\n");
  printf("Menampilkan seluruh data pasien\n");
  printf("------------------------------------\n");
  for (int i = 0; i < jumlahPasien; i++)
  {

    if (dataPasien[i].noRegistrasi == 0)
    {
      break;
    }

    printf("\nPasien ke-%d\n", i + 1);
    printf("Nomor Registrasi: %d\n", dataPasien[i].noRegistrasi);
    printf("Nama Lengkap: %s", dataPasien[i].namaLengkap);
    printf("Alamat: %s", dataPasien[i].alamat);
    printf("Umur: %d\n", dataPasien[i].umur);
    printf("Jenis Kelamin: %s\n", dataPasien[i].jenisKelamin ? "Laki-laki" : "Perempuan");
  }
}

int main()
{
  pasien dataPasien[500];

  int jumlahPasien = 0;
  int pilihan;

  while (1)
  {
    printf("\n------------------------------------\n");
    printf("Program Data Klinik\n");
    printf("------------------------------------\n");
    printf("1. Input Data Pasien\n");
    printf("2. Mencari Data Pasien\n");
    printf("3. Menampilkan seluruh Data Pasien\n");
    printf("4. Keluar\n");
    printf("------------------------------------\n");
    printf("Masukkan pilihan anda: ");
    scanf("%d", &pilihan);
    getchar();

    switch (pilihan)
    {
    case 1:
      if (jumlahPasien < 500)
      {
        printf("\n------------------------------------\n");
        printf("Input Data Pasien\n");
        printf("------------------------------------\n");

        printf("Masukkan nama pasien: ");
        fgets(dataPasien[jumlahPasien].namaLengkap, sizeof(dataPasien[jumlahPasien].namaLengkap), stdin);

        printf("Masukkan alamat: ");
        fgets(dataPasien[jumlahPasien].alamat, sizeof(dataPasien[jumlahPasien].alamat), stdin);

        do
        {
          printf("Masukkan jenis kelamin (1 untuk laki-laki, 0 untuk perempuan): ");
          scanf("%d", &dataPasien[jumlahPasien].jenisKelamin);
          getchar();

          if (dataPasien[jumlahPasien].jenisKelamin != 0 && dataPasien[jumlahPasien].jenisKelamin != 1)
          {
            printf("Tolong input jenis kelamin sesuai intruksi!\n");
          }
        } while (dataPasien[jumlahPasien].jenisKelamin != 0 && dataPasien[jumlahPasien].jenisKelamin != 1);

        printf("Masukkan umur: ");
        scanf("%d", &dataPasien[jumlahPasien].umur);
        getchar();

        dataPasien[jumlahPasien].noRegistrasi = jumlahPasien + 1;

        printf("\nNo Registrasi Pasien yang baru dimasukkan adalah: %d\n", dataPasien[jumlahPasien].noRegistrasi);

        jumlahPasien++;
      }
      else
      {
        printf("Data pasien sudah penuh.\n");
      }
      break;

    case 2:
    {
      int searchNoRegis;
      char tempNamaLengkap[100];
      char tempAlamat[100];
      int tempUmur;

      printf("\n------------------------------------\n");
      printf("Mencari Data Pasien\n");
      printf("------------------------------------\n");
      printf("Note: isi angka 0 atau skip(enter) jika tidak diketahui\n");

      printf("Masukkan nomor registrasi pasien: ");
      scanf("%d", &searchNoRegis);
      getchar();

      printf("Masukkan nama lengkap pasien: ");
      fgets(tempNamaLengkap, sizeof(tempNamaLengkap), stdin);
      tempNamaLengkap[strcspn(tempNamaLengkap, "\n")] = '\0';

      printf("Masukkan alamat pasien: ");
      fgets(tempAlamat, sizeof(tempAlamat), stdin);
      tempAlamat[strcspn(tempAlamat, "\n")] = '\0';

      printf("Masukkan umur pasien: ");
      scanf("%d", &tempUmur);
      getchar();

      searchPasien(dataPasien, jumlahPasien, searchNoRegis, tempNamaLengkap, tempAlamat, tempUmur);
      break;
    }

    case 3:
      menampilkanDataPasien(dataPasien, jumlahPasien);
      break;

    case 4:
      return 0;

    default:
      printf("Pilihan anda tidak valid. Silakan coba lagi.\n");
      break;
    }
  }

  return 0;
}
