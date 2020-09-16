#include <stdio.h>
#include <stdlib.h>
#include <mcimage.h>
#include <ldiffimage.h>
#include <math.h>

int main(int argc, char **argv){
	struct xvimage	*image1, *image2;

	if(argc != 4){
		fprintf(stderr, "usage: %s img1.pgm img2.pgm out.pgm \n", argv[0]);
		exit(0);
	}

	image1 = readimage(argv[1]);
	// handle error
	image2 = readimage(argv[2]);
	// handle error
	
	if (image1 == NULL || image2 == NULL){
    	fprintf(stderr, "diffimage: readimage failed\n");
    	exit(0);
  	}
  	
  	if (image1->row_size!=image2->row_size || image1->col_size!=image2->col_size){
    	fprintf(stderr, "diffimage: readimage failed\n");
    	exit(0);
  	}
	
	if (!ldiffimage(image1, image2)){
    	fprintf(stderr, "diffimage: function ldiffimage failed\n");
    	exit(0);
  	}

	writeimage(image1, argv[argc-1]);
  	freeimage(image1);
  	freeimage(image2);
	return 0;
}
