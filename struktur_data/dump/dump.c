#include <stdio.h>
#include <stdlib.h>

// Menginisiasi kumpulan variabel data dan Node dengan Struct
struct Node
{
    int data;          // Variabel data yang akan disimpan di tiap node
    struct Node *next; // Alamat untuk node berikutnya
};

// Fungsi untuk menyisipkan elemen di posisi tertentu
void menaruhData(struct Node **head, int new_data, int position)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = new_data;

    if (position == 1)
    {
        new_node->next = *head;
        *head = new_node;
        return;
    }

    struct Node *temp = *head;
    for (int i = 1; i < position - 1 && temp != NULL; i++)
    {
        temp = temp->next;
    }

    // Jika posisi lebih dari panjang linked list, masukkan di akhir
    if (temp == NULL)
    {
        printf("Posisi lebih besar dari panjang linked list, menyisipkan di akhir.\n");
        free(new_node);
        return;
    }

    new_node->next = temp->next;
    temp->next = new_node;
}

// Fungsi untuk menghapus elemen di posisi tertentu
void hapusData(struct Node **head, int position)
{
    if (*head == NULL)
    {
        printf("Linked list kosong, tidak ada yang bisa dihapus.\n");
        return;
    }

    struct Node *temp = *head;

    // Jika node yang akan dihapus adalah head
    if (position == 1)
    {
        *head = temp->next; // Pindahkan head ke node berikutnya
        free(temp);         // Hapus memori node lama
        return;
    }

    // Cari node yang ingin dihapus dan memutuskan hubungan antara node yang diinginkan dengan node - 1
    for (int i = 1; temp != NULL && i < position - 1; i++)
    {
        temp = temp->next;
    }

    // Jika posisi melebihi panjang linked list
    if (temp == NULL || temp->next == NULL)
    {
        printf("Posisi melebihi panjang linked list, tidak ada yang dihapus.\n");
        return;
    }

    // Node yang akan dihapus
    struct Node *deleted_node = temp->next;

    // Hubungkan node sebelumnya dengan node setelah node yang dihapus
    temp->next = deleted_node->next;

    // Bebaskan memori node yang dihapus
    free(deleted_node);
}

// Fungsi untuk mencetak elemen di dalam linked list
void printList(struct Node *node)
{
    while (node != NULL)
    {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

int main()
{
    // Deklarasi dan inisialisasi node-node yang sudah ada
    struct Node *head = NULL;
    struct Node *second = NULL;
    struct Node *third = NULL;

    // Alokasi memori untuk 3 node
    head = (struct Node *)malloc(sizeof(struct Node));
    second = (struct Node *)malloc(sizeof(struct Node));
    third = (struct Node *)malloc(sizeof(struct Node));

    // Isi data dan hubungkan node-node
    head->data = 10;
    head->next = second;

    second->data = 20;
    second->next = third;

    third->data = 30;
    third->next = NULL;

    // Cetak linked list sebelum penyisipan
    printf("Linked list sebelum penyisipan: ");
    printList(head);

    // Input elemen baru dan posisi dari user
    int new_data, position, delete_position;
    printf("Masukkan elemen baru: ");
    scanf("%d", &new_data);
    printf("Masukkan posisi untuk menyisipkan elemen: ");
    scanf("%d", &position);

    // Sisipkan elemen baru di posisi yang dipilih user
    menaruhData(&head, new_data, position);

    // Cetak linked list setelah penyisipan
    printf("Linked list setelah penyisipan: ");
    printList(head);

    // Input posisi dari user untuk menghapus node
    printf("Masukkan posisi untuk menghapus elemen: ");
    scanf("%d", &delete_position);

    // Hapus elemen di posisi yang dipilih user
    hapusData(&head, delete_position);

    // Cetak linked list setelah penghapusan
    printf("Linked list setelah penghapusan: ");
    printList(head);

    return 0;
}
