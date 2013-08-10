#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char** argv) {
	int cant;
	float x , y , xn , yn ;
	const char * archivo1 = "salida.grande.txt" ;
	char archivo2[100];

	FILE * file1 = fopen(archivo1, "r");

	cant = 2;
	while (cant == 2) {
		cant = fscanf(file1, "Solution: (%f,%f" , &x , &y );
		fscanf(file1, "%*[^\n]\n" );

		fscanf(file1, " F=%s" , &archivo2[0]);
		fscanf(file1, "%*[^\n]\n" );

		int len =  strlen(&archivo2[0]);

		archivo2[len - 2] = 'c' ;
		archivo2[len - 1] = 'k' ;

		FILE * file2 = fopen(archivo2, "r");

		fscanf(file2 , "DEVICE:\t\tx=%f\t\ty=%f" , &xn , &yn) ;

		float dx = x - xn;
		float dy = y - yn;

		float error = sqrt(pow(dx,2) + pow(dy, 2));

		printf("x=%f xn=%f y=%f yn=%f\n", x, xn, y, yn);
		printf("F=%s error=%f\n", archivo2 , error);


		fclose(file2);
	}



	fclose(file1);



}
