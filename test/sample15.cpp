#include <stdio.h>

void dis1(int x0, int y0, int n, int m) {
  int x = x0;
  int y = y0;
  if (y < x)
    return;
  while (x < n) {
    if (y < m) {
      y = y + 1;
    } else {
      x = x + 1;
    }
  }
}

void dis2(int x0, int z0, int n) {
  int x = x0;
  int z = z0;
  while (x < n) {
    if (z > x) {
      x = x + 1;
    } else {
      z = z + 1;
    }
  }
}

// void dis3(int x0, int z0, int n) {
//   int x = x0;
//   int z = z0;
//   if (x < z) {
//     while (x < n) {
//       if (z > x) {
//         x = x + 1;
//       } else {
//         z = z + 1;
//       }
//     }
//   }
// }