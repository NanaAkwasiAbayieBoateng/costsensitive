#include <R.h>
#include <R_ext/Print.h>
#include <Rinternals.h>
#include <Rmath.h>
#include <stdlib.h>
#include <stddef.h>

int calculate_V(double C[], double V[], size_t nrow, size_t ncol, int nthreads);

SEXP r_calc_v(SEXP C, SEXP V, SEXP nrow, SEXP ncol)
{
	size_t n_row = (size_t) INTEGER(nrow)[0];
	size_t n_col = (size_t) INTEGER(ncol)[0];
	double *V_arr = (double*) malloc(sizeof(double) * n_row * n_col);
	double *C_arr = (double*) malloc(sizeof(double) * n_row * n_col);
	double *C_ptr = (double*) REAL(C);
	double *V_ptr = (double*) REAL(V);
	if (V_arr == NULL || C_arr == NULL) {
		REprintf("Could not allocate enough memory for the procedure");
		return EXIT_FAILURE;
	}
	size_t ntot = n_row * n_col;
	for (size_t i = 0; i < ntot; i++) {
		C_arr[i] = C_ptr[i];
	}

	int failed = calculate_V(C_arr, V_arr, n_row, n_col, 1);
	if (failed) {
		REprintf("Could not allocate enough memory for the procedure");
		free(C_arr);
		free(V_arr);
		return EXIT_FAILURE;
	}

	for (size_t i = 0; i < ntot; i++) {
		V_ptr[i] = V_arr[i];
	}
	free(C_arr);
	free(V_arr);
	return EXIT_SUCCESS;
}
