#include <stdio.h>
#include <stdlib.h>
#include <mcimage.h>
#include <lw_averaging.h>

int main(int argc, char **argv){
	struct xvimage *image;
	uint32_t a, b, i;
	char *fname;
	FILE *fp;
	
	if(argc != 4){
		fprintf(stderr, "usage: %s kernel.txt out.pgm \n", argv[0]);
		exit(0);
	}
	
	image = readimage(argv[1]);	
	if (image == NULL){
    	fprintf(stderr, "w_averaging: readimage failed\n");
    	exit(0);
  	}
	
	fname = argv[2];
	if (fname == NULL){
    	fprintf(stderr, "w_averaging: cannot read filename\n");
    	exit(0);
  	}
	
	fp = fopen(fname,"r");
	
	// a rows and b columns
	fscanf(fp, "%d\n%d", &a, &b); 
	printf("%d lines, %d columns\n", a, b);
	
	float *kernel = malloc(a*b*sizeof(float*));
	for(i=0; i<a*b; ++i)
		fscanf(fp, "%f", &kernel[i]);
	for(i=0; i<a*b; ++i)
		printf("%f\n", kernel[i]);
	
	if(fp==NULL){
		fprintf(stderr, "w_averaging: Can't open input file %s!", fname);
		exit(0);
	}
	
				



  	
	if (!lw_averaging(&image, kernel ,3, 3)){
    	fprintf(stderr, "w_averaging: function lw_averaging failed\n");
    	exit(0);
  	}

	writeimage(image, argv[argc-1]);
  	freeimage(image);
  	free(kernel);
	return 0;
}
