/*
 * Nama         : Jovianie, Fardan, Newten
 * NPM          : 140810240010, 140810240084, 140810240090
 * Nama Program : Parkir.cpp (Sistem Parkir)
 * Tanggal      : 7 Oktober 2025
 */

import java.util.Scanner;

import static java.lang.System.exit;

class Time {
    private int jam;
    private int menit; 
    private int detik;

    public Time() {

    }

    public int parseTime(String waktu) {
        String[] parts;
        if (waktu.contains(":")) {
            parts = waktu.split(":");
        } else {
            parts = waktu.trim().split("\\s+");
        }

        if (parts.length != 3) {
            throw new IllegalArgumentException("Format waktu tidak valid. Gunakan format HH:MM:SS atau 'HH MM SS'");
        }

        try {
            int p0 = Integer.parseInt(parts[0]);
            int p1 = Integer.parseInt(parts[1]);
            int p2 = Integer.parseInt(parts[2]);

            if (p0 < 0 || p0 >= 24 || p1 < 0 || p1 >= 60 || p2 < 0 || p2 >= 60) {
                throw new IllegalArgumentException("Nilai jam, menit, atau detik di luar batas.");
            }

            setJam(p0);
            setMenit(p1);
            setDetik(p2);

            return toDetik();
        } catch (NumberFormatException e) {
            throw new IllegalArgumentException("Format waktu tidak valid. Gunakan angka untuk jam, menit, dan detik.");
        }
    }

    public Time(int jam, int menit, int detik){
        if (jam >= 0 && jam < 24){
            this.jam = jam;
        } else {
            this.jam = 0;
        }

        if (menit >= 0 && menit < 60){
            this.menit = menit;
        } else {
            this.menit = 0;
        }

        if (detik >= 0 && detik < 60){
            this.detik = detik; 
        } else {
            this.detik = 0;
        }
    } 

    public int getJam() {
        return this.jam;
    }

    public void setJam(int jam) {
        if (jam >= 0 && jam < 24){
            this.jam = jam;
        } else {
            this.jam = 0;
        }
    }

    public int getMenit() {
        return this.menit;
    }

    public void setMenit(int menit) {
        if (menit >= 0 && menit < 60){
            this.menit = menit;
        } else {
            this.menit = 0;
        }
    }

    public int getDetik() {
        return this.detik;
    }

    public void setDetik(int detik) {
        if (detik >= 0 && detik < 60){
            this.detik = detik;
        } else {
            this.detik = 0;
        }
    }
    
    public void inputTime(Scanner input){
        while (true) {
            System.out.print("Masukkan waktu (HH:MM:SS atau HH MM SS): ");
            String waktuInput = input.nextLine();
            try {
                parseTime(waktuInput);
                break;
            } catch (IllegalArgumentException e) {
                System.out.println("Input waktu tidak valid: " + e.getMessage());
                System.out.println("Coba lagi.");
            }
        }
    }
        
    public int toDetik(){
        return this.jam * 3600 + this.menit * 60 + this.detik;
    }

    @Override
    public String toString() {
        return String.format("%02d:%02d:%02d", this.jam, this.menit, this.detik);
    }
}

final class Date {
    private int tahun;
    private int bulan;
    private int tanggal;

    public Date() {
        this.tahun = 0;
        this.bulan = 0;
        this.tanggal = 0;
    }

    public Date(int tahun, int bulan, int tanggal) {
        setTahun(tahun);
        setBulan(bulan);
        setTanggal(tanggal);
    }

    public int getTahun() {
        return this.tahun;
    }
    public void setTahun(int tahun) {
        if (tahun >= 0){
            this.tahun = tahun;
        } else {
            this.tahun = 0;
        }
    }
    public int getBulan() { 
        return this.bulan;
    }
    public void setBulan(int bulan) {
        if (bulan > 0 && bulan <= 12){
            this.bulan = bulan;
        } else {
            this.bulan = 0;
        }
    }
    
    public int getTanggal() {
        return this.tanggal;
    }

    public boolean isKabisat(){
        return (this.tahun % 400 == 0 || (this.tahun % 4 == 0 && this.tahun % 100 != 0));
    }

