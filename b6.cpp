#include<bits/stdc++.h>
#define sz(x) (int) (x).size()

using namespace std;

vector<int> z_function (const vector<int> &A) { // Thuật toán Z-function
    vector<int> z(sz(A), 0);
    z[0] = 0;
    int L = 0, R = 0;
    for (int i = 1; i < sz(A); i++) {
        z[i] = 0;
        if (i <= R)
            z[i] = min(z[i - L], R - i + 1);

        while (i + z[i] < sz(A) and A[z[i]] == A[i + z[i]])
            z[i]++;

        if (i + z[i] - 1 > R) {
            R = i + z[i] - 1;
            L = i;
        }
    }
    return z;
}

int main () {
    vector<int> a, b;
    int m, n; cin >> m >> n;
    a.resize(m), b.resize(n);
    for (int i = 0; i < m; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    int mi = *min_element(a.begin(), a.end());
    mi = min(mi, *min_element(b.begin(), b.end())) - 1;

    vector<int> s = a; // s = a + | + b
    s.push_back(mi); // thêm một phần tử không có trong cả a và b vào để ngăn cách a và b (chọn "|" là giá tri nhỏ nhất của 2 mảng trừ đi 1)
    for (int x : b) s.push_back(x);

    vector<int> z = z_function(s), result;

    for (int i = m + 1; i < sz(s); i++) if (z[i] == m)
        result.push_back(i - m - 1);

    cout << sz(result) << '\n';
    for (int x : result) cout << x << ' ';
}
