#include<stdio.h>
#include<math.h>
#include<time.h>
#include<assert.h>

#define A 40

typedef long long LL;
typedef long double LLF;

LLF c1[A+1][A+1];
LLF c2[A+1][A+1];

void init_caches() {
  LL x,y;
  for(x=0;x<=A;x++) for(y=0;y<=A;y++) {
    c1[x][y] = x? (x*x*x)*asinhl((LLF)y/x): 0;
    c2[x][y] = sqrtl(x*x+y*y);
  }
}

// indefinite integral SS sqrt(x²+y²)(ax+b)(cy+d) dx dy
// maxima:
//   assume(x>=0)$
//   assume(y>=0)$
//   sprint(ratsimp(integrate(integrate(sqrt(x^2+y^2)*(a*x+b)*(c*y+d),x),y)))$
// and some manual post-processing, like:
//   log((sqrt+y)/y)-log((sqrt-y)/y) -> 2 asinh(y/x)
LLF F(LLF a, LLF b, LLF c, LLF d, LL x, LL y) {
  assert(0<=x && x<=A);
  assert(0<=y && y<=A);
  return (
    + (x? (15*a*d*x + 20*b*d) * c1[x][y]: 0)
    + (y? (15*b*c*y + 20*b*d) * c1[y][x]: 0)
    + c2[x][y] * (8*a*c*((x*x+y*y)*(x*x+y*y)) + 10*(a*d*(y*y*y)+b*c*(x*x*x)) + 25*x*y*(b*c*y + a*d*x) + 40*b*d*(x*y))
  )/120;
}

// definite integral F in rectangle (x0,x1,y0,y1)
LLF F_(LLF a, LLF b, LLF c, LLF d, LL x0, LL x1, LL y0, LL y1) {
  return F(a,b,c,d,x1,y1) + F(a,b,c,d,x0,y0) - F(a,b,c,d,x0,y1) - F(a,b,c,d,x1,y0);
}

typedef struct{ int x0,x1; LLF a,b; } seg;  // linear segment ax+b for x0<=x<=x1
typedef struct{ char len; seg _[4]; } segments;

int min(int a,int b) { return (a<b)?a:b; }
int max(int a,int b) { return (a>b)?a:b; }

segments get_segments(int a, int x0, int x1) {
  segments segs;
  int h,i=0;

  if(x0 > a-x1) { h=x0; x0=a-x1; x1=a-h; };
  int d = x1-x0, da = d*a;
  
  if(x0) 
    segs._[i++] = (seg){ 0,x0,  0, 2.l/a }; 
  if(x0<min(x1,a-x1))
    segs._[i++] = (seg){ x0,min(x1,a-x1),  -1.l/da, (LLF)(x1+d)/da };
  if(x1<a-x1) 
    segs._[i++] = (seg){ x1,a-x1,  0, 1.l/a };
  if(a-x1<x1)
    segs._[i++] = (seg){ a-x1,x1,  -2./da, (LLF)(x1+(a-x0))/da }; 
  if(max(x1,a-x1)<a-x0)
    segs._[i++] = (seg){ max(x1,a-x1),a-x0,  -1.l/da, (LLF)(a-x0)/da }; 
  
  segs.len = i;
  return segs;
}

// expected distance from inner rectangle (x0,x1,y0,y1) to rectangle (0,m,0,n)
// (inner means 0<=x0<x1<=m, 0<=y0<y1<=n)
LLF D(int m, int n, int x0, int x1, int y0, int y1) {
  segments 
    segs1 = get_segments(m,x0,x1),
    segs2 = get_segments(n,y0,y1);
  
  LLF total = 0;
  int i,j;
  
  for(i=0;i<segs1.len;i++) for(j=0;j<segs2.len;j++) {
    seg s1 = segs1._[i];
    seg s2 = segs2._[j];
    total += F_(s1.a,s1.b, s2.a,s2.b, s1.x0,s1.x1, s2.x0,s2.x1);
  }
  return total;
}


LLF S(int a) {
  LLF total=0, dtotal, Daa = D(a,a, 0,a,0,a), Dmn, x,y,z, p,q;
  int m,n,x0,y0,x1,y1,cnt,sym;
  
  for(m=1;m<=a-2;m++) for(n=1;n<=m;n++) { 
    dtotal = 0;
    cnt = 0;
    for(x0=1;x0<=(a-m)/2;x0++) for(y0=1;y0<=(a-n)/2;y0++) {
      sym = ((n<m)?2:1)*((2*x0<a-m)?2:1)*((2*y0<a-n)?2:1);
      cnt += sym;
      dtotal += D(a,a, x0,x0+m,y0,y0+n) * sym;
    }
    Dmn =  D(m,n, 0,m,0,n);
    p = (LLF)(m*n)/(a*a);
    q = 1-p;
    total += ( cnt*(Daa + Dmn*p*p) - dtotal*2*p )/(q*q);
  }
  return total;
};


int main() {
  init_caches();

  LL a,c0,c1;
  LLF total,t;
  for(a=3;a<=A;a++) {
    c0=clock(); total=S(a); c1=clock(); t=(LLF)(c1-c0)/CLOCKS_PER_SEC;
    printf("%d %.9llf %.6llf\n",a,total,t);
  }
}