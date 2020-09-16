#include <stdio.h>
#include <stdlib.h>
#include <mcimage.h>
#include <lthreshold.h>
#include <math.h>

int main(int argc, char **argv){
	struct xvimage *image;
	uint32_t low_thr, high_thr; 

	if(argc != 5){
		fprintf(stderr, "usage: %s img.pgm low_thr high_thr out.pgm \n", argv[0]);
		exit(0);
	}

	image = readimage(argv[1]);
	
	if (image == NULL){
    	fprintf(stderr, "diffimage: readimage failed\n");
    	exit(0);
  	}
  	
  	low_thr = atoi(argv[2]);
  	high_thr = atoi(argv[3]);
	
	if (!lthreshold(image, low_thr, high_thr)){
    	fprintf(stderr, "diffimage: function lthreshold failed\n");
    	exit(0);
  	}

	writeimage(image, argv[argc-1]);
  	freeimage(image);
	return 0;
}
