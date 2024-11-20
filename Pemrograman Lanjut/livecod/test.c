#include <stdio.h>
#include <string.h>

typedef struct matakuliah
{
    /* data */
    int kodeMatkul;
    char namaMatkul[50];
    int jam;
    int ruangKelas;
} mk;

int main()
{
    int n;
    mk matakuliah[3];

    matakuliah[0].kodeMatkul = 1;
    strcpy(matakuliah[0].namaMatkul, "Pemrograman Lanjut");
    matakuliah[0].jam = 7;
    matakuliah[0].ruangKelas = 301;

    matakuliah[1].kodeMatkul = 2;
    strcpy(matakuliah[1].namaMatkul, "Struktur Data");
    matakuliah[1].jam = 10;
    matakuliah[1].ruangKelas = 305;

    matakuliah[2].kodeMatkul = 3;
    strcpy(matakuliah[2].namaMatkul, "Basis Data");
    matakuliah[2].jam = 7;
    matakuliah[2].ruangKelas = 301;

    // Menampilkan seluruh data
    for (int i = 0; i < 3; i++)
    {
        /* code */
        printf("Data Matkul ke-%d\n", i + 1);
        printf("Kode Matkul: %d\n", matakuliah[i].kodeMatkul);
        printf("Nama Matkul: %s\n", matakuliah[i].namaMatkul);
        printf("Jam Matkul: %d\n", matakuliah[i].jam);
        printf("Ruang Kelas Matkul: %d\n", matakuliah[i].ruangKelas);
        printf("\n");
    }

    return 0;
}
