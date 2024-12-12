#include <stdio.h>
#include <stdlib.h>

// Menginisiasi kumpulan variabel data dan Node dengan Struct
struct Node
{
    int data;          // Variabel data yang akan disimpan di tiap node
    struct Node *next; // Alamat untuk node berikutnya
    struct Node *prev; // Alamat untuk node sebelumnya
};

// Fungsi untuk mencetak elemen di dalam double linked list
void printList(struct Node *node)
{
    while (node != NULL)
    {
        printf("%d <-> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

// Fungsi untuk menghapus elemen di posisi tertentu
void deleteNode(struct Node **head, int position)
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
        *head = temp->next;
        if (*head != NULL)
        {
            (*head)->prev = NULL;
        }
        free(temp);
        return;
    }

    // Cari node yang ingin dihapus
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

    struct Node *deleted_node = temp->next;

    // Hubungkan node sebelumnya dengan node setelah node yang dihapus
    temp->next = deleted_node->next;
    if (deleted_node->next != NULL)
    {
        deleted_node->next->prev = temp;
    }

    free(deleted_node);
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
    head->prev = NULL;

    second->data = 20;
    second->next = third;
    second->prev = head;

    third->data = 30;
    third->next = NULL;
    third->prev = second;

    // Cetak linked list sebelum di sisipkan
    printf("Linked list sebelum di sisipkan: ");
    printList(head);

    // Input posisi dari user untuk menghapus node
    int delete_position;
    printf("Masukkan posisi untuk menghapus elemen: ");
    scanf("%d", &delete_position);

    // Hapus elemen di posisi yang dipilih user
    deleteNode(&head, delete_position);

    // Cetak linked list setelah penghapusan
    printf("Linked list setelah penghapusan: ");
    printList(head);

    return 0;
}
