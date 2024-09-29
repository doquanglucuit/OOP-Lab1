#include<bits/stdc++.h>

using namespace std;

int numDay[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // số ngày trong 1 tháng

void find_day (int stt, int Y) {
    int M = 1;
    while (stt - numDay[M] > 0) {
        stt -= numDay[M];
        M++;
    }
    int D = stt;
    cout << D << '\/' << M << '\/' << Y << '\n';
}

int main () {
    int D, M, Y; cin >> D >> M >> Y;
    if (Y % 4 == 0 and Y % 100 != 0) numDay[2] = 29; // xử lí năm nhuận
    int stt = D;
    for (int i = 1; i < M; i++) stt += numDay[i];

    if (D == 1 and M == 1) {
        cout << "Ngay sau: " << 2 << '\/' << 1 << '\/' << Y << '\n';
        cout << "Ngay truoc:" << 31 << '\/' << 12 << '\/' << Y - 1 << '\n';
    }
    else if (D == 31 and M == 12) {
        cout << "Ngay sau: " << 1 << '\/' << 1 << '\/' << Y + 1<< '\n';
        cout << "Ngay truoc:" << 30 << '\/' << 12 << '\/' << Y << '\n';
    }
    cout << "Ngay sau: "; find_day(stt - 1, Y);
    cout << "Ngay truoc:"; find_day(stt + 1, Y);
    cout << "STT: " << stt << '\n';
}
