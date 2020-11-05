#include <stdio.h>
#include <stdlib.h>
#include <mcimage.h>
#include <lcga.h> 
#include <pthread.h>

typedef struct params{
	int r;
	int f;
	int s;
	float kh;
	int w_wise;   
}params;

typedef struct oned{
	struct params *ps;
	struct xvimage **cimage;
}oned;

void *tcga(void *args){
	oned *t_oned = (oned*) args;
	params *t_p = (params*) t_oned->ps;
	if (!lcga(t_oned->cimage, t_p->r, t_p->f , t_p->s, t_p->kh, t_p->w_wise)){
    	fprintf(stderr, "w_averaging: function lw_averaging failed\n");
    	exit(1);
  	}
	return NULL;
}


int main(int argc, char **argv){
	struct xvimage **image;
	uint8_t rgb=0; // O if grayscale, 1 otherwise
	pthread_t threads[3]; //threads for rgb values
	oned color_d[3]; // data stuct for each thread
	params g_params; // global args as struct
	
	if(argc != 8){
		fprintf(stderr, "usage: %s img.pgm r_radius f_radius sigma k_sigma window-wise out.pgm  \n", argv[0]);
		exit(1);
	}
	
	image = malloc(3*sizeof(struct xvimage*));
	image[0] = readimage(argv[1]);	
	if (image[0] == NULL){
		printf("Try to read input as color image\n");
        readrgbimage(argv[1], &image[0], &image[1], &image[2]);
		rgb=1;
        if(image[0] == NULL){	
    	    fprintf(stderr, "cga: readimage failed\n");
    	    exit(1);
        }
		printf("Success\n");
  	}
	
    g_params.r = atoi(argv[2]); // read big radius
    g_params.f = atoi(argv[3]); // read little radius
    // assert r_radius > f_radius
    g_params.s = atoi(argv[4]); // read sigma
    g_params.kh = atof(argv[5]);	// read k for h=k*s
    g_params.w_wise = atoi(argv[6]); // 0 if pixel-wise, > 0 otherwise

	if(rgb==0){ // if grayscale image
		color_d[0] = (oned){&g_params, &image[0]};
		tcga((void*) &color_d[0]);
		writeimage(*image, argv[argc-1]);
  		freeimage(*image);
	} else { // if rgb image
		for(int i=0; i<3; ++i){
			color_d[i] = (oned){&g_params, &image[i]};
			pthread_create(&threads[i], NULL, tcga, (void*) &color_d[i]);
		}
		for(int i=0; i<3; ++i) pthread_join(threads[i], NULL);
		writergbimage(image[0], image[1], image[2], argv[argc-1]);
		for(int i=0; i<3; ++i) freeimage(image[i]);
	}
	return 0;
}