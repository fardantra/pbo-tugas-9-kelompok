/*
 * Nama         : Jovianie, Fardan, Newten
 * NPM          : 140810240010, 140810240084, 140810240090
 * Nama Program : Parkir.cpp (Sistem Parkir)
 * Tanggal      : 21 Oktober 2025
 */

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

class Time {
private:
    int jam;
    int menit;
    int detik;

public:
    Time() {
        jam = 0;
        menit = 0;
        detik = 0;
    }

    int parseTime(string waktu) {
        string parts[3];
        int idx = 0;
        string temp = "";
        
        if (waktu.find(":") != string::npos) {
            for (int i = 0; i < waktu.length(); i++) {
                if (waktu[i] == ':') {
                    parts[idx++] = temp;
                    temp = "";
                } else {
                    temp += waktu[i];
                }
            }
            parts[idx] = temp;
        } else {
            istringstream iss(waktu);
            for (int i = 0; i < 3; i++) {
                iss >> parts[i];
            }
        }

        if (idx != 2 && (parts[0].empty() || parts[1].empty() || parts[2].empty())) {
            throw invalid_argument("Format waktu tidak valid. Gunakan format HH:MM:SS atau 'HH MM SS'");
        }

        try {
            int p0 = stoi(parts[0]);
            int p1 = stoi(parts[1]);
            int p2 = stoi(parts[2]);

            if (p0 < 0 || p0 >= 24 || p1 < 0 || p1 >= 60 || p2 < 0 || p2 >= 60) {
                throw invalid_argument("Nilai jam, menit, atau detik di luar batas.");
            }

            setJam(p0);
            setMenit(p1);
            setDetik(p2);

            return toDetik();
        } catch (...) {
            throw invalid_argument("Format waktu tidak valid. Gunakan angka untuk jam, menit, dan detik.");
        }
    }

    Time(int jam, int menit, int detik) {
        if (jam >= 0 && jam < 24) {
            this->jam = jam;
        } else {
            this->jam = 0;
        }

        if (menit >= 0 && menit < 60) {
            this->menit = menit;
        } else {
            this->menit = 0;
        }

        if (detik >= 0 && detik < 60) {
            this->detik = detik;
        } else {
            this->detik = 0;
        }
    }

    int getJam() {
        return this->jam;
    }

    void setJam(int jam) {
        if (jam >= 0 && jam < 24) {
            this->jam = jam;
        } else {
            this->jam = 0;
        }
    }

    int getMenit() {
        return this->menit;
    }

    void setMenit(int menit) {
        if (menit >= 0 && menit < 60) {
            this->menit = menit;
        } else {
            this->menit = 0;
        }
    }

    int getDetik() {
        return this->detik;
    }

    void setDetik(int detik) {
        if (detik >= 0 && detik < 60) {
            this->detik = detik;
        } else {
            this->detik = 0;
        }
    }

    void inputTime() {
        while (true) {
            cout << "Masukkan waktu (HH:MM:SS atau HH MM SS): ";
            string waktuInput;
            getline(cin, waktuInput);
            try {
                parseTime(waktuInput);
                break;
            } catch (invalid_argument& e) {
                cout << "Input waktu tidak valid: " << e.what() << endl;
                cout << "Coba lagi." << endl;
            }
        }
    }

    int toDetik() {
        return this->jam * 3600 + this->menit * 60 + this->detik;
    }

    string toString() {
        ostringstream oss;
        oss << setfill('0') << setw(2) << this->jam << ":"
            << setw(2) << this->menit << ":"
            << setw(2) << this->detik;
        return oss.str();
    }

    void setNow() {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        this->jam = ltm->tm_hour;
        this->menit = ltm->tm_min;
        this->detik = ltm->tm_sec;
    }
};

class Date {
private:
    int tahun;
    int bulan;
    int tanggal;

public:
    Date() {
        this->tahun = 0;
        this->bulan = 0;
        this->tanggal = 0;
    }

