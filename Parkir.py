"""
Nama         : Jovianie, Fardan, Newten
NPM          : 140810240010, 140810240084, 140810240090
Nama Program : Parkir.py (Sistem Parkir)
Tanggal      : 21 Oktober 2025
"""

from datetime import datetime
import sys
import math

class Time:
    def __init__(self, jam=0, menit=0, detik=0):
        self.jam = 0
        self.menit = 0
        self.detik = 0
        
        if 0 <= jam < 24:
            self.jam = jam
        
        if 0 <= menit < 60:
            self.menit = menit
        
        if 0 <= detik < 60:
            self.detik = detik
    
    def parse_time(self, waktu):
        if ':' in waktu:
            parts = waktu.split(':')
        else:
            parts = waktu.strip().split()
        
        if len(parts) != 3:
            raise ValueError("Format waktu tidak valid. Gunakan format HH:MM:SS atau 'HH MM SS'")
        
        try:
            p0 = int(parts[0])
            p1 = int(parts[1])
            p2 = int(parts[2])
            
            if p0 < 0 or p0 >= 24 or p1 < 0 or p1 >= 60 or p2 < 0 or p2 >= 60:
                raise ValueError("Nilai jam, menit, atau detik di luar batas.")
            
            self.set_jam(p0)
            self.set_menit(p1)
            self.set_detik(p2)
            
            return self.to_detik()
        except ValueError as e:
            if "invalid literal" in str(e):
                raise ValueError("Format waktu tidak valid. Gunakan angka untuk jam, menit, dan detik.")
            raise
    
    def get_jam(self):
        return self.jam
    
    def set_jam(self, jam):
        if 0 <= jam < 24:
            self.jam = jam
        else:
            self.jam = 0
    
    def get_menit(self):
        return self.menit
    
    def set_menit(self, menit):
        if 0 <= menit < 60:
            self.menit = menit
        else:
            self.menit = 0
    
    def get_detik(self):
        return self.detik
    
    def set_detik(self, detik):
        if 0 <= detik < 60:
            self.detik = detik
        else:
            self.detik = 0
    
    def input_time(self):
        while True:
            waktu_input = input("Masukkan waktu (HH:MM:SS atau HH MM SS): ")
            try:
                self.parse_time(waktu_input)
                break
            except ValueError as e:
                print(f"Input waktu tidak valid: {e}")
                print("Coba lagi.")
    
    def to_detik(self):
        return self.jam * 3600 + self.menit * 60 + self.detik
    
    def __str__(self):
        return f"{self.jam:02d}:{self.menit:02d}:{self.detik:02d}"
    
    def set_now(self):
        now = datetime.now()
        self.jam = now.hour
        self.menit = now.minute
        self.detik = now.second


