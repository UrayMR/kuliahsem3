// 23081010029
// Uray Muhammad Rajsyafiq

#include <stdio.h>
#include <string.h>

// Definisi struct jurnal
typedef struct journal
{
    char judul[100];
    char namaPenulis[100];
    char afiliasi[100];
    char email[100];
    char abstrak[500];
    char kataKunci[100];
} jurnal;

// Fungsi untuk menghitung jumlah kata dalam string
int hitungKata(const char *str)
{
    int count = 0;
    char prevChar = ' ';

    // perulangan jika masih ada character yang tersisa dalam array of char(string)
    while (*str)
    {
        if (*str != ' ' && prevChar == ' ') // mengecek apakah character tidak sama dengan ' ' dan karakter sebelumnya adalah ' ' atau spasi, maka akan dihitung sebagai 1 kata
        {
            count++;
        }
        prevChar = *str; // menyimpan karakter sekarang menjadi karakter sebelumnya dan di ulang hingga sesuai kondisi if
        str++;           // mengecek ke karakter selanjutnya hingga false atau mencapai delimiter
    }
    return count;
}

// Fungsi untuk validasi email
int validasiEmail(const char *email)
{
    const char *domain = ".ac.id";

    // untuk mencari apakah ada ".ac.id" di email yang di input(parameter)
    const char *search = strstr(email, domain);

    // search[strlen(domain)] == '\0' atau '\n'
    // mengidentifikasi char *search di index ke strlen(domain)
    if (search != NULL && strcmp(search, domain) == 0 && (search[strlen(domain)] == '\0' || search[strlen(domain)] == '\n'))
    {
        return 1; // Email valid
    }
    return 0; // Email tidak valid
}

// Fungsi untuk validasi kata kunci
int validasiKataKunci(const char *kataKunci)
{
    int count = 1; // Minimal 1 kata kunci
    for (int i = 0; i < strlen(kataKunci); i++)
    {
        if (kataKunci[i] == ',')
        {
            count++; // menghitung seberapa banyak kata kunci, dengan mengidentifikasi berapa banyak ',' di string input
        }
    }
    return count >= 3 && count <= 5; // Valid jika antara 3-5 kata
}

int main()
{
    int jurnalCount;

    printf("Berapa banyak jurnal yang ingin di input?");
    scanf("%d", &jurnalCount);
    getchar();

    jurnal jurnals[jurnalCount];
    char output[1000]; // Buffer untuk output akhir

    // Input judul
    for (int j = 0; j < jurnalCount; j++)
    {
        /* code */
        system("cls");
        printf("\n ------ Input Jurnal ke-%d ------ \n", j + 1);

        do
        {
            printf("Masukkan judul jurnal (5-14 kata):\n");
            fgets(jurnals[j].judul, sizeof(jurnals[j].judul), stdin);

            // menghapus delimiter dengan mencari delimiter di jurnals[j].judul dengan strcspn
            jurnals[j].judul[strcspn(jurnals[j].judul, "\n")] = 0;

            if (hitungKata(jurnals[j].judul) < 5 || hitungKata(jurnals[j].judul) > 14)
            {
                printf("Judul harus terdiri dari 5-14 kata!\n");
            }
        } while (hitungKata(jurnals[j].judul) < 5 || hitungKata(jurnals[j].judul) > 14);

        // Input nama penulis
        do
        {
            printf("Masukkan nama penulis (maksimal 3 penulis, dipisahkan koma):\n");
            fgets(jurnals[j].namaPenulis, sizeof(jurnals[j].namaPenulis), stdin);

            jurnals[j].namaPenulis[strcspn(jurnals[j].namaPenulis, "\n")] = 0;

            int penulisCount = 1; // Minimal 1 penulis
            for (int i = 0; i < strlen(jurnals[j].namaPenulis); i++)
            {
                if (jurnals[j].namaPenulis[i] == ',')
                {
                    penulisCount++;
                }
            }

            if (penulisCount > 3)
            {
                printf("Maksimal 3 penulis diperbolehkan!\n");
            }
        } while (hitungKata(jurnals[j].namaPenulis) < 1 || hitungKata(jurnals[j].namaPenulis) > 3);

        // Input afiliasi
        printf("Masukkan afiliasi penulis:\n");
        fgets(jurnals[j].afiliasi, sizeof(jurnals[j].afiliasi), stdin);
        jurnals[j].afiliasi[strcspn(jurnals[j].afiliasi, "\n")] = 0;

        // Input email
        do
        {
            printf("Masukkan email penulis (harus berdomain .ac.id):\n");
            fgets(jurnals[j].email, sizeof(jurnals[j].email), stdin);
            jurnals[j].email[strcspn(jurnals[j].email, "\n")] = 0;

            if (!validasiEmail(jurnals[j].email))
            {
                printf("Email harus berdomain .ac.id!\n");
            }
        } while (!validasiEmail(jurnals[j].email));

        // 23081010029
        // Uray Muhammad Rajsyafiq

        // Input abstrak
        do
        {
            printf("Masukkan abstrak (maksimal 200 kata):\n");
            fgets(jurnals[j].abstrak, sizeof(jurnals[j].abstrak), stdin);
            jurnals[j].abstrak[strcspn(jurnals[j].abstrak, "\n")] = 0;

            if (hitungKata(jurnals[j].abstrak) > 200)
            {
                printf("Abstrak tidak boleh lebih dari 200 kata!\n");
            }
        } while (hitungKata(jurnals[j].abstrak) > 200);

        // Input kata kunci
        do
        {
            printf("Masukkan kata kunci (3-5 kata, dipisahkan koma):\n");
            fgets(jurnals[j].kataKunci, sizeof(jurnals[j].kataKunci), stdin);
            jurnals[j].kataKunci[strcspn(jurnals[j].kataKunci, "\n")] = 0;

            if (!validasiKataKunci(jurnals[j].kataKunci))
            {
                printf("Kata kunci harus terdiri dari 3-5 kata!\n");
            }
        } while (!validasiKataKunci(jurnals[j].kataKunci));
    }

    // Menggabungkan semua bagian menjadi satu string
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
