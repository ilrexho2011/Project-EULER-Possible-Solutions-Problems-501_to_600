#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
const int MAX = 365;
const i64 ITER = 1e8;
const double EPS = 1e-60;
int ar[MAX];
int cant[MAX];

const int people = 4, rg = 7, days = 365;  const int topc = 300;
//const int people = 3, rg = 1, days = 10; const int topc = 20; // max number of people without fulfilling the condition
//const int people = 2, rg = 1, days = 5;  const int topc = 20;
//const int people = 3, rg = 7, days = 100; const int topc = 200;
void montecarlo(){
    srand(time(NULL));
    i64 tot = 0;

    for(i64 i = 1; i <= ITER; i++){
        //if(i % 10000 == 0)cout << i << endl;
        int cur = 0;
        while(true){
            cur++;
            int d = rand() % days;
            bool ended = false;
            for(int j = d - rg; j <= d; j++){
                int jj = j < 0 ? j + days : j;
                if(ar[jj] == i){
                    cant[jj] += 1;
                }
                else{
                    cant[jj] = 1;
                    ar[jj] = i;
                }
                if(cant[jj] >= people){
                    ended = true;
                    break;
                }
            }
            if(ended){
                tot += cur;
                break;
            }

        }
    }

    double ans = tot * 1.0 / ITER;
    cout << setprecision(11) << ans << endl;
}

struct frac{
    i64 a, b;
    frac(){a = 0, b = 1;}
    void summ(i64 aa, i64 bb){
        frac n;
        n.b = bb / __gcd(b, bb) * b;
        n.a = a * (n.b / b) + aa * (n.b / bb);
        n.simplify();
        *this = n;
    }
    void simplify(){
        i64 d = __gcd(a, b);
        a/= d, b/=d;
    }
};
i64 TOP = 1e11;
i64 ans;
i64 mprob;
void search(int cur, i64 prob){
    for(int d = 0; d < days; d++){
        bool ended = false;
        for(int j = d - rg; j <= d; j++){
            int jj = j < 0 ? j + days : j;
            cant[jj] += 1;
            if(cant[jj] >= people)
                ended = true;
        }
        if(!ended)search(cur + 1, prob * days);
        for(int j = d - rg; j <= d; j++){
            int jj = j < 0 ? j + days : j;
            cant[jj] -= 1;
        }
        if(ended){
            if(TOP < prob){
                ans *= prob / TOP;
                TOP = prob;
            }
            mprob = max(prob, mprob);
            ans += cur * TOP / prob;
        }
    }
}


int greedy(){
    bool ended = false;
    int ans = 0;
    while(!ended){
        ended = true;
        for(int d = 0; d < days; d++){
            bool pos = false;
            for(int j = d - rg; j <= d; j++){
                int jj = j < 0 ? j + days : j;
                cant[jj] += 1;
                if(cant[jj] >= people)
                    pos = true;
            }
            if(pos){
                for(int j = d - rg; j <= d; j++){
                    int jj = j < 0 ? j + days : j;
                    cant[jj] -= 1;
                }
            }
            else{
                ans++;
                ended = false;
            }
        }
    }
    return ans;

}

void exact(){

	/*for(days = 2; days <= 6; days++)
		for(people = 2; people <= 4; people++)
			for(rg = 0; rg < days; rg++){
				mprob = 0;
				TOP = 1;
				for(int i = 0; i < days ; i++)cant[i] = 0;
				ans = 0;
				search(1, days);
				ans /= TOP / mprob;
				TOP /=  TOP / mprob;
				assert(mprob == TOP);
				vector<pair<int, int>> pp;
				i64 rans = ans;
				for(int i = 2; (i64)i * i <= ans; i++){
					if(rans%i == 0){
						pp.push_back({i, 0});
						while(rans%i == 0)pp.back().second++, rans /= i;
					}
				}
				if(rans > 1)pp.push_back({rans, 1});
				cout << rg << " " << " " << people << " " << days << " " << ans << " " << TOP << " " << ans * 1.0 / TOP << endl;
				if(ans % days != 0 || (people  > 1 && (ans % (days * days)) != 0)){
					cout << "lol" << endl;
				}
				for(int i = 0 ; i< (int)pp.size(); i++)
					cout << pp[i].first << "^" << pp[i].second << (i == pp.size() - 1?  '\n' : '*');
			}*/
    search(1, days);
    cout << rg << " " << " " << people << " " << days << " " << ans << " " << TOP << " " << setprecision(12) << ans * 1.0 / TOP << endl;

}
const int MAXM = 1e6;
int mapm[MAXM];
int nums[MAXM];
int suffixs[MAXM];
int totm = 0;

double prob[topc];

void ssearch(int pos, int cur, int num, int suff){
    if(pos == rg + 1){
        mapm[num] = totm;
        suffixs[totm] = suff;
        nums[totm++] = num;
        return;
    }
    i64 fac = 1; // just in case i64
    for(int i = 0; i < people - cur; i++){
        if(i > 0){
            fac = fac * (cur + i) / i;
        }
        ssearch(pos + 1, cur + i, num * people + i, pos == 0 ? 0 : suff + i);

    }
}



vector<vector< vector<double> > > DP[2];


void solve(){


    prob[0] = 1;
    for(int t = 1; t < 2 * people; t++) prob[t] = prob[t - 1] / days;

    memset(mapm, -1, sizeof(mapm));
    ssearch(0, 0, 0, 0);
    cout << totm << endl;

    for(int u = 0; u < 2; u++){
        DP[u].resize(totm);
        for(int i = 0; i < totm; i++){
            DP[u][i].resize(totm);
            for(int j = 0; j < totm; j++)
                DP[u][i][j].resize(topc, 0.0);
        }
    }



    int ex = 1;
    for(int t = 0; t < rg; t++) ex *= people;

    for(int i = 0; i < totm; i++){
        int curi = nums[i];


        for(int j = 0; j < totm; j++){
            int curj = nums[j];
            int tmi = curi;
            bool done = false;
            for(int t = 1; t < rg + 1; t++){
                curj /= people;
                curj += (tmi % people)*ex;
                if(mapm[curj] == -1){
                    done = true;
                    break;
                }
                tmi /= people;
            }

            i64 fac = 1;
            int digs = 0;
            for(int t = 0, ti = nums[i], tj = nums[j]; t < rg + 1; t++){



                for(int tt = 1; tt <= tj % people; tt++ ){
                    fac = fac * (digs + tt) / tt;
                }
                digs += tj % people;
                tj /= people;




                for(int tt = 1; tt <= ti % people; tt++ ){
                    fac = fac * (digs + tt) / tt;
                }
                digs += ti % people;
                ti /= people;

            }
            if(!done)DP[0][i][j][digs] = fac * prob[digs] ; // FIXED to take into account both
            //cout << i << " " << j << " " << digs << " " << DP[0][i][j][digs] << endl;
        }
    }


    cout << "finish" << endl;


    for(int d = 1; d <= days - 1 - 2 * ( rg + 1); d++){ // TODO check this range (hope checked!!)

        for(int i = 0; i < totm; i++){
            for(int j = 0; j < totm; j++)
                for(int c = 0; c < topc; c++){

                    if(DP[0][i][j][c] < EPS)continue;

                    int curj = (nums[j] % ex) * people; // remove first digit
                    i64 fac = 1; // just in case i64
                    for(int t = 0; t < people - suffixs[j]; t++){

                        if(t > 0){
                            fac = fac * (c + t) / t;
                        }

                        int nj = mapm[curj + t];  assert(nj != -1);

                        DP[1][i][nj][c + t] += DP[0][i][j][c] * fac * prob[t];
                    }


                }
        }

        for(int i = 0; i < totm; i++)
            for(int j = 0; j < totm; j++)
                for(int c = 0; c < topc; c++){
                    DP[0][i][j][c] = DP[1][i][j][c];
                    DP[1][i][j][c] = 0;
                }



    }

    cout << "finished dp stuff" << endl;

    double ans = 0;
    for(int i = 0; i < totm; i++)
        for(int j = 0; j < totm; j++)
            for(int c = 0; c < topc; c++){
                if(DP[0][i][j][c] < EPS)continue;
                int d;

                vector<int> dd;
                int curi = nums[i], curj = nums[j];

                for(int t = 0; t < rg + 1; t++){
                    dd.push_back(curi % people);
                    curi /= people;
                }
                dd.push_back(0); // center, last position
                for(int t = 0; t < rg + 1; t++){
                    dd.push_back(curj % people);
                    curj /= people;
                }
                reverse(dd.begin(), dd.end());

                i64 fac = 1; // just in case i64
                for(d = 0; ; d++){

                    dd[rg + 1] = d;
                    int sum = 0;
                    for(int t = 0; t < rg + 1; t++)sum += dd[t];
                    bool done = false;
                    for(int t = 1; t <= rg + 1; t++){
                        sum -= dd[t - 1];
                        sum += dd[t + rg];
                        if(sum >= people){
                            done = true;
                            break;
                        }
                    }

                    if(done)break;

                    if(d > 0){
                        fac = fac * (c + d) / d;
                    }

                }
                if(d == 0)continue;

                ans += ( c + d ) * DP[0][i][j][c] * fac * prob[d];



            }
    cout << setprecision(12) << days * ans << endl;


}



int main(){
    //exact();
    solve();


}