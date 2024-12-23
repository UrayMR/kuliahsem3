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
    return -1;
  return node->height;
}

// Mendapatkan tinggi node AVL
int getHeightAVL(AVLNode *node)
{
  if (node == NULL)
    return -1;
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
    return -1;
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
  node->height = 0;
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
  {
    namaPenumpang[0] = '\0'; // Set empty string if not found
    return root;
  }

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

    strcpy(namaPenumpang, root->namaPenumpang);
  }

  root->height = 1 + max(getHeightBST(root->left), getHeightBST(root->right));

  return root;
}

int checkPenumpangBST(BSTNode *root, int noPenumpang)
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
  node->height = 0;
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

    printf("========================================================================================================\n");
    printf("| %-3s | %-20s | %-3s | %-3s | %-10s | %-20s | %-20s |\n", "No", "Nama", "Height", "Bus", "Posisi", "Tujuan", "Keberangkatan", "Kedatangan");
    printf("|-----|----------------------|--------|-----|------------|----------------------|----------------------|\n");

    printf("| %-3d | %-20s | %-6d | %-3d | %-10s | %-20s | %-20s |\n", root->noPenumpang, root->namaPenumpang, root->height, root->idBus, "Root", buses[root->idBus].tujuan, buses[root->idBus].departure_time, buses[root->idBus].arrival_time);
    printf("========================================================================================================\n");
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

    printf("========================================================================================================\n");
    printf("| %-3s | %-20s | %-3s | %-3s | %-10s | %-20s | %-20s |\n", "No", "Nama", "Height", "Bus", "Posisi", "Tujuan", "Keberangkatan", "Kedatangan");
    printf("|-----|----------------------|--------|-----|------------|----------------------|----------------------|\n");

    printf("| %-3d | %-20s | %-6d | %-3d | %-10s | %-20s | %-20s |\n", root->noPenumpang, root->namaPenumpang, root->height, root->idBus, "Root", buses[root->idBus].tujuan, buses[root->idBus].departure_time, buses[root->idBus].arrival_time);
    printf("========================================================================================================\n");
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
    printf("| %-3d | %-20s | %-6d | %-3d | %-10s | %-20s | %-20s |\n",
           root->noPenumpang, root->namaPenumpang, root->height, root->idBus, posisi,
           buses[root->idBus].tujuan, buses[root->idBus].departure_time, buses[root->idBus].arrival_time);
    inorderBST(root->right, "Kanan");
  }
}

// Inorder traversal AVL
void inorderAVL(AVLNode *root, char *posisi)
{
  if (root != NULL)
  {
    inorderAVL(root->left, "Kiri");
    printf("| %-3d | %-20s | %-6d | %-3d | %-10s | %-20s | %-20s |\n",
           root->noPenumpang, root->namaPenumpang, root->height, root->idBus, posisi,
           buses[root->idBus].tujuan, buses[root->idBus].departure_time, buses[root->idBus].arrival_time);
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
  printf("\n==================================\n");
  printf("\nTambahkan Bus\n");
  printf("\n==================================\n");
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
    printf("\n========================================================================================");
    printf("\n-------------------------------Data Bus yang tersedia-----------------------------------\n");
    printf("========================================================================================\n");
    printf("| %-3s | %-20s | %-20s | %-20s | %-3s |\n", "ID", "Tujuan", "Keberangkatan", "Kedatangan", "Penumpang");
    printf("|-----|----------------------|----------------------|----------------------|-----------|\n");
    for (int i = 0; i < jumlahBus; i++)
    {
      printf("| %-3d | %-20s | %-20s | %-20s | %-3d / %-3d |\n",
             buses[i].idBus, buses[i].tujuan, buses[i].departure_time, buses[i].arrival_time,
             buses[i].countPenumpang, buses[i].maxPenumpang);
    }
  }
  else
  {
    printf("Tidak ada bus yang tersedia\n");
  }
}

void editBus()
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
  printf("\nMasukkan ID Bus yang akan diedit: ");
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
        printf("\nBus dengan ID %d sudah penuh.\n", idBus);
        return;
      }
      buses[i].countPenumpang++;
      break;
    }
  }

  if (!busFound)
  {
    printf("\nBus dengan ID %d tidak ditemukan.\n", idBus);
    return;
  }

  int noPenumpang;
  char namaPenumpang[50];

  while (1)
  {
    printf("\nMasukkan nomor penumpang: ");
    scanf("%d", &noPenumpang);
    getchar();

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

// ================ FUNGSI PENYIMPANAN ================
void saveBusCSV()
{
  FILE *file = fopen("bus.csv", "w");
  if (!file)
  {
    printf("Error: tidak dapat membuka file!\n");
    return;
  }

  for (int i = 0; i < jumlahBus; i++)
  {
    fprintf(file, "%d,%s,%s,%s,%d,%d\n",
            buses[i].idBus,
            buses[i].tujuan,
            buses[i].departure_time,
            buses[i].arrival_time,
            buses[i].countPenumpang,
            buses[i].maxPenumpang);
  }
  fclose(file);
}

void loadBusCSV()
{
  FILE *file = fopen("bus.csv", "r");
  if (!file)
  {
    printf("Info: File bus.csv tidak ditemukan. Membuat file baru.\n");
    return;
  }

  jumlahBus = 0; // Reset jumlah bus

  while (jumlahBus < MAX_BUS && fscanf(file, "%d,%[^,],%[^,],%[^,],%d,%d\n",
                                       &buses[jumlahBus].idBus,
                                       buses[jumlahBus].tujuan,
                                       buses[jumlahBus].departure_time,
                                       buses[jumlahBus].arrival_time,
                                       &buses[jumlahBus].countPenumpang,
                                       &buses[jumlahBus].maxPenumpang) != EOF)
  {
    jumlahBus++;
  }

  fclose(file);
}

void helperSave(BSTNode *root, FILE *file)
{
  if (root != NULL)
  {
    helperSave(root->left, file);
    fprintf(file, "%d,%s,%d\n",
            root->noPenumpang,
            root->namaPenumpang,
            root->idBus);
    helperSave(root->right, file);
  }
}

void savePenumpangCSV(BSTNode *bstRoot)
{
  FILE *file = fopen("penumpang.csv", "w");
  if (!file)
  {
    printf("Error: tidak dapat membuka file!\n");
    return;
  }

  helperSave(bstRoot, file);

  fclose(file);
}

void loadPenumpangCSV(BSTNode **bstRoot, AVLNode **avlRoot)
{
  FILE *file = fopen("penumpang.csv", "r");
  if (!file)
  {
    printf("Info: File penumpang.csv tidak ditemukan. Membuat file baru.\n");
    return;
  }

  int noPenumpang, idBus;
  char namaPenumpang[50];

  while (fscanf(file, "%d,%49[^,],%d\n", &noPenumpang, namaPenumpang, &idBus) != EOF)
  {
    *bstRoot = insertBST(*bstRoot, noPenumpang, namaPenumpang, idBus);
    *avlRoot = insertAVL(*avlRoot, noPenumpang, namaPenumpang, idBus);
  }

  fclose(file);
}

// ================ PROGRAM UTAMA ================
int main()
{
  system("color f0");
  printf("Program dimulai\n");

  BSTNode *bstRoot = NULL;
  AVLNode *avlRoot = NULL;

  printf("Memuat data bus dari CSV\n");
  loadBusCSV();
  printf("Selesai memuat data bus dari CSV\n");
  printf("Memuat data penumpang dari CSV\n");
  loadPenumpangCSV(&bstRoot, &avlRoot);
  printf("Selesai memuat data penumpang dari CSV\n");

  int mainMenu, busMenu, penumpangMenu;
  while (1)
  {
    system("cls");
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
      // Bus Menu
      system("cls");
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
        system("cls");
        tambahBus();
        saveBusCSV();
        system("pause");
        break;
      case 2:
        system("cls");
        displayBus();
        system("pause");
        break;
      case 3:
        system("cls");
        editBus();
        saveBusCSV();
        system("pause");
        break;
      case 4:
        system("cls");
        hapusBus();
        saveBusCSV();
        system("pause");
        break;
      case 5:
        printf("Keluar dari Bus Menu.\n");
        system("pause");
        break;
      default:
        printf("Pilihan tidak valid.\n");
        system("pause");
        break;
      }
      break;

    case 2:
      // Penumpang Menu
      system("cls");
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
        system("cls");
        tambahPenumpang(&bstRoot, &avlRoot);
        savePenumpangCSV(bstRoot);
        system("pause");
        break;
      }
      case 2:
      {
        system("cls");
        int noPenumpang, kategoriPencarian;
        printf("\n==============================\n");
        printf("\nMencari Penumpang\n");
        printf("\n==============================\n");
        printf("1. Binary Search Tree\n");
        printf("2. AVL Tree\n");
        printf("\nPilih metode pencarian: ");
        scanf("%d", &kategoriPencarian);

        switch (kategoriPencarian)
        {
        case 1:
          printf("\nMasukkan nomor penumpang: ");
          scanf("%d", &noPenumpang);
          cariPenumpangBST(bstRoot, noPenumpang);
          system("pause");
          break;
        case 2:
          printf("\nMasukkan nomor penumpang: ");
          scanf("%d", &noPenumpang);
          cariPenumpangAVL(avlRoot, noPenumpang);
          system("pause");
          break;
        default:
          printf("Pilihan tidak valid\n");
          system("pause");
        }
        break;
      }
      case 3:
      {
        system("cls");
        printf("\n==============================\n");
        printf("\nMenghapus Penumpang\n");
        printf("\n==============================\n");
        int noPenumpang;
        char namaPenumpang[50] = "";
        printf("Masukkan nomor penumpang yang akan dihapus: ");
        scanf("%d", &noPenumpang);

        bstRoot = deleteBST(bstRoot, noPenumpang, namaPenumpang);
        avlRoot = deleteAVL(avlRoot, noPenumpang, namaPenumpang);
        savePenumpangCSV(bstRoot);

        if (strlen(namaPenumpang) > 0)
          printf("Menghapus %d - %s dalam data Penumpang\n", noPenumpang, namaPenumpang);
        else
          printf("Nomor penumpang %d tidak ditemukan.\n", noPenumpang);
        system("pause");

        break;
      }
      case 4:
      {
        system("cls");
        int kategoriTree;
        printf("\n==============================\n");
        printf("\nMenampilkan Tree\n");
        printf("\n==============================\n");
        printf("1. Binary Search Tree\n");
        printf("2. AVL Tree\n");
        printf("\nPilih jenis tree:\n");
        scanf("%d", &kategoriTree);

        switch (kategoriTree)
        {
        case 1:
          system("cls");
          printf("\n========================================================================================================");
          printf("\n------------------------------------------In-Order Traversal BST----------------------------------------\n");
          printf("========================================================================================================\n");
          printf("| %-3s | %-20s | %-3s | %-3s | %-10s | %-20s | %-20s |\n", "No", "Nama", "Height", "Bus", "Posisi", "Tujuan", "Keberangkatan", "Kedatangan");
          printf("|-----|----------------------|--------|-----|------------|----------------------|----------------------|\n");
          if (bstRoot == NULL)
          {
            printf("BST kosong.\n");
          }
          else
          {
            inorderBST(bstRoot, "Root");
          }
          system("pause");
          break;
        case 2:
          system("cls");
          printf("\n========================================================================================================");
          printf("\n------------------------------------------In-Order Traversal AVL----------------------------------------\n");
          printf("========================================================================================================\n");
          printf("| %-3s | %-20s | %-3s | %-3s | %-10s | %-20s | %-20s |\n", "No", "Nama", "Height", "Bus", "Posisi", "Tujuan", "Keberangkatan", "Kedatangan");
          printf("|-----|----------------------|--------|-----|------------|----------------------|----------------------|\n");
          if (avlRoot == NULL)
          {
            printf("AVL Tree kosong.\n");
          }
          else
          {
            inorderAVL(avlRoot, "Root");
          }
          system("pause");
          break;
        default:
          printf("Pilihan tidak valid\n");
          system("pause");
        }
        break;
      }
      case 5:
        printf("Keluar dari Penumpang Menu.\n");
        system("pause");
        break;
      default:
        printf("Pilihan tidak valid.\n");
        system("pause");
        break;
      }
      break;

    case 3:
      printf("Keluar dari program.\n");
      savePenumpangCSV(bstRoot);
      saveBusCSV();
      system("pause");
      return 1;
      break;

    default:
      printf("Pilihan tidak valid.\n");
      system("pause");
    }
  }
  return 0;
}