#include <iostream>
using namespace std;

int main(){
    // 1D Array
    // int n;
    // cin>>n;
    // int *D = new int [n];

    // // 2D Array 
    // int n,m;
    // cin>>n>>m;
    // int **D2 = new int *[n];
    // for(int i=0; i<n; i++){
    //     *D2 = new int [m];
    // }

    // 3D Array
    // int i, j, k;
    // cin >> i >> j >> k;

    // // Allocate
    // int ***dDA = new int**[i];
    // for(int x = 0; x < i; x++) {
    //     dDA[x] = new int*[j];
    //     for(int z = 0; z < j; z++) {
    //         dDA[x][z] = new int[k];
    //     }
    // }
    // // Fill
    // for(int r = 0; r < i; r++) {
    //     for(int u = 0; u < j; u++) {
    //         for(int p = 0; p < k; p++)
    //             dDA[r][u][p] = r + u + p;
    //     }
    // }
    // // Print
    // for(int r = 0; r < i; r++) {
    //     for(int u = 0; u < j; u++) {
    //         for(int p = 0; p < k; p++)
    //             cout << dDA[r][u][p] << " ";
    //         cout << endl;
    //     }
    //     cout << endl;
    // }
    // // Proper Deallocation
    // for(int x = 0; x < i; x++) {
    //     for(int z = 0; z < j; z++) {
    //         delete[] dDA[x][z];   // delete k-sized array
    //     }
    //     delete[] dDA[x];          // delete j-sized pointer array
    // }
    // delete[] dDA;                 // delete i-sized pointer array

    // 4D Array
    int i, j, k, u;
    cin>>i>>j>>k>>u;
    
    int ****D4 = new int ***[i];
    int a,b,c,d;
    for(a=0; a<i; a++){
        D4[a] = new int **[j];
        for(b=0; b<j; b++){
            D4[a][b] = new int *[k];
            for(c=0; c<k; c++){
                D4[a][b][c] = new int[u];
            }
        }
    }
    for(a=0; a<i; a++){
        for(b=0; b<j; b++){
            for(c=0; c<k; c++){
                for(d=0; d<u; d++){
                    D4[a][b][c][d] = a+b+c+d;
                }
            }
        }
    }
    for(a=0; a<i; a++){
        for(b=0; b<j; b++){
            for(c=0; c<k; c++){
                for(d=0; d<u; d++){
                    cout<< D4[a][b][c][d]<<" ";
                }
                cout<<endl;
            }
            cout<<endl;
        }
        cout<<endl;
    }
    for(a=0; a<i; a++){
        for(b=0; b<j; b++){
            for(c=0; c<k; c++){
                delete[] D4[a][b][c];
            }
            delete[] D4[a][b];
        }
        delete[] D4[a];
    }
    delete[] D4;
    return 0;
}