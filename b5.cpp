#include<bits/stdc++.h>

using namespace std;

int numberDayOfMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // số ngày trong 1 tháng

void find_day (int D, int M, int Y) {
    if (D == 0) {
        M--;
        if (M == 0) M = 12, Y = Y - 1;
        D = numberDayOfMonth[M];
    }
    else if (D > numberDayOfMonth[M]) {
        M++;
        if (M == 13) M = 1, Y = Y + 1;
        D = 1;
    }
    cout << D << '\/' << M << '\/' << Y << '\n';
}

int main () {
    int D, M, Y; cin >> D >> M >> Y;
    if (Y % 4 == 0 and Y % 100 != 0) numberDayOfMonth[2] = 29; // xử lí năm nhuận
    int stt = D;
    for (int i = 1; i < M; i++) stt += numberDayOfMonth[i];

    cout << "Next day: "; find_day(D + 1, M, Y);
    cout << "Previous day: "; find_day(D - 1, M, Y);
    cout << stt << '\n';
}
