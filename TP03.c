#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define ROWS 800
#define COLS 800

int arr[ROWS][COLS];

void extrema(int t[], int taille, int *min, int *max) {
	*min = t[0];
	*max = t[0];
	for (int k= 0; k<taille;k++) {
		if (t[k]<*min) {
			*min = t[k];}
		if (t[k]>*max) {
			*max = t[k];}
	}
}



void incremente(int *p) {
	*p = *p +1;
}

struct complexe {
	double re;
	double im;
};

double module (struct complexe *z) {
	double modu = z->im*z->im + z->re*z->re;
	return modu;
};

void suivant(struct complexe *z,struct complexe *c) {
	struct complexe nvZ;
	nvZ. re = z->re*z->re -(z->im * z->im)+ c->re;
	nvZ.im = 2*z->re*z->im + c->im;
	*z = nvZ;
}

int divergence (struct complexe *c, int itermax) {
	struct complexe Z;
	Z.re =0;
	Z.im = 0;
	for (int n=0; n<=itermax;n++) {
		suivant(&Z, c);
		if (sqrt(module(&Z))>2) return n;
	}
	return itermax+1;
}

struct complexe indices2c(double i, double j) {
	struct complexe Z1;
	Z1.re = j;
	Z1.im = i;
	return Z1;
}

void remplir_tab(double xmin, double xmax, double ymin, double ymax, int itermax) {
	double distx = fabs(xmax-xmin);
	double disty = fabs(ymax-ymin);
	for (int y = 0;y<ROWS;y++) {
		for (int x= 0; x<COLS;x++) {
			double re = x * (double)distx/COLS + xmin;
			double im = y *(double)disty/ROWS+ymin;
			struct complexe Z = indices2c(im,re);
			arr[y][x]= divergence(&Z,itermax);
		}
 	}
}

void print_tab(int itermax) {
	printf("P2\n");
	printf("%d %d\n", COLS, ROWS);
	printf("%d\n", itermax);
	for (int y = 0; y<ROWS; y++) {
		for (int x = 0; x<COLS;x++) {
			printf("%d ", arr[y][x]);
		}
		printf("\n");
	}
}

int main (int argc, char* argv[]) {
	double xmin = -2;
	double ymin = -2;
	double xmax = 2;
	double ymax = 2;
	int itermax = 20;
	if (argc == 2) {
		itermax = atof(argv[1]);
	}
	if (argc == 6) {
		xmin = atof(argv[1]);
		xmax = atof(argv[2]);
		ymin = atof(argv[3]);
		ymax = atof(argv[4]);
		itermax = atoi(argv[5]);
	}
	remplir_tab(xmin,xmax,ymin,ymax,itermax);
	print_tab(itermax);
	return 0;
}


