#include <bits/stdc++.h>
using namespace std;
const int MAX = 1e2 + 10;
double dp[MAX][2];
double dpn[MAX][2];
double sdp[MAX][2];
const double EPS = 1e-12;


double GaussJordan(vector<vector<double> > &a, vector<vector<double> > &b) {
	const int n = a.size();
	const int m = b[0].size();
	vector<int> irow(n), icol(n), ipiv(n);
	double det = 1;

	for (int i = 0; i < n; i++) {
		int pj = -1, pk = -1;
		for (int j = 0; j < n; j++)
			if (!ipiv[j])
				for (int k = 0; k < n; k++)
					if (!ipiv[k])
						if (pj == -1 || fabs(a[j][k]) > fabs(a[pj][pk])) {
							pj = j;
							pk = k;
						}
		if (fabs(a[pj][pk]) < EPS) {
			cerr << "Matrix is singular." << endl;
			exit(0);
		}
		ipiv[pk]++;
		swap(a[pj], a[pk]);
		swap(b[pj], b[pk]);
		if (pj != pk)
			det *= -1;
		irow[i] = pj;
		icol[i] = pk;

		double c = 1.0 / a[pk][pk];
		det *= a[pk][pk];
		a[pk][pk] = 1.0;
		for (int p = 0; p < n; p++)
			a[pk][p] *= c;
		for (int p = 0; p < m; p++)
			b[pk][p] *= c;
		for (int p = 0; p < n; p++)
			if (p != pk) {
				c = a[p][pk];
				a[p][pk] = 0;
				for (int q = 0; q < n; q++)
					a[p][q] -= a[pk][q] * c;
				for (int q = 0; q < m; q++)
					b[p][q] -= b[pk][q] * c;
			}
	}

	for (int p = n - 1; p >= 0; p--)
		if (irow[p] != icol[p]) {
			for (int k = 0; k < n; k++)
				swap(a[k][irow[p]], a[k][icol[p]]);
		}

	return det;
}



double rsolve(int m, int n){
    
    
    int M = m + 6;
    vector<vector<double>> A = vector<vector <double> >(2 * M, vector<double>(2 * M, 0.));
    vector<vector<double>> B = vector<vector<double> >(2 * M, vector<double> (1, 0));
    

    int iprob = m - n + 1;
    for(int i = n + 5; i <= m + 5; i++){
        A[0][i + M] += 1;
    }
    A[0][0] += - iprob;
    
    for(int i = n; i <= m; i++)
        for(int j = n; j <= m; j++){
            if(i < j) 
                B[0 + M][0] -= i;
            else{
                B[0 + M][0] -= (j + 5);
                A[0 + M][i - j + M] += 1;
            }
        }
    A[0 + M][0 + M] += -iprob * iprob;
    
    
    for(int diff = 1; diff <= m + 5; diff++){
        
        for(int i = n; i <= m; i++){
            if(diff - i - 5 > 0) 
                B[diff][0] -= i;
            else{
                B[diff][0] -= diff;
                A[diff][i + 5 - diff + M] += 1;
            }
        }
        A[diff][diff] += -iprob;
        
        
        for(int i = n; i <= m; i++){
            if(diff - i - 5 > 0) {
                B[diff + M][0] -= (i + 5);
                A[diff + M][diff - i - 5] += 1;
            }
            else{
                B[diff + M][0] -= diff;
                A[diff + M][i + 5 - diff] += 1;
            }
        }
        A[diff + M][diff + M] += -iprob;
        
    }
    
    
    
    GaussJordan(A, B);
    
    
    
    
    
    
    return B[0][0];
}









double solve(int m, int n){
    for(int i = 0 ; i <= m + 5; i++)
        dp[i][0] = dp[i][1] = 0;
    int iters = 10000000;
    double prob = 1.0 / (m - n + 1);
    for(int it = 0; it < iters; it++){
        
        sdp[0][0] = dp[0][0];
        sdp[0][1] = dp[0][1];
        for(int diff = 1; diff <= m + 5; diff++){
            sdp[diff][0] = sdp[diff - 1][0] + dp[diff][0];
            sdp[diff][1] = sdp[diff - 1][1] + dp[diff][1];
        }
        
        for(int diff = 1; diff <= m + 5; diff++){
            
            double nd = 0;
            if(diff > n + 5) nd += (n + diff - 5 - 1) * (diff - 5 - 1 - n + 1) / 2;
            if(diff <= m + 5){
                if(diff - 5 >= n)nd += diff * (m + 5 - diff + 1) +  sdp[m + 5 - diff][ 1];
                else nd += diff * (m - n + 1) +  sdp[m + 5 - diff][1] - sdp[n + 5 - diff - 1][1];
            }
            dpn[diff][0] = nd * prob;
            
            nd = 0;
            if(diff > n + 5) nd += (n + 5 + diff - 1) * (diff - 1 - n - 5 + 1) / 2 + sdp[diff - n - 5][ 0] - sdp[0][0];
            if(diff <= m + 5){ 
                if(diff - 5 >= n) nd += diff * (m + 5 - diff + 1) +  sdp[m + 5 - diff][0];
                else nd += diff * (m - n + 1) +  sdp[m + 5 - diff][0] - sdp[n + 5 - diff - 1][0];
            }
            dpn[diff][1] = nd * prob;
        }
        
        dpn[0][0] = (sdp[m + 5][1] - sdp[n + 5 - 1][1]) *  prob;
        
        double nd = 0;
        for(int i = n; i <= m; i++){
            nd += (m - i) * i;
            nd += (n + 5 + i + 5) * (i - n + 1) / 2 + sdp[i - n][1];
        }
        dpn[0][1] = nd * prob * prob;
        
        if(it > 100 and abs(dpn[0][0] - dp[0][0]) < EPS)
            break;
        
        if(it == iters - 1){
            printf("%.16lf %.16lf\n", dpn[0][0], dp[0][0]);
            printf("precision problem\n");
            exit(-1);
        }
        for(int diff = 0; diff <= m + 5; diff++){
            dp[diff][0] = dpn[diff][0];
            dp[diff][1] = dpn[diff][1];
        }
    }
    return dp[0][0];
    
}

int main()
{
    printf("%.2lf\n", rsolve(72, 7));
    printf("%.2lf\n", rsolve(60, 30));
    printf("%.2lf\n", solve(60, 30));
    //exit(0);
	double ans = 0;
    int k = 100;
    //k = 5;
    for(int m = 2; m <= k; m++ )
        for(int n = 1; n < m; n++){
            printf("%d %d\n", m, n);
            ans += rsolve(m, n);
        }
    printf("%.2lf\n", ans);
	return 0;
}