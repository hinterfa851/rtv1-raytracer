#include "includes/rtv1.h"

void white_filler(d_mlx *box)
{
        int i;
        int j;

        i = 0;
        j = 0;
        while (i < 600)
        {
                while (j < 600)
                {
                        printf("%d\t %d\n", i, j);
                        *(int *)(box->color_arr + (i + j*600)*(box->bits_per_pixel/8)) = 0xFFFFFF;
                        j++;
                }
        j =0;
        i++;
        }
}



void make_circle(d_mlx *box, int i_pos, int j_pos, int r, int color)
{
        int i;
        int j;

        i = 0;
        j = 0;
        while (i < 600)
        {
                while (j < 600)
                {
//                      if ((i_pos - r < i) && (i_pos + r > i) && (j_pos - r < j) && (j_pos + r > j))
                        if ((i - i_pos) * (i - i_pos) + (j - j_pos) * (j - j_pos) < r*r)
                                *(int *)(box->color_arr + (i + j*600)*(box->bits_per_pixel/8)) = color;
                        j++;
                }
        j =0;
        i++;
        }
}
