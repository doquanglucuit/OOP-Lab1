#include<bits/stdc++.h>
#define sz(x) (int) (x).size()
using namespace std;

int numDay[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool check_flycode (const string &s) {
    bool ok = sz(s) <= 5;
    for (int i = 0; i < sz(s); i++) ok &= (('a' <= s[i] and s[i] <= 'z') or ('A' <= s[i] and s[i] <= 'Z') or ('0' <= s[i] and s[i] <= '9'));
    return ok;
}

bool check_date (const string &s) { // YYYY/MM/DD
    if (sz(s) != 10) return false;
    bool ok = true;
    for (int i = 0; i < 10; i++) if (i != 4 and i != 7)
        ok &= '0' <= s[i] and s[i] <= '9';
    else ok &= (s[i] == '\/');
    if (not ok) return false;

    int D = (s[8] - '0') * 10 + s[9] - '0';
    int M = (s[5] - '0') * 10 + s[6] - '0';
    int Y = (s[0] - '0') * 1000 + (s[1] - '0') * 100 + (s[2] - '0') * 10 + (s[3] - '0');
    if (M > 12 or M < 1) return false;
    if (Y % 4 == 0 and Y % 100 != 0 and M == 2) { // xử lí riêng trường hợp năm nhuận
        if (D < 1 or D > 29) return false;
    }
    else {
        if (D < 1 or D > numDay[M]) return false;
    }
    return true;
}

bool check_time (const string &s) { //00:00 23:59
    if (sz(s) != 5) return false;
    bool ok = true;
    for (int i = 0; i < 5; i++) if (i != 2)
        ok &= '0' <= s[i] and s[i] <= '9';
    else ok &= s[i] == ':';
    int H = (s[0] - '0') * 10 + s[1] - '0';
    int M = (s[3] - '0') * 10 + s[4] - '0';

    return 0 <= H and H <= 23 and 0 <= M and M <= 59;
}

bool check_location (const string &s) {
    bool ok = sz(s) <= 20;
    for (int i = 0; i < sz(s); i++) {
        ok &= ('a' <= s[i] and s[i] <= 'z') or ('A' <= s[i] and s[i] <= 'Z') or (s[i] == ' ');
    }
    return ok;
}

struct Flight {
    string flycode, date, time, from, to;
    Flight () {}
    Flight (string _flycode, string _date, string _time, string _from, string _to):
        flycode(_flycode), date(_date), time(_time), from(_from), to(_to) {}

    void input () { // Hàm nhập xuất thông tin các chuyến bay
        cout << "Nhap ma chuyen bay(toi da 5 ki tu, khong co khoang trang va ki tu dac biet): ";
        cin.ignore();
        getline(cin, flycode);
        while (not check_flycode(flycode)) {
            cout << "Nhap sai dinh dang, vui long nhap lai ma chuyen bay: ";
            getline(cin, flycode);
        }

        cout << "Nhap ngay bay(theo dinh dang YYYY/MM/DD): ";
        getline(cin, date);
        while (not check_date(date)) {
            cout << "Nhap sai dinh dang hoac ngay khong hop le, vui long nhap lai ngay bay: ";
            getline(cin, date);
        }

        cout << "Nhap gio bay(theo dinh dang HH:MM): ";
        getline(cin, time);
        while (not check_time(time)) {
            cout << "Nhap sai dinh dang hoac gio khong hop le, vui long nhap lai gio bay: ";
            getline(cin, time);
        }

        cout << "Nhap noi di(toi da 20 ki tu, khong co so va ki tu dac biet): ";
        getline(cin, from);
        while (not check_location(from)) {
            cout << "Nhap sai dinh dang, vui long nhap lai noi di: ";
            getline(cin, from);
        }

        cout << "Nhap noi den(toi da 20 ki tu, khong co so va ki tu dac biet): ";
        getline(cin, to);
        while (not check_location(to)) {
            cout << "Nhap sai dinh dang, vui long nhap lai noi den: ";
            getline(cin, to);
        }
        cout << endl;
    }

    bool check_flight (const string &s) { // tim kiem chuyen bay theo ma chuyen bay hoac noi di noi den.
        return s == flycode or s == from or s == to;
    }

    bool find_flight_by_date_and_from (const string &_date, const string &_from) { // kiem tra chuyen bay theo ngay va noi xuat phat
        return date == _date and from == _from;
    }

    bool find_flight_by_from_and_to (const string &_from, const string &_to) { // kiểm tra chuyến bay theo nơi đi và nơi đến
        return from == _from and to == _to;
    }

    bool operator < (const Flight &oth) const { // dinh nghia phep so sanh 2 chuyen bay theo thoi gian
        if (date != oth.date) return date < oth.date;
        return time < oth.time;
    }

    void print () {
        cout << "Ma chuyen bay: " << flycode << ", Ngay bay: " << date << ", Gio bay: " << time << ", Noi di: " << from << ", Noi den: " << to << endl;
    }
};

int n;
vector<Flight> flights;

void input () {
    cout << "Nhap so chuyen bay: ";
    cin >> n;
    flights.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cout << "Nhap thong tin chuyen bay " << i << ": " << endl;
        flights[i].input();
    }
}

void solve () {
    cout << "Day la danh sach cac chuyen bay theo thu tu ngay va gio khoi hanh:";
    for (int i = 1; i <= n; i++)
        flights[i].print();

    cout << "Ban dang can tim kiem chuyen bay nao (vui long nhap dung ma chuyen bay, noi di hoac noi den): ";
    string key; getline(cin, key);
    vector<int> result;
    for (int i = 1; i <= n; i++) if (flights[i].check_flight(key))
        result.push_back(i);

    cout << "Co " << sz(result) << " ket qua tim thay: ";
    for (int x : result)
        flights[x].print();

    cout << "Nhap ngay va noi xuat phat ban muon tim kiem" << endl;
    cout << "Nhap ngay (theo dinh dang YYYY/MM/DD): ";

    string date, from, to;
    getline(cin, date);
    while (not check_date(date)) {
        cout << "Nhap sai dinh dang hoac ngay khong hop le, vui long nhap lai: ";
        getline(cin, date);
    }

    cout << "Nhap noi xuat phat(toi da 20 ki tu, khong co so va ki tu dac biet): ";
    getline(cin, from);
    while (not check_location(from)) {
        cout << "Nhap sai dinh dang, vui long nhap lai noi xuat phat: ";
        getline(cin, from);
    }

    result.clear();
    for (int i = 1; i <= n; i++) {
        if (flights[i].find_flight_by_date_and_from(date, from))
            result.push_back(i);
    }

    cout << "Co " << sz(result) << " ket qua tim thay: ";
    for (int x : result)
        flights[x].print();

    cout << "Nhap noi di va noi den can tra cuu" << endl;
    cout << "Nhap noi di(toi da 20 ki tu, khong co so va ki tu dac biet): ";
    getline(cin, from);
    while (not check_location(from)) {
        cout << "Nhap sai dinh dang, vui long nhap lai noi di: ";
        getline(cin, from);
    }

    cout << "Nhap noi den(toi da 20 ki tu, khong co so va ki tu dac biet): ";
    getline(cin, to);
    while (not check_location(to)) {
        cout << "Nhap sai dinh dang, vui long nhap lai noi den: ";
        getline(cin, to);
    }

    result.clear();
    for (int i = 1; i <= n; i++) {
        if (flights[i].find_flight_by_from_and_to(from, to))
            result.push_back(i);
    }

    cout << "Co " << sz(result) << " ket qua tim thay: ";
    for (int x : result)
        flights[x].print();
}

int main () {
    input();
    solve();
}