    public void setTanggal(int tanggal) {
        int[] hariNormal = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int[] hariKabisat = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int maxTanggal = 0;

        boolean kabisat = isKabisat();

        if (this.bulan > 0 && this.bulan <= 12){
            maxTanggal = (kabisat ? hariKabisat[this.bulan-1] : hariNormal[this.bulan-1]);
        }

        if (tanggal > 0 && tanggal <= maxTanggal){
            this.tanggal = tanggal;
        } else {
            this.tanggal = 0;
        }
    }

    public void inputDate(Scanner input){
        while (true) {
            System.out.print("Masukkan tanggal (DD/MM/YYYY atau DD MM YYYY): ");
            String line = input.nextLine().trim();
            try {
                parseDate(line);
                break;
            } catch (IllegalArgumentException e) {
                System.out.println("Input tanggal tidak valid: " + e.getMessage());
                System.out.println("Coba lagi.");
            }
        }
    }

    public void parseDate(String s) {
        String[] parts;
        if (s.contains("/")) {
            parts = s.split("/");
        } else {
            parts = s.trim().split("\\s+");
        }

        if (parts.length != 3) {
            throw new IllegalArgumentException("Format tanggal tidak valid. Gunakan DD MM YYYY");
        }

        try {
            int p0 = Integer.parseInt(parts[0]);
            int p1 = Integer.parseInt(parts[1]);
            int p2 = Integer.parseInt(parts[2]);
            int day = p0;
            int month = p1;
            int year = p2;

            // Validasi year, month, day sebelum diset
            if (year < 0) {
                throw new IllegalArgumentException("Tahun tidak boleh negatif.");
            }

             // Validasi tahun 4 digit
            if (year < 1000 || year > 9999) {
                throw new IllegalArgumentException("Tahun harus 4 digit (YYYY). Contoh: 2025");
            }

            if (month < 1 || month > 12) {
                throw new IllegalArgumentException("Bulan harus antara 1 dan 12.");
            }

            // hitung maksimal tanggal berdasarkan bulan dan apakah kabisat
            boolean kabisat = (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
            int[] hariNormal = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            int[] hariKabisat = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            int maxTanggal = (kabisat ? hariKabisat[month-1] : hariNormal[month-1]);

            if (day < 1 || day > maxTanggal) {
                throw new IllegalArgumentException("Tanggal harus antara 1 dan " + maxTanggal + " untuk bulan tersebut.");
            }

            // semua valid, set ke field
            setTahun(year);
            setBulan(month);
            setTanggal(day);
        } catch (NumberFormatException e) {
            throw new IllegalArgumentException("Format tanggal tidak valid. Gunakan angka untuk tanggal, bulan, tahun.");
        }
    }

    @Override
    public String toString(){
        return String.format("%02d/%02d/%04d", this.tanggal, this.bulan, this.tahun);
    }

    public int toHari(){
        int totalHari;
        int year = getTahun();
        int month = getBulan();
        int date = getTanggal();

        int[] hariNormal = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int[] hariKabisat = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        boolean kabisat = isKabisat();
        totalHari = date;

        for (int i = 0; i < month - 1; i++){
            totalHari += (kabisat ? hariKabisat[i] : hariNormal[i]);
        }

        for (int t = 0; t < year; t++){
            boolean kab = (t % 400 == 0 || (t % 4 == 0 && t % 100 != 0));
            totalHari += (kab ? 366:365);
        }
        return totalHari;
    }
}

class Waktu {
    private Date date;
    private Time time;

    public Waktu() {
        this.date = new Date();
        this.time = new Time();
    }

    public Waktu(Date date, Time time){
        this.date = date;
        this.time = time;
    }

    public Date getDate() {
        return this.date;
    }

    public void setDate(Date date) {
        this.date = date;
    }

    public Time getTime() {
        return this.time;
    }

    public void setTime(Time time) {
        this.time = time;
    }
}

class Person {
    private String nama;
    private String alamat;

    public Person(String nama, String alamat) {
        this.nama = nama;
        this.alamat = alamat;
    }

    public Person() {
    }

    public String getNama() {
        return this.nama;
    }

    public void setNama(String nama) {
        this.nama = nama;
    }

    public String getAlamat() {
        return this.alamat;
    }

    public void setAlamat(String alamat) {
        this.alamat = alamat;
    }    

