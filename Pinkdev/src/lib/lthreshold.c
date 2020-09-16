#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <mcimage.h>
#include <lthreshold.h>

/* ==================================== */
uint32_t lthreshold(struct xvimage *image,/* input: images to process */  
        uint32_t low_thr,
        uint32_t high_thr 
                                           /* output: modified image  */       
             )
/* ==================================== */
{
  uint32_t indexpixel;
  uint8_t *ptrimage;
  uint8_t newval;
  uint32_t rs, cs, N;

  rs = image->row_size;
  cs = image->col_size;
  N = rs * cs;
  
  /* ---------------------------------------------------------- */
  /* calcul du resultat */
  /* ---------------------------------------------------------- */

	ptrimage = (uint8_t *)(image->image_data);
	for(indexpixel=0; indexpixel<N; ++indexpixel){
		newval = (uint8_t)ptrimage[indexpixel]>=low_thr && ptrimage[indexpixel]<=high_thr;
		ptrimage[indexpixel] = (uint8_t)newval*255;
	}

  return 1; /* Everythng went fine / tout s'est bien passe */
}





