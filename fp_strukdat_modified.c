#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ================ STRUKTUR DATA ================

// Struktur Node untuk Binary Search Tree (BST)
typedef struct BSTNode
{
  int noPenumpang;
  char namaPenumpang[50];
  int height;
  int idBus;
  struct BSTNode *left, *right;
} BSTNode;

// Struktur Node untuk AVL Tree
typedef struct AVLNode
{
  int noPenumpang;
  char namaPenumpang[50];
  int height;
  int idBus;
  struct AVLNode *left, *right;
} AVLNode;

// Struktur untuk Bus
typedef struct Bus
{
  int idBus;
  char tujuan[50];
  char departure_time[50];
  char arrival_time[50];
  int countPenumpang;
  int maxPenumpang;
} Bus;

#define MAX_BUS 100
Bus buses[MAX_BUS];
int jumlahBus = 0;

// ================ FUNGSI UTILITAS ================

// Mendapatkan tinggi node BST
int getHeightBST(BSTNode *node)
{
  if (node == NULL)
    return 0;
  return node->height;
}

// Mendapatkan tinggi node AVL
int getHeightAVL(AVLNode *node)
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
  return getHeightAVL(node->left) - getHeightAVL(node->right);
}

// ================ FUNGSI BST ================

// Membuat node BST baru
BSTNode *newBSTNode(int noPenumpang, char *namaPenumpang, int idBus)
{
  BSTNode *node = (BSTNode *)malloc(sizeof(BSTNode));
  node->noPenumpang = noPenumpang;
  strcpy(node->namaPenumpang, namaPenumpang);
  node->idBus = idBus;
  node->height = 1;
  node->left = node->right = NULL;
  return node;
}

// Menyisipkan node baru ke dalam BST
BSTNode *insertBST(BSTNode *node, int noPenumpang, char *namaPenumpang, int idBus)
{
  if (node == NULL)
    return newBSTNode(noPenumpang, namaPenumpang, idBus);

  if (noPenumpang < node->noPenumpang)
    node->left = insertBST(node->left, noPenumpang, namaPenumpang, idBus);
  else if (noPenumpang > node->noPenumpang)
    node->right = insertBST(node->right, noPenumpang, namaPenumpang, idBus);

  node->height = 1 + max(getHeightBST(node->left), getHeightBST(node->right));

  return node;
}

// Menghapus node dari BST
BSTNode *deleteBST(BSTNode *root, int noPenumpang, char *namaPenumpang)
{
  if (root == NULL)
    return root;

  if (noPenumpang < root->noPenumpang)
    root->left = deleteBST(root->left, noPenumpang, namaPenumpang);
  else if (noPenumpang > root->noPenumpang)
    root->right = deleteBST(root->right, noPenumpang, namaPenumpang);
  else
  {

    strcpy(namaPenumpang, root->namaPenumpang);

    if (root->left == NULL)
    {
      BSTNode *temp = root->right;
      free(root);
      return temp;
    }
    else if (root->right == NULL)
    {
      BSTNode *temp = root->left;
      free(root);
      return temp;
    }

    BSTNode *temp = root->right;
    while (temp->left != NULL)
      temp = temp->left;

    root->noPenumpang = temp->noPenumpang;
    strcpy(root->namaPenumpang, temp->namaPenumpang);
    root->right = deleteBST(root->right, temp->noPenumpang, namaPenumpang);
  }

  root->height = 1 + max(getHeightBST(root->left), getHeightBST(root->right));

  return root;
}

int checkPenumpangBST(AVLNode *root, int noPenumpang)
{
  if (root == NULL)
    return 0;

  if (noPenumpang == root->noPenumpang)
    return 1;
  else if (noPenumpang < root->noPenumpang)
    return checkPenumpangBST(root->left, noPenumpang);
  else
    return checkPenumpangBST(root->right, noPenumpang);
}

// ================ FUNGSI AVL TREE ================

// Membuat node AVL baru
AVLNode *newAVLNode(int noPenumpang, char *namaPenumpang, int idBus)
{
  AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
  node->noPenumpang = noPenumpang;
  strcpy(node->namaPenumpang, namaPenumpang);
  node->idBus = idBus;
  node->height = 1;
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

  y->height = max(getHeightAVL(y->left), getHeightAVL(y->right)) + 1;
  x->height = max(getHeightAVL(x->left), getHeightAVL(x->right)) + 1;

  return x;
}

