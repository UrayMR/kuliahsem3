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

// Struktur Node untuk Binary Search Tree (BST)
typedef struct BSTNode
{
    int noPenumpang;
    char namaPenumpang[50];
    struct BSTNode *left, *right;
} BSTNode;

// Struktur Node untuk AVL Tree
typedef struct AVLNode
{
    int noPenumpang;
    char namaPenumpang[50];
    int height; // Tinggi node untuk keseimbangan AVL
    struct AVLNode *left, *right;
} AVLNode;

// ================ FUNGSI UTILITAS ================

// Mendapatkan tinggi node AVL
int getHeight(AVLNode *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

// Mendapatkan nilai maksimum dari dua bilangan
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Mendapatkan faktor keseimbangan node AVL
int getBalance(AVLNode *node)
{
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

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
void enqueue(Queue *q, int noPenumpang, char *namaPenumpang, int pilihan)
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

    if (pilihan != 2)
    {
        printf("Penumpang no-%d atas nama %s masuk ke antrian.\n", noPenumpang, namaPenumpang);
    }
}

// Mengeluarkan penumpang dari antrian (untuk naik bus)
void dequeue(Queue *q, Queue *doneQ, int pilihan)
{
    if (isEmpty(q))
    {
        printf("Antrian kosong. Tidak ada penumpang untuk naik bus.\n");
        return;
    }

    Node *temp = q->front;
    printf("Penumpang no-%d atas nama %s naik bus.\n", temp->noPenumpang, temp->namaPenumpang);

    // Memindahkan data penumpang ke antrian selesai
    enqueue(doneQ, temp->noPenumpang, temp->namaPenumpang, pilihan);

    // Update pointer front
    q->front = q->front->next;
    if (q->front == NULL)
    {
        q->rear = NULL;
    }

    free(temp);
}

// ================ FUNGSI BST ================

// Membuat node BST baru
BSTNode *newBSTNode(int noPenumpang, char *namaPenumpang)
{
    BSTNode *node = (BSTNode *)malloc(sizeof(BSTNode));
    node->noPenumpang = noPenumpang;
    strcpy(node->namaPenumpang, namaPenumpang);
    node->left = node->right = NULL;
    return node;
}

// Menyisipkan node baru ke dalam BST
BSTNode *insertBST(BSTNode *node, int noPenumpang, char *namaPenumpang)
{
    // Jika pohon kosong, buat node baru
    if (node == NULL)
        return newBSTNode(noPenumpang, namaPenumpang);

    // Rekursif menyisipkan ke subtree yang tepat
    if (noPenumpang < node->noPenumpang)
        node->left = insertBST(node->left, noPenumpang, namaPenumpang);
    else if (noPenumpang > node->noPenumpang)
        node->right = insertBST(node->right, noPenumpang, namaPenumpang);

    return node;
}

// ================ FUNGSI AVL TREE ================

// Membuat node AVL baru
AVLNode *newAVLNode(int noPenumpang, char *namaPenumpang)
{
    AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
    node->noPenumpang = noPenumpang;
    strcpy(node->namaPenumpang, namaPenumpang);
    node->height = 1; // Node baru selalu memiliki tinggi 1
    node->left = node->right = NULL;
    return node;
}

// Rotasi kanan untuk menyeimbangkan AVL Tree
AVLNode *rightRotate(AVLNode *y)
{
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    // Update tinggi
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// Rotasi kiri untuk menyeimbangkan AVL Tree
AVLNode *leftRotate(AVLNode *x)
{
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    // Update tinggi
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// Menyisipkan node baru ke dalam AVL Tree
AVLNode *insertAVL(AVLNode *node, int noPenumpang, char *namaPenumpang)
{
    // Melakukan penyisipan BST normal
    if (node == NULL)
        return newAVLNode(noPenumpang, namaPenumpang);

    if (noPenumpang < node->noPenumpang)
        node->left = insertAVL(node->left, noPenumpang, namaPenumpang);
    else if (noPenumpang > node->noPenumpang)
        node->right = insertAVL(node->right, noPenumpang, namaPenumpang);
    else // Nilai sama tidak diperbolehkan dalam BST
        return node;

    // Update tinggi node
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // Dapatkan faktor keseimbangan
    int balance = getBalance(node);

    // Jika node tidak seimbang, ada 4 kasus

    // Kasus Left Left
    if (balance > 1 && noPenumpang < node->left->noPenumpang)
        return rightRotate(node);

    // Kasus Right Right
    if (balance < -1 && noPenumpang > node->right->noPenumpang)
        return leftRotate(node);

    // Kasus Left Right
    if (balance > 1 && noPenumpang > node->left->noPenumpang)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Kasus Right Left
    if (balance < -1 && noPenumpang < node->right->noPenumpang)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// ================ FUNGSI PENCARIAN ================

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

// Mencari penumpang dalam BST
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

// Mencari penumpang dalam AVL Tree
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

// ================ FUNGSI TAMPILAN ================

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

// ================ FUNGSI TRAVERSAL BST DAN AVL ================

// Inorder traversal BST
void inorderBST(BSTNode *root)
{
    if (root != NULL)
    {
        inorderBST(root->left);
        printf("No: %d, Nama: %s\n", root->noPenumpang, root->namaPenumpang);
        inorderBST(root->right);
    }
}

// Inorder traversal AVL
void inorderAVL(AVLNode *root)
{
    if (root != NULL)
    {
        inorderAVL(root->left);
        printf("No: %d, Nama: %s (Tinggi: %d)\n", root->noPenumpang, root->namaPenumpang, root->height);
        inorderAVL(root->right);
    }
}

// ================ PROGRAM UTAMA ================

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
        printf("\n==============================\n");
        printf("\nSistem Antrian Bus\n");
        printf("\n==============================\n");
        printf("1. Tambah Penumpang ke Antrian\n");
        printf("2. Penumpang Naik Bus\n");
        printf("3. Lihat Antrian Penumpang\n");
        printf("4. Lihat Penumpang yang Sudah Naik Bus\n");
        printf("5. Cari Penumpang dalam Queue\n");
        printf("6. Tampilkan Tree (Inorder)\n");
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

            // Menambahkan ke semua struktur data
            enqueue(&antrian, noPenumpang, namaPenumpang, pilihan);
            bstRoot = insertBST(bstRoot, noPenumpang, namaPenumpang);
            avlRoot = insertAVL(avlRoot, noPenumpang, namaPenumpang);
            break;
        }

        case 2:
        {
            dequeue(&antrian, &doneQ, pilihan);
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
            int noPenumpang, kategoriPencarian;
            printf("\n==============================\n");
            printf("\nKategori Pencarian\n");
            printf("\n==============================\n");
            printf("\n1. Sequential Search\n2. Binary Search Tree\n3. AVL Tree");
            printf("\nMasukkan nomor kategori pencarian: ");
            scanf("%d", &kategoriPencarian);
            scanf("%d", &noPenumpang);

            switch (kategoriPencarian)
            {
            case 1:
                printf("\nMasukkan nomor penumpang");
                scanf("%d", &noPenumpang);
                cariPenumpang(&antrian, noPenumpang);
                break;
            case 2:
                printf("\nMasukkan nomor penumpang");
                scanf("%d", &noPenumpang);
                cariPenumpangBST(bstRoot, noPenumpang);
                break;
            case 3:
                printf("\nMasukkan nomor penumpang");
                scanf("%d", &noPenumpang);
                cariPenumpangAVL(avlRoot, noPenumpang);
                break;

            default:
                break;
            }

            break;
        }

        case 6:
        {
            int kategoriTrees;
            printf("\n==============================\n");
            printf("\nKategori Trees\n");
            printf("\n==============================\n");
            printf("\n1. Binary Search Tree\n2. AVL Tree\n");
            printf("\nMasukkan nomor kategori pencarian: ");
            scanf("%d", &kategoriTrees);

            switch (kategoriTrees)
            {
            case 1:
                printf("\nInorder traversal BST:\n");
                if (bstRoot == NULL)
                {
                    printf("BST kosong.\n");
                }
                else
                {
                    inorderBST(bstRoot);
                }
                break;
            case 2:
                printf("\nInorder traversal AVL Tree:\n");
                if (avlRoot == NULL)
                {
                    printf("AVL Tree kosong.\n");
                }
                else
                {
                    inorderAVL(avlRoot);
                }
            default:
                break;
            }

            break;
        }

        case 0:
        {
            printf("\nTerima kasih telah menggunakan sistem antrian bus.\n");
            break;
        }

        default:
        {
            printf("\nPilihan tidak valid. Silakan coba lagi.\n");
            break;
        }
        }
    } while (pilihan != 0);

    return 0;
}