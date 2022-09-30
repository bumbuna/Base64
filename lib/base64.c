/*
 * base64.c - lib
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

int base64Encode(int (*inFun)(unsigned char *, int *),
                 int (*outFun)(char *, int)) {
  while (1) {
    unsigned int x = 0;
    int i = 3;
    if ((*inFun)((void *)&x, &i) == -1) {
      return -1;
    }
    if (i == 0)
      break;
    unsigned char *c = (void *)&x;
    int swap = 0;
    int rshift = 8;
    if (i == 1)
      rshift += 16;
    else if (i == 2) {
      swap = 1;
      rshift += 8;
    } else {
      swap = 2;
    }
    if (swap) {
      c[0] ^= c[swap];
      c[swap] ^= c[0];
      c[0] ^= c[swap];
    }
    x <<= rshift;
    char out[4] = {0,0,'=','='};
    unsigned int a = 0xfc000000;
    for (int j = 0; j < (i == 1 ? 2 : i == 2 ? 3 : 4); j++) {
      unsigned int k = x & a;
      k >>= 26;
      if (k >= 0 && k < 26) {
        out[j] = 'A' + k;
      } else if (k >= 26 && k < 52) {
        out[j] = 'a' + k - 26;
      } else if (k >= 52 && k < 62) {
        out[j] = '0' + k - 52;
      } else if (k == 62) {
        out[j] = '+';
      } else {
        out[j] = '/';
      }
      x <<= 6;
    }
    (*outFun)(out, 4);
  }
  return 0;
}
