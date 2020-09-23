#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mcimage.h>
#include <lpow_law.h>

/* ==================================== */
uint32_t lpow_law(struct xvimage *image,		/* input: images to process */
				 uint32_t cst, float p  
                                   			/* output: modified image  */       
             )
/* ==================================== */
{
	uint32_t indexpixel;
	uint8_t *ptrimage;
	uint32_t newval;
	uint32_t rs, cs, N;

	rs = image->row_size;
	cs = image->col_size;
	N = rs * cs;
  
	/* ---------------------------------------------------------- */
	/* calcul du resultat */
	/* ---------------------------------------------------------- */
  	
	ptrimage = (uint8_t *)(image->image_data);

	for(indexpixel=0; indexpixel<N; ++indexpixel){
		newval=cst*pow(ptrimage[indexpixel], p);
		ptrimage[indexpixel] = newval>255 ? 255 : (uint8_t)newval;
	}
	
	return 1; /* Everythng went fine / tout s'est bien passe */
}





