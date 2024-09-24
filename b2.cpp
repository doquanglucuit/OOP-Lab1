#include<bits/stdc++.h>
using namespace std;
int main () {
    long long a, b, c, d; cin >> a >> b >> c >> d; // Nhập phân số
    int sign = (1LL * b * d > 0 ? 1 : -1); // So sánh, in kết quả
    if (sign * (1LL * a * d - 1LL * b * c) > 0) cout << a << ' ' << b;
    else cout << c << ' ' << d;
}
