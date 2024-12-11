#include <stdio.h>
#include <string.h>

#define MAX_MAHASISWA 100

typedef struct data
{
    long long int npm;
    char nama[100];
    char prodi[100];
    float ipk;
} dataMhs;

void tampilkanData(dataMhs Mhs[], int jumlahMhs)
{
    printf("---------------------------------------\n");
    printf("Data Mahasiswa\n");
    printf("---------------------------------------\n");
    for (int i = 0; i < jumlahMhs; i++)
    {
        printf("NPM: %lld\n", Mhs[i].npm);
        printf("Nama: %s\n", Mhs[i].nama);
        printf("Program Studi: %s\n", Mhs[i].prodi);
        printf("IPK: %.2f\n", Mhs[i].ipk);
        printf("---------------------------------------\n");
    }
}

void bubbleSort(dataMhs Mhs[], int jumlahMhs, int pilihan, int pilihanAsc)
{
    dataMhs temp;
    for (int i = 0; i < jumlahMhs - 1; i++)
    {
        for (int j = 0; j < jumlahMhs - i - 1; j++)
        {
            int compare = 0;
            switch (pilihan)
            {
            case 1:
                compare = (Mhs[j].npm > Mhs[j + 1].npm) - (Mhs[j].npm < Mhs[j + 1].npm);
                break;
            case 2:
                compare = strcmp(Mhs[j].nama, Mhs[j + 1].nama);
                break;
            case 3:
                compare = strcmp(Mhs[j].prodi, Mhs[j + 1].prodi);
                break;
            case 4:
                compare = (Mhs[j].ipk > Mhs[j + 1].ipk) - (Mhs[j].ipk < Mhs[j + 1].ipk);
                break;
            }
            if ((pilihanAsc == 1 && compare > 0) || (pilihanAsc == 0 && compare < 0))
            {
                temp = Mhs[j];
                Mhs[j] = Mhs[j + 1];
                Mhs[j + 1] = temp;
            }
        }
    }
}

void insertionSort(dataMhs Mhs[], int jumlahMhs, int pilihan, int pilihanAsc)
{
    for (int i = 1; i < jumlahMhs; i++)
    {
        dataMhs key = Mhs[i];
        int j = i - 1;
        int compare;
        while (j >= 0)
        {
            switch (pilihan)
            {
            case 1:
                compare = (Mhs[j].npm > key.npm) - (Mhs[j].npm < key.npm);
                break;
            case 2:
                compare = strcmp(Mhs[j].nama, key.nama);
                break;
            case 3:
                compare = strcmp(Mhs[j].prodi, key.prodi);
                break;
            case 4:
                compare = (Mhs[j].ipk > key.ipk) - (Mhs[j].ipk < key.ipk);
                break;
            }

            if ((pilihanAsc == 1 && compare > 0) || (pilihanAsc == 0 && compare < 0))
            {
                Mhs[j + 1] = Mhs[j];
                j--;
            }
            else
            {
                break;
            }
        }
        Mhs[j + 1] = key;
    }
}

void selectionSort(dataMhs Mhs[], int jumlahMhs, int pilihan, int pilihanAsc)
{
    for (int i = 0; i < jumlahMhs - 1; i++)
    {
        int idx = i;
        for (int j = i + 1; j < jumlahMhs; j++)
        {
            int compare;
            switch (pilihan)
            {
            case 1:
                compare = (Mhs[j].npm > Mhs[idx].npm) - (Mhs[j].npm < Mhs[idx].npm);
                break;
            case 2:
                compare = strcmp(Mhs[j].nama, Mhs[idx].nama);
                break;
            case 3:
                compare = strcmp(Mhs[j].prodi, Mhs[idx].prodi);
                break;
            case 4:
                compare = (Mhs[j].ipk > Mhs[idx].ipk) - (Mhs[j].ipk < Mhs[idx].ipk);
                break;
            }
            if ((pilihanAsc == 1 && compare < 0) || (pilihanAsc == 0 && compare > 0))
            {
                idx = j;
            }
        }
        dataMhs temp = Mhs[idx];
        Mhs[idx] = Mhs[i];
        Mhs[i] = temp;
    }
}

void sortData(dataMhs Mhs[], int jumlahMhs, int pilihan, int pilihanAsc, int metode)
{
    switch (metode)
    {
    case 1:
        bubbleSort(Mhs, jumlahMhs, pilihan, pilihanAsc);
        break;
    case 2:
        insertionSort(Mhs, jumlahMhs, pilihan, pilihanAsc);
        break;
    case 3:
        selectionSort(Mhs, jumlahMhs, pilihan, pilihanAsc);
        break;
    default:
        printf("Metode tidak valid!\n");
        break;
    }
}

