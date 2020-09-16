#include <stdio.h>
#include <stdlib.h>
#include <mcimage.h>
#include <linverse.h>
#include <math.h>

int main(int argc, char **argv){
	struct xvimage *image;

	if(argc != 3){
		fprintf(stderr, "usage: %s out.pgm \n", argv[0]);
		exit(0);
	}

	image = readimage(argv[1]);
	
	if (image == NULL){
    	fprintf(stderr, "diffimage: readimage failed\n");
    	exit(0);
  	}
  	
	
	if (!linverse(image)){
    	fprintf(stderr, "diffimage: function linverse failed\n");
    	exit(0);
  	}

	writeimage(image, argv[argc-1]);
  	freeimage(image);
	return 0;
}
