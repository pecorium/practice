#define _GNU_SOURCE
#include <stdio.h>
#include <tgmath.h>

double sq(double x) { return x * x; }

double GaussianPDF(double x, double m, double s) {
  return 1 / sqrt(2 * M_PI * sq(s)) * exp(-(sq(x - m) / (2 * sq(s))));
}

int main(void) {
  for (int x = 30; x <= 70; x += 10) {
    double p = GaussianPDF(x, 50, 10);
    printf("%d: %f\n", x, p);
  }
  return 0;
}
