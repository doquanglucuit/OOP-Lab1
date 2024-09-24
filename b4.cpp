#include<bits/stdc++.h>
using namespace std;
int main () {
    double x; cin >> x;
    double sinx = 0, n = 0, sign = 1.0, tmp = 1.0 * x;
    while (not (tmp < 0.00001)) { // nếu phần tử hiện tại < 0.00001 thì không tính nữa
        sinx += tmp * sign;
        n++;
        tmp = tmp * x * x / ((2 * n) * (2 * n + 1));
        sign = -sign;
    }
    cout << fixed << setprecision(5) << sinx;
}
