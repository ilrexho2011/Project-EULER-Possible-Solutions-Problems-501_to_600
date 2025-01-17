#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long ll;
#define maxn 10010
int tpp[maxn],mod;
namespace ut{
	int qmU(int a){ return a-((((~a)+mod)>>31)&mod); }
	int qmD(int a){ return a+((a>>31)&mod); }
} using namespace ut;
namespace binom{
	int C[maxn][maxn];
	inline void init(){
		for(int i=0;i<maxn;++i){
		 C[i][0]=1;
		 for(int j=1;j<=i;++j) C[i][j]=qmU(C[i-1][j-1]+C[i-1][j]);
		}
	}
} using namespace binom;
namespace count{
	int f[maxn],g[maxn],fe[maxn];
	inline void init(){
		f[1]=1; g[1]=0;
		fe[1]=1;
		/// f:{{{1}}},g:{}
		for(int i=2;i<maxn;++i){
			for(int j=1;j<i;++j){
				g[i]=(ll(g[i])+ll(C[i-1][j-1])*fe[j]%mod*ll(tpp[i-j]))%mod;
			}
			g[i]=qmU(g[i]+g[i-1]);
			f[i]=qmD(tpp[i]-g[i]);
			fe[i]=f[i];
			for(int j=1;j<i;++j){
				fe[i]=qmD((fe[i]-ll(C[i][j])*fe[j])%mod);
			}
//			printf("%d %d %d\n",f[i],g[i],fe[i]);
		}
	}
} using namespace count;
inline void init_tpp(){
	tpp[0]=1;
	for(int i=1;i<maxn;++i){
		tpp[i]=ll(tpp[i-1])*tpp[i-1]%mod;
		tpp[i]=qmU(tpp[i]+tpp[i]);
	}
	for(int i=0;i<maxn;++i) tpp[i]=qmD(tpp[i]-1);
}
int F[maxn][maxn];
int main(){
	freopen("ernd.in","r",stdin);
	freopen("ernd.out","w",stdout);
	int n,k; scanf("%d%d%d",&n,&k,&mod);
	init_tpp();
	binom::init();
	count::init();
	for(int i=1;i<=n;++i){
		F[i][1]=f[i];
//		printf("%d",F[i][1]);
		for(int j=2;j<=k;++j){
			// Restrict 1 in graph
			for(int v=1;v<i;++v){
				F[i][j]=(F[i][j]+ll(C[i-1][v-1])*fe[v]%mod*ll(F[i-v][j-1]))%mod;
			}
			// Restrict 1 not in graph
			F[i][j]=qmU(F[i-1][j]+F[i][j]); // {2..i} with k comp.
//			printf(" %d",F[i][j]);
		}
//		putchar('\n');
	}
	printf("%d\n",F[n][k]);
//	printf("%d %d\n",f[n],g[n]);
	return 0;
}