// Rotasi kiri untuk menyeimbangkan AVL Tree
AVLNode *leftRotate(AVLNode *x)
{
  AVLNode *y = x->right;
  AVLNode *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(getHeightAVL(x->left), getHeightAVL(x->right)) + 1;
  y->height = max(getHeightAVL(y->left), getHeightAVL(y->right)) + 1;

  return y;
}

// Menyisipkan node baru ke dalam AVL Tree
AVLNode *insertAVL(AVLNode *node, int noPenumpang, char *namaPenumpang, int idBus)
{
  if (node == NULL)
    return newAVLNode(noPenumpang, namaPenumpang, idBus);

  if (noPenumpang < node->noPenumpang)
    node->left = insertAVL(node->left, noPenumpang, namaPenumpang, idBus);
  else if (noPenumpang > node->noPenumpang)
    node->right = insertAVL(node->right, noPenumpang, namaPenumpang, idBus);
  else
    return node;

  node->height = 1 + max(getHeightAVL(node->left), getHeightAVL(node->right));

  int balance = getBalance(node);

  if (balance > 1 && noPenumpang < node->left->noPenumpang)
    return rightRotate(node);

  if (balance < -1 && noPenumpang > node->right->noPenumpang)
    return leftRotate(node);

  if (balance > 1 && noPenumpang > node->left->noPenumpang)
  {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  if (balance < -1 && noPenumpang < node->right->noPenumpang)
  {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

// Menghapus node dari AVL Tree
AVLNode *deleteAVL(AVLNode *root, int noPenumpang, char *namaPenumpang)
{
  if (root == NULL)
    return root;

  if (noPenumpang < root->noPenumpang)
    root->left = deleteAVL(root->left, noPenumpang, namaPenumpang);
  else if (noPenumpang > root->noPenumpang)
    root->right = deleteAVL(root->right, noPenumpang, namaPenumpang);
  else
  {
    strcpy(namaPenumpang, root->namaPenumpang);

    if (root->left == NULL || root->right == NULL)
    {
      AVLNode *temp = root->left ? root->left : root->right;

      if (temp == NULL)
      {
        temp = root;
        root = NULL;
      }
      else
        *root = *temp;

      free(temp);
    }
    else
    {
      AVLNode *temp = root->right;
      while (temp->left != NULL)
        temp = temp->left;

      root->noPenumpang = temp->noPenumpang;
      strcpy(root->namaPenumpang, temp->namaPenumpang);
      root->right = deleteAVL(root->right, temp->noPenumpang, namaPenumpang);
    }
  }

  if (root == NULL)
    return root;

  root->height = 1 + max(getHeightAVL(root->left), getHeightAVL(root->right));

  int balance = getBalance(root);

  if (balance > 1 && getBalance(root->left) >= 0)
    return rightRotate(root);

  if (balance > 1 && getBalance(root->left) < 0)
  {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  if (balance < -1 && getBalance(root->right) <= 0)
    return leftRotate(root);

  if (balance < -1 && getBalance(root->right) > 0)
  {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}

// ================ FUNGSI PENCARIAN ================

// Mencari penumpang dalam BST
void cariPenumpangBST(BSTNode *root, int noPenumpang)
{
  if (root == NULL)
  {
    printf("Penumpang %d tidak ditemukan dalam BST.\n", noPenumpang);
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
    printf("Height: %d\n", root->height);

    int busFound = 0;
    for (int i = 0; i < jumlahBus; i++)
    {
      if (buses[i].idBus == root->idBus)
      {
        printf("ID Bus: %d\n", root->idBus);
        printf("Tujuan: %s\n", buses[i].tujuan);
        printf("Waktu Keberangkatan: %s\n", buses[i].departure_time);
        printf("Waktu Kedatangan: %s\n", buses[i].arrival_time);
        busFound = 1;
        break;
      }
    }

    if (!busFound)
    {
      printf("Penumpang tidak menaiki bus yang terdaftar!\n");
    }
  }
}

// Mencari penumpang dalam AVL Tree
void cariPenumpangAVL(AVLNode *root, int noPenumpang)
{
  if (root == NULL)
  {
    printf("Penumpang %d tidak ditemukan dalam AVL Tree.\n", noPenumpang);
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
    printf("Height: %d\n", root->height);

    int busFound = 0;
    for (int i = 0; i < jumlahBus; i++)
    {
      if (buses[i].idBus == root->idBus)
      {
        printf("ID Bus: %d\n", root->idBus);
        printf("Tujuan: %s\n", buses[i].tujuan);
        printf("Waktu Keberangkatan: %s\n", buses[i].departure_time);
        printf("Waktu Kedatangan: %s\n", buses[i].arrival_time);
        busFound = 1;
        break;
      }
    }

    if (!busFound)
    {
      printf("Penumpang tidak menaiki bus yang terdaftar!\n");
    }
  }
}

int checkPenumpangAVL(AVLNode *root, int noPenumpang)
{
  if (root == NULL)
    return 0;

  if (noPenumpang == root->noPenumpang)
    return 1;
  else if (noPenumpang < root->noPenumpang)
    return checkPenumpangAVL(root->left, noPenumpang);
  else
    return checkPenumpangAVL(root->right, noPenumpang);
}

// ================ FUNGSI TRAVERSAL ================

// Inorder traversal BST
void inorderBST(BSTNode *root, char *posisi)
{
  if (root != NULL)
  {
    inorderBST(root->left, "Kiri");
    printf("Nomor: %d, ", root->noPenumpang);
    printf("Nama: %s, ", root->namaPenumpang);
    printf("Height: %d, ", root->height);
    printf("Posisi: %s, ", posisi);

    int busFound = 0;
    for (int i = 0; i < jumlahBus; i++)
    {
      if (buses[i].idBus == root->idBus)
      {
        printf("ID Bus: %d\n", root->idBus);
        printf("Tujuan: %s\n", buses[i].tujuan);
        printf("Waktu Keberangkatan: %s\n", buses[i].departure_time);
        printf("Waktu Kedatangan: %s\n", buses[i].arrival_time);
        busFound = 1;
        break;
      }
    }

    if (!busFound)
    {
      printf("Penumpang tidak menaiki bus yang terdaftar!\n");
    }

    inorderBST(root->right, "Kanan");
  }
}

// Inorder traversal AVL
void inorderAVL(AVLNode *root, char *posisi)
{
  if (root != NULL)
  {
    inorderAVL(root->left, "Kiri");
    printf("Nomor: %d, ", root->noPenumpang);
    printf("Nama: %s, ", root->namaPenumpang);
    printf("Height: %d, ", root->height);
    printf("Posisi: %s, ", posisi);

    int busFound = 0;
    for (int i = 0; i < jumlahBus; i++)
    {
      if (buses[i].idBus == root->idBus)
      {
        printf("ID Bus: %d\n", root->idBus);
        printf("Tujuan: %s\n", buses[i].tujuan);
        printf("Waktu Keberangkatan: %s\n", buses[i].departure_time);
        printf("Waktu Kedatangan: %s\n", buses[i].arrival_time);
        busFound = 1;
        break;
      }
    }

    if (!busFound)
    {
      printf("Penumpang tidak menaiki bus yang terdaftar!\n");
    }

    inorderAVL(root->right, "Kanan");
  }
}

// ================ FUNGSI BUS ================
void tambahBus()
{
  if (jumlahBus >= MAX_BUS)
  {
    printf("Kapasitas maksimal Bus telah tercapai.\n");
    return;
  }

  Bus newBus;
  printf("Masukkan ID Bus: ");
  scanf("%d", &newBus.idBus);
  getchar();

  for (int i = 0; i < jumlahBus; i++)
  {
    if (buses[i].idBus == newBus.idBus)
    {
      printf("ID Bus sudah digunakan, silakan gunakan ID lain.\n");
      return;
    }
  }

  printf("Masukkan Tujuan Bus: ");
  fgets(newBus.tujuan, sizeof(newBus.tujuan), stdin);
  newBus.tujuan[strcspn(newBus.tujuan, "\n")] = 0;

  printf("Masukkan Jam Keberangkatan Bus: ");
  fgets(newBus.departure_time, sizeof(newBus.departure_time), stdin);
  newBus.departure_time[strcspn(newBus.departure_time, "\n")] = 0;

  printf("Masukkan Jam Kedatangan Bus: ");
  fgets(newBus.arrival_time, sizeof(newBus.arrival_time), stdin);
  newBus.arrival_time[strcspn(newBus.arrival_time, "\n")] = 0;

  printf("Masukkan kapasitas maksimal penumpang: ");
  scanf("%d", &newBus.maxPenumpang);

  newBus.countPenumpang = 0;

  buses[jumlahBus] = newBus;
  jumlahBus++;
  printf("Bus %d berhasil ditambahkan!\n", newBus.idBus);
}

void displayBus()
{
  if (jumlahBus > 0)
  {
    printf("\n==============================\n");
    printf("\nData Bus yang tersedia\n");
    printf("\n==============================\n");
    for (int i = 0; i < jumlahBus; i++)
    {
      printf("ID Bus: %d, ", buses[i].idBus);
      printf("Tujuan Bus: %s, ", buses[i].tujuan);
      printf("Jam Keberangkatan: %s, ", buses[i].departure_time);
      printf("Jam Kedatangan: %s, ", buses[i].arrival_time);
      printf("Kapasitas Penumpang: %d / %d \n", buses[i].countPenumpang, buses[i].maxPenumpang);
    }
  }
  else
  {
    printf("Tidak ada bus yang tersedia\n");
  }
}

void editBus()
{
  int idBus;
  printf("Masukkan ID Bus yang akan diedit: ");
  scanf("%d", &idBus);
  getchar();

  int busFound = 0;
  for (int i = 0; i < jumlahBus; i++)
  {
    if (buses[i].idBus == idBus)
    {
      printf("Masukkan tujuan baru: ");
      fgets(buses[i].tujuan, sizeof(buses[i].tujuan), stdin);
      buses[i].tujuan[strcspn(buses[i].tujuan, "\n")] = 0;

      printf("Masukkan jam keberangkatan baru:");
      fgets(buses[i].departure_time, sizeof(buses[i].departure_time), stdin);
      buses[i].departure_time[strcspn(buses[i].departure_time, "\n")] = 0;

      printf("Masukkan jam sampai baru: ");
      fgets(buses[i].arrival_time, sizeof(buses[i].arrival_time), stdin);
      buses[i].arrival_time[strcspn(buses[i].arrival_time, "\n")] = 0;

      printf("Masukkan kapasitas maksimal penumpang baru: ");
      scanf("%d", &buses[i].maxPenumpang);

      if (buses[i].countPenumpang > buses[i].maxPenumpang)
      {
        buses[i].countPenumpang = buses[i].maxPenumpang;
      }

      busFound = 1;

      printf("Data bus dengan ID %d berhasil diedit!\n", buses[i].idBus);
      break;
    }
  }

  if (!busFound)
  {
    printf("Bus dengan ID %d tidak ditemukan.\n", idBus);
  }
}

void hapusBus()
{
  int idBus;
  printf("Masukkan ID Bus yang akan dihapus: ");
  scanf("%d", &idBus);

  for (int i = 0; i < jumlahBus; i++)
  {
    if (buses[i].idBus == idBus)
    {
      for (int j = i; j < jumlahBus - 1; j++)
      {
        buses[j] = buses[j + 1];
      }
      jumlahBus--;
      printf("Bus dengan ID %d berhasil dihapus.\n", idBus);
      return;
    }
  }

  printf("Bus dengan ID %d tidak ditemukan.\n", idBus);
}

// ================ TAMBAH PENUMPANG ================
void tambahPenumpang(BSTNode **bstRoot, AVLNode **avlRoot)
{
  if (jumlahBus > 0)
  {
    displayBus();
  }
  else
  {
    printf("Tidak ada bus yang tersedia.\n");
    return;
  }

  int idBus;
  printf("\nMasukkan ID Bus untuk penumpang: ");
  scanf("%d", &idBus);

  // Cek apakah bus ada dan menyimpan index bus
  int busFound = 0;
  for (int i = 0; i < jumlahBus; i++)
  {
    if (buses[i].idBus == idBus)
    {
      busFound = 1;
      if (buses[i].countPenumpang >= buses[i].maxPenumpang)
      {
        printf("Bus dengan ID %d sudah penuh.\n", idBus);
        return;
      }
      buses[i].countPenumpang++;
      break;
    }
  }

  if (!busFound)
  {
    printf("Bus dengan ID %d tidak ditemukan.\n", idBus);
    return;
  }

  int noPenumpang;
  char namaPenumpang[50];

  while (1)
  {
    printf("Masukkan nomor penumpang: ");
    scanf("%d", &noPenumpang);

    // Cek duplikasi di BST dan AVL
    if (checkPenumpangBST(*bstRoot, noPenumpang) || checkPenumpangAVL(*avlRoot, noPenumpang))
    {
      printf("Nomor penumpang %d sudah digunakan, silakan masukkan nomor lain.\n", noPenumpang);
    }
    else
    {
      break;
    }
  }

  printf("Masukkan nama penumpang: ");
  fgets(namaPenumpang, sizeof(namaPenumpang), stdin);
  namaPenumpang[strcspn(namaPenumpang, "\n")] = 0;

  *bstRoot = insertBST(*bstRoot, noPenumpang, namaPenumpang, idBus);
  *avlRoot = insertAVL(*avlRoot, noPenumpang, namaPenumpang, idBus);

  printf("Penumpang %d - %s berhasil ditambahkan ke bus %d.\n", noPenumpang, namaPenumpang, idBus);
}

// ================ PROGRAM UTAMA ================
int main()
{
  BSTNode *bstRoot = NULL;
  AVLNode *avlRoot = NULL;

  int mainMenu, busMenu, penumpangMenu;
  while (1)
  {
    printf("\n==================================\n");
    printf("\nSistem Manajemen Bus dan Penumpang\n");
    printf("\n==================================\n");
    printf("1. Bus Menu\n");
    printf("2. Penumpang Menu\n");
    printf("3. Keluar\n");
    printf("Pilihan: ");
    scanf("%d", &mainMenu);
    getchar();

    switch (mainMenu)
    {
    case 1:
      printf("\n==================================\n");
      printf("\nBus Menu\n");
      printf("\n==================================\n");
      printf("1. Tambah Bus\n");
      printf("2. Lihat Data Bus\n");
      printf("3. Edit Bus\n");
      printf("4. Hapus Bus\n");
      printf("5. Keluar\n");
      printf("Pilihan: ");
      scanf("%d", &busMenu);
      getchar();

      switch (busMenu)
      {
      case 1:
        tambahBus();
        break;
      case 2:
        displayBus();
        break;
      case 3:
        editBus();
        break;
      case 4:
        hapusBus();
        break;
      case 5:
        printf("Keluar dari program.\n");
        break;
      default:
        printf("Pilihan tidak valid.\n");
        break;
      }
      break;

    case 2:
      printf("\n==================================\n");
      printf("\nPenumpang Menu\n");
      printf("\n==================================\n");
      printf("1. Tambah Data Penumpang\n");
      printf("2. Cari Data Penumpang\n");
      printf("3. Hapus Data Penumpang\n");
      printf("4. Tampilkan Tree (Inorder)\n");
      printf("5. Keluar\n");
      printf("Pilihan: ");
      scanf("%d", &penumpangMenu);
      getchar();

      switch (penumpangMenu)
      {
      case 1:
      {
        tambahPenumpang(&bstRoot, &avlRoot);
        break;
      }
      case 2:
      {
        int noPenumpang, kategoriPencarian;
        printf("\nPilih metode pencarian:\n");
        printf("1. Binary Search Tree\n");
        printf("2. AVL Tree\n");
        printf("Pilihan: ");
        scanf("%d", &kategoriPencarian);

        printf("Masukkan nomor penumpang: ");
        scanf("%d", &noPenumpang);

        switch (kategoriPencarian)
        {
        case 1:
          cariPenumpangBST(bstRoot, noPenumpang);
          break;
        case 2:
          cariPenumpangAVL(avlRoot, noPenumpang);
          break;
        default:
          printf("Pilihan tidak valid\n");
        }
        break;
      }
      case 3:
      {
        int noPenumpang;
        char namaPenumpang[50] = "";
        printf("Masukkan nomor penumpang yang akan dihapus: ");
        scanf("%d", &noPenumpang);

        bstRoot = deleteBST(bstRoot, noPenumpang, namaPenumpang);
        avlRoot = deleteAVL(avlRoot, noPenumpang, namaPenumpang);

        if (strlen(namaPenumpang) > 0)
          printf("Menghapus %d - %s dalam data Penumpang\n", noPenumpang, namaPenumpang);
        else
          printf("Nomor penumpang %d tidak ditemukan.\n", noPenumpang);

        break;
      }
      case 4:
      {
        int kategoriTree;
        printf("\nPilih jenis tree:\n");
        printf("1. Binary Search Tree\n");
        printf("2. AVL Tree\n");
        printf("Pilihan: ");
        scanf("%d", &kategoriTree);

        switch (kategoriTree)
        {
        case 1:
          printf("\nInorder traversal BST:\n");
          if (bstRoot == NULL)
          {
            printf("BST kosong.\n");
          }
          else
          {
            inorderBST(bstRoot, "Root");
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
            inorderAVL(avlRoot, "Root");
          }
          break;
        default:
          printf("Pilihan tidak valid\n");
        }
        break;
      }
      case 5:
        printf("Keluar dari program.\n");
        break;
      default:
        printf("Pilihan tidak valid.\n");
        break;
      }
      break;

    case 3:
      printf("Keluar dari program.\n");
      return 1;
      break;

    default:
      printf("Pilihan tidak valid.\n");
      break;
    }
  }
  return 0;
}