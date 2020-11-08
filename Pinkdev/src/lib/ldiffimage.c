#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <mcimage.h>
#include <laddconst.h>

uint32_t ldiffimage(struct xvimage * image1, struct xvimage * image2){
    float max = 0.0;
    uint32_t indexpixel, newval, rs, cs, N;
    uint8_t *ptrimage1, *ptrimage2;

    rs = image1->row_size;
    cs = image1->col_size;
    N = rs * cs;
    
    /*---------------------- start processing ----------------------*/

    ptrimage1 = (unsigned char *)(image1->image_data);
    ptrimage2 = (unsigned char *)(image2->image_data);

    for(indexpixel=0; indexpixel<N; ++indexpixel){
        newval = (uint32_t)abs(ptrimage1[indexpixel]-ptrimage2[indexpixel]);
        max = max < newval ? newval : max;
        ptrimage1[indexpixel] = (uint8_t) newval;
    }

    /*---------------------- write and shift to range [0-255] ----------------------*/
    for(indexpixel=0; indexpixel<N; ++indexpixel)
        ptrimage1[indexpixel] = (uint8_t)(ptrimage1[indexpixel]*(255.0/max));   

    return 1; /* Everything went fine */
}