class Date:
    def __init__(self, tahun=0, bulan=0, tanggal=0):
        self.tahun = 0
        self.bulan = 0
        self.tanggal = 0
        
        self.set_tahun(tahun)
        self.set_bulan(bulan)
        self.set_tanggal(tanggal)
    
    def get_tahun(self):
        return self.tahun
    
    def set_tahun(self, tahun):
        if tahun >= 0:
            self.tahun = tahun
        else:
            self.tahun = 0
    
    def get_bulan(self):
        return self.bulan
    
    def set_bulan(self, bulan):
        if 0 < bulan <= 12:
            self.bulan = bulan
        else:
            self.bulan = 0
    
    def get_tanggal(self):
        return self.tanggal
    
    def is_kabisat(self):
        return (self.tahun % 400 == 0 or (self.tahun % 4 == 0 and self.tahun % 100 != 0))
    
    def set_tanggal(self, tanggal):
        hari_normal = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
        hari_kabisat = [31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
        max_tanggal = 0
        
        kabisat = self.is_kabisat()
        
        if 0 < self.bulan <= 12:
            max_tanggal = hari_kabisat[self.bulan-1] if kabisat else hari_normal[self.bulan-1]
        
        if 0 < tanggal <= max_tanggal:
            self.tanggal = tanggal
        else:
            self.tanggal = 0
    
    def input_date(self):
        while True:
            line = input("Masukkan tanggal (DD/MM/YYYY atau DD MM YYYY): ").strip()
            try:
                self.parse_date(line)
                break
            except ValueError as e:
                print(f"Input tanggal tidak valid: {e}")
                print("Coba lagi.")
    
    def parse_date(self, s):
        if '/' in s:
            parts = s.split('/')
        else:
            parts = s.strip().split()
        
        if len(parts) != 3:
            raise ValueError("Format tanggal tidak valid. Gunakan DD MM YYYY")
        
        try:
            p0 = int(parts[0])
            p1 = int(parts[1])
            p2 = int(parts[2])
            day = p0
            month = p1
            year = p2
            
            if year < 0:
                raise ValueError("Tahun tidak boleh negatif.")
            
            if year < 1000 or year > 9999:
                raise ValueError("Tahun harus 4 digit (YYYY). Contoh: 2025")
            
            if month < 1 or month > 12:
                raise ValueError("Bulan harus antara 1 dan 12.")
            
            kabisat = (year % 400 == 0 or (year % 4 == 0 and year % 100 != 0))
            hari_normal = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
            hari_kabisat = [31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
            max_tanggal = hari_kabisat[month-1] if kabisat else hari_normal[month-1]
            
            if day < 1 or day > max_tanggal:
                raise ValueError(f"Tanggal harus antara 1 dan {max_tanggal} untuk bulan tersebut.")
            
            self.set_tahun(year)
            self.set_bulan(month)
            self.set_tanggal(day)
        except ValueError as e:
            if "invalid literal" in str(e):
                raise ValueError("Format tanggal tidak valid. Gunakan angka untuk tanggal, bulan, tahun.")
            raise
    
    def __str__(self):
        return f"{self.tanggal:02d}/{self.bulan:02d}/{self.tahun:04d}"
    
    def to_hari(self):
        year = self.get_tahun()
        month = self.get_bulan()
        date = self.get_tanggal()
        
        hari_normal = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
        hari_kabisat = [31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
        
        kabisat = self.is_kabisat()
        total_hari = date
        
        for i in range(month - 1):
            total_hari += hari_kabisat[i] if kabisat else hari_normal[i]
        
        for t in range(year):
            kab = (t % 400 == 0 or (t % 4 == 0 and t % 100 != 0))
            total_hari += 366 if kab else 365
        
        return total_hari
    
    def set_now(self):
        now = datetime.now()
        self.tahun = now.year
        self.bulan = now.month
        self.tanggal = now.day


class Waktu:
    def __init__(self, date=None, time=None):
        self.date = date if date is not None else Date()
        self.time = time if time is not None else Time()
    
    def get_date(self):
        return self.date
    
    def set_date(self, date):
        self.date = date
    
    def get_time(self):
        return self.time
    
    def set_time(self, time):
        self.time = time


class Person:
    def __init__(self, nama="", alamat=""):
        self.nama = nama
        self.alamat = alamat
    
    def get_nama(self):
        return self.nama
    
    def set_nama(self, nama):
        self.nama = nama
    
    def get_alamat(self):
        return self.alamat
    
    def set_alamat(self, alamat):
        self.alamat = alamat
    
    def input_person(self):
        print("=== Data Pemilik ===")
        nama = input("Nama: ")
        self.set_nama(nama)
        alamat = input("Alamat: ")
        self.set_alamat(alamat)


class Kendaraan:
    def __init__(self, no_kendaraan=""):
        self.waktu_datang = Waktu()
        self.waktu_pulang = Waktu()
        self.pemilik = Person()
        self.no_kendaraan = no_kendaraan
        self.status = 0
    
    def get_waktu_datang(self):
        return self.waktu_datang
    
    def set_waktu_datang(self, waktu_datang):
        self.waktu_datang = waktu_datang
    
    def get_waktu_pulang(self):
        return self.waktu_pulang
    
    def set_waktu_pulang(self, waktu_pulang):
        self.waktu_pulang = waktu_pulang
    
    def get_status(self):
        return self.status
    
    def set_status(self, status):
        if status == 0 or status == 1:
            self.status = status
        else:
            print("Status tidak valid.")
            sys.exit(-1)
    
    def get_no_kendaraan(self):
        return self.no_kendaraan
    
    def get_pemilik(self):
        return self.pemilik
    
    def set_pemilik(self, pemilik):
        self.pemilik = pemilik
    
    def set_no_kendaraan(self, no_kendaraan):
        self.no_kendaraan = no_kendaraan
    
    def get_status_string(self):
        return "Reguler" if self.status == 0 else "Menginap"
    
    def lama_hari(self):
        selisih_hari = self.waktu_pulang.get_date().to_hari() - self.waktu_datang.get_date().to_hari()
        if selisih_hari < 0:
            selisih_hari = 0
        return selisih_hari
    
    def lama_jam(self):
        detik_datang = self.waktu_datang.get_time().to_detik()
        detik_pulang = self.waktu_pulang.get_time().to_detik()
        selisih = detik_pulang - detik_datang
        if selisih < 0:
            selisih += 24 * 3600
        
        jam = selisih // 3600
        menit = (selisih % 3600) // 60
        detik = selisih % 60
        
        return Time(jam, menit, detik)
    
    def get_lama_jam_string(self, waktu):
        return f"{waktu.get_jam():02d}:{waktu.get_menit():02d}:{waktu.get_detik():02d}"
    
    def hitung_biaya(self):
        return 0
    
    def input_kendaraan(self):
        self.pemilik.input_person()
        
        self.set_no_kendaraan(input("Masukkan nomor kendaraan: "))
        
        self.set_status(int(input("Masukkan status parkir (0 = Reguler, 1 = Menginap): ")))
        
        pilihan = input("Gunakan waktu otomatis dari sistem? (y/n): ")
        
        if pilihan.lower() == 'y':
            self.get_waktu_datang().get_date().set_now()
            self.get_waktu_datang().get_time().set_now()
            input("Tekan 'Enter' untuk pulang dari parkir: ")
            self.get_waktu_pulang().get_date().set_now()
            self.get_waktu_pulang().get_time().set_now()
        else:
            print("=== Waktu datang ===")
            self.get_waktu_datang().get_date().input_date()
            self.get_waktu_datang().get_time().input_time()
            print("=== Waktu pulang ===")
            self.get_waktu_pulang().get_date().input_date()
            self.get_waktu_pulang().get_time().input_time()


class Mobil(Kendaraan):
    def __init__(self, no_kendaraan=""):
        super().__init__(no_kendaraan)
    
    def hitung_biaya(self):
        if self.get_status() == 1:
            return 15000 * (self.lama_hari() + 1)
        else:
            t = self.lama_jam()
            jam = t.get_jam() + t.get_menit() / 60.0
            return int(math.ceil(jam)) * 2000


class Motor(Kendaraan):
    def __init__(self, no_kendaraan=""):
        super().__init__(no_kendaraan)
    
    def hitung_biaya(self):
        if self.get_status() == 1:
            return 25000 * (self.lama_hari() + 1)
        else:
            t = self.lama_jam()
            jam = t.get_jam() + t.get_menit() / 60.0
            return int(math.ceil(jam)) * 3000


class Truk(Kendaraan):
    def __init__(self, no_kendaraan=""):
        super().__init__(no_kendaraan)
    
    def hitung_biaya(self):
        if self.get_status() == 1:
            return 40000 * (self.lama_hari() + 1)
        else:
            t = self.lama_jam()
            jam = t.get_jam() + t.get_menit() / 60.0
            return int(math.ceil(jam)) * 5000


class LarikKendaraan:
    def __init__(self, max_kendaraan=0):
        self.larik_kendaraan = [None] * max_kendaraan if max_kendaraan > 0 else []
        self.n = 0
    
    def get_kendaraan(self):
        return self.larik_kendaraan
    
    def set_kendaraan(self, larik_kendaraan):
        self.larik_kendaraan = larik_kendaraan
    
    def get_index(self):
        return self.n
    
    def set_index(self, n):
        self.n = n
    
    def tambah_kendaraan(self, kendaraan):
        self.larik_kendaraan[self.n] = kendaraan
        self.n += 1
    
    def output(self):
        print("\n\t\t\tDaftar Kendaraan Parkir")
        print("=" * 150)
        print(f"{'No':<3} {'NoKend':<8} {'JenisKend':<10} {'Status':<10} {'TglDatang':<12} {'TglPulang':<12} "
              f"{'JamDatang':<10} {'JamPulang':<10} {'LamaHr':<8} {'LamaJam':<12} {'Biaya':<10} "
              f"{'Nama Pemilik':<15} {'Alamat Pemilik':<15}")
        print("-" * 150)
        
        total_biaya = 0
        for i in range(self.n):
            k = self.larik_kendaraan[i]
            lama_jam = k.lama_jam()
            biaya = k.hitung_biaya()
            total_biaya += biaya
            
            print(f"{i+1:<3} "
                f"{k.get_no_kendaraan():<10} "
                f"{k.__class__.__name__:<10} "
                f"{k.get_status_string():<10} "
                f"{str(k.get_waktu_datang().get_date()):<12} "
                f"{str(k.get_waktu_pulang().get_date()):<12} "
                f"{str(k.get_waktu_datang().get_time()):<10} "
                f"{str(k.get_waktu_pulang().get_time()):<10} "
                f"{k.lama_hari():<6} "
                f"{k.get_lama_jam_string(lama_jam):<8} "
                f"{biaya:>10,}".replace(',', '.') + " "
                f"{k.get_pemilik().get_nama():<20} "
                f"{k.get_pemilik().get_alamat():<15}"
            )

        
        print("-" * 150)
        print(f"Total Biaya Parkir : {total_biaya:,}".replace(',', '.'))


def main():
    jumlah_kendaraan = int(input("Masukkan jumlah kendaraan: "))
    
    if jumlah_kendaraan <= 0:
        print("Masukkan nomor yang valid.")
        sys.exit(-1)
    
    larik_kendaraan = LarikKendaraan(jumlah_kendaraan)
    
    for i in range(jumlah_kendaraan):
        print(f"\n=== Data Kendaraan ke-{i + 1} ===")
        jenis = int(input("Jenis Kendaraan: (0: Motor, 1: Mobil, 2: Truk): "))
        
        if jenis == 0:
            motor = Motor()
            motor.input_kendaraan()
            larik_kendaraan.tambah_kendaraan(motor)
        elif jenis == 1:
            mobil = Mobil()
            mobil.input_kendaraan()
            larik_kendaraan.tambah_kendaraan(mobil)
        elif jenis == 2:
            truk = Truk()
            truk.input_kendaraan()
            larik_kendaraan.tambah_kendaraan(truk)
        else:
            print("Nomor tidak valid.")
            sys.exit(-1)
    
    larik_kendaraan.output()


if __name__ == "__main__":
    main()