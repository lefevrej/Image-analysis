#include <stdio.h>
#include <stdlib.h>
#include <mcimage.h>
#include <lcga.h>

int main(int argc, char **argv){
	struct xvimage *image;
    float kh;
    int r_radius, f_radius, s, w_wise; 
	
	if(argc != 8){
		fprintf(stderr, "usage: %s img.pgm r_radius f_radius sigma k_sigma window-wise out.pgm  \n", argv[0]);
		exit(1);
	}
	
	image = readimage(argv[1]);	
	if (image == NULL){
    	fprintf(stderr, "cga: readimage failed\n");
    	exit(1);
  	}
	
    r_radius = atoi(argv[2]); // read big radius
    f_radius = atoi(argv[3]); // read little radius
    // assert r_radius > f_radius
    s = atoi(argv[4]); // read sigma
    kh = atof(argv[5]);	// read k for h=k*s
    w_wise = atoi(argv[6]); // 0 if pixel-wise, > 0 otherwise

    printf("r=%d, rf=%d, s=%d, k=%f, w_wise=%d\n", r_radius, f_radius, s, kh, w_wise);
  	
	if (!lcga(&image, r_radius, f_radius ,s, kh, w_wise)){
    	fprintf(stderr, "w_averaging: function lw_averaging failed\n");
    	exit(1);
  	}

	writeimage(image, argv[argc-1]);
  	freeimage(image);
	return 0;
}