    public void inputPerson(){
        Scanner input = new Scanner (System.in);
        System.out.println("=== Data Pemilik ===");
        System.out.print("Nama: ");
        String nama = input.nextLine();
        setNama(nama);
        System.out.print("Alamat: ");
        String alamat = input.nextLine();
        setAlamat(alamat);
    }
}


abstract class Kendaraan {
    private Waktu waktuDatang;
    private Waktu waktuPulang;
    private Person pemilik;
    private String noKendaraan;
    private int status;


    public Kendaraan(String noKendaraan) {
        this.pemilik = new Person();
        this.noKendaraan = noKendaraan;
    }

    public Kendaraan() {
        this.waktuDatang = new Waktu();
        this.waktuPulang = new Waktu();
        this.pemilik = new Person();
    }

    public Waktu getWaktuDatang() {
        return this.waktuDatang;
    }

    public void setWaktuDatang(Waktu waktuDatang) {
        this.waktuDatang = waktuDatang;
    }

    public Waktu getWaktuPulang() {
        return this.waktuPulang;
    }

    public void setWaktuPulang(Waktu waktuPulang) {
        this.waktuPulang = waktuPulang;
    }

    public int getStatus() {
        return this.status;
    }

    public void setStatus(int status) {
        if (status == 0 || status == 1) {
            this.status = status;
        } else {
            System.out.println("Status tidak valid.");
            exit(-1);
        }
    }
    
    public String getNoKendaraan() {
        return this.noKendaraan;
    }
    
    public Person getPemilik() {
        return this.pemilik;
    }

    public void setPemilik(Person pemilik) {
        this.pemilik = pemilik;
    }

    public void setNoKendaraan(String noKendaraan) {
        this.noKendaraan = noKendaraan;
    }

    public String getStatusString(){ return (this.status==0)?"Reguler":"Menginap"; }

    public int lamaHari(){
        int selisihHari = waktuPulang.getDate().toHari() - waktuDatang.getDate().toHari();
        if (selisihHari < 0){
            selisihHari = 0;
        }
        return selisihHari;
    }

    public Time lamaJam(){
        int detikDatang = waktuDatang.getTime().toDetik();
        int detikPulang = waktuPulang.getTime().toDetik();
        int selisih = detikPulang - detikDatang;
        if (selisih < 0){
            selisih += 24*3600;
        }

        int jam = selisih / 3600;
        int menit = (selisih % 3600) / 60;
        int detik = selisih % 60;

        return new Time(jam, menit, detik);
    }

    public String getLamaJamString(Time waktu){
        return String.format("%02d:%02d:%02d", waktu.getJam(), waktu.getMenit(), waktu.getDetik());
    }

    public int hitungBiaya(){
        return 0;
    }

    public void inputKendaraan(Scanner input){
        pemilik.inputPerson();

        System.out.print("Masukkan nomor kendaraan: ");
        setNoKendaraan(input.nextLine());

        System.out.print("Masukkan status parkir (0 = Reguler, 1 = Menginap): ");
        setStatus(Integer.parseInt(input.nextLine()));

        System.out.println("=== Waktu datang ===");
        getWaktuDatang().getDate().inputDate(input);
        getWaktuDatang().getTime().inputTime(input);

        System.out.println("=== Waktu pulang ===");
        getWaktuPulang().getDate().inputDate(input);
        getWaktuPulang().getTime().inputTime(input);
    }
}

class Mobil extends Kendaraan {
    public Mobil(){
        super();
    }

    public Mobil(String noKendaraan){
        super(noKendaraan);
    }

    @Override
    public int hitungBiaya(){
        if (getStatus() == 1){
            return 15000 * (lamaHari() + 1);
        }
        else {
            Time t = lamaJam();
            double jam = t.getJam() + t.getMenit()/60.0;
            return (int)Math.ceil(jam) * 2000;
        }
    }
}

class Motor extends Kendaraan {
    public Motor(){
        super();
    }

    public Motor(String noKendaraan){
        super(noKendaraan);
    }

    @Override
    public int hitungBiaya(){
        if (getStatus() == 1){
            return 25000 * (lamaHari() + 1);
        }
        else {
            Time t = lamaJam();
            double jam = t.getJam() + t.getMenit()/60.0;
            return (int)Math.ceil(jam) * 3000;
        }
    }
}

class Truk extends Kendaraan {
    public Truk(){
        super();
    }

