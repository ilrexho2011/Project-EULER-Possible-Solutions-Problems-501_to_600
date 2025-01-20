#include<bits/stdc++.h>
#include<omp.h>
using namespace std;
typedef unsigned long long u64;

const u64 N = 1e14;

constexpr u64 isqrt(u64 x) {
	u64 r = sqrt(x);
	for(;r*r > x;) --r;
	for(;(r+1)*(r+1) <= x; ++r);
	return r;
}

const u64 S = isqrt(N);
const array<u64, 6> sp = {3, 7, 11, 19, 23, 31};
const u64 M = 4 * sp[0] * sp[1] * sp[2] * sp[3] * sp[4] * sp[5];

u64 inv[M];

vector<u64> p1, p3;
vector<pair<u64, u64>> cnt;


u64 calc(const u64 R, u64 s[]) {
	const size_t n = (N - R) / M + 1;
	static const u64 BAD = 1ULL << 48, d = 1ULL << 50,
		HI = ~0ULL << 48, LO = ~HI;
	for(size_t i = 0, x = R ; i <n; ++i, x += M)
		s[i] = x;
	auto locate = [R](u64 x) {
		auto a = inv[x%M] * R % M * (__uint128_t)x;
		assert(a % M == R && a % x == 0 && a < M * x);
		return u64((a - R) / M);
	};
	for(u64 q : p3)
		for(u64 i = locate(q); i < n; i += q)
			s[i] |= BAD;
	for(u64 p : p1) {
		u64 i = locate(p), x = i * M + R;
		for(; i < n; i += p)
		if(!(s[i] & BAD)){
			u64 t = (s[i] & LO) / p;
			s[i] += d;
			if(t % p == 0) {
				s[i] -= d;
				t /= p;
				if(t % p == 0) s[i] |= BAD;
			}
			s[i] = s[i] & HI | t;
		}
	}
	u64 res = 0;
	u64 x = R;
	for(int i = 0, j = 0; i < n; ++i, x += M) if(!(s[i] & BAD)) {
		if((s[i] & LO) > 1) s[i] += d;
		s[i] >>= 50;
		for( ;x > cnt[j].first;) ++j;
		res += cnt[j].second << s[i];
		//printf("%llu %llu %llu\n", x, cnt[j].second,s[i]);
	}
	return res;
}

void ec(int64_t a, int64_t b, int64_t&x, int64_t& y) {
	if(b==0) {x = 1; y = 0; return;}
	ec(b, a%b, y, x);
	y -= a / b * x;
}

int main() {
	{	bitset<S+1> a;
		for(u64 p = 2; p <= S; p += 1 + (p & 1))
			if(!a.test(p)) {
				switch(p&3){
				case 1: p1.push_back(p); break;
				case 3: p3.push_back(p); break;
				}
				for(u64 j = p * p; j <= S; j += p)
					a.set(j);
			}
		a.set();
		p1.push_back(2);
		for(auto p : p1)
			for(u64 j = p; j <= S; j += p) a.reset(j);
		p1.pop_back();
		for(auto q : p3) {
			auto qq = q*q;
			for(u64 j = qq; j <= S; j+= qq ) a.reset(j);
		}
		map<u64, u64> c;
		for(u64 x = 1; x <= S; x += 2) if(a.test(x))
			for(u64 m : {x * x, x * x << 1}) if(m <= N)
				++c[((N / m - 1) & ~3ULL) + 1];
		cnt.assign(c.cbegin(), c.cend());
		cnt.push_back({N+10, 0});
		for(int j = cnt.size() - 2; j >=0; --j)
			cnt[j].second += cnt[j+1].second;
		p3.erase(p3.begin(), p3.begin() + sp.size());
	}

	vector<u64> rs;
	for(int r = 1; r < M; r += 4) {
		rs.push_back(r);
		for(auto p: sp) if(r % p == 0){
			rs.pop_back();
			break;
		}
	}
	random_shuffle(rs.begin(), rs.end());

	for(int i = 1; i < M; i += 2) {
		int64_t x, y;
		ec(M, i, x, y);
		inv[i] = (y + M) % M;
	}

	u64 res = 0;

#	define TC 72
	static u64 mem[TC][(N / M | 0xF) + 0x11];
#	pragma omp parallel for schedule(dynamic, 30) reduction(+:res) num_threads(TC)
	for(size_t i = 0; i < rs.size(); ++i) {
		const int tid =  omp_get_thread_num();
		res +=  calc(rs[i], mem[tid]);
		if(tid == TC - 1 || tid == 0 || ((i ^ tid) & 63) == 0)
			cerr << "Thread #" << tid << " finished task #"
				<< i << "/" << rs.size() << endl;
	}
	cout << res << endl;
}