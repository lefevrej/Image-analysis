#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <mcimage.h>
#include <lequalize.h>
#include <string.h>

/* ==================================== */
uint32_t lequalize(struct xvimage *image/* input: images to process */  
                                           /* output: modified image  */       
             )
/* ==================================== */
{
  uint32_t indexpixel;
  uint8_t *ptrimage;
  double newval, N;
  uint32_t rs, cs, hist[256];

  rs = image->row_size;
  cs = image->col_size;
  N = rs * cs;
  
  /* ---------------------------------------------------------- */
  /* calcul du resultat */
  /* ---------------------------------------------------------- */
  	
	ptrimage = (uint8_t *)(image->image_data);
	memset(hist, 0, sizeof(uint32_t)*256);
	
	for(indexpixel=0; indexpixel<N; ++indexpixel)
		hist[ptrimage[indexpixel]]++;
		
	for(indexpixel=1; indexpixel<256; ++indexpixel)
		hist[indexpixel]+=hist[indexpixel-1];

	for(indexpixel=0; indexpixel<N; ++indexpixel){
		newval=(hist[ptrimage[indexpixel]]/N)*255.0;
		ptrimage[indexpixel] = (uint8_t)newval;
	}
	
  return 1; /* Everythng went fine / tout s'est bien passe */
}