void salinData(dataMhs sumber[], dataMhs tujuan[], int jumlahMhs)
{
    for (int i = 0; i < jumlahMhs; i++)
    {
        tujuan[i] = sumber[i];
    }
}

int sequentialSearch(dataMhs Mhs[], int jumlahMhs, int pilihan, void *key)
{
    for (int i = 0; i < jumlahMhs; i++)
    {
        /* code */
        int compare = 0;
        switch (pilihan)
        {
        case 1:
            compare = (*(long long int *)key == Mhs[i].npm);
            break;
        case 2:
            compare = strcmp((char *)key, Mhs[i].nama) == 0;
            break;
        case 3:
            compare = strcmp((char *)key, Mhs[i].prodi) == 0;
            break;
        case 4:
            compare = (*(float *)key == Mhs[i].ipk);
            break;
        default:
            break;
        }
        if (compare)
        {
            /* code */
            return i;
        }
    }
    return -1;
}

int binarySearch(dataMhs Mhs[], int jumlahMhs, int pilihan, void *key)
{
    int low = 0, high = jumlahMhs - 1, mid, compare;

    while (low < high)
    {
        mid = low + (high - low) / 2;

        switch (pilihan)
        {
        case 1:
            compare = (*(long long int *)key > Mhs[mid].npm) - (*(long long int *)key < Mhs[mid].npm);
            break;
        case 2:
            compare = strcmp((char *)key, Mhs[mid].nama);
            break;
        case 3:
            compare = strcmp((char *)key, Mhs[mid].prodi);
            break;
        case 4:
            compare = (*(float *)key > Mhs[mid].ipk) - (*(float *)key < Mhs[mid].ipk);
            break;
        default:
            break;
        }
        if (compare == 0)
        {
            /* code */
            return mid;
        }
        else if (compare < 0)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return -1;
}

int jumpSearch(dataMhs Mhs[], int jumlahMhs, int pilihan, void *key)
{
    int step = sqrt(jumlahMhs);
    int prev = 0;
    int compare;

    while (prev < jumlahMhs)
    {
        switch (pilihan)
        {
        case 1:
            compare = (*(long long int *)key > Mhs[prev].npm) - (*(long long int *)key < Mhs[prev].npm);
            break;
        case 2:
            compare = strcmp((char *)key, Mhs[prev].nama);
            break;
        case 3:
            compare = strcmp((char *)key, Mhs[prev].prodi);
            break;
        case 4:
            compare = (*(float *)key > Mhs[prev].ipk) - (*(float *)key < Mhs[prev].ipk);
            break;
        default:
            return -1;
        }

        if (compare <= 0)
            break;

        prev = prev + step;
        if (prev >= jumlahMhs)
            return -1;
    }

    while (prev >= 0)
    {
        switch (pilihan)
        {
        case 1:
            compare = (*(long long int *)key == Mhs[prev].npm);
            break;
        case 2:
            compare = strcmp((char *)key, Mhs[prev].nama) == 0;
            break;
        case 3:
            compare = strcmp((char *)key, Mhs[prev].prodi) == 0;
            break;
        case 4:
            compare = (*(float *)key == Mhs[prev].ipk);
            break;
        default:
            return -1;
        }

        if (compare)
            return prev;

        prev--;
    }

    return -1;
}

int main()
{
    dataMhs Mhs[MAX_MAHASISWA];
    int jumlahMhs = 0;
    int pilihan;

    while (1)
    {
        printf("---------------------------------------\n");
        printf("Manajemen Data Mahasiswa\n");
        printf("---------------------------------------\n");
        printf("1. Input Data Mahasiswa\n");
        printf("2. Tampilkan Sorting Data Mahasiswa\n");
        printf("3. Tampilkan Seluruh Data Mahasiswa\n");
        printf("4. Search Data Mahasiswa\n");
        printf("5. Keluar\n");
        printf("---------------------------------------\n");
        printf("Pilihan anda: ");
        scanf("%d", &pilihan);

        switch (pilihan)
        {
        case 1:
            if (jumlahMhs >= MAX_MAHASISWA)
            {
                printf("Maaf, jumlah data mahasiswa sudah mencapai batas maksimum.\n");
                break;
            }

            printf("---------------------------------------\n");
            printf("Input data Mahasiswa\n");
            printf("---------------------------------------\n");

            printf("NPM: ");
            scanf("%lld", &Mhs[jumlahMhs].npm);

            int found = 0;
            for (int i = 0; i < jumlahMhs; i++)
            {
                if (Mhs[i].npm == Mhs[jumlahMhs].npm)
                {
                    found = 1;
                    printf("Maaf, NPM %lld sudah terdaftar.\n", Mhs[jumlahMhs].npm);
                    break;
                }
            }

            if (!found)
            {
                printf("Nama: ");
                scanf(" %[^\n]s", Mhs[jumlahMhs].nama);
                printf("Program Studi: ");
                scanf(" %[^\n]s", Mhs[jumlahMhs].prodi);
                printf("IPK: ");
                scanf("%f", &Mhs[jumlahMhs].ipk);
                jumlahMhs++;
            }
            break;

        case 2:
        {
            if (jumlahMhs == 0)
            {
                printf("Data mahasiswa kosong!\n");
                break;
            }

            dataMhs salinanMhs[MAX_MAHASISWA];
            salinData(Mhs, salinanMhs, jumlahMhs);

            int pilihanSort, pilihanAsc, metodeSort;

            printf("1. NPM\n2. Nama\n3. Jurusan\n4. IPK\nPilih kategori untuk sorting: ");
            scanf("%d", &pilihanSort);

            printf("1. Ascending\n2. Descending\nPilih Urutan: ");
            scanf("%d", &pilihanAsc);

            printf("1. Bubble Sort\n2. Insertion Sort\n3. Selection Sort\nPilih metode sorting: ");
            scanf("%d", &metodeSort);

            sortData(salinanMhs, jumlahMhs, pilihanSort, pilihanAsc, metodeSort);
            tampilkanData(salinanMhs, jumlahMhs);
            break;
        }
        case 3:
            tampilkanData(Mhs, jumlahMhs);
            break;
        case 4:
            if (jumlahMhs == 0)
            {
                /* code */
                printf("Data Mahasiswa Kosong!");
                break;
            }

            int pilihanSearch, metodeSearch;
            printf("1. NPM\n2. Nama\n3. Jurusan\n4. IPK\nPilih Kategori untuk pencarian:");
            scanf("%d", &pilihanSearch);

            printf("1. Sequential\n2. Binary\n3. Jump Search\nPilih Metode untuk pencarian:");
            scanf("%d", &metodeSearch);

            dataMhs salinanMhs[MAX_MAHASISWA];
            salinData(Mhs, salinanMhs, jumlahMhs);

            int foundIndex = -1;
            if (metodeSearch == 2 || metodeSearch == 3)
            {
                sortData(salinanMhs, jumlahMhs, pilihanSearch, 1, 1);
            }

            switch (pilihanSearch)
            {
            case 1:
                printf("Masukkan NPM: ");
                long long int npmKey;
                scanf("%lld", &npmKey);
                if (metodeSearch == 1)
                    foundIndex = sequentialSearch(salinanMhs, jumlahMhs, pilihanSearch, &npmKey);
                else if (metodeSearch == 2)
                    foundIndex = binarySearch(salinanMhs, jumlahMhs, pilihanSearch, &npmKey);
                else
                    foundIndex = jumpSearch(salinanMhs, jumlahMhs, pilihanSearch, &npmKey);
                break;
            case 2:
                printf("Masukkan Nama: ");
                char namaKey[100];
                scanf(" %[^\n]s", namaKey);
                if (metodeSearch == 1)
                    foundIndex = sequentialSearch(salinanMhs, jumlahMhs, pilihanSearch, namaKey);
                else if (metodeSearch == 2)
                    foundIndex = binarySearch(salinanMhs, jumlahMhs, pilihanSearch, namaKey);
                else
                    foundIndex = jumpSearch(salinanMhs, jumlahMhs, pilihanSearch, namaKey);
                break;
            case 3:
                printf("Masukkan Jurusan: ");
                char jurusanKey[100];
                scanf(" %[^\n]s", jurusanKey);
                if (metodeSearch == 1)
                    foundIndex = sequentialSearch(salinanMhs, jumlahMhs, pilihanSearch, jurusanKey);
                else if (metodeSearch == 2)
                    foundIndex = binarySearch(salinanMhs, jumlahMhs, pilihanSearch, jurusanKey);
                else
                    foundIndex = jumpSearch(salinanMhs, jumlahMhs, pilihanSearch, jurusanKey);
                break;
            case 4:
                printf("Masukkan IPK: ");
                float ipkKey;
                scanf("%f", &ipkKey);
                if (metodeSearch == 1)
                    foundIndex = sequentialSearch(salinanMhs, jumlahMhs, pilihanSearch, &ipkKey);
                else if (metodeSearch == 2)
                    foundIndex = binarySearch(salinanMhs, jumlahMhs, pilihanSearch, &ipkKey);
                else
                    foundIndex = jumpSearch(salinanMhs, jumlahMhs, pilihanSearch, &ipkKey);
                break;
            default:
                break;
            }

            if (foundIndex != -1)
            {
                printf("Data Ditemukan: \n");
                tampilkanData(&salinanMhs[foundIndex], 1);
            }
            else
            {
                printf("Data tidak ditemukan\n");
            }
            break;
        case 5:
            return 0;
        }
    }
    return 0;
}
