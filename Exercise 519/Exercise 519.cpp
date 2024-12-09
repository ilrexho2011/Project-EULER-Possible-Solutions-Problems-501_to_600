#include <iostream>
#include <time.h>

using namespace std;

const int mod = 1000 * 1000 * 1000;

void add(int &a, int b)
{
    a += b;
    if (a >= mod)
        a -= mod;

    if (a < 0 || a > mod)
        cout << ":(" << endl;
}

int a[1 << 15][1 << 8];
int t[1 << 15];

int T(int n)
{
    return n >= 0 ? t[n] : 0;
}

int main()
{
    t[0] = 3;

    for (int n = 1; n <= 20001; n++)
    {
        a[n][1] = T(n - 1);
        add(a[n][1], a[n][1]);

        if (n >= 3)
        {
            a[n][2] = T(n - 3);
            add(a[n][2], a[n][2]);
            add(a[n][2], T(n - 2));
        }

        if (n >= 6)
        {
            a[n][3] = mod - T(n - 4);
            add(a[n][3], a[n][3]);
            add(a[n][3], T(n - 3));
        }

        for (int k = 4; k * (k + 1) <= 2 * n; k++)
        {
            a[n][k] = a[n - 1][k - 1];
            add(a[n][k], mod - a[n - k][k - 2]);
        }

        for (int k = 1; k * (k + 1) <= 2 * n; k++)
            add(t[n], a[n][k]);
    }

    for (int n = 1; n <= 20; n++)
    {
        for (int k = 1; k <= 5; k++)
            cout << a[n][k] / 2 << "\t";
        cout << "  " << t[n] / 2 << endl;
    }

    cout << t[4] / 2 << endl;
    cout << t[10] / 2 << endl;
    cout << t[20000] << " " << t[20000] / 2 << " " << (t[20000] + mod) / 2 << endl;
    cout << (double)clock() / CLOCKS_PER_SEC << endl;

    return 0;
}