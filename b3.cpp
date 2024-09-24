#include<bits/stdc++.h>
using namespace std;
void rut_gon (long long &x, long long &y) { // Hàm để rút gọn phân số
    long long g = __gcd(x, y);
    x /= g, y /= g;
}
void in_phan_so (long long &x, long long &y) {
    rut_gon(x, y);
    cout << x << ' ' << y << '\n';
}
int main () {
    long long a, b, c, d; cin >> a >> b >> c >> d;
    rut_gon(a, b); rut_gon(c, d);
    long long tu = 1LL * a * d + 1LL * b * c, mau = 1LL * b * d; // Cộng
    in_phan_so(tu, mau);
    tu = 1LL * a * d - 1LL * b * c, mau = 1LL * b * d; // Trừ
    in_phan_so(tu, mau);
    tu = 1LL * a * c, mau = 1LL * b * d; // Nhân
    in_phan_so(tu, mau);
    tu = 1LL * a * d, mau = 1LL * b * c; // Chia
    in_phan_so(tu, mau);
}
