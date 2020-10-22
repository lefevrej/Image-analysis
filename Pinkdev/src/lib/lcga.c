#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mcimage.h>
#include <lcga.h>

#define max(X,Y) ((X)>=(Y)?(X):(Y))

// return 1 the the point belong to the image, 0 otherwise
int belong_image(int i, int j, int rs, int cs){
	return i<cs && i>0 && j>0 && j<rs;
}


/* ==================================== */
uint32_t lcga(struct xvimage **image,		/* input: images to process */
			    int r_r, int f_r, uint32_t s, float kh, uint8_t w_wise
                                   			/* output: modified image  */       
             )
/* ==================================== */
{
	uint32_t ip, jp, rs, cs;
	int32_t di, dj, diw, djw, diq, djq, s_2, nb_f, nb_sf;
	uint8_t *ptrimage, *ptrimage2;
	float newval, sum_q, sum_w, d, w, h_2, av_q, av_p;
	struct xvimage *image2 = copyimage(*image);

	rs = (*image)->row_size;
	cs = (*image)->col_size;
	h_2 = powf(kh*s,2); // (k*sigma)**2
	s_2 = 2.0*pow(s,2); //2*sigma**2
	printf("s_2=%d, h_2=%f\n", s_2, h_2);
  
	/* ---------------------------------------------------------- */
	/* calcul du resultat */
	/* ---------------------------------------------------------- */
  	
	ptrimage = (uint8_t *)((*image)->image_data);
	ptrimage2 = (uint8_t *)(image2->image_data);

	int cnt=1;
	// pick p over the whole image
    for(ip=0; ip<cs; ++ip){
        for(jp=0; jp<rs; ++jp){
			sum_q=0.0;
			sum_w=0.0;

			if(ip*(rs-1)+jp > cnt*((cs*rs)/100)){
				printf("\rProgress: %d%%", cnt+1);
				fflush(0);
				cnt++;
			}

			// pick q in the big window around p
            for(diq=-r_r+f_r; diq<r_r-f_r+1; ++diq){
                for(djq=-r_r+f_r; djq<r_r-f_r+1; ++djq){
					d=0.0; //init distance between windows
					nb_f=0;
					// pick value in the small widow around p&q
					for(di=-f_r; di<f_r+1; ++di){
						for(dj=-f_r; dj<f_r+1; ++dj){
							if(belong_image(ip+di, jp+dj, rs, cs) && belong_image(ip+diq+di, jp+djq+dj, rs, cs)){
							//stack dist between windows
								if(w_wise!=0){ //if we are in the window-wise case
									av_q=0.0;
									av_p=0.0;
									nb_sf=0;
									for(diw=-f_r; diw<f_r+1; ++diw){
										for(djw=-f_r; djw<f_r+1; ++djw){
											if(belong_image(ip+di+diw, jp+dj+djw, rs, cs) && belong_image(ip+diq+di+diw, jp+djq+dj+djw, rs, cs)){
												av_q+=ptrimage[(ip+diq+di+diw)*rs+jp+djq+dj+djw];
												av_p+=ptrimage[(ip+di+diw)*rs+jp+dj+djw];
												nb_sf++;//increment the number of elements processed in the second window
											}
										}
									}
									av_q/=nb_sf;
									av_p/=nb_sf;
								} else {//pixel-wise case
									av_q=ptrimage[(ip+diq+di)*rs+jp+djq+dj];
									av_p=ptrimage[(ip+di)*rs+jp+dj];
								}
								nb_f++;//increment the number of elements processed in the window
								d+=powf(av_p-av_q, 2);
							}	
						}
					}
					if(nb_f!=0){
						d/=nb_f;
						w=expf( -max( d-s_2, 0.0 ) / h_2 );
						sum_q += ptrimage[(ip+diq)*rs+jp+djq]*w;
						sum_w += w;
					}					
                }
            }
			newval = (1.0/sum_w)*sum_q;
			if (newval < NDG_MIN) newval = NDG_MIN;
			if (newval > NDG_MAX) newval = NDG_MAX;
			ptrimage2[ip*rs+jp]=(uint8_t)newval;
        }
    }		
	freeimage(*image);
	*image = image2;
	
	return 1; /* Everythng went fine / tout s'est bien passe */
}