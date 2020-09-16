#include <stdio.h>
#include <stdlib.h>
#include <mcimage.h>
#include <lnormalize.h>
#include <math.h>

int main(int argc, char **argv){
	struct xvimage *image;
	uint32_t low_l, high_l; 

	if(argc != 5){
		fprintf(stderr, "usage: %s img.pgm low_l high_l out.pgm \n", argv[0]);
		exit(0);
	}

	image = readimage(argv[1]);
	
	if (image == NULL){
    	fprintf(stderr, "diffimage: readimage failed\n");
    	exit(0);
  	}
  	
  	low_l = atoi(argv[2]);
  	high_l = atoi(argv[3]);
	
	if (!lnormalize(image, low_l, high_l)){
    	fprintf(stderr, "diffimage: function lnormalize failed\n");
    	exit(0);
  	}

	writeimage(image, argv[argc-1]);
  	freeimage(image);
	return 0;
}
