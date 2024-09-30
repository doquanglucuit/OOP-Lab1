#include <bits/stdc++.h>
using namespace std;

struct Ngay {
    int ngay, thang, nam;
};

struct ThongTinTaiKhoan {
    string maSo;
    string loaiTK;
    string hoTen;
    Ngay ngayMoSo;
    string cmnd;
    double soTien;
};

map<string, bool> quanLyTaiKhoan;
map<string, int> laiSuat;
vector<ThongTinTaiKhoan> dsTaiKhoan;

void hienThiTroGiup() {
    cout << "1: Mo tai khoan tiet kiem moi\n";
    cout << "2: Tim kiem thong tin tai khoan\n";
    cout << "3: Cap nhat lai suat\n";
    cout << "4: Tinh toan tien lai\n";
    cout << "5: Rut tien\n";
    cout << "6.1: Sap xep tai khoan theo so tien (giam dan)\n";
    cout << "6.2: Sap xep tai khoan theo ngay mo so (tang dan)\n";
    cout << "end: Thoat\n";
}

bool kiemTraMaSo(const string &maSo) {
    if (quanLyTaiKhoan[maSo]) {
        cout << "Tai khoan da ton tai\n";
        return false;
    }
    if (maSo.size() > 5) return false;

    return all_of(maSo.begin(), maSo.end(), [](char c) {
        return isalnum(c);
    });
}

bool kiemTraLoaiTK(const string &loai) {
    return (loai == "ngan han" || loai == "dai han");
}

bool kiemTraTen(const string &ten) {
    if (ten.size() > 30) return false;
    return all_of(ten.begin(), ten.end(), [](char c) {
        return isalpha(c) || isspace(c);
    });
}

bool kiemTraCMND(const string &cmnd) {
    return (cmnd.size() == 9 || cmnd.size() == 12) && all_of(cmnd.begin(), cmnd.end(), ::isdigit);
}

void nhapNgay(Ngay &ngay) {
    cout << "Nhap ngay (ngay thang nam): ";
    cin >> ngay.ngay >> ngay.thang >> ngay.nam;
}

bool kiemTraNgay(const Ngay &ngay) {
    if (ngay.nam < 1 || ngay.thang < 1 || ngay.thang > 12) return false;

    int soNgayTrongThang[] = {0, 31, 28, 31, 30, 31, 30, 31, 30, 31, 30, 31};
    bool namNhuan = (ngay.nam % 4 == 0 && ngay.nam % 100 != 0) || (ngay.nam % 400 == 0);

    if (namNhuan) soNgayTrongThang[2] = 29;
    return (ngay.ngay >= 1 && ngay.ngay <= soNgayTrongThang[ngay.thang]);
}

void moTaiKhoan() {
    ThongTinTaiKhoan tkMoi;

    cout << "Ma so tai khoan: ";
    getline(cin, tkMoi.maSo);
    while (!kiemTraMaSo(tkMoi.maSo)) {
        cout << "Ma so khong hop le. Vui long nhap lai: ";
        getline(cin, tkMoi.maSo);
    }
    quanLyTaiKhoan[tkMoi.maSo] = true;

    cout << "Chon loai tai khoan (ngan han hoac dai han): ";
    getline(cin, tkMoi.loaiTK);
    while (!kiemTraLoaiTK(tkMoi.loaiTK)) {
        cout << "Loai khong hop le. Vui long nhap 'ngan han' hoac 'dai han': ";
        getline(cin, tkMoi.loaiTK);
    }
    laiSuat[tkMoi.maSo] = (tkMoi.loaiTK == "ngan han") ? 6 : 7;

    cout << "Ho va ten: ";
    getline(cin, tkMoi.hoTen);
    while (!kiemTraTen(tkMoi.hoTen)) {
        cout << "Ten khong hop le. Vui long nhap lai: ";
        getline(cin, tkMoi.hoTen);
    }

    cout << "So chung minh nhan dan: ";
    getline(cin, tkMoi.cmnd);
    while (!kiemTraCMND(tkMoi.cmnd)) {
        cout << "CMND khong hop le. Vui long nhap lai: ";
        getline(cin, tkMoi.cmnd);
    }

    nhapNgay(tkMoi.ngayMoSo);
    while (!kiemTraNgay(tkMoi.ngayMoSo)) {
        cout << "Ngay khong hop le. Vui long nhap lai:\n";
        nhapNgay(tkMoi.ngayMoSo);
    }

    cout << "So tien gui: ";
    cin >> tkMoi.soTien;
    while (tkMoi.soTien < 0) {
        cout << "So tien khong the am. Vui long nhap lai: ";
        cin >> tkMoi.soTien;
    }
    cin.ignore();

    dsTaiKhoan.push_back(tkMoi);
}

