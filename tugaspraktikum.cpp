#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <stdexcept>

using namespace std;

class TokoElektronik {
private:
    array<string, 3> etalase;

public:
    TokoElektronik() {
        etalase[0] = "Laptop ASUS";
        etalase[1] = "HP Samsung";
        etalase[2] = "TV LG";
    }

    string ambilProduk(size_t nomorRak) {
        try {
            return etalase.at(nomorRak);
        }
        catch (out_of_range& e) {
            throw runtime_error("Gagal Mengambil Barang : Rak nomor " + to_string(nomorRak) + " kosong atau tidak tersedia!");
        }
    }
};

void tampilkanGudang() {
    ifstream baca("gudang.txt");
    string baris;
    cout << "\n=== DATA BARANG GUDANG ===" << endl;
    
    if (baca.is_open()) {
        int no = 1;
        bool adaData = false;
        while (getline(baca, baris)) {
            cout << no << ". " << baris << endl;
            no++;
            adaData = true;
        }
        if (!adaData) {
            cout << "(Gudang kosong)" << endl;
        }
        baca.close();
    } else {
        cout << "(Belum ada data)" << endl;
    }
    cout << "==========================" << endl;
}

int main() {
    TokoElektronik tokoGibran;
    int pilihan;
    string namaBarang;

    do {
        tampilkanGudang();

        cout << "\n--- MENU TOKO GIBRAN JAYA ---" << endl;
        cout << "1. Tambah Barang (Create)" << endl;
        cout << "2. Ubah Barang (Update)" << endl;
        cout << "3. Hapus Barang (Delete)" << endl;
        cout << "4. Simulasi Cek Etalase (Exception)" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;

        if (pilihan == 1) {
            ofstream tulis("gudang.txt", ios::app);
            if (tulis.is_open()) {
                cout << "Masukkan nama barang baru: ";
                cin.ignore();
                getline(cin, namaBarang);
                tulis << namaBarang << endl;
                tulis.close();
                cout << "Barang berhasil disimpan!" << endl;
            }
        } 
        else if (pilihan == 2) {
            ifstream baca("gudang.txt");
            string listBarang[100];
            string baris;
            int total = 0;

            while (getline(baca, baris)) {
                listBarang[total] = baris;
                total++;
            }
            baca.close();

            if (total > 0) {
                int noUbah;
                cout << "Pilih nomor barang yg mau diubah: ";
                cin >> noUbah;

                if (noUbah > 0 && noUbah <= total) {
                    cout << "Masukkan nama barunya: ";
                    cin.ignore();
                    getline(cin, listBarang[noUbah - 1]);

                    ofstream tulis("gudang.txt");
                    for (int i = 0; i < total; i++) {
                        tulis << listBarang[i] << endl;
                    }
                    tulis.close();
                    cout << "Data berhasil diubah!" << endl;
                } else {
                    cout << "Nomor salah!" << endl;
                }
            }
        } 
        else if (pilihan == 3) {
            ifstream baca("gudang.txt");
            string listBarang[100];
            string baris;
            int total = 0;

            while (getline(baca, baris)) {
                listBarang[total] = baris;
                total++;
            }
            baca.close();

            if (total > 0) {
                int noHapus;
                cout << "Pilih nomor barang yg mau dihapus: ";
                cin >> noHapus;

                if (noHapus > 0 && noHapus <= total) {
                    ofstream tulis("gudang.txt");
                    for (int i = 0; i < total; i++) {
                        if (i == (noHapus - 1)) continue;
                        tulis << listBarang[i] << endl;
                    }
                    tulis.close();
                    cout << "Barang berhasil dihapus!" << endl;
                } else {
                    cout << "Nomor salah!" << endl;
                }
            }
        } 
        else if (pilihan == 4) {
            cout << "\n--- Menjalankan Simulasi Etalase ---" << endl;
            
            cout << "[Skenario 1] Coba ambil rak indeks 1..." << endl;
            try {
                string hasil = tokoGibran.ambilProduk(1);
                cout << "-> Sukses! Barangnya: " << hasil << endl;
            } 
            catch (runtime_error& e) {
                cout << "-> Error: " << e.what() << endl;
            }

            cout << "\n[Skenario 2] Coba ambil rak indeks 5..." << endl;
            try {
                string hasil = tokoGibran.ambilProduk(5);
                cout << "-> Sukses! Barangnya: " << hasil << endl;
            } 
            catch (runtime_error& e) {
                cout << "-> Error: " << e.what() << endl;
            }
        }
        else if (pilihan == 5) {
            cout << "Keluar dari program. Terima kasih!" << endl;
        }
        else {
            cout << "Pilihan tidak ada!" << endl;
        }

    } while (pilihan != 5);

    return 0;
}