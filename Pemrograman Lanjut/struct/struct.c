#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char nama[50];
    int nilai[4];
    float mean;
} mhs;

void inputData(mhs *dataMhs, int jumlah)
{
    int total;
    float mean;

    for (int i = 0; i < jumlah; i++)
    {
        total = 0;
        printf("-----------------------------\n");
        printf("Tambah data mahasiswa ke-%d\n", i + 1);
        printf("-----------------------------\n");
        printf("Masukkan nama mahasiswa: ");
        scanf("%s", &dataMhs[i].nama);

        printf("Masukkan nilai kehadiran: ");
        scanf("%d", &dataMhs[i].nilai[0]);
        printf("Masukkan nilai Tugas: ");
        scanf("%d", &dataMhs[i].nilai[1]);
        printf("Masukkan nilai UTS: ");
        scanf("%d", &dataMhs[i].nilai[2]);
        printf("Masukkan nilai UAS: ");
        scanf("%d", &dataMhs[i].nilai[3]);

        for (int k = 0; k < 4; k++)
        {
            total += dataMhs[i].nilai[k];
        }
        mean = (float)total / 4;
        dataMhs[i].mean = mean;

        printf("\n");
    }
}

void tampilkanData(mhs *dataMhs, int jumlah)
{
    printf("-----------------------------\n");
    printf("Data Mahasiswa\n");
    printf("-----------------------------\n");
    for (int i = 0; i < jumlah; i++)
    {
        printf("Mahasiswa ke-%d\n", i + 1);
        printf("Nama Mahasiswa: %s\n", dataMhs[i].nama);
        printf("Nilai Kehadiran: %d\n", dataMhs[i].nilai[0]);
        printf("Nilai Tugas: %d\n", dataMhs[i].nilai[1]);
        printf("Nilai UTS: %d\n", dataMhs[i].nilai[2]);
        printf("Nilai UAS: %d\n", dataMhs[i].nilai[3]);
        printf("Nilai rata-rata: %.2f\n", dataMhs[i].mean);
        printf("\n");
    }
}

int main()
{
    int pilihan;
    int jumlah;
    mhs *dataMhs;

    while (1)
    {
        printf("-----------------------------\n");
        printf("Program input nilai mahasiswa\n");
        printf("-----------------------------\n");
        printf("1. Input Mahasiswa\n");
        printf("2. Data Mahasiswa\n");
        printf("3. Keluar\n");
        printf("-----------------------------\n");
        printf("Masukkan Pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan)
        {
        case 1:
            printf("Masukkan jumlah mahasiswa: ");
            scanf("%d", &jumlah);

            dataMhs = (mhs *)malloc(jumlah * sizeof(mhs));

            if (dataMhs == NULL)
            {
                printf("Memori tidak cukup!\n");
                return 1;
            }

            inputData(dataMhs, jumlah);
            break;
        case 2:
            tampilkanData(dataMhs, jumlah);
            break;
        case 3:
            free(dataMhs);
            return 0;
        default:
            printf("Pilihan tidak valid. \n");
            break;
        }
    }

    return 0;
}