bool soSanhTheoSoTien(const ThongTinTaiKhoan &a, const ThongTinTaiKhoan &b) {
    return a.soTien > b.soTien;
}

bool soSanhTheoNgayMo(const ThongTinTaiKhoan &a, const ThongTinTaiKhoan &b) {
    if (a.ngayMoSo.nam != b.ngayMoSo.nam) return a.ngayMoSo.nam < b.ngayMoSo.nam;
    if (a.ngayMoSo.thang != b.ngayMoSo.thang) return a.ngayMoSo.thang < b.ngayMoSo.thang;
    return a.ngayMoSo.ngay < b.ngayMoSo.ngay;
}

void timKiemTaiKhoan() {
    cout << "Chon mot lua chon:\n";
    cout << "1: Hien thi tat ca tai khoan\n";
    cout << "2: Tim kiem theo ma so\n";
    cout << "3: Tim kiem theo khoang thoi gian\n";
    int option;
    cin >> option;
    cin.ignore();

    vector<ThongTinTaiKhoan> ketQua;
    switch (option) {
        case 1:
            ketQua = dsTaiKhoan;
            break;
        case 2: {
            string maSo;
            cout << "Nhap ma so tai khoan: ";
            getline(cin, maSo);
            for (const auto &tk : dsTaiKhoan) {
                if (tk.maSo == maSo) {
                    ketQua.push_back(tk);
                }
            }
            break;
        }
        case 3: {
            Ngay batDau, ketThuc;
            cout << "Nhap ngay bat dau (ngay thang nam): ";
            cin >> batDau.ngay >> batDau.thang >> batDau.nam;
            while (!kiemTraNgay(batDau)) {
                cout << "Ngay khong hop le. Vui long nhap lai:\n";
                cin >> batDau.ngay >> batDau.thang >> batDau.nam;
            }

            cout << "Nhap ngay ket thuc (ngay thang nam): ";
            cin >> ketThuc.ngay >> ketThuc.thang >> ketThuc.nam;
            while (!kiemTraNgay(ketThuc)) {
                cout << "Ngay khong hop le. Vui long nhap lai:\n";
                cin >> ketThuc.ngay >> ketThuc.thang >> ketThuc.nam;
            }

            for (const auto &tk : dsTaiKhoan) {
                if (soSanhTheoNgayMo(tk, { "", "", "", batDau, "", 0 }) &&
                    soSanhTheoNgayMo({ "", "", "", ketThuc, "", 0 }, tk)) {
                    ketQua.push_back(tk);
                }
            }
            break;
        }
        default:
            cout << "Lua chon khong hop le\n";
            return;
    }

    cout << "Danh sach ket qua:\n";
    for (const auto &tk : ketQua) {
        cout << tk.maSo << ", " << tk.hoTen << ", " << tk.loaiTK << ", " << tk.cmnd
             << ", " << tk.ngayMoSo.ngay << "/" << tk.ngayMoSo.thang << "/" << tk.ngayMoSo.nam
             << ", " << tk.soTien << '\n';
    }
}

