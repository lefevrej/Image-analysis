#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mcimage.h>
#include <lw_averaging.h>

// return 1 the the point belong to the image, 0 otherwise
int belong_image(int i, int j, int rs, int cs){
    return i<cs && i>0 && j>0 && j<rs;
}

/* ==================================== */
uint32_t lw_averaging(struct xvimage **image, float *weights, uint32_t a, uint32_t b){
	uint32_t i, j, k;
	int32_t di, dj, ka, kb;
	uint8_t *ptrimage, *ptrimage2;
	float newval, k_sum;
	uint32_t rs, cs;
	struct xvimage *image2 = copyimage(*image);

	rs = (*image)->row_size;
	cs = (*image)->col_size;
  
    /*---------------------- start processing ----------------------*/
  	
	ptrimage = (uint8_t *)((*image)->image_data);
	ptrimage2 = (uint8_t *)(image2->image_data);
	
	/*k_sum = 0;
	for(i=0; i<a*b; ++i)
		k_sum+=weights[i];*/
		
	ka=a/2;
	kb=b/2;
	for(i=0; i<cs; ++i){
		for(j=0; j<rs; ++j){
			newval = 0;
			k = 0;
            k_sum = 0;
			for(di=-kb; di<kb+1; ++di){
				for(dj=-ka; dj<ka+1; ++dj){
                    if(belong_image(i+di, j+dj, rs, cs)){
					    newval+=weights[k]*ptrimage[j+dj+(i+di)*(rs)];
                        k_sum+=weights[k];
					    k++;
                    }
				}
			}
			newval/=k_sum;
			if (newval < NDG_MIN) newval = NDG_MIN;
			if (newval > NDG_MAX) newval = NDG_MAX;
			ptrimage2[j+i*(rs)]=(uint8_t)newval;
		}
	}
	
		
	freeimage(*image);
	*image = image2;
	
	return 1; /* Everythng went fine / tout s'est bien passe */
}





