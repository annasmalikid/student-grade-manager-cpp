#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>
#include <string>

using namespace std;

// Struktur untuk menyimpan data Mahasiswa
struct Mahasiswa {
    string nama;
    float nilai_tugas;
    float nilai_uts;
    float nilai_uas;
    float nilai_akhir;
    char grade;
};

// Fungsi untuk menghitung nilai akhir dengan bobot 20%, 30%, 50%
float hitung_nilai_akhir(float tugas, float uts, float uas) {
    return tugas * 0.2 + uts * 0.3 + uas * 0.5;
}

// Fungsi untuk menentukan grade
char tentukan_grade(float nilai_akhir) {
    if (nilai_akhir >= 85)
        return 'A';
    else if (nilai_akhir >= 75)
        return 'B';
    else if (nilai_akhir >= 65)
        return 'C';
    else if (nilai_akhir >= 55)
        return 'D';
    else
        return 'E';
}

// Fungsi Validasi Input Nilai (Penting untuk aplikasi profesional)
float getInputNilai(const string& prompt) {
    float nilai;
    while (true) {
        cout << prompt;
        // Cek apakah input valid (berupa angka)
        if (!(cin >> nilai)) {
            cout << "❌ Input Error: Masukkan hanya nilai angka.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        // Cek rentang nilai
        if (nilai >= 0 && nilai <= 100) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bersihkan buffer
            return nilai;
        } else {
            cout << "⚠️ Nilai harus antara 0 dan 100. Coba lagi.\n";
        }
    }
}

int main() {
    int jumlah_siswa;

    cout << "=================================================\n";
    cout << "  PROGRAM SISTEM PENILAIAN MAHASISWA (C++) \n";
    cout << "  Bobot: Tugas 20%, UTS 30%, UAS 50% \n";
    cout << "=================================================\n";

    // Validasi input jumlah siswa (sederhana)
    cout << "Masukkan jumlah siswa: ";
    if (!(cin >> jumlah_siswa) || jumlah_siswa <= 0) {
        cout << "❌ Input tidak valid atau jumlah siswa nol. Program dihentikan.\n";
        return 1;
    }
    // Membersihkan buffer setelah cin >> jumlah_siswa
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<Mahasiswa> daftar_siswa;

    // Input data siswa
    for (int i = 0; i < jumlah_siswa; ++i) {
        Mahasiswa siswa;

        cout << "\n--- Data Siswa ke-" << i + 1 << " ---\n";
        cout << "Nama Siswa: ";
        // Menggunakan getline untuk nama yang mengandung spasi
        getline(cin, siswa.nama);
        
        // Menggunakan fungsi validasi yang baru
        siswa.nilai_tugas = getInputNilai("Nilai Tugas (0-100): ");
        siswa.nilai_uts = getInputNilai("Nilai UTS (0-100): ");
        siswa.nilai_uas = getInputNilai("Nilai UAS (0-100): ");

        // Hitung nilai akhir dan tentukan grade
        siswa.nilai_akhir = hitung_nilai_akhir(siswa.nilai_tugas, siswa.nilai_uts, siswa.nilai_uas);
        siswa.grade = tentukan_grade(siswa.nilai_akhir);

        daftar_siswa.push_back(siswa);
    }

    // Tampilkan tabel hasil
    cout << "\n========================================================================================\n";
    cout << left << setw(4) << "No"
         << left << setw(20) << "Nama Mahasiswa"
         << right << setw(10) << "Tugas"
         << right << setw(10) << "UTS"
         << right << setw(10) << "UAS"
         << right << setw(15) << "Nilai Akhir"
         << right << setw(10) << "GRADE" << endl;
    cout << "========================================================================================\n";

    // Set format untuk angka desimal
    cout << fixed << setprecision(2);
    
    for (int i = 0; i < jumlah_siswa; ++i) {
        cout << left << setw(4) << i + 1
             << left << setw(20) << daftar_siswa[i].nama.substr(0, 18) // Batasi panjang nama
             << right << setw(10) << daftar_siswa[i].nilai_tugas
             << right << setw(10) << daftar_siswa[i].nilai_uts
             << right << setw(10) << daftar_siswa[i].nilai_uas
             << right << setw(15) << daftar_siswa[i].nilai_akhir
             << right << setw(10) << daftar_siswa[i].grade << endl;
    }
    cout << "========================================================================================\n";

    return 0;
}
