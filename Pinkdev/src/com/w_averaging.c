#include <stdio.h>
#include <stdlib.h>
#include <mcimage.h>
#include <lw_averaging.h>
#include <pthread.h>

typedef struct data_dim{
    float *kernel;
    struct xvimage **cimage;
    uint32_t a,b;
} data_dim;

void *twa(void *args){
	data_dim *color_d = (data_dim*) args;
	if (!lw_averaging(color_d->cimage, color_d->kernel, color_d->a, color_d->b)){
    	fprintf(stderr, "w_averaging: function lw_averaging failed\n");
    	exit(1);
  	}
	return NULL;
}

int main(int argc, char **argv){
    struct xvimage **image;
    pthread_t threads[3]; //threads for rgb values
    data_dim color_d[3];
    float *kernel;
    uint8_t rgb=0; // O if grayscale, 1 otherwise
    uint32_t a, b, i;
    FILE *fp;

    if (argc != 4){
        fprintf(stderr, "usage: %s img.pgm kernel.txt out.pgm \n", argv[0]);
        exit(1);
    }

    /*---------------------- read image ----------------------*/
    image = malloc(3*sizeof(struct xvimage*));
	image[0] = readimage(argv[1]);	
	if (image[0] == NULL){
		printf("Try to read input as color image\n");
        readrgbimage(argv[1], &image[0], &image[1], &image[2]);
		rgb=1;
        if(image[0] == NULL){	
    	    fprintf(stderr, "w_averaging: readimage failed\n");
    	    exit(1);
        }
		printf("Success\n");
  	}   

    /*---------------------- read kernel ----------------------*/
    if((fp = fopen(argv[2], "r")) == NULL){
        fprintf(stderr, "w_averaging: Can't open input file %s!", argv[2]);
        exit(1);
    }
    fscanf(fp, "%d\n%d", &a, &b); // a rows and b columns
    kernel = malloc(a*b*sizeof(float*));
    for (i=0; i<a*b; ++i) fscanf(fp, "%f", &kernel[i]);

    /*---------------------- processing ----------------------*/
	if(rgb==0){ // if grayscale image
		color_d[0] = (data_dim){kernel, &image[0], a, b};
		twa((void*) &color_d[0]);
		writeimage(*image, argv[argc-1]);
  		freeimage(*image);
	} else { // if rgb image
		for(int i=0; i<3; ++i){
			color_d[i] = (data_dim){kernel, &image[i], a, b};
			pthread_create(&threads[i], NULL, twa, (void*) &color_d[i]);
		}
		for(int i=0; i<3; ++i) pthread_join(threads[i], NULL);
		writergbimage(image[0], image[1], image[2], argv[argc-1]);
		for(int i=0; i<3; ++i) freeimage(image[i]);
	}
    free(kernel);
    return 0;
}