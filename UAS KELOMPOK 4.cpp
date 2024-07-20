#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Barang {
    int id;
    string nama;
    int jumlah;
    double harga;
};

class Inventaris {
private:
    vector<Barang> daftarBarang;
    int nextId = 1;

public:
    void tambahBarang(const std::string& nama, int jumlah, double harga) {
        Barang barang = {nextId++, nama, jumlah, harga};
        daftarBarang.push_back(barang);
        std::cout << "Barang berhasil ditambahkan.\n";
    }

    void hapusBarang(int id) {
        auto it = find_if(daftarBarang.begin(), daftarBarang.end(),
                               [id](const Barang& b) { return b.id == id; });
        if (it != daftarBarang.end()) {
            daftarBarang.erase(it);
            cout << "Barang berhasil dihapus.\n";
        } else {
            cout << "Barang tidak ditemukan.\n";
        }
    }

    Barang* cariBarang(int id) {
        auto it = find_if(daftarBarang.begin(), daftarBarang.end(),
                               [id](const Barang& b) { return b.id == id; });
        if (it != daftarBarang.end()) {
            return &(*it);
        }
        return nullptr;
    }

    void updateBarang(int id, const string& nama, int jumlah, double harga) {
        Barang* barang = cariBarang(id);
        if (barang) {
            barang->nama = nama;
            barang->jumlah = jumlah;
            barang->harga = harga;
            cout << "Data barang berhasil diperbarui.\n";
        } else {
            cout << "Barang tidak ditemukan.\n";
        }
    }

    void tampilkanBarang() {
        if (daftarBarang.empty()) {
            cout << "Inventaris kosong.\n";
            return;
        }
        cout << "Daftar Barang:\n";
        for (const auto& barang : daftarBarang) {
        cout << "ID: " << barang.id << ", Nama: " << barang.nama
                      << ", Jumlah: " << barang.jumlah << ", Harga: " << barang.harga << "\n";
        }
    }
};
