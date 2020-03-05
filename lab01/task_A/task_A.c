/* task_A.c
 *
 * Calvin Skinner
 * Susan Hasting
 *
 * Description: Print hello world multiple time in a for loop
 * 	based on the size of int and long. One for loop for
 *	size of int and another for loop for size of long.
 */

#include <stdio.h> // library for printf()

int main(int argc, char *argv[]){

//	Print "HELLO WORLD" every loop where i is zero to size of int.
//	sizeof() return number of bytes.
	printf("Size of int: %d\n", (int)sizeof(int));
	for (int i=1; i<=sizeof(int); i++){
		printf("%d: HELLO WORLD\n", (int)i);
	}
	
//	Make things look nice and good
	printf("\n\n");

//	sizeof(long)...
	printf("Size of long: %d\n", (int)sizeof(long));
	for (int i=1; i<=sizeof(long); i++){
		printf("%d: HELLO WORLD\n", (int)i);
	}

//	Return 0 because I have believe this program has no errors
	return 0;
}