    Date(int tahun, int bulan, int tanggal) {
        setTahun(tahun);
        setBulan(bulan);
        setTanggal(tanggal);
    }

    int getTahun() {
        return this->tahun;
    }

    void setTahun(int tahun) {
        if (tahun >= 0) {
            this->tahun = tahun;
        } else {
            this->tahun = 0;
        }
    }

    int getBulan() {
        return this->bulan;
    }

    void setBulan(int bulan) {
        if (bulan > 0 && bulan <= 12) {
            this->bulan = bulan;
        } else {
            this->bulan = 0;
        }
    }

    int getTanggal() {
        return this->tanggal;
    }

    bool isKabisat() {
        return (this->tahun % 400 == 0 || (this->tahun % 4 == 0 && this->tahun % 100 != 0));
    }

    void setTanggal(int tanggal) {
        int hariNormal[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int hariKabisat[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int maxTanggal = 0;

        bool kabisat = isKabisat();

        if (this->bulan > 0 && this->bulan <= 12) {
            maxTanggal = (kabisat ? hariKabisat[this->bulan - 1] : hariNormal[this->bulan - 1]);
        }

        if (tanggal > 0 && tanggal <= maxTanggal) {
            this->tanggal = tanggal;
        } else {
            this->tanggal = 0;
        }
    }

    void inputDate() {
        while (true) {
            cout << "Masukkan tanggal (DD/MM/YYYY atau DD MM YYYY): ";
            string line;
            getline(cin, line);
            try {
                parseDate(line);
                break;
            } catch (invalid_argument& e) {
                cout << "Input tanggal tidak valid: " << e.what() << endl;
                cout << "Coba lagi." << endl;
            }
        }
    }

    void parseDate(string s) {
        string parts[3];
        int idx = 0;
        string temp = "";

        if (s.find("/") != string::npos) {
            for (int i = 0; i < s.length(); i++) {
                if (s[i] == '/') {
                    parts[idx++] = temp;
                    temp = "";
                } else {
                    temp += s[i];
                }
            }
            parts[idx] = temp;
        } else {
            istringstream iss(s);
            for (int i = 0; i < 3; i++) {
                iss >> parts[i];
            }
        }

        if (parts[0].empty() || parts[1].empty() || parts[2].empty()) {
            throw invalid_argument("Format tanggal tidak valid. Gunakan DD MM YYYY");
        }

        try {
            int p0 = stoi(parts[0]);
            int p1 = stoi(parts[1]);
            int p2 = stoi(parts[2]);
            int day = p0;
            int month = p1;
            int year = p2;

            if (year < 0) {
                throw invalid_argument("Tahun tidak boleh negatif.");
            }

            if (year < 1000 || year > 9999) {
                throw invalid_argument("Tahun harus 4 digit (YYYY). Contoh: 2025");
            }

            if (month < 1 || month > 12) {
                throw invalid_argument("Bulan harus antara 1 dan 12.");
            }

            bool kabisat = (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
            int hariNormal[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            int hariKabisat[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            int maxTanggal = (kabisat ? hariKabisat[month - 1] : hariNormal[month - 1]);

            if (day < 1 || day > maxTanggal) {
                throw invalid_argument("Tanggal harus antara 1 dan " + to_string(maxTanggal) + " untuk bulan tersebut.");
            }

            setTahun(year);
            setBulan(month);
            setTanggal(day);
        } catch (...) {
            throw invalid_argument("Format tanggal tidak valid. Gunakan angka untuk tanggal, bulan, tahun.");
        }
    }

    string toString() {
        ostringstream oss;
        oss << setfill('0') << setw(2) << this->tanggal << "/"
            << setw(2) << this->bulan << "/"
            << setw(4) << this->tahun;
        return oss.str();
    }

    int toHari() {
        int totalHari;
        int year = getTahun();
        int month = getBulan();
        int date = getTanggal();

        int hariNormal[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int hariKabisat[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        bool kabisat = isKabisat();
        totalHari = date;

        for (int i = 0; i < month - 1; i++) {
            totalHari += (kabisat ? hariKabisat[i] : hariNormal[i]);
        }

        for (int t = 0; t < year; t++) {
            bool kab = (t % 400 == 0 || (t % 4 == 0 && t % 100 != 0));
            totalHari += (kab ? 366 : 365);
        }
        return totalHari;
    }

    void setNow() {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        this->tahun = 1900 + ltm->tm_year;
        this->bulan = 1 + ltm->tm_mon;
        this->tanggal = ltm->tm_mday;
    }
};

class Waktu {
private:
    Date date;
    Time time;

public:
    Waktu() {
        this->date = Date();
        this->time = Time();
    }

    Waktu(Date date, Time time) {
        this->date = date;
        this->time = time;
    }

    Date& getDate() {
        return this->date;
    }

    void setDate(Date date) {
        this->date = date;
    }

    Time& getTime() {
        return this->time;
    }

    void setTime(Time time) {
        this->time = time;
    }
};

class Person {
private:
    string nama;
    string alamat;

public:
    Person(string nama, string alamat) {
        this->nama = nama;
        this->alamat = alamat;
    }

    Person() {
        this->nama = "";
        this->alamat = "";
    }

    string getNama() {
        return this->nama;
    }

    void setNama(string nama) {
        this->nama = nama;
    }

    string getAlamat() {
        return this->alamat;
    }

    void setAlamat(string alamat) {
        this->alamat = alamat;
    }

    void inputPerson() {
        cout << "=== Data Pemilik ===" << endl;
        cout << "Nama: ";
        string nama;
        getline(cin, nama);
        setNama(nama);
        cout << "Alamat: ";
        string alamat;
        getline(cin, alamat);
        setAlamat(alamat);
    }
};

class Kendaraan {
private:
    Waktu waktuDatang;
    Waktu waktuPulang;
    Person pemilik;
    string noKendaraan;
    int status;

public:
    Kendaraan(string noKendaraan) {
        this->pemilik = Person();
        this->noKendaraan = noKendaraan;
        this->status = 0;
    }

    Kendaraan() {
        this->waktuDatang = Waktu();
        this->waktuPulang = Waktu();
        this->pemilik = Person();
        this->noKendaraan = "";
        this->status = 0;
    }

    Waktu& getWaktuDatang() {
        return this->waktuDatang;
    }

    void setWaktuDatang(Waktu waktuDatang) {
        this->waktuDatang = waktuDatang;
    }

    Waktu& getWaktuPulang() {
        return this->waktuPulang;
    }

    void setWaktuPulang(Waktu waktuPulang) {
        this->waktuPulang = waktuPulang;
    }

    int getStatus() {
        return this->status;
    }

    void setStatus(int status) {
        if (status == 0 || status == 1) {
            this->status = status;
        } else {
            cout << "Status tidak valid." << endl;
            exit(-1);
        }
    }

    string getNoKendaraan() {
        return this->noKendaraan;
    }

    Person& getPemilik() {
        return this->pemilik;
    }

    void setPemilik(Person pemilik) {
        this->pemilik = pemilik;
    }

    void setNoKendaraan(string noKendaraan) {
        this->noKendaraan = noKendaraan;
    }

    string getStatusString() {
        return (this->status == 0) ? "Reguler" : "Menginap";
    }

    int lamaHari() {
        int selisihHari = waktuPulang.getDate().toHari() - waktuDatang.getDate().toHari();
        if (selisihHari < 0) {
            selisihHari = 0;
        }
        return selisihHari;
    }

    Time lamaJam() {
        int detikDatang = waktuDatang.getTime().toDetik();
        int detikPulang = waktuPulang.getTime().toDetik();
        int selisih = detikPulang - detikDatang;
        if (selisih < 0) {
            selisih += 24 * 3600;
        }

        int jam = selisih / 3600;
        int menit = (selisih % 3600) / 60;
        int detik = selisih % 60;

        return Time(jam, menit, detik);
    }

    string getLamaJamString(Time waktu) {
        ostringstream oss;
        oss << setfill('0') << setw(2) << waktu.getJam() << ":"
            << setw(2) << waktu.getMenit() << ":"
            << setw(2) << waktu.getDetik();
        return oss.str();
    }

    virtual int hitungBiaya() {
        return 0;
    }

    void inputKendaraan() {
        pemilik.inputPerson();

        cout << "Masukkan nomor kendaraan: ";
        string noKend;
        getline(cin, noKend);
        setNoKendaraan(noKend);

        cout << "Masukkan status parkir (0 = Reguler, 1 = Menginap): ";
        string statusStr;
        getline(cin, statusStr);
        setStatus(stoi(statusStr));

        cout << "Gunakan waktu otomatis dari sistem? (y/n): ";
        string pilihan;
        getline(cin, pilihan);

        if (pilihan == "y" || pilihan == "Y") {
            waktuDatang.getDate().setNow();
            waktuDatang.getTime().setNow();
            cout << "Tekan 'Enter' untuk pulang dari parkir: ";
            string enter;
            getline(cin, enter);
            waktuPulang.getDate().setNow();
            waktuPulang.getTime().setNow();
        } else {
            cout << "=== Waktu datang ===" << endl;
            waktuDatang.getDate().inputDate();
            waktuDatang.getTime().inputTime();
            cout << "=== Waktu pulang ===" << endl;
            waktuPulang.getDate().inputDate();
            waktuPulang.getTime().inputTime();
        }
    }

    virtual string getClassName() {
        return "Kendaraan";
    }
};

class Mobil : public Kendaraan {
public:
    Mobil() : Kendaraan() {}

    Mobil(string noKendaraan) : Kendaraan(noKendaraan) {}

    int hitungBiaya() override {
        if (getStatus() == 1) {
            return 15000 * (lamaHari() + 1);
        } else {
            Time t = lamaJam();
            double jam = t.getJam() + t.getMenit() / 60.0;
            return (int)ceil(jam) * 2000;
        }
    }

    string getClassName() override {
        return "Mobil";
    }
};

class Motor : public Kendaraan {
public:
    Motor() : Kendaraan() {}

    Motor(string noKendaraan) : Kendaraan(noKendaraan) {}

    int hitungBiaya() override {
        if (getStatus() == 1) {
            return 25000 * (lamaHari() + 1);
        } else {
            Time t = lamaJam();
            double jam = t.getJam() + t.getMenit() / 60.0;
            return (int)ceil(jam) * 3000;
        }
    }

    string getClassName() override {
        return "Motor";
    }
};

class Truk : public Kendaraan {
public:
    Truk() : Kendaraan() {}

    Truk(string noKendaraan) : Kendaraan(noKendaraan) {}

    int hitungBiaya() override {
        if (getStatus() == 1) {
            return 40000 * (lamaHari() + 1);
        } else {
            Time t = lamaJam();
            double jam = t.getJam() + t.getMenit() / 60.0;
            return (int)ceil(jam) * 5000;
        }
    }

    string getClassName() override {
        return "Truk";
    }
};

class LarikKendaraan {
private:
    int n;
    Kendaraan** larikKendaraan;

public:
    LarikKendaraan() {
        n = 0;
        larikKendaraan = nullptr;
    }

    LarikKendaraan(int maxKendaraan) {
        this->larikKendaraan = new Kendaraan*[maxKendaraan];
        this->n = 0;
    }

    Kendaraan** getKendaraan() {
        return this->larikKendaraan;
    }

    void setKendaraan(Kendaraan** larikKendaraan) {
        this->larikKendaraan = larikKendaraan;
    }

    int getIndex() {
        return this->n;
    }

    void setIndex(int n) {
        this->n = n;
    }

    void tambahKendaraan(Kendaraan* kendaraan) {
        this->larikKendaraan[this->n] = kendaraan;
        this->n++;
    }

    string formatNumber(int num) {
        string s = to_string(num);
        string result = "";
        int count = 0;
        for (int i = s.length() - 1; i >= 0; i--) {
            if (count == 3) {
                result = "," + result;
                count = 0;
            }
            result = s[i] + result;
            count++;
        }
        return result;
    }

    void output() {
        cout << "\n\t\t\tDaftar Kendaraan Parkir" << endl;
        cout << string(180, '=') << endl;
        cout << left << setw(3) << "No" << " "
             << setw(8) << "NoKend" << " "
             << setw(10) << "JenisKend" << " "
             << setw(10) << "Status" << " "
             << setw(12) << "TglDatang" << " "
             << setw(12) << "TglPulang" << " "
             << setw(10) << "JamDatang" << " "
             << setw(10) << "JamPulang" << " "
             << setw(8) << "LamaHr" << " "
             << setw(12) << "LamaJam" << " "
             << setw(10) << "Biaya" << " "
             << setw(15) << "Nama Pemilik" << " "
             << setw(15) << "Alamat Pemilik" << endl;
        cout << string(180, '-') << endl;

        int totalBiaya = 0;
        for (int i = 0; i < n; i++) {
            Kendaraan* k = this->larikKendaraan[i];
            Time lamaJam = k->lamaJam();
            int biaya = k->hitungBiaya();
            totalBiaya += biaya;

            cout << left << setw(3) << (i + 1) << " "
                 << setw(8) << k->getNoKendaraan() << " "
                 << setw(10) << k->getClassName() << " "
                 << setw(10) << k->getStatusString() << " "
                 << setw(12) << k->getWaktuDatang().getDate().toString() << " "
                 << setw(12) << k->getWaktuPulang().getDate().toString() << " "
                 << setw(10) << k->getWaktuDatang().getTime().toString() << " "
                 << setw(10) << k->getWaktuPulang().getTime().toString() << " "
                 << setw(8) << k->lamaHari() << " "
                 << setw(12) << k->getLamaJamString(lamaJam) << " "
                 << setw(10) << formatNumber(biaya) << " "
                 << setw(15) << k->getPemilik().getNama() << " "
                 << setw(15) << k->getPemilik().getAlamat() << endl;
        }

        cout << string(180, '-') << endl;
        cout << "Total Biaya Parkir : " << formatNumber(totalBiaya) << endl;
    }
};

int main() {
    cout << "Masukkan jumlah kendaraan: ";
    string jumlahStr;
    getline(cin, jumlahStr);
    int jumlahKendaraan = stoi(jumlahStr);

    if (jumlahKendaraan <= 0) {
        cout << "Masukkan nomor yang valid." << endl;
        exit(-1);
    }

    LarikKendaraan larikKendaraan(jumlahKendaraan);

    for (int i = 0; i < jumlahKendaraan; i++) {
        cout << "\n=== Data Kendaraan ke-" << (i + 1) << " ===" << endl;
        cout << "Jenis Kendaraan: (0: Motor, 1: Mobil, 2: Truk): ";
        string jenisStr;
        getline(cin, jenisStr);
        int jenis = stoi(jenisStr);

        switch (jenis) {
            case 0: {
                Motor* motor = new Motor();
                motor->inputKendaraan();
                larikKendaraan.tambahKendaraan(motor);
                break;
            }
            case 1: {
                Mobil* mobil = new Mobil();
                mobil->inputKendaraan();
                larikKendaraan.tambahKendaraan(mobil);
                break;
            }
            case 2: {
                Truk* truk = new Truk();
                truk->inputKendaraan();
                larikKendaraan.tambahKendaraan(truk);
                break;
            }
            default:
                cout << "Nomor tidak valid." << endl;
                exit(-1);
                break;
        }
    }

    larikKendaraan.output();

    return 0;
}