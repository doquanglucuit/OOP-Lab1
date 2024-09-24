#include<bits/stdc++.h>
using namespace std;
void rut_gon (long long &x, long long &y) { // Hàm để rút gọn phân số
    long long g = __gcd(x, y);
    x /= g, y /= g;
    if (y < 0) x = -x, y = -y;
}
int main () {
    long long a, b; cin >> a >> b; // Nhập phân số
    rut_gon(a, b);
    cout << a << ' ' << b; // In kết quả
}
