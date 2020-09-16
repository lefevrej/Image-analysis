#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <mcimage.h>
#include <lnormalize.h>

/* ==================================== */
uint32_t lnormalize(struct xvimage *image,/* input: images to process */  
        uint32_t low_l,
        uint32_t high_l 
                                           /* output: modified image  */       
             )
/* ==================================== */
{
  uint32_t indexpixel;
  uint8_t *ptrimage;
  uint8_t newval;
  uint32_t rs, cs, N;
  uint32_t min=255, max=0;

  rs = image->row_size;
  cs = image->col_size;
  N = rs * cs;
  
  /* ---------------------------------------------------------- */
  /* calcul du resultat */
  /* ---------------------------------------------------------- */
	ptrimage = (uint8_t *)(image->image_data);
	for(indexpixel=0; indexpixel<N; ++indexpixel){
		min = ((uint8_t)ptrimage[indexpixel])<min ? (uint8_t)ptrimage[indexpixel] : min;
		max = ((uint8_t)ptrimage[indexpixel])>max ? (uint8_t)ptrimage[indexpixel] : max;
		
	}

	for(indexpixel=0; indexpixel<N; ++indexpixel){
		newval = (uint8_t)(((uint32_t)ptrimage[indexpixel]) - min)*(high_l-low_l)/(max-min)+low_l;
		ptrimage[indexpixel] = newval;
	}

  return 1; /* Everythng went fine / tout s'est bien passe */
}