void rutTien() {
    string maSo;
    cout << "Nhap ma so tai khoan can rut: ";
    cin >> maSo;
    while (!quanLyTaiKhoan[maSo]) {
        cout << "Tai khoan khong ton tai. Nhap lai hoac go 'thoat' de thoat: ";
        cin >> maSo;
        if (maSo == "thoat") return;
    }

    double soTienRut;
    for (auto &tk : dsTaiKhoan) {
        if (tk.maSo == maSo) {
            cout << "So tien can rut: ";
            cin >> soTienRut;
            while (soTienRut < 0 || tk.soTien < soTienRut) {
                cout << "So tien rut khong hop le. Nhap lai: ";
                cin >> soTienRut;
            }
            tk.soTien -= soTienRut;
            cout << "Rut tien thanh cong. So du con lai: " << tk.soTien << '\n';
            break;
        }
    }
}

void capNhatLaiSuat() {
    string maSo;
    cout << "Nhap ma so tai khoan: ";
    getline(cin, maSo);
    while (!quanLyTaiKhoan[maSo]) {
        cout << "Tai khoan khong ton tai. Nhap lai hoac go 'thoat' de thoat: ";
        getline(cin, maSo);
        if (maSo == "thoat") return;
    }

    double lai;
    cout << "Nhap lai suat moi: ";
    cin >> lai;
    if (lai < 0) {
        cout << "Lai suat khong hop le. Vui long nhap lai.\n";
        return;
    }

    laiSuat[maSo] = lai;
    cout << "Cap nhat lai suat thanh cong cho tai khoan: " << maSo << '\n';
}

void tinhToanTienLai() {
    string maSo;
    cout << "Nhap ma so tai khoan: ";
    getline(cin, maSo);
    while (!quanLyTaiKhoan[maSo]) {
        cout << "Tai khoan khong ton tai. Nhap lai hoac go 'out' de thoat: ";
        getline(cin, maSo);
        if (maSo == "out") return;
    }

    for (const auto &tk : dsTaiKhoan) {
        if (tk.maSo == maSo) {
            Ngay hienTai;
            time_t now = time(0);
            tm *ltm = localtime(&now);
            hienTai.nam = 1900 + ltm->tm_year;
            hienTai.thang = 1 + ltm->tm_mon;
            hienTai.ngay = ltm->tm_mday;

            // Tinh so ngay giua hai ngay
            int soNgay = (hienTai.nam - tk.ngayMoSo.nam) * 365 + (hienTai.thang - tk.ngayMoSo.thang) * 30 + (hienTai.ngay - tk.ngayMoSo.ngay);
            double lai = (tk.soTien * soNgay * laiSuat[tk.maSo]) / 100;

            cout << "So tien lai: " << lai << '\n';
            break;
        }
    }
}

int main() {
    cout << "Kinh chao quy khach\n";
    hienThiTroGiup();

    string luaChon;
    while (true) {
        cout << "\nChon dich vu (1-6.2, 'help' hoac 'end'): ";
        cin >> luaChon;
        cin.ignore(); // Xoa bo dem nhap

        if (luaChon == "1") {
            moTaiKhoan();
        } else if (luaChon == "2") {
            timKiemTaiKhoan();
        } else if (luaChon == "3") {
            capNhatLaiSuat();
        } else if (luaChon == "4") {
            tinhToanTienLai();
        } else if (luaChon == "5") {
            rutTien();
        } else if (luaChon == "6.1") {
            sort(dsTaiKhoan.begin(), dsTaiKhoan.end(), soSanhTheoSoTien);
        } else if (luaChon == "6.2") {
            sort(dsTaiKhoan.begin(), dsTaiKhoan.end(), soSanhTheoNgayMo);
        } else if (luaChon == "help") {
            hienThiTroGiup();
        } else if (luaChon == "end") {
            break;
        } else {
            cout << "Lua chon khong hop le\n";
        }
    }

    return 0;
}
