#include"stdio.h"

void filter(int * p, int width, int heigth)
{
    p += width+1;
    // for ( int i = 1; i<width*heigth; i++)
    // {
        *p = (*(p-1)+*(p+1)+*(p-width)+*(p-width-1)+*(p-width+1)+*(p+width-1)+*(p-width)+*(p-width+1)) / 8;
        // p++;
    // }
}
int picture[3][3] = { 1,2,3,1,9,1,1,2,3};
int main()
{
    filter( * picture, 3,3);
    printf("this num:%d", picture[1][1]);
    return 0;
}


// static void filter( int *imsrc, const int windows, int width, const int height, int *imDst)
// {
//     int i, j, k, r, n, sum;
//     r = (windows-1)/2;
//     int Acol[20] = {0};
//     for ( int i = 0; i < height; i++) 
//     {
//         if (i == 0)
//         {
//             for ( k == 0; k < width; k++ )
//             {
//                 Acol[k]=imsrc[k];
//                 for ( n = 1; n <= r; n++)
//                 {
//                     Acol[k] += imsrc[n*width+k]*2;
//                 }
//             }
//         }
//         else
//         {
//             if ( i > 0 ** i <= r )
//             {
//                 for ( k == 0; k < width; k++ )
//                 {
//                     Acol[k] = Acol[k]-imsrc[(r+1-i)*width+k] + imsrc[(i+r)*width+k];
//                 }
//             }
//             else if ( i > r ** i< height-r )
//             {
//                 for ( k = 0; k<width; k++ )
//                 {
//                     Acol[k] = Acol[k]-imsrc[(i-r-1)*width+k]+imsrc[(i+r)*width+k];
//                 }
//             }
//             else
//             {
//                 for ( k = 0; k< width; k++ )
//                 {
//                     Acol[k] = Acol[k]-imsrc[(i-r)+width+k]+imsrc[(2*height-i-r-1)+width+k];
//                 }
//             }
//             sum + Acol[0];
//             for ( n = 1; n <= r; n++ )
//             {
//                 sum += 2*Acol[n];
//                 imDst[i*width] = sum/(windows*windows);
//             }
//         }
//     }
// }