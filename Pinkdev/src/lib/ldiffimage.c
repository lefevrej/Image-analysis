#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <mcimage.h>
#include <laddconst.h>

/* ==================================== */
uint32_t ldiffimage(struct xvimage * image1, struct xvimage * image2 /* input: images to process */  
                                           /* output: modified image  */       
             )
/* ==================================== */
{
  uint32_t indexpixel;
  uint8_t *ptrimage1, *ptrimage2;
  uint32_t newval;
  uint32_t rs, cs, N;

  rs = image1->row_size;
  cs = image1->col_size;
  N = rs * cs;
  
  /* ---------------------------------------------------------- */
  /* calcul du resultat */
  /* ---------------------------------------------------------- */

	ptrimage1 = (unsigned char *)(image1->image_data);
	ptrimage2 = (unsigned char *)(image2->image_data);

	for(indexpixel=0; indexpixel<N; ++indexpixel){
		newval = (uint32_t)abs(ptrimage1[indexpixel]-ptrimage2[indexpixel]);
		ptrimage1[indexpixel] = (uint8_t)newval;
	}

  return 1; /* Everythng went fine / tout s'est bien passe */
}





