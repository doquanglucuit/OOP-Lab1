#include<bits/stdc++.h>
#define sz(x) (int) (x).size()

using namespace std;


vector<int> z_function (const string &A) { // Thuật toán Z-function
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

bool check_valid_name (const string &s) { // Kiểm tra xem tên có hợp lệ hay không
    bool ok = 0 < sz(s) and sz(s) <= 40;
    for (int i = 0; i < sz(s); i++)
        ok &= (s[i] == ' ') or ('a' <= s[i] and s[i] <= 'z') or ('A' <= s[i] and s[i] <= 'Z');
    return ok;
}

struct Student {
    string hoten;
    double toan, van, ngoaingu;

    Student () {}
    Student (string _hoten, double _toan, double _van, double _ngoaingu): hoten(_hoten), toan(_toan), van(_van), ngoaingu(_ngoaingu) {}
    void input () {
        // Hàm nhập dữ liệu học sinh, yêu cầu nhập lại khi nhập sai.
        cout << "Nhap ho ten(chi chua ki tu trang, chu hoa va chu thuong, khong duoc de trong va toi da 40 ki tu): ";
        cin.ignore();
        getline(cin, hoten);
        while (not check_valid_name(hoten)) {
            cout << "Khong hop le, vui long nhap lai: ";
            getline(cin, hoten);
        }

        cout << "Nhap diem toan: ";
        while (cin >> toan) {
            if (toan > 10.0 or toan < 0) cout << "Nhap diem toan khong hop le, vui long nhap lai: ";
            else break;
        }
        cout << "Nhap diem van: ";
        while (cin >> van) {
            if (van > 10.0 or van < 0) cout << "Nhap diem van khong hop le, vui long nhap lai: ";
            else break;
        }
        cout << "Nhap diem ngoai ngu: ";
        while (cin >> ngoaingu) {
            if (ngoaingu > 10.0 or ngoaingu < 0) cout << "Nhap diem ngoai ngu khong hop le, vui long nhap lai: ";
            else break;
        }
    }

    double dtb () { return 0.25 * (2.0 * toan + van + ngoaingu); } // Theo công thức trong đề.

    string xeploai () {
        double d = this->dtb();
        if (d >= 9) return "Xuat sac";
        else if (d >= 8) return "Gioi";
        else if (d >= 6.5) return "Kha";
        else if (d >= 5) return "Trung Binh";
        return "Yeu";
    }

    bool find_key (const string &key) { // trả về true nếu key khớp 1 phần với hoten
        string tmp = key + '#' + hoten;
        for (int i = 0; i < sz(tmp); i++) {
            if ('A' <= tmp[i] and tmp[i] <= 'Z') tmp[i] = tmp[i] - 'A' + 'a';
        }
        vector<int> z = z_function(tmp);
        for (int i = sz(key) + 1; i < sz(tmp); i++) if (z[i] == sz(key))
            return true;
        return false;
    }

    void print() {
        cout << "Ho ten: " << hoten << ',';
        cout << "Diem trung binh: " << this->dtb() << ',';
        cout << "Xep loai: " << this->xeploai() << ',';
        cout << endl;
    }
};


int main () {
    int n;
    vector<Student> students;
    cout << "Nhap so luong hoc sinh: "; cin >> n;
    students.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cout << "Hoc sinh " << i << ":" << endl;
        students[i].input();
    }

    vector<int> max_average_index;
    max_average_index.push_back(1);
    for (int i = 2; i <= n; i++) {
        if (students[i].dtb() > students[max_average_index.back()].dtb()) {
            max_average_index.clear();
            max_average_index.push_back(i);
        }
        else if (students[i].dtb() == students[max_average_index.back()].dtb()) {
            max_average_index.push_back(i);
        }
    }

    cout << "Thong tin cua cac hoc sinh: " << endl;
    for (int i = 1; i <= n; i++) {
        cout << "Hoc sinh " << i <<": ";
        students[i].print();
    }
    cout << "Co " << sz(max_average_index) << " hoc sinh co diem toan cao nhat:" << endl;
    for (int id : max_average_index) {
        cout << "Hoc sinh " << id <<": ";
        students[id].print();
    }

    vector<int> min_average_index;
    min_average_index.push_back(1);
    for (int i = 2; i <= n; i++) {
        if (students[i].dtb() < students[min_average_index.back()].dtb()) {
            min_average_index.clear();
            min_average_index.push_back(i);
        }
        else if (students[i].dtb() == students[min_average_index.back()].dtb()) {
            min_average_index.push_back(i);
        }
    }
    cout << "Danh sach cac hoc sinh co diem trung binh thap nhat: ";
    for (int id : min_average_index) cout << "Hoc sinh " << id << ", "; cout << endl;

    cin.ignore();
    string key_name;
    cout << "Nhap tu khoa tim kiem: "; getline(cin, key_name);
    if (not check_valid_name(key_name)) cout << "Tu khoa khong hop le, khong tim thay ket qua." << endl;
    else {
        vector<int> result;
        for (int i = 1; i <= n; i++) if (students[i].find_key(key_name))
            result.push_back(i);
        cout << "Co " << sz(result) << " ket qua tim thay:" << endl;
        for (int x : result) cout << "Hoc sinh " << x << ": " << students[x].hoten << endl;
    }

}
