# Gauss

Implementation of Gaussian elimination with partial pivoting, in Pthread and OpenMP.

- To build the programs, use
  
  `$ make` (or `$ make all `)

- To remove all the generated files after building, use
  
  `$ make clean`

- After building, three programs (gauss_seq, gauss_pth, gauss_omp) will be made in the bin folder. They receive two arguments like
  
  `$ bin/gauss_omp 2000 8`
  
  where the first argument is the problem size (i.e dimension of the matrix), and the second argument is the number of threads.

- This is for KAIST 2016 CS492 'Analysis of Concurrent Program'.

ex. Running `gauss_XXX 3000 4` on my computer...

![Screenshot](https://raw.githubusercontent.com/Avantgarde95/Gauss/master/Screenshot.png)