    public Truk(String noKendaraan){
        super(noKendaraan);
    }

    @Override
    public int hitungBiaya(){
        if (getStatus() == 1){
            return 40000 * (lamaHari() + 1);
        }
        else {
            Time t = lamaJam();
            double jam = t.getJam() + t.getMenit()/60.0;
            return (int)Math.ceil(jam) * 5000;
        }
    }
}

class LarikKendaraan {
    private int n;
    private Kendaraan[] larikKendaraan;

    public LarikKendaraan (){};

    public LarikKendaraan (int maxKendaraan){
        this.larikKendaraan = new Kendaraan[maxKendaraan];
        this.n = 0;
    }

    public Kendaraan[] getKendaraan() {
        return this.larikKendaraan;
    }

    public void setKendaraan(Kendaraan[] larikKendaraan) {
        this.larikKendaraan = larikKendaraan;
    }

    public int getIndex() {
        return this.n;
    }

    public void setIndex(int n) {
        this.n = n;
    }


    public void tambahKendaraan(Kendaraan kendaraan){
        this.larikKendaraan[this.n] = kendaraan;
        this.n++;
    }

    public void output(){
        System.out.println("\n\t\t\tDaftar Kendaraan Parkir");
        System.out.println("=".repeat(180));
        System.out.printf("%-3s %-8s %-10s %-10s %-12s %-12s %-10s %-10s %-8s %-12s %-10s %-15s %-15s%n",
                "No","NoKend","JenisKend","Status","TglDatang","TglPulang",
                "JamDatang","JamPulang","LamaHr","LamaJam","Biaya", "Nama Pemilik", "Alamat Pemilik");
        System.out.println("-".repeat(180));

        int totalBiaya = 0;
        for (int i = 0; i < n; i++){
            Kendaraan k = this.larikKendaraan[i];
            Time lamaJam = k.lamaJam();
            int biaya = k.hitungBiaya();
            totalBiaya += biaya;

            System.out.printf("%-3d %-8s %-10s %-10s %-12s %-12s %-10s %-10s %-8d %-12s %-10s %-15s %-15s%n",
                (i+1),
                k.getNoKendaraan(),
                k.getClass().getSimpleName(),
                k.getStatusString(),
                k.getWaktuDatang().getDate().toString(),
                k.getWaktuPulang().getDate().toString(),
                k.getWaktuDatang().getTime().toString(),
                k.getWaktuPulang().getTime().toString(),
                k.lamaHari(), k.getLamaJamString(lamaJam),
                String.format("%,d", biaya),

                k.getPemilik().getNama(), k.getPemilik().getAlamat()
            );
        }

        System.out.println("-".repeat(180));
        System.out.printf("Total Biaya Parkir : %,d%n", totalBiaya);
    }
}

public class Parkir { 
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        System.out.print("Masukkan jumlah kendaraan: ");
        int jumlahKendaraan = Integer.parseInt(input.nextLine());

        if (jumlahKendaraan <= 0){
            System.out.println("Masukkan nomor yang valid.");
            exit(-1);
        }
        
        LarikKendaraan larikKendaraan = new LarikKendaraan(jumlahKendaraan);

        for (int i = 0; i < jumlahKendaraan; i++){
            System.out.println("\n=== Data Kendaraan ke-" + (i + 1) + " ===");
            System.out.print("Jenis Kendaraan: (0: Motor, 1: Mobil, 2: Truk): ");
            switch (Integer.parseInt(input.nextLine())) {
                case 0:
                    Motor motor = new Motor();
                    motor.inputKendaraan(input);
                    larikKendaraan.tambahKendaraan(motor);
                    break;
                case 1:
                    Mobil mobil = new Mobil();
                    mobil.inputKendaraan(input);
                    larikKendaraan.tambahKendaraan(mobil);
                    break;
                case 2:
                    Truk truk = new Truk();
                    truk.inputKendaraan(input);
                    larikKendaraan.tambahKendaraan(truk);
                    break;
                default:
                    System.out.println("Nomor tidak valid.");
                    exit(-1);
                    break;
            }
        }

        larikKendaraan.output();
    }
}
