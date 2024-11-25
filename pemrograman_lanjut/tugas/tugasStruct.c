// 23081010029
// Uray Muhammad Rajsyafiq
// Tugas Pemrograman Lanjut Struct of Array

// Membuat sistem input data+nilai mahasiswa dengan dynamic memory

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct mahasiswa
{
    char nama[50];
    int nilai[4];
    float mean;
} mhs;

void inputData(mhs *dataMhs, int jumlahMhs)
{
    printf("----------------------------------\n");
    printf("Input %d data mahasiswa\n", jumlahMhs);
    printf("----------------------------------\n");
    for (int i = 0; i < jumlahMhs; i++)
    {
        float mean;
        int total = 0;

        printf("Data mahasiswa ke-%d\n", i + 1);
        printf("Masukkan nama mahasiswa: ");
        fgets(dataMhs[i].nama, sizeof(dataMhs[i].nama), stdin);
        dataMhs[i].nama[strcspn(dataMhs[i].nama, "\n")] = '\0';

        printf("Masukkan nilai kehadiran: ");
        scanf("%d", &dataMhs[i].nilai[0]);
        printf("Masukkan nilai tugas: ");
        scanf("%d", &dataMhs[i].nilai[1]);
        printf("Masukkan nilai UTS: ");
        scanf("%d", &dataMhs[i].nilai[2]);
        printf("Masukkan nilai UAS: ");
        scanf("%d", &dataMhs[i].nilai[3]);
        printf("----------------------------------\n");

        for (int j = 0; j < 4; j++)
        {
            total += dataMhs[i].nilai[j];
        }

        mean = (float)total / 4;
        dataMhs[i].mean = mean;

        getchar();
    }
    system("pause");
    system("cls");
}

void tampilkanData(mhs *dataMhs, int jumlahMhs)
{
    printf("----------------------------------\n");
    printf("Menampilkan seluruh data mahasiswa\n");
    printf("----------------------------------\n");
    for (int i = 0; i < jumlahMhs; i++)
    {
        printf("Data mahasiswa ke-%d\n", i + 1);
        printf("Nama mahasiswa: %s\n", dataMhs[i].nama);
        printf("Nilai kehadiran: %d\n", dataMhs[i].nilai[0]);
        printf("Nilai tugas: %d\n", dataMhs[i].nilai[1]);
        printf("Nilai UTS: %d\n", dataMhs[i].nilai[2]);
        printf("Nilai UAS: %d\n", dataMhs[i].nilai[3]);
        printf("Rata-rata nilai: %.2f\n", dataMhs[i].mean);
        printf("----------------------------------\n");
    }
    system("pause");
    system("cls");
}

int main()
{
    int pilihan, jumlahMhs = 0;

    mhs *dataMhs = NULL;

    while (1)
    {
        system("cls");
        printf("------------------------------------\n");
        printf("Program input data & nilai Mahasiswa\n");
        printf("------------------------------------\n");
        printf("1. Input data Mahasiswa\n");
        printf("2. Melihat seluruh data Mahasiswa\n");
        printf("3. Keluar\n");
        printf("------------------------------------\n");
        printf("Masukkan pilihan anda: ");
        scanf("%d", &pilihan);

        switch (pilihan)
        {
        case 1:
            printf("Masukkan jumlah mahasiswa: ");
            scanf("%d", &jumlahMhs);
            getchar();

            dataMhs = (mhs *)malloc(jumlahMhs * sizeof(mhs));
            if (dataMhs == NULL)
            {
                printf("Gagal alokasi memori.\n");
                return 1;
            }
            system("cls");
            inputData(dataMhs, jumlahMhs);
            break;

        case 2:
            if (jumlahMhs > 0)
            {
                system("cls");
                tampilkanData(dataMhs, jumlahMhs);
            }
            else
            {
                printf("Tidak ada data mahasiswa.\n");
                system("pause");
            }

            break;
        case 3:
            free(dataMhs);
            return 0;

        default:
            printf("Pilihan anda tidak valid.\n");
            system("pause");
            break;
        }
    }

    return 0;
}