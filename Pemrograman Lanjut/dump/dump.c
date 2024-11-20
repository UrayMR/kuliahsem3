#include <stdio.h>
#include <string.h>

struct user
{
    char nama[50];
    int usia;
    float gaji;
} pegawai;

int main()
{
    strcpy(pegawai.nama, "Bambang Sutedjo");

    pegawai.usia = 2024 - 2005;
    pegawai.gaji = 2500;

    printf("Nama: %s\n", pegawai.nama);
    printf("Usia: %d\n", pegawai.usia);
    printf("Gaji: %.f\n", pegawai.gaji);

    return 0;
}