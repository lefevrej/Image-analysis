#include <stdio.h>
#include <stdlib.h>
#include <mcimage.h>
#include <llog.h>

int main(int argc, char **argv){
	struct xvimage *image;
	uint32_t cst;
	
	if(argc != 4){
		fprintf(stderr, "usage: %s cst out.pgm \n", argv[0]);
		exit(0);
	}

	image = readimage(argv[1]);
	
	if (image == NULL){
    	fprintf(stderr, "log: readimage failed\n");
    	exit(0);
  	}
  	
  	cst = atoi(argv[2]);
	
	if (!llog(image, cst)){
    	fprintf(stderr, "log: function llog failed\n");
    	exit(0);
  	}

	writeimage(image, argv[argc-1]);
  	freeimage(image);
	return 0;
}
