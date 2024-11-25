// 23081010029
// Uray Muhammad Rajsyafiq

#include <stdio.h>
#include <stdlib.h>

// Struktur kumpulan variabel node
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// Fungsi untuk insert node baru di posisi yang diinginkan
void insertAtPosition(struct Node** head_ref, int new_data, int position) {

    // Alokasi memori untuk node baru
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = NULL;
    new_node->prev = NULL;

    // Kondisi dimana position = 1 / menjadi head
    if (position == 1) {
        new_node->next = *head_ref;
        if (*head_ref != NULL) {
            (*head_ref)->prev = new_node;
        }
        *head_ref = new_node; // inisiasi node baru menjadi head
        return;
    }

    struct Node* temp = *head_ref;

    // Menyusuri list dengan loop untuk membuatkan tempat node baru 
    // dan menunjuk "next" ke lokasi yang diinginkan
    // Karena akan disisipkan sebelum &position
    for (int i = 1; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    // Kondisi untuk memeriksa apakan node yang ingin disisipkan berada di luar jangkauan
    if (temp == NULL) {
        printf("Position out of range\n");
        free(new_node);
        return;
    }

    // Memasukkan next dan prev new node kedalam list
    new_node->next = temp->next;
    new_node->prev = temp;

    if (temp->next != NULL) {
        temp->next->prev = new_node;
    }
    temp->next = new_node;
}

// Fungsi untuk print Double Linked List secara keseluruhan
void printList(struct Node* head) {
    printf("Forward Traversal:\n");
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

// 23081010029
// Uray Muhammad Rajsyafiq

int main() {
    // Inisialisasi Struct Node
    struct Node* head = NULL;
    struct Node* kedua = NULL;
    struct Node* ketiga = NULL;

    // Alokasi memori untuk setiap node
    head = (struct Node*)malloc(sizeof(struct Node));
    kedua = (struct Node*)malloc(sizeof(struct Node));
    ketiga = (struct Node*)malloc(sizeof(struct Node));

    // Inisialisasi setiap node dengan diisikan data dan disambungkan satu sama lain
    head->data = 20;    // First node
    head->next = kedua;
    head->prev = NULL;  // Head tidak memiliki "sebelum"

    kedua->data = 30;  // Second node
    kedua->next = ketiga;
    kedua->prev = head;

    ketiga->data = 40;   // Third node
    ketiga->next = NULL;
    ketiga->prev = kedua;

    // Print Double Linked List pada awalnya (original)
    printf("Original list:\n");
    printList(head);

    // Memasukkan data dan posisi untuk node baru
    int new_data, position;

    printf("Masukkan data baru: ");
    scanf("%d", &new_data);

    printf("Masukkan posisi data baru: ");
    scanf("%d", &position);

    // Memasukkan node(data) dengan posisi yang diinginkan
    insertAtPosition(&head, new_data, position);

    // Double Linked List setelah disisipkan data baru
    printf("List setelah disisipkan node(data) baru di index ke-%d:\n", position);
    printList(head);

    return 0;
}
