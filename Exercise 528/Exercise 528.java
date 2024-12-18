public class Problem528 {

    private static long binom(long n, long k, long mod) {
        n %= mod;
        long numerator = 1;
        long denomintor = 1;
        for(int i = 1; i <= k; i++) {
            numerator = (numerator*(n - i + 1))%mod;
            denomintor = (denomintor*i)%mod;
        }
        return numerator*MathFunctions.inverseMod(denomintor, mod)%mod;
    }
    
    private static long S(long n, int k, long b, long mod) {

        class InnerClass {
            long sum = 0;

            private void innerMethod(int sign, long exponent, long bPow, int m) {
                if(exponent > n || m > k)
                    return;
                long term = sign*binom(n + k - exponent, k, mod);
                sum = (sum + term)%mod;
                while(exponent + b*bPow + 1 <= n && m + 1 <= k) {
                    bPow *= b;
                    m++;
                    innerMethod(-sign, exponent + bPow + 1, bPow, m);
                }

            }
        }

        InnerClass innerClass = new InnerClass();
        innerClass.innerMethod(1, 0, 1, 0);
        return Math.floorMod(innerClass.sum, mod);
    }

    private static long problem(long mod) {
        long result = 0;
        for(long k = 10; k <= 15; k++)
            result = (result + S((long) Math.pow(10, k), (int) k, k, mod))%mod;
        return result;
    }

    public static void main(String... args) {
        long mod = 1_000_000_007;
        long result = problem(mod);
        System.out.println(result);
    }
}