#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definisi node untuk linked list yang menyimpan data penumpang dan data penumpang selanjutnya
typedef struct Node
{
    int noPenumpang;        // Data penumpang
    char namaPenumpang[50]; // Nama penumpang
    struct Node *next;      // Pointer ke node berikutnya
} Node;

// Definisi Antrian/Queue
typedef struct
{
    Node *front; // Node paling depan
    Node *rear;  // Node paling belakang
} Queue;

// Definisi Node untuk Binary Search Tree
typedef struct BSTNode
{
    int noPenumpang;
    char namaPenumpang[50];
    struct BSTNode *left, *right;
} BSTNode;

// Definisi Node untuk AVL Tree
typedef struct AVLNode
{
    int noPenumpang;
    char namaPenumpang[50];
    int height;
    struct AVLNode *left, *right;
} AVLNode;

// Inisialisasi Queue
void initializeQueue(Queue *q)
{
    q->front = NULL; // Antrian kosong, front = NULL
    q->rear = NULL;  // Antrian kosong, rear = NULL
}

// Mengecek apakah antrian kosong
int isEmpty(Queue *q)
{
    return (q->front == NULL);
}

// Menambahkan data penumpang ke Queue
void enqueue(Queue *q, int noPenumpang, char *namaPenumpang, int pilihan)
{
    Node *temp = q->front; // Cek duplikasi
    while (temp != NULL)
    {
        if (temp->noPenumpang == noPenumpang)
        {
            printf("Nomor penumpang %d sudah digunakan. Silakan gunakan nomor lain.\n", noPenumpang);
            return;
        }
        temp = temp->next;
    }

    Node *newNode = (Node *)malloc(sizeof(Node)); // Alokasi memori
    if (newNode == NULL)
    {
        printf("Memori penuh, tidak bisa menambah penumpang.\n");
        return;
    }

    newNode->noPenumpang = noPenumpang;
    strcpy(newNode->namaPenumpang, namaPenumpang);
    newNode->next = NULL;

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

    if (pilihan != 2)
    {
        printf("Penumpang no-%d atas nama %s masuk ke antrian.\n", noPenumpang, namaPenumpang);
    }
}

// Menghapus penumpang dari Queue
void dequeue(Queue *q, Queue *doneQ, int pilihan)
{
    if (isEmpty(q))
    {
        printf("Antrian kosong. Tidak ada penumpang untuk naik bus.\n");
        return;
    }

    Node *temp = q->front;
    printf("Penumpang no-%d atas nama %s naik bus.\n", temp->noPenumpang, temp->namaPenumpang);
    enqueue(doneQ, temp->noPenumpang, temp->namaPenumpang, pilihan);
    q->front = q->front->next;

    if (q->front == NULL)
    {
        q->rear = NULL;
    }

    free(temp);
}

// Menampilkan antrian
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

// Fungsi untuk mencari penumpang dalam Queue
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
            printf("Penumpang ditemukan:\n");
            printf("Nomor: %d\n", temp->noPenumpang);
            printf("Nama: %s\n", temp->namaPenumpang);
            return;
        }
        temp = temp->next;
    }
    printf("Penumpang dengan nomor %d tidak ditemukan.\n", noPenumpang);
}

// Fungsi untuk mencari penumpang dalam BST
void cariPenumpangBST(BSTNode *root, int noPenumpang)
{
    if (root == NULL)
    {
        printf("Penumpang tidak ditemukan dalam BST.\n");
        return;
    }

    if (noPenumpang < root->noPenumpang)
        cariPenumpangBST(root->left, noPenumpang);
    else if (noPenumpang > root->noPenumpang)
        cariPenumpangBST(root->right, noPenumpang);
    else
    {
        printf("Penumpang ditemukan dalam BST:\n");
        printf("Nomor: %d\n", root->noPenumpang);
        printf("Nama: %s\n", root->namaPenumpang);
    }
}

// Fungsi untuk mencari penumpang dalam AVL Tree
void cariPenumpangAVL(AVLNode *root, int noPenumpang)
{
    if (root == NULL)
    {
        printf("Penumpang tidak ditemukan dalam AVL Tree.\n");
        return;
    }

    if (noPenumpang < root->noPenumpang)
        cariPenumpangAVL(root->left, noPenumpang);
    else if (noPenumpang > root->noPenumpang)
        cariPenumpangAVL(root->right, noPenumpang);
    else
    {
        printf("Penumpang ditemukan dalam AVL Tree:\n");
        printf("Nomor: %d\n", root->noPenumpang);
        printf("Nama: %s\n", root->namaPenumpang);
    }
}

// Main Program
int main()
{
    Queue antrian, doneQ;
    initializeQueue(&antrian);
    initializeQueue(&doneQ);

    BSTNode *bstRoot = NULL;
    AVLNode *avlRoot = NULL;

    int pilihan;
    do
    {
        printf("\n=== Sistem Antrian ===\n");
        printf("1. Tambah Penumpang ke Antrian\n");
        printf("2. Penumpang Naik Bus\n");
        printf("3. Lihat Antrian Penumpang\n");
        printf("4. Lihat Penumpang yang Sudah Naik Bus\n");
        printf("5. Cari Penumpang dalam Queue\n");
        printf("6. Cari Penumpang dalam BST\n");
        printf("7. Cari Penumpang dalam AVL Tree\n");
        printf("0. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        int noPenumpang;
        char namaPenumpang[50];

        switch (pilihan)
        {
        case 1:
            printf("Masukkan nomor penumpang: ");
            scanf("%d", &noPenumpang);
            printf("Masukkan nama penumpang: ");
            scanf(" %[^\n]s", namaPenumpang);

            enqueue(&antrian, noPenumpang, namaPenumpang, pilihan);
            bstRoot = insertBST(bstRoot, noPenumpang, namaPenumpang);
            avlRoot = insertAVL(avlRoot, noPenumpang, namaPenumpang);
            break;

        case 2:
            dequeue(&antrian, &doneQ, pilihan);
            break;

        case 3:
            displayQueue(&antrian);
            break;

        case 4:
            displayPenumpangBus(&doneQ);
            break;

        case 5:
            printf("Masukkan nomor penumpang yang ingin dicari: ");
            scanf("%d", &noPenumpang);
            cariPenumpang(&antrian, noPenumpang);
            break;

        case 6:
            printf("Masukkan nomor penumpang yang ingin dicari di BST: ");
            scanf("%d", &noPenumpang);
            cariPenumpangBST(bstRoot, noPenumpang);
            break;

        case 7:
            printf("Masukkan nomor penumpang yang ingin dicari di AVL Tree: ");
            scanf("%d", &noPenumpang);
            cariPenumpangAVL(avlRoot, noPenumpang);
            break;

        case 0:
            printf("Terima kasih telah menggunakan sistem antrian.\n");
            break;

        default:
            printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 0);

    // Free memory (cleanup)
    while (!isEmpty(&antrian))
    {
        Node *temp = antrian.front;
        antrian.front = antrian.front->next;
        free(temp);
    }

    while (!isEmpty(&doneQ))
    {
        Node *temp = doneQ.front;
        doneQ.front = doneQ.front->next;
        free(temp);
    }

    return 0;
}