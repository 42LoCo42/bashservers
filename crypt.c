#!/usr/bin/tcc -run -lcrypt
#include <crypt.h>
#include <errno.h>
#include <error.h>
#include <stdio.h>
#include <string.h>

void syntax_error(const char* name) {
	error(1, 0, "Syntax: %s <password> <-s salt | -p prefix>", name);
}

int main(int argc, char** argv) {
	if(argc < 4) {
		syntax_error(argv[0]);
	}

	char* salt = NULL;
	if(strcmp(argv[2], "-p") == 0) {
		salt = crypt_gensalt(argv[3], 0, NULL, 0);
		if(salt == NULL) {
			error(2, errno, "Salt generation failed");
		}
	} else if(strcmp(argv[2], "-s") == 0) {
		salt = argv[3];
	} else {
		syntax_error(argv[0]);
	}

	char* hash = crypt(argv[1], salt);
	if(hash == NULL || hash == salt) {
		error(3, errno, "Hashing failed");
	}
	printf("%s %s\n", hash, salt);
}
