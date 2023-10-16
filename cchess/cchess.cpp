#include <bits/stdc++.h>

#define inRange(x, y) (x >= 0 && x < 8 && y >= 0 && y < 8)
#define calculaDistancia(a, b, c, d) (a * c) + (b * d)

using namespace std;

int tabuleiro[8][8];

int procurarMenorCaminho(int a, int b, int c, int d){
    queue<int> q;
    q.push(a);
    q.push(b);
    while(!q.empty()){
        int x = q.front();
        q.pop();
        int y = q.front();
        q.pop();
        int a[] = {-1, -2, -2, -1, 1, 2, 2, 1};
        int b[] = {-2, -1, 1, 2, 2, 1, -1, -2};
        for(int i=0;i<8;i++){
            int tmpX = x + a[i];
            int tmpY = y + b[i];
            if(inRange(tmpX, tmpY) && tabuleiro[tmpX][tmpY] > tabuleiro[x][y] + calculaDistancia(x, y, tmpX, tmpY)){
                tabuleiro[tmpX][tmpY] = tabuleiro[x][y] + calculaDistancia(x, y, tmpX, tmpY);
                q.push(tmpX);
                q.push(tmpY);
            }
        }
    }

    if (tabuleiro[c][d] == 1000000001) {
        return -1;
    } 

    return tabuleiro[c][d];
}

int main(){
    int a, b, c, d;
    while(scanf("%d%d%d%d", &a, &b, &c, &d) != EOF){
        for(int i=0;i<8;i++)
            for(int j=0;j<8;j++)
                tabuleiro[i][j] = 1000000001;
        tabuleiro[a][b] = 0;
        printf("%d\n", procurarMenorCaminho(a, b, c, d));
    }
    return 0;
}
