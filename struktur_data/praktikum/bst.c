#include <stdio.h>
#include <stdlib.h>
// Struktur untuk node pada tree
struct Node
{
  int data;
  struct Node *left;
  struct Node *right;
};
// Fungsi untuk membuat node baru
struct Node *newNode(int data)
{
  struct Node *node = (struct Node *)malloc(sizeof(struct Node));
  node->data = data;
  node->left = NULL;
  node->right = NULL;
  return node;
}
// Fungsi untuk menyisipkan node baru ke dalam BST
struct Node *insert(struct Node *node, int data)
{
  if (node == NULL)
  {
    return newNode(data);
  }
  if (data < node->data)
  {
    node->left = insert(node->left, data);
  }
  else if (data > node->data)
  {
    node->right = insert(node->right, data);
  }
  return node;
}
// Fungsi untuk mencari node dalam BST
struct Node *search(struct Node *root, int data)
{
  if (root == NULL || root->data == data)
  {
    return root;
  }
  if (data < root->data)
  {
    return search(root->left, data);
  }
  return search(root->right, data);
}
// Fungsi untuk inorder traversal (mengunjungi node dari terkecil ke terbesar)
void inorderTraversal(struct Node *root)
{
  if (root != NULL)
  {
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
  }
}
// Fungsi utama

int main()
{
  struct Node *root = NULL;
  root = insert(root, 50);
  insert(root, 30);
  insert(root, 20);
  insert(root, 40);
  insert(root, 70);
  insert(root, 60);
  insert(root, 80);
  printf("Inorder traversal dari BST:\n");
  inorderTraversal(root);
  int key = 40;
  struct Node *result = search(root, key);

  if (result != NULL)
  {
    printf("\nNode dengan data %d ditemukan.\n", key);
  }
  else
  {
    printf("\nNode dengan data %d tidak ditemukan.\n", key);
  }
  return 0;
}
