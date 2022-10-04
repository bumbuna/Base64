/*
* base64.c
*
* Copyright 2022 Jacob Bumbuna <developer@devbumbuna.com>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
* MA 02110-1301, USA.
*
*
*/

#include "../include/base64.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>

static int newFile = 0;
static FILE *inFile;

int readFile(const char *fileName) {
	if(inFile) {
		fclose(inFile);
	}
	inFile = fopen(fileName, "r");
	return errno;
}

int inFun(unsigned char *buf, int *readBytes) {
  	if(feof(inFile)) {
		return (*readBytes = 0);
	}
	*readBytes = fread(buf, 1, *readBytes, inFile);
	if(*readBytes ==0 && ferror(inFile)) {
		return -1;
	}
	return 0;
}

int outFun(char *str, int strLen) {
	fwrite(str, strLen, 1, stdout);
	return 0;
}

int main(int argc, char **argv) {
	for(int i = 1; i < argc; i++) {
		if(readFile(argv[i]) != 0) {
			perror("file");
			continue;
		}
		outFun(argv[i], strlen(argv[1]));
		outFun(": ", 2);
		base64Decode(inFun, outFun);
		outFun("\n", 1);
	}
        return 0;
}
