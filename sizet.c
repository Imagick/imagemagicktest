#define MaxTextExtent 4096
#include <stddef.h>
#include <stdio.h>


void foo(size_t filename_len) {

    size_t amagad = MaxTextExtent;

	if (filename_len >= amagad) {
		printf("filename_len %zu >= amagad %zu\n", filename_len, amagad);
		printf("filename_len %x >= amagad %x\n", filename_len, amagad);
	}
	else {
		printf("this works at least.\n");
	}
}


int main(int argc,char **argv) {
    foo(11);
    foo(140458315481099);
}