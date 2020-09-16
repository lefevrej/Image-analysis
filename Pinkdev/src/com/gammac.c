#include <stdio.h>
#include <stdlib.h>
#include <mcimage.h>
#include <lgammac.h>
#include <math.h>

int main(int argc, char **argv){
	struct xvimage *image;
	float gamma;

	if(argc != 4){
		fprintf(stderr, "usage: %s gamma out.pgm \n", argv[0]);
		exit(0);
	}

	image = readimage(argv[1]);
	
	if (image == NULL){
    	fprintf(stderr, "diffimage: readimage failed\n");
    	exit(0);
  	}
  	
  	gamma = atof(argv[2]);
	
	if (!lgammac(image, gamma)){
    	fprintf(stderr, "diffimage: function lgamma failed\n");
    	exit(0);
  	}

	writeimage(image, argv[argc-1]);
  	freeimage(image);
	return 0;
}
