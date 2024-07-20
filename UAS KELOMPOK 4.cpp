#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Barang {
    int id;
    std::string nama;
    int jumlah;
    double harga;
};

class Inventaris {
private:
    std::vector<Barang> daftarBarang;
    int nextId = 1;

public:
    Inventaris() {
        // Menambahkan beberapa barang saat inisialisasi
        tambahBarang("Laptop", 10, 8000000);
        tambahBarang("Smartphone", 20, 3000000);
        tambahBarang("Tablet", 15, 4000000);
        tambahBarang("Headphone", 30, 500000);
        tambahBarang("Mouse", 50, 200000);
    }

    void tambahBarang(const std::string& nama, int jumlah, double harga) {
        Barang barang = {nextId++, nama, jumlah, harga};
        daftarBarang.push_back(barang);
    }

    void hapusBarang(int id) {
        auto it = std::find_if(daftarBarang.begin(), daftarBarang.end(),
                               [id](const Barang& b) { return b.id == id; });
        if (it != daftarBarang.end()) {
            daftarBarang.erase(it);
            std::cout << "Barang berhasil dihapus.\n";
        } else {
            std::cout << "Barang tidak ditemukan.\n";
        }
    }

    Barang* cariBarang(int id) {
        auto it = std::find_if(daftarBarang.begin(), daftarBarang.end(),
                               [id](const Barang& b) { return b.id == id; });
        if (it != daftarBarang.end()) {
            return &(*it);
        }
        return nullptr;
    }

    void updateBarang(int id, const std::string& nama, int jumlah, double harga) {
        Barang* barang = cariBarang(id);
        if (barang) {
            barang->nama = nama;
            barang->jumlah = jumlah;
            barang->harga = harga;
            std::cout << "Data barang berhasil diperbarui.\n";
        } else {
            std::cout << "Barang tidak ditemukan.\n";
        }
    }

    void tampilkanBarang() {
        if (daftarBarang.empty()) {
            std::cout << "Inventaris kosong.\n";
            return;
        }
        std::cout << "Daftar Barang:\n";
        for (const auto& barang : daftarBarang) {
            std::cout << "ID: " << barang.id << ", Nama: " << barang.nama
                      << ", Jumlah: " << barang.jumlah << ", Harga: " << barang.harga << "\n";
        }
    }
};

int main() {
    Inventaris inventaris;
    int pilihan;

    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Hapus Barang\n";
        std::cout << "2. Cari Barang\n";
        std::cout << "3. Update Barang\n";
        std::cout << "4. Tampilkan Semua Barang\n";
        std::cout << "0. Keluar\n";
        std::cout << "Pilihan Anda: ";
        std::cin >> pilihan;

        switch (pilihan) {
            case 1: {
                int id;
                std::cout << "ID barang yang akan dihapus: ";
                std::cin >> id;
                inventaris.hapusBarang(id);
                break;
            }
            case 2: {
                int id;
                std::cout << "ID barang yang dicari: ";
                std::cin >> id;
                Barang* barang = inventaris.cariBarang(id);
                if (barang) {
                    std::cout << "Barang ditemukan:\n";
                    std::cout << "ID: " << barang->id << ", Nama: " << barang->nama
                              << ", Jumlah: " << barang->jumlah << ", Harga: " << barang->harga << "\n";
                } else {
                    std::cout << "Barang tidak ditemukan.\n";
                }
                break;
            }
            case 3: {
                int id;
                std::string nama;
                int jumlah;
                double harga;
                std::cout << "ID barang yang akan diupdate: ";
                std::cin >> id;
                std::cout << "Nama baru: ";
                std::cin.ignore();
                std::getline(std::cin, nama);
                std::cout << "Jumlah baru: ";
                std::cin >> jumlah;
                std::cout << "Harga baru: ";
                std::cin >> harga;
                inventaris.updateBarang(id, nama, jumlah, harga);
                break;
            }
            case 4:
                inventaris.tampilkanBarang();
                break;
            case 0:
                std::cout << "Terima kasih telah menggunakan sistem inventaris.\n";
                break;
            default:
                std::cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);

    return 0;
}
