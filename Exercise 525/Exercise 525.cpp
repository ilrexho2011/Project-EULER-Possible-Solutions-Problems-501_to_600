#include <stdio.h>
#include <math.h>

double C(int a, int b)
{
  if (a > b) { double t = a; a = b; b = t; }
  int n = 100000;
  double a2 = a*a, b2 = b*b;
  double a4 = a2*a2, b4 = b2*b2;
  double x0 = a, y0 = 0, tm = acos(0);
  double X0 = 0, Y0 = a, c  = 0, z = 0;
  for (int i = 1; i <= n; i++) {
    double t = tm * i / n;
    double x = a * cos(t), y = b * sin(t);
    c += hypot(x-x0, y-y0);
    double d = b4*x*x + a4*y*y;
    double x1 = a2*b4*x/d, y1 = a4*b2*y/d;
    double X = c - hypot(x1-x, y1-y);
    double Y = hypot(x1, y1);
    z += hypot(X-X0, Y-Y0);
    x0 = x; y0 = y; X0 = X; Y0 = Y;
  }
  return 4 * z;
}

int main(void)
{
  printf("%.8lf\n", C(1, 4) + C(3, 4));
  return 0;
}