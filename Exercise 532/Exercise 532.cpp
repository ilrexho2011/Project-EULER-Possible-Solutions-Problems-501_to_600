const int maxp = 100000;
#include <pe>
const double pi = acos(-1.0);

SL long double cross(long double x1, long double y1, long double x2, long double y2)
{
  return x1 * y2 - y1 * x2;
}
SL long double sq(long double x) {return x*x;}

long double solve(int n)
{
  long double ret = 0;
  const long double init_phi = asin(0.999);
  const int N = 50000000;
  const long double each = init_phi / (N - 1);
  const long double theta = 0;
  const long double delta = 2 * pi / n;
  long double phi = init_phi;
  for (int i = 1; i < N; ++i)
  {
    const long double prev = phi - each;

    const long double x0 = sin(phi) * cos(theta);
    const long double y0 = sin(phi) * sin(theta);
    const long double z0 = cos(phi);
    
    const long double x1 = sin(phi) * cos(theta + delta);
    const long double y1 = sin(phi) * sin(theta + delta);
    const long double z1 = cos(phi);
    
    const long double A = cross(y0, z0, y1, z1);
    const long double B = -cross(x0, z0, x1, z1);
    const long double C = cross(x0, y0, x1, y1);
    
    const long double A1 = x0;
    const long double B1 = y0;
    const long double C1 = z0;
    
    const long double dx = cross(B, C, B1, C1);
    const long double dy = -cross(A, C, A1, C1);
    const long double dz = cross(A, B, A1, B1);
    
    const long double L = sqrt(sq(dx) + sq(dy) + sq(dz));
    ret += (cos(prev)-cos(phi)) * L / dz;
    phi = prev;
  }
  return ret;
}

int main()
{
  int n = 827;
  double length = (double)solve(n);
  printf("%d %.16f %.16f\n", n, length, length * n);
  return 0;
}