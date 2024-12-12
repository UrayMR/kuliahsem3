#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ================ STRUKTUR DATA ================

// Struktur Node untuk Linked List (Queue)
typedef struct Node
{
    int noPenumpang;        // Nomor identifikasi penumpang
    char namaPenumpang[50]; // Nama penumpang
    struct Node *next;      // Pointer ke node berikutnya
} Node;

// Struktur Antrian (Queue)
typedef struct
{
    Node *front; // Node terdepan antrian
    Node *rear;  // Node terbelakang antrian
} Queue;

// ================ FUNGSI QUEUE ================

// Inisialisasi Queue kosong
void initializeQueue(Queue *q)
{
    q->front = NULL;
    q->rear = NULL;
}

// Mengecek apakah Queue kosong
int isEmpty(Queue *q)
{
    return (q->front == NULL);
}

// Menambahkan penumpang ke dalam antrian
void enqueue(Queue *q, int noPenumpang, char *namaPenumpang)
{
    // Cek duplikasi nomor penumpang
    Node *temp = q->front;
    while (temp != NULL)
    {
        if (temp->noPenumpang == noPenumpang)
        {
            printf("Nomor penumpang %d sudah digunakan. Silakan gunakan nomor lain.\n", noPenumpang);
            return;
        }
        temp = temp->next;
    }

    // Membuat node baru
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("Memori penuh, tidak bisa menambah penumpang.\n");
        return;
    }

    // Mengisi data node baru
    newNode->noPenumpang = noPenumpang;
    strcpy(newNode->namaPenumpang, namaPenumpang);
    newNode->next = NULL;

    // Memasukkan node ke dalam antrian
    if (isEmpty(q))
    {
        q->front = newNode;
        q->rear = newNode;
    }
    else
    {
        q->rear->next = newNode;
        q->rear = newNode;
    }

    printf("Penumpang no-%d atas nama %s masuk ke antrian.\n", noPenumpang, namaPenumpang);
}

// Mengeluarkan penumpang dari antrian (untuk naik bus)
void dequeue(Queue *q, Queue *doneQ)
{
    if (isEmpty(q))
    {
        printf("Antrian kosong. Tidak ada penumpang untuk naik bus.\n");
        return;
    }

    Node *temp = q->front;
    printf("Penumpang no-%d atas nama %s naik bus.\n", temp->noPenumpang, temp->namaPenumpang);

    // Memindahkan data penumpang ke antrian selesai
    enqueue(doneQ, temp->noPenumpang, temp->namaPenumpang);

    // Update pointer front
    q->front = q->front->next;
    if (q->front == NULL)
    {
        q->rear = NULL;
    }

    free(temp);
}

// Mencari penumpang dalam Queue
void cariPenumpang(Queue *q, int noPenumpang)
{
    if (isEmpty(q))
    {
        printf("Antrian kosong. Tidak ada penumpang yang dapat dicari.\n");
        return;
    }

    Node *temp = q->front;
    while (temp != NULL)
    {
        if (temp->noPenumpang == noPenumpang)
        {
            printf("Penumpang ditemukan dalam Queue:\n");
            printf("Nomor: %d\n", temp->noPenumpang);
            printf("Nama: %s\n", temp->namaPenumpang);
            return;
        }
        temp = temp->next;
    }
    printf("Penumpang dengan nomor %d tidak ditemukan dalam Queue.\n", noPenumpang);
}

// Menampilkan antrian penumpang
void displayQueue(Queue *q)
{
    if (isEmpty(q))
    {
        printf("Antrian kosong.\n");
        return;
    }

    Node *temp = q->front;
    printf("Penumpang dalam antrian: \n");
    while (temp != NULL)
    {
        printf("Penumpang no-%d\n", temp->noPenumpang);
        printf("Nama Penumpang: %s\n", temp->namaPenumpang);
        temp = temp->next;
    }
    printf("\n");
}

// Menampilkan penumpang yang sudah naik bus
void displayPenumpangBus(Queue *doneQ)
{
    if (isEmpty(doneQ))
    {
        printf("Belum ada penumpang yang naik bus.\n");
        return;
    }

    Node *temp = doneQ->front;
    printf("Penumpang yang sudah naik bus: \n");
    while (temp != NULL)
    {
        printf("Penumpang no-%d\n", temp->noPenumpang);
        printf("Nama Penumpang: %s\n", temp->namaPenumpang);
        temp = temp->next;
    }
    printf("\n");
}

// ================ PROGRAM UTAMA ================

int main()
{
    Queue antrian, doneQ;
    initializeQueue(&antrian);
    initializeQueue(&doneQ);

    int pilihan;
    do
    {
        printf("\n==============================\n");
        printf("\nSistem Antrian Bus\n");
        printf("\n==============================\n");
        printf("1. Tambah Penumpang ke Antrian\n");
        printf("2. Penumpang Naik Bus\n");
        printf("3. Lihat Antrian Penumpang\n");
        printf("4. Lihat Penumpang yang Sudah Naik Bus\n");
        printf("5. Cari Penumpang dalam Queue\n");
        printf("0. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);
        getchar(); // Membersihkan buffer

        switch (pilihan)
        {
        case 1:
        {
            int noPenumpang;
            char namaPenumpang[50];

            printf("\nMasukkan nomor penumpang: ");
            scanf("%d", &noPenumpang);
            getchar(); // Membersihkan buffer

            printf("Masukkan nama penumpang: ");
            fgets(namaPenumpang, sizeof(namaPenumpang), stdin);
            namaPenumpang[strcspn(namaPenumpang, "\n")] = 0; // Menghapus newline dari fgets

            enqueue(&antrian, noPenumpang, namaPenumpang);
            break;
        }

        case 2:
        {
            dequeue(&antrian, &doneQ);
            break;
        }

        case 3:
        {
            displayQueue(&antrian);
            break;
        }

        case 4:
        {
            displayPenumpangBus(&doneQ);
            break;
        }

        case 5:
        {
            int noPenumpang;
            printf("\nMasukkan nomor penumpang: ");
            scanf("%d", &noPenumpang);
            cariPenumpang(&antrian, noPenumpang);
            break;
        }

        case 0:
            printf("Keluar dari program.\n");
            break;

        default:
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
            break;
        }

    } while (pilihan != 0);

    return 0;
}
