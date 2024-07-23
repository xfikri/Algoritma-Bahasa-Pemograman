#include <iostream>
#include <limits>
#include <string>
using namespace std;

// Struct for item information
struct Barang {
    string namaBarang;
    string kondisi;
    int jumlah;
};

// Struct for login data
struct Login {
    string nama;
    string nim;
};

// Struct to store inventory data
struct Inventaris {
    Barang barang;
    Login login;
};

// Constant for array size
const int maxArray = 50;

// Declare array to store inventory data
Inventaris daftarInventaris[maxArray];
int totalBarang = 0, totalLogin = 0, pilihan;

// Function prototypes
int cariIndexBarang(const string& namaBarang);
int login();
void menu();
void lihatBarang();
void tambahBarang();
void updateBarang();
void hapusBarang();

// Main function
int main() {
    if (login()) {
        menu();
    }
    return 0;
}

// Function to display menu and perform CRUD operations
void menu() {
    do {
        cout << "\n===== PILIHAN MENU =====\n";
        cout << "1. Lihat Barang\n";
        cout << "2. Tambah Barang\n";
        cout << "3. Ubah Barang\n";
        cout << "4. Hapus Barang\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        // Validate input
        while (cin.fail() || pilihan < 1 || pilihan > 5) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid. Masukkan angka antara 1 dan 5: ";
            cin >> pilihan;
        }

        // Switch statement for menu options
        switch (pilihan) {
            case 1: lihatBarang(); break;
            case 2: tambahBarang(); break;
            case 3: updateBarang(); break;
            case 4: hapusBarang(); break;
            case 5: cout << "Terima Kasih.\n"; break;
        }
    } while (pilihan != 5);
}

// Function for login feature
int login() {
    while (totalLogin < 3) {
        cout << "\n===== LOGIN =====\n";
        cout << "Nama : ";
        cin >> daftarInventaris[totalLogin].login.nama;
        cout << "NIM : ";
        cin >> daftarInventaris[totalLogin].login.nim;

        if ((daftarInventaris[totalLogin].login.nama == "Frans" || daftarInventaris[totalLogin].login.nama == "frans") && daftarInventaris[totalLogin].login.nim == "20230801536") {
            cout << "Login berhasil!\n";
            cout << "\nSELAMAT DATANG DI INVENTORY SEKOLAH\n";
            return 1;
        } else {
            cout << "Login gagal. Silakan coba lagi.\n";
            totalLogin++;
        }
    }

    if (totalLogin == 3) {
        cout << "Anda telah melebihi batas percobaan login. Program berhenti.\n";
        return 0;
    }
    return 0;
}

// Function to find item index by name
int cariIndexBarang(const string& namaBarang) {
    for (int i = 0; i < totalBarang; ++i) {
        if (daftarInventaris[i].barang.namaBarang == namaBarang) {
            return i;
        }
    }
    return -1; // if item not found
}

// Procedure to display all items
void lihatBarang() {
    if (totalBarang > 0) {
        cout << "\n===== DATA BARANG DI INVENTORI SEKOLAH ===== \n";
        for (int i = 0; i < totalBarang; i++) {
            cout << "Nama Barang : " << daftarInventaris[i].barang.namaBarang << " | Kondisi Barang : " << daftarInventaris[i].barang.kondisi << " | Jumlah Barang : " << daftarInventaris[i].barang.jumlah << endl;
        }
    } else {
        cout << "\nBelum ada barang di inventory\n";
    }
}

// Procedure to add new item
void tambahBarang() {
    if (totalBarang < maxArray) {
        cout << "Masukkan nama barang : ";
        cin.ignore();
        getline(cin, daftarInventaris[totalBarang].barang.namaBarang);

        cout << "Masukkan jumlah barang : ";
        while (!(cin >> daftarInventaris[totalBarang].barang.jumlah)) {
            cout << "Input tidak valid. Masukkan jumlah barang dalam bentuk angka : ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Kondisi barang : ";
        cin.ignore();
        getline(cin, daftarInventaris[totalBarang].barang.kondisi);

        totalBarang++;
        cout << "Data barang berhasil ditambahkan.\n";
    } else {
        cout << "Penyimpanan penuh. Tidak dapat menambahkan data lagi.\n";
    }
}

// Procedure to update item data
void updateBarang() {
    string update;
    cout << "Masukkan nama barang yang akan diubah datanya : ";
    cin.ignore();
    getline(cin, update);

    int index = cariIndexBarang(update);
    if (index != -1) {
        cout << "Masukkan nama barang yang baru : ";
        getline(cin, daftarInventaris[index].barang.namaBarang);

        cout << "Masukkan jumlah barang yang baru : ";
        while (!(cin >> daftarInventaris[index].barang.jumlah)) {
            cout << "Input tidak valid. Masukkan jumlah barang dalam bentuk angka : ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Kondisi barang yang baru : ";
        cin.ignore();
        getline(cin, daftarInventaris[index].barang.kondisi);
        cout << "Data barang berhasil diupdate.\n";
    } else {
        cout << "Nama barang tidak ditemukan.\n";
    }
}

// Procedure to delete item data
void hapusBarang() {
    string update;
    cout << "Masukkan nama barang yang akan dihapus datanya : ";
    cin.ignore();
    getline(cin, update);

    int index = cariIndexBarang(update);
    if (index != -1) {
        for (int i = index; i < totalBarang - 1; ++i) {
            daftarInventaris[i] = daftarInventaris[i + 1];
        }
        totalBarang--;
        cout << "Data barang berhasil dihapus.\n";
    } else {
        cout << "Nama barang tidak ditemukan.\n";
    }
}

