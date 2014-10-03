#include <iostream>
#include <limits.h>
using namespace std;
#include <cstddef>  // size_t

int ** array(size_t md, size_t nd) {
    int ** m = new int * [md];
    m[0] = new int [md * nd];
    size_t i = 0;
    for (i = 1; i != md; ++i) {
        m[i] = m[i - 1] + nd;
        for ( size_t j = 0; j != nd; j++)
           m[i][j] = 0;
    };
    return m;
}

int ** transpose(const int * const * m, size_t r, size_t c) {
    // put your code here
    int ** res = array(r, c);
    size_t i = 0;
    for(;i<r;i++)
        for(int j = 0;j<c;j++)
           res[i][j] = m[j][i];
    return res;
}

int getMinElem(int * line, int n) {
    int minCand = INT_MAX;
    int minTmp = 0;
    for(int i = 0;i<n;i++)
        if (line[i] < minCand)
            minCand = line[i];
    return minCand;
}

void swap_min(int **mt, int m, int n) {
    int * tmp = 0;
    int minCand = INT_MAX;
    int minTmp = 0;
    int minIndex = 0;
    for (int i = 0; i != m; i++) {
        minTmp = getMinElem(mt[i], n);
        if (minTmp < minCand) {
            minCand = minTmp;
            minIndex = i;
        };
    };
    if (minIndex) {
        tmp = mt[0];
        mt[0] = mt[minIndex];
        mt[minIndex] = tmp;
    };
}

int main() {
    size_t md = 5;
    size_t nd = 4;
    int ** m = array(md, nd);
    m[0][0] = 4; m[0][1] = 5; m[0][2] = 6; m[0][3] = 7;
    m[2][0] = 3; m[2][1] = 2; m[2][2] = 6; m[2][3] = 1;

    int ** tm = transpose(m, nd, md);
    size_t i = 0;
    for(;i<nd;i++) {
        for(size_t j = 0;j<md;j++)
           printf("%d", tm[i][j]);
        printf("\n");
    };
}