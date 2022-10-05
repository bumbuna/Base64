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
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static int newFile = 0;
static FILE *inFile;
static int decode = 0;

int readFile(const char *fileName) {
  if (inFile) {
    fclose(inFile);
  }
  inFile = fopen(fileName, "r");
  return errno;
}

int inFun(unsigned char *buf, int *readBytes) {
  if (feof(inFile)) {
    return (*readBytes = 0);
  }
  int toRead = *readBytes;
  int i = 0;
  do {
    if (feof(inFile))
      break;
    buf[i] = fgetc(inFile);
    if(feof(inFile)) break;
    if (decode && !isalnum(buf[i]) && buf[i] != '=' && buf[i] != '+' && buf[i] != '/') {
      continue; // ignore non-base64 characters when decoding
    }
    i++;
  } while (i < *readBytes);
  *readBytes = i;
  if (ferror(inFile)) {
    return -1;
  }
  return 0;
}

int outFun(char *str, int strLen) {
  fwrite(str, strLen, 1, stdout);
  return 0;
}

int main(int argc, char **argv) {

  int c = -1;
  while ((c = getopt(argc, argv, "dvh")) != -1) {
    switch (c) {
    case 'd': {
      decode = 1;
      break;
    }
    case '?':
    case 'h': {
      fprintf(stderr,
              "Usage: %s [option] [file] ...\n"
              "\t-d decode the files from base64\n"
              "\t-v show version info\n"
              "\t-h show help information\n",
              argv[0]);

      return c == '?' ? -1 : 0;
    }
    case 'v': {
      printf("[LIB]BASE64  :   v%d.%d.%d.%d\n"
             "COMPILER     :   %s %s\n"
             "COMPILE TIME :   %s\n",
             BASE64_MAJOR_VER, BASE64_MINOR_VER, BASE64_PATCH_VER,
             BASE64_TWEAK_VER, BASE64_COMPILER_ID, BASE64_COMPILER_VERSION,
             BASE64_COMPILE_TIME);
      return 0;
    }
    }
  }

  for (int i = optind; i < argc || (i == optind && i == argc); i++) {
    if ( (optind == argc) || !strcmp(argv[i], "-")) {
      inFile = stdin;
    } else if (readFile(argv[i]) != 0) {
      perror("file");
      continue;
    }
    if (isatty(fileno(stdout)) && inFile != stdin) {
      outFun(argv[i], strlen(argv[i]));
      outFun(": ", 2);
    }
    decode ? base64Decode(inFun, outFun) : base64Encode(inFun, outFun);
    if (isatty(fileno(stdout))) {
      outFun("\n", 1);
    }
  }
  return 0;
}
