#include <stdio.h>
#include <stdlib.h>
#include <mcimage.h>
#include <lcga.h> 
#include <pthread.h>

struct params{
	int r;
	int f;
	int s;
	float kh;
	int w_wise;   
} g_params;

struct oned{
	struct params *ps;
	struct xvimage **cimage;
};

void *tcga(void *args){
	struct oned *t_oned = (struct oned*) args;
	struct params *t_p = (struct params*) t_oned->ps;
	if (!lcga(t_oned->cimage, t_p->r, t_p->f , t_p->s, t_p->kh, t_p->w_wise)){
    	fprintf(stderr, "w_averaging: function lw_averaging failed\n");
    	exit(1);
  	}
	return NULL;
}


int main(int argc, char **argv){
	struct xvimage **image;
    //float kh;
	uint8_t rgb=0;
    //int r_radius, f_radius, s, w_wise; 
	pthread_t r_t, g_t;
	
	if(argc != 8){
		fprintf(stderr, "usage: %s img.pgm r_radius f_radius sigma k_sigma window-wise out.pgm  \n", argv[0]);
		exit(1);
	}
	
	image = malloc(3*sizeof(struct xvimage*));
	image[0] = readimage(argv[1]);	
	if (image[0] == NULL){
        readrgbimage(argv[1], &image[0], &image[1], &image[2]);
		rgb=1;
        if(image[0] == NULL){	
    	    fprintf(stderr, "cga: readimage failed\n");
    	    exit(1);
        }
  	}
	
    g_params.r = atoi(argv[2]); // read big radius
    g_params.f = atoi(argv[3]); // read little radius
    // assert r_radius > f_radius
    g_params.s = atoi(argv[4]); // read sigma
    g_params.kh = atof(argv[5]);	// read k for h=k*s
    g_params.w_wise = atoi(argv[6]); // 0 if pixel-wise, > 0 otherwise

    printf("r=%d, rf=%d, s=%d, k=%f, w_wise=%d\n", g_params.r, g_params.f, g_params.s, g_params.kh, g_params.w_wise);
  	
	struct oned r_d = {&g_params, &image[0]};
	struct oned g_d = {&g_params, &image[1]};
	struct oned b_d = {&g_params, &image[2]};
	pthread_create(&r_t, NULL, tcga, (void*) &r_d);
	pthread_create(&g_t, NULL, tcga, (void*) &g_d);

	tcga(&b_d);
	pthread_join(r_t, NULL);
	pthread_join(g_t, NULL);

	
	/*if (!lcga(&image, r_radius, f_radius ,s, kh, w_wise)){
    	fprintf(stderr, "w_averaging: function lw_averaging failed\n");
    	exit(1);
  	}*/

	if(rgb==0){
		printf("salope\n");
		writeimage(*image, argv[argc-1]);
  		freeimage(*image);
	} else {
		printf("bop\n");
		fflush(0);
		writergbimage(image[0], image[1], image[2], argv[argc-1]);
	}
	return 0;
}