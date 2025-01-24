#include <iostream>
using namespace std;
#include <vector>
#include <map>
#include <fstream>
#include <gmpxx.h>
mpz_class modulo=1000000007;

int Limit=10000000;

mpz_class puissance(mpz_class a,int b){
    vector<bool> binary;
    vector<mpz_class> L_b;
    while (b>0) {
        binary.push_back(b%2);
        b/=2;
        a=a%modulo;
        L_b.push_back(a);
        a*=a;
    }
    mpz_class r=1;
    for (int i=0; i<binary.size(); i++) {
        if(binary[i]){
            r*=L_b[i];
            r=r%modulo;
        }
    }
    return r;
}

long deux_puissance(long in){
    long r=1;
    while (r<=in) {
        r*=2;
    }
    return r;
}

int deux_p=1048576;

vector<int> walsh_hadamard(vector<int> In){
    vector<int> tem_1(1048576);
    vector<int> tem_2(1048576);
    
    for (int size=deux_p; size>=2; size/=2) {
        for (int i=0; i<deux_p/size; i++) {
            for (int j=0; j<size/2; j++) {
                tem_1[i*size+j]=In[i*size+j];
                tem_1[i*size+j+size/2]=In[i*size+j];
                tem_2[i*size+j]=In[i*size+j+size/2];
                tem_2[i*size+j+size/2]=-In[i*size+j+size/2];
            }
        }
        for (int i=0; i<deux_p; i++) {
            In[i]=(tem_1[i]+tem_2[i]);
        }
    }
    return In;
}
int main(int argc, const char * argv[]) {
    modulo*=(mpz_class)(1048576);
    
    map<int,int> N_NI;
    map<int,int> n_n;
    vector<int> primes;
    vector<int> fs(1048576);
    vector<int> Fs;
    for (int i=0; i<1048576; i++) {
        fs[i]=0;
    }
    int p;
    int NI;

    ifstream infile("/Users/xiangpengzhang/Documents/euler/prime/prime_sieve_atkins.txt");
    vector<bool> numbers(Limit);
    for (int i=0; i<Limit; i++) {
        numbers[i]=false;
    }
    while (infile>>p and p<=Limit) {
        primes.push_back(p);
        numbers[p]=true;
    }
    cout<<primes.size()<<endl;
    for (int i=3; i<Limit; i+=2) {
        if (not numbers[i]) {
            NI=0;
            for (auto it=primes.begin(); it!=primes.end(); it++) {
                NI++;
                if (i%(*it)==0) {
                    N_NI[i]=NI;
                    break;
                }
            }
        }
    }
    for (int i=0; i<primes.size(); i++) {
        N_NI[primes[i]]=i+1;
    }

    for (auto it=N_NI.begin(); it!=N_NI.end(); it++) {
        n_n[it->second]++;
    }
    
    n_n[0]=Limit/2-1;
    n_n[1]=1;
    
    cout<<N_NI.size()<<endl;
    cout<<n_n.size()<<endl;
    
    cout<<deux_puissance(n_n.size())<<endl;
    for (auto it=n_n.begin(); it!=n_n.end(); it++) {
        fs[it->first]=(it->second);
    }
    Fs=walsh_hadamard(fs);
    mpz_class R=0;
    for (int i=0; i<deux_p; i++) {
        R+=(puissance(mpz_class(Fs[i]), int(Limit)));
        R=R%modulo;
    }
    cout<<R/1048576<<endl;
    return 0;
}
