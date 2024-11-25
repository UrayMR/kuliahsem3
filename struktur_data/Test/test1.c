#include <stdio.h>

int kombinasi(int n, int r)
{
    if (r == 0 || r == n)
        // Syarat Segitiga pascal
        // Apabila r = 0 atau r = n, maka = 1
        return 1;
    else
        // Rekursif apabila r != 0 atau != n, maka
        // Call fungsi kombinasi dengan (n = n - 1, r = r - 1 ) + kombinasi dengan (n= n-1 , r)
        return kombinasi(n - 1, r - 1) + kombinasi(n - 1, r);
    // Misal.. untuk baris 3
    // Maka loop k = 0; k <= i (baris) dengan kombinasi(i, k) yang i=n , dan k=r
    // baris 3 =
    // call 1 dengan k = 0 ; kombinasi (3,0) ; 1
    // call 2 dengan k = 1 ; kombinasi (3,1) ; kombinasi(3-1 , 1-1) + kombinasi(3-1 , 1) ; 1 + kombinasi(2,1)
    // 1 + kombinasi (2,1) = 1 + (kombinasi(1,0) + kombinasi(1-1)) = 1 + 1 = 2
    // call 3 dengan k = 2 ; kombinasi (3,2) ; kombinasi(3-1, 2-1) + kombinasi(3-1,2) ;
    // kombinasi(2,1) + kombinasi(2,2) ; kombinasi(2-1, 1-1) + 1; 1 + 1 = 2
    // call 4 dengan k = 3 ; kombinasi (3,3) ; 1

    // 1 2 2 1
}

void main()
{
    int n;
    printf("Masukkan jumlah baris segitiga Pascal: ");
    scanf("%d", &n);

    // Looping per baris
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i; j++)
        {
            // Looping untuk mengisi space kosong apabila j(index) < jumlah baris - baris
            // Misal, n = 3
            // Untuk baris 1 dengan n = 3, space kosong sebanyak 3 - 1 = 2 space kosong
            printf(" ");
        }

        for (int k = 0; k <= i; k++)
        {
            // Looping untuk kombinasi segitiga pascal (bagian center)
            printf("%d ", kombinasi(i, k));
        }

        // untuk spasi ketika baris tersebut sudah kelar isinya
        printf("\n");
    }
}
