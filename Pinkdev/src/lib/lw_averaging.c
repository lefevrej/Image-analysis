#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mcimage.h>
#include <lw_averaging.h>

/* ==================================== */
uint32_t lw_averaging(struct xvimage **image,		/* input: images to process */
				 float *weights, uint32_t a, uint32_t b
                                   			/* output: modified image  */       
             )
/* ==================================== */
{
	uint32_t i, j, ik, jk, k, ka, kb;
	uint8_t *ptrimage, *ptrimage2;
	float newval, k_sum;
	uint32_t rs, cs;
	struct xvimage *image2 = copyimage(*image);

	rs = (*image)->row_size;
	cs = (*image)->col_size;
  
	/* ---------------------------------------------------------- */
	/* calcul du resultat */
	/* ---------------------------------------------------------- */
  	
	ptrimage = (uint8_t *)((*image)->image_data);
	ptrimage2 = (uint8_t *)(image2->image_data);
	
	k_sum = 0;
	for(i=0; i<a*b; ++i)
		k_sum+=weights[i];
		
	ka=a/2;
	kb=b/2;
	for(i=kb; i<rs-kb; ++i){
		for(j=ka; j<cs-ka; ++j){
			newval = 0;
			k = 0;
			for(ik= i-kb; ik<i+kb+1; ++ik){
				for(jk= j-ka; jk<j+ka+1; ++jk){
					newval+=weights[k]*ptrimage[jk+ik*(rs)];
					k++;
				}
			}
			newval = newval>255 ? 255 : newval;
			ptrimage2[j+i*(rs)]=newval<0 ? 0 : (uint8_t)newval;
		}
	}
	
		
	freeimage(*image);
	*image = image2;
	
	return 1; /* Everythng went fine / tout s'est bien passe */
}





