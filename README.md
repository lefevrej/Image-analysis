# Image analysis

Here you will find the implementation of different command line operators and in particular the implementation of the weighted averaging filter and the complete graph avareging.

The code is distributed in several directories: [lib](https://github.com/lefevrej/Image-analysis/tree/master/Pinkdev/src/lib) for the code of the libraries and [com](https://github.com/lefevrej/Image-analysis/tree/master/Pinkdev/src/com) for the executables.

To run the weighted averaging filter, you must provide a kernel. The format of this kernel is specified in this [example](https://github.com/lefevrej/Image-analysis/blob/master/images/gauss3x3.txt).

Below is an example of the execution of the weighted averaging filter "w_averaging" and of the complete graph averaging "cga" for a research window of radius 10, a small window of radius 2, sigma = 20, k = 0.4 to obtain h=0.4*sigma and 0 for the pixel-wise agorithm (1 for the window-wise).

```sh
$ w_averaging input.pgm kernel.txt output.pgm  
$ cga input.pgm 10 2 20 .4 0 output.pgm
```
