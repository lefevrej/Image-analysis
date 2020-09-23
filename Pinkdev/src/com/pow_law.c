#include <stdio.h>
#include <stdlib.h>
#include <mcimage.h>
#include <lpow_law.h>

int main(int argc, char **argv){
	struct xvimage *image;
	uint32_t cst;
	float pow;
	
	if(argc != 5){
		fprintf(stderr, "usage: %s cst pow out.pgm \n", argv[0]);
		exit(0);
	}

	image = readimage(argv[1]);
	
	if (image == NULL){
    	fprintf(stderr, "pow_law: readimage failed\n");
    	exit(0);
  	}
  	
  	cst = atoi(argv[2]);
  	pow = atof(argv[3]);
	
	if (!lpow_law(image, cst, pow)){
    	fprintf(stderr, "pow_law: function lpow_law failed\n");
    	exit(0);
  	}

	writeimage(image, argv[argc-1]);
  	freeimage(image);
	return 0;
}
