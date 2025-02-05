from math import log, floor

M = 6  # Answer: 3828125
M = 123456789  # Answer: 4228020

##def D(m):  # see problem 567
##    d = 0
##    invpow2 = 1/2
##    for n in range(1, m+1):
##        d = 1/n * invpow2 + d/2
##        invpow2 /= 2
##    return d

## H(n) = 2^n D(n) ==> H(n) = 1/n + H(n-1)

def H(m):
    return sum(1/n for n in range(1, m+1))

logd = log(H(M), 10) - M*log(2.0, 10)
d = pow(10.0, logd - floor(logd))
s = str(d).replace('.', '')
for i in range(len(s)):
    if s[i] != '0': break
print(s[i:i+7])