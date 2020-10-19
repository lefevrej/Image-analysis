#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mcimage.h>
#include <lcga.h>

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })


/* ==================================== */
uint32_t lcga(struct xvimage **image,		/* input: images to process */
			    int r_r, int f_r, uint32_t s, float kh
                                   			/* output: modified image  */       
             )
/* ==================================== */
{
	printf("r=%d, rf=%d, s=%d, k=%f\n", r_r, f_r, s, kh);

	uint32_t ip, jp, rs, cs;
	int32_t di, dj, diq, djq, s_2;
	uint8_t *ptrimage, *ptrimage2;
	float newval, sum_q, sum_w, d, w, h_2, nb_f;
	struct xvimage *image2 = copyimage(*image);

	rs = (*image)->row_size;
	cs = (*image)->col_size;
	printf("nb pixels=%d, %dx%d\n", cs*rs, cs, rs);
	h_2 = powf(kh*s,2); // (k*sigma)**2
	s_2 = 2.0*pow(s,2); //2*sigma**2
	printf("random=%d\n",(int)powf(2.0*f_r+1, 2));
	nb_f = powf(2.0*f_r+1, 2); //number of pixels in f_radius
	printf("s_2=%d, h_2=%f, nb_f=%d\n", s_2, h_2, (int)nb_f);
  
	/* ---------------------------------------------------------- */
	/* calcul du resultat */
	/* ---------------------------------------------------------- */
  	
	ptrimage = (uint8_t *)((*image)->image_data);
	ptrimage2 = (uint8_t *)(image2->image_data);

	int cnt=1, cnt2=0;
    for(ip=r_r; ip<cs-r_r; ++ip){
        for(jp=r_r; jp<rs-r_r; ++jp){
			if(ip==jp && ip==r_r) printf("p\n");
			sum_q=0.0;
			sum_w=0.0;

			if(ip*(rs-1)+jp > cnt*(((cs-r_r)*cs+cs-r_r)/100)){
				printf("%d%%\n", cnt);
				cnt++;
			}
			//printf("%d\n", ip*rs+jp);

			if(ip==jp && ip==r_r) printf("%d -> %d\n", -r_r+f_r, r_r-f_r+1);
			diq=-r_r+f_r;
			if(ip==jp && ip==r_r) printf("diq=%d\n", diq);

            for(diq=-r_r+f_r; diq<r_r-f_r+1; ++diq){
				//printf("diq\n");
                for(djq=-r_r+f_r; djq<r_r-f_r+1; ++djq){
                    d=0.0; //init distance between windows
					//printf("q\n");
                    for(di=-f_r; di<f_r+1; ++di){
                        for(dj=-f_r; dj<f_r+1; ++dj){
							//printf("index q=%d\n", (ip+diq+di)*rs+jp+djq+dj);
							//fflush(0);

							//stack dist between windows
                            d+=powf(ptrimage[(ip+di)*rs+jp+dj]-ptrimage[(ip+diq+di)*rs+jp+djq+dj], 2);
							/*if(cnt2%((int)powf(2.0*f_r+1, 2))==0){
								printf("d=%f\n", d);
							}*/

							cnt2++;
                        }
                    }
					d/=nb_f;
					//printf("d=%f\n", d);
					w=expf(-max( d-s_2, 0.0 ) / h_2 );
					/*if(d-s_2<10.0){
						printf("houra -> w=%f, d=%f\n", w, d);
					}*/
					//printf("w=%f\n", w);
					sum_q += ptrimage[(ip+diq)*rs+jp+djq]*w;
					sum_w += w;
                }
            }
			if(ip==jp && ip==r_r) printf("write\n");
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





