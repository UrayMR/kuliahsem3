#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Uray Muhammad Rajsyafiq
// 23081010029

void handlePercobaan()
{
    int percobaan;
    system("cls");
    printf("Anda memilih opsi Percobaan.\n");
    printf("1. Percobaan ke-1 (Fungsi rekursif untuk menghitung nilai faktorial)\n");
    printf("2. Percobaan ke-2 (Fungsi menghitung nilai faktorial dengan rekursi tail)\n");
    printf("3. Percobaan ke-3 (Fungsi rekursi untuk menampilkan deret Fibonacci)\n");
    printf("4. Percobaan ke-4 (Fungsi rekursi untuk menentukan bilangan prima atau bukan prima)\n");
    printf("5. Percobaan ke-5 (Fungsi rekursi untuk menghitung pangkat)\n");
    scanf("%d", &percobaan);

    switch (percobaan)
    {
    case 1:
        percobaan1();
        break;
    case 2:
        percobaan2();
        break;
    case 3:
        percobaan3();
        break;
    case 4:
        percobaan4();
        break;
    case 5:
        percobaan5();
        break;
    default:
        printf("Pilihan tidak valid.\n");
        break;
    }
}

// Fungsi rekursif untuk menghitung faktorial secara normal
int faktorial1(int x)
{
    if (x == 1)
        return x;
    else
        return x * faktorial1(x - 1);
    // jika x = 3, maka
    // faktorial1(3) = 3 * faktorial1(2)
    // faktorial1(2) = 2 * faktorial1(1)
    // faktorial1(1) = 1
    // Sehingga, faktorial1(3) = 3 * 2 * 1 = 6
}

void percobaan1()
{
    int N;
    printf("Masukkan N = ");
    scanf("%d", &N);
    printf("Hasil %d! = %d\n", N, faktorial1(N));
}

// Fungsi rekursif untuk menghitung faktorial dengan teknik tail recursion
int faktorial2(int x, int a)
{
    if (x == 1)
        return a;
    else
        return faktorial2(x - 1, x * a);
    // misal x = 2, maka
    //(2-1, 2*1) = 1, 2 (karena x == 1, maka return a)

    // misal x = 3, maka
    //(3-1, 3*1) = 2, 3
    //(2-1, 2*3) = 1, 6 (karena x == 1, maka return a))
    // = 6
}

void percobaan2()
{
    int N;
    printf("Masukkan N = ");
    scanf("%d", &N);
    printf("Hasil %d! = %d\n", N, faktorial2(N, 1));
}

// Fungsi rekursif untuk menampilkan deret Fibonacci
int fibo(int x)
{
    if (x <= 0 || x <= 1)
        return x;
    // Jika x = 0 atau x = 1, maka tetap saja ditulis 0 , 1 , 1
    else
        return fibo(x - 2) + fibo(x - 1);
    // Jika tidak, misal index/x = 3
    // Maka, (x-2) +  (x-1) = 3-2 + 3-1 = 1+2 = 3
    // 0, 1, 1, 3, dst
}

void percobaan3()
{
    int n;
    printf("Masukkan jumlah deret = ");
    scanf("%d", &n);
    printf("Deret Fibonacci dari %d = ", n);

    for (int i = 0; i < n; i++)
        // loop hingga jumlah deret
        printf("%d ", fibo(i));
    printf("\n");
}

// Fungsi rekursi untuk menentukan bilangan prima atau bukan prima

int prime(int number, int index)
{
    if (index == 1)
        return 1;
    else if (number % index == 0)
        return 0;
    else
        return prime(number, --index);
    // Mengurutkan hingga sebanyak index yang diingin. jadi misal dari 10, 10-1,10-2,10-3 dst
}

void percobaan4()
{
    int num;
    printf("Masukkan bilangan sampai dengan : ");
    scanf("%d", &num);
    printf("Deret bilangan prima : ");

    for (int i = 1; i <= num; i++)
        if (prime(i, (int)sqrt(i)))
            // Contoh : prima (4, sqrt(4)= 2) berarti bukan prima
            printf("%d ", i);
}

// Fungsi rekursi untuk menghitung pangkat
int pangkat(int x, int y)
{
    if (y == 0)
        return 1;
    else
        return x * pangkat(x, y - 1);
    // 2 * pangkat(2, 3-1) = pangkat(2, 3) = 2^3 = 2 * 2^2 = 8
    // 2 * pangkat(2, 2-1) = pangkat(2, 2) = 2^2 = 2 * 2^1 = 4
    // 2 * pangkat(2, 1-1) = pangkat(2, 1) = 2^1 = 2 * 2^0 = 2
    // 2 * pangkat(2, 0)   = pangkat(2, 0) = 2^0 = return 1
}

void percobaan5()
{
    int x, y;
    printf("Bilangan x:  ");
    scanf("%d", &x);
    printf("Pangkat y:  ");
    scanf("%d", &y);

    printf("%d pangkat %d = %d\n", x, y, pangkat(x, y));
}

void handleLatihan()
{
    int latihan;
    system("cls");
    printf("Anda memilih opsi Latihan Soal.\n");
    printf("1. Buatlah program rekursif untuk menghitung segitiga Pascal!\n");
    printf("2. Masukkan jumlah N karakter dan cetak dalam semua kombinasi!\n");
    scanf("%d", &latihan);

    switch (latihan)
    {
    case 1:
        latihan1();
        break;
    case 2:
        // latihan2();
        break;
    default:
        printf("Pilihan tidak valid.\n");
        break;
    }
}

// Membuat segitiga pascal
int kombinasi(n, r)
{
    if (r == 0 || r == n)
        return 1;
    else
        return kombinasi(n - 1, r - 1) + kombinasi(n - 1, r);
}

void latihan1()
{
    int n;
    printf("Masukkan jumlah baris segitiga Pascal: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i; j++)
        {
            printf("");

            for (int k = 0; k <= i; k++)
            {
                printf("%d ", kombinasi(i, k));
            }
        }
    }
}

int main()
{
    int opsi;
    printf("Opsi manakah yang ingin anda lakukan : \n");
    printf("1. Percobaan \n");
    printf("2. Latihan Soal \n");
    scanf("%d", &opsi);

    if (opsi == 1)
    {
        handlePercobaan();
    }
    else if (opsi == 2)
    {
        handleLatihan();
    }
    else
    {
        printf("Pilihan tidak valid.\n");
    }

    return 0;
}
