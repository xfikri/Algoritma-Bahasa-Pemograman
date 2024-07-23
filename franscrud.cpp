#include <iostream>
#include <limits>
#include <sstream>
using namespace std;

// Struct untuk informasi barang
struct Barang {
    int id_barang;
    string namaBarang;
    string kondisi;
    int jumlah;
};

// Struct untuk data login
struct Login {
    string nama;
    string nim;
};

// Struct untuk menyimpan data inventaris
struct Inventaris {
    Barang barang;
    Login login;
};

// Nilai tetap untuk array
const int maxArray = 50;

// Deklarasi array pointer Inventaris untuk menyimpan data inventaris
Inventaris* daftarInventaris[maxArray];
int totalBarang = 0, totalLogin = 0, pilihan;

// Prototype fungsi dan prosedur
int cariIndexBarang(const int& idBarang);
int login(Inventaris** daftarInventaris);
int menu();
int menuSorting();
void lihatBarang(Inventaris** daftarInventaris, int totalBarang);
void tambahBarang(Inventaris** daftarInventaris, int* totalBarang);
void updateBarang(Inventaris** daftarInventaris, int* totalBarang);
void hapusBarang(Inventaris** daftarInventaris, int* totalBarang);
void bubbleSortById(Inventaris** daftarInventaris, int totalBarang);
void quickSortByQuantity(Inventaris** daftarInventaris, int low, int high);
int partisi(Inventaris** daftarInventaris, int low, int high);
void insertionSortByName(Inventaris** daftarInventaris, int totalBarang);
int interpolationSearchAscending(Inventaris** daftarInventaris, int kiri, int kanan, int target);
int binarySearchDescending(Inventaris** daftarInventaris, int kiri, int kanan, int target);

int main() {
    login(daftarInventaris);
    return 0;
}

// Fungsi untuk menampilkan menu dan CRUD
int menu() {
    cout << "\n===== PILIHAN MENU =====\n";
    cout << "1. Lihat Barang\n";
    cout << "2. Tambah Barang\n";
    cout << "3. Ubah Barang\n";
    cout << "4. Hapus Barang\n";
    cout << "5. Keluar\n";
    cin >> pilihan;

    while (cin.fail() || pilihan < 1 || pilihan > 5) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input tidak valid. Masukkan angka antara 1 dan 5 : ";
        cin >> pilihan;
    }

    switch (pilihan) {
        case 1:
            lihatBarang(daftarInventaris, totalBarang);
            break;
        case 2:
            tambahBarang(daftarInventaris, &totalBarang);
            break;
        case 3: 
            updateBarang(daftarInventaris, &totalBarang);
            break;
        case 4:
            hapusBarang(daftarInventaris, &totalBarang);
            break;
        case 5:
            cout << "Terima Kasih.\n";
            return 0;
        default:
            cout << "Pilihan tidak valid.\n";
    }

    menu();
    return 0;
}

// Fungsi fitur login
int login(Inventaris** daftarInventaris) {
    for (int i = 0; i < maxArray; ++i) {
        daftarInventaris[i] = new Inventaris;
    }

    totalBarang = 0;
    totalLogin = 0;

    while (totalLogin < 3) {
        cout << "\n===== LOGIN =====\n";
        cout << "Nama : ";
        cin >> daftarInventaris[totalLogin]->login.nama;
        cout << "NIM : ";
        cin >> daftarInventaris[totalLogin]->login.nim;

        // Cek login menggunakan nama dan NIM yang baru
        if ((daftarInventaris[totalLogin]->login.nama == "Frans") && daftarInventaris[totalLogin]->login.nim == "20230801536") {
            cout << "Login berhasil!\n";
            cout << "\nSELAMAT DATANG DI INVENTORY SEKOLAH\n";
            menu();
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

// Fungsi untuk mencari index barang berdasarkan id
int cariIndexBarang(const int& idBarang) {
    for (int i = 0; i < totalBarang; ++i) {
        if (daftarInventaris[i]->barang.id_barang == idBarang) {
            return i;
        }
    }
    return -1;
}

// Fungsi untuk menampilkan metode sorting
int menuSorting() {
    int pilihanSort;

    cout << "\n===== Pilihan Metode Sorting =====\n";
    cout << "1. Bubble Sort By ID (Ascending)\n";
    cout << "2. Quick Sort By Quantity (Descending)\n";
    cout << "3. Insertion Sort By Name (Ascending)\n";
    cout << "4. Exit\n";
    cin >> pilihanSort;

    while (cin.fail() || pilihanSort < 1 || pilihanSort > 4) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input tidak valid. Masukkan angka antara 1 dan 4 : ";
        cin >> pilihanSort;
    }

    switch (pilihanSort) {
        case 1:
            bubbleSortById(daftarInventaris, totalBarang);
            break;
        case 2:
            quickSortByQuantity(daftarInventaris, 0, totalBarang - 1);
            break;
        case 3: 
            insertionSortByName(daftarInventaris, totalBarang);
            break;
        case 4:
            cout << "Terima Kasih.\n";
            return 0;
        default:
            cout << "Pilihan tidak valid.\n";
    }
    return 0;
}

// Fungsi untuk menampilkan metode searching
int menuSearch() {
    int pilihanSearch, targetBinary, targetInterpolation, hasilPencarianBinary, hasilPencarianInterpolation;

    cout << "\n===== Pilihan Metode Searching =====\n";
    cout << "1. Interpolation Search (Ascending)\n";
    cout << "2. Binary Search (Descending)\n";
    cout << "3. Exit\n";
    cin >> pilihanSearch;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (cin.fail() || pilihanSearch < 1 || pilihanSearch > 3) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input tidak valid. Masukkan angka antara 1 dan 3 : ";
        cin >> pilihanSearch;
    }

    switch (pilihanSearch) {
        case 1:
            cout << "Masukkan ID barang yang ingin dicari : ";
            cin >> targetInterpolation;

            hasilPencarianInterpolation = interpolationSearchAscending(daftarInventaris, 0, totalBarang - 1, targetInterpolation);
            if (hasilPencarianInterpolation != -1) {
                cout << "Data ditemukan pada indeks : " << hasilPencarianInterpolation << endl;
                cout << "ID Barang : " << daftarInventaris[hasilPencarianInterpolation]->barang.id_barang << "| Nama Barang : " << daftarInventaris[hasilPencarianInterpolation]->barang.namaBarang << " | Jumlah Barang : " << daftarInventaris[hasilPencarianInterpolation]->barang.jumlah << " | Kondisi Barang : " << daftarInventaris[hasilPencarianInterpolation]->barang.kondisi << endl;
            } else {
                cout << "Data tidak ditemukan. Data harus terurut secara Ascending dahulu" << endl;
            }
            break;

        case 2:
            cout << "Masukkan ID barang yang ingin dicari : ";
            cin >> targetBinary;

            hasilPencarianBinary = binarySearchDescending(daftarInventaris, 0, totalBarang - 1, targetBinary);
            if (hasilPencarianBinary != -1) {
                cout << "Data ditemukan pada indeks : " << hasilPencarianBinary << endl;
                cout << "ID Barang : " << daftarInventaris[hasilPencarianBinary]->barang.id_barang << "| Nama Barang : " << daftarInventaris[hasilPencarianBinary]->barang.namaBarang << " | Jumlah Barang : " << daftarInventaris[hasilPencarianBinary]->barang.jumlah << " | Kondisi Barang : " << daftarInventaris[hasilPencarianBinary]->barang.kondisi << endl;
            } else {
                cout << "Data tidak ditemukan. Data harus terurut secara Descending dahulu" << endl;
            }
            break;

        case 3:
            cout << "Terima Kasih.\n";
            return 0;
        default:
            cout << "Pilihan tidak valid.\n";
    }
    return 0;
}

// Prosedur untuk menampilkan semua daftar barang
void lihatBarang(Inventaris** daftarInventaris, int totalBarang) {
    string pilihanSort, pilihanSearch;
    if (totalBarang > 0) {
        cout << "\n===== DATA BARANG DI INVENTORI SEKOLAH ===== \n";
        for (int i = 0; i < totalBarang; i++) {
            cout << "ID Barang : " << daftarInventaris[i]->barang.id_barang << "| Nama Barang : " << daftarInventaris[i]->barang.namaBarang << " | Jumlah Barang : " << daftarInventaris[i]->barang.jumlah << " | Kondisi Barang : " << daftarInventaris[i]->barang.kondisi << endl;
        }
        menuSorting();
        menuSearch();
    } else {
        cout << "Data Barang Kosong. Tambah Data Barang Terlebih Dahulu\n";
    }
}

// Prosedur untuk menambah barang
void tambahBarang(Inventaris** daftarInventaris, int* totalBarang) {
    if (*totalBarang >= maxArray) {
        cout << "Kapasitas array sudah penuh.\n";
        return;
    }

    Inventaris* barangBaru = new Inventaris;

    cout << "Masukkan ID Barang: ";
    cin >> barangBaru->barang.id_barang;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Masukkan Nama Barang: ";
    getline(cin, barangBaru->barang.namaBarang);
    cout << "Masukkan Jumlah Barang: ";
    cin >> barangBaru->barang.jumlah;
    cout << "Masukkan Kondisi Barang: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, barangBaru->barang.kondisi);

    daftarInventaris[*totalBarang] = barangBaru;
    (*totalBarang)++;
}

// Prosedur untuk mengupdate barang
void updateBarang(Inventaris** daftarInventaris, int* totalBarang) {
    int idBarang;
    cout << "Masukkan ID Barang yang ingin diubah: ";
    cin >> idBarang;
    
    int index = cariIndexBarang(idBarang);
    if (index != -1) {
        cout << "Masukkan Nama Barang Baru: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, daftarInventaris[index]->barang.namaBarang);
        cout << "Masukkan Jumlah Barang Baru: ";
        cin >> daftarInventaris[index]->barang.jumlah;
        cout << "Masukkan Kondisi Barang Baru: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, daftarInventaris[index]->barang.kondisi);
    } else {
        cout << "ID Barang tidak ditemukan.\n";
    }
}

// Prosedur untuk menghapus barang
void hapusBarang(Inventaris** daftarInventaris, int* totalBarang) {
    int idBarang;
    cout << "Masukkan ID Barang yang ingin dihapus: ";
    cin >> idBarang;
    
    int index = cariIndexBarang(idBarang);
    if (index != -1) {
        delete daftarInventaris[index];
        for (int i = index; i < *totalBarang - 1; ++i) {
            daftarInventaris[i] = daftarInventaris[i + 1];
        }
        (*totalBarang)--;
    } else {
        cout << "ID Barang tidak ditemukan.\n";
    }
}

// Fungsi untuk melakukan bubble sort berdasarkan ID barang
void bubbleSortById(Inventaris** daftarInventaris, int totalBarang) {
    for (int i = 0; i < totalBarang - 1; ++i) {
        for (int j = 0; j < totalBarang - i - 1; ++j) {
            if (daftarInventaris[j]->barang.id_barang > daftarInventaris[j + 1]->barang.id_barang) {
                Inventaris* temp = daftarInventaris[j];
                daftarInventaris[j] = daftarInventaris[j + 1];
                daftarInventaris[j + 1] = temp;
            }
        }
    }
    cout << "Data barang sudah diurutkan berdasarkan ID (Ascending).\n";
}

// Fungsi untuk melakukan quick sort berdasarkan jumlah barang
void quickSortByQuantity(Inventaris** daftarInventaris, int low, int high) {
    if (low < high) {
        int pi = partisi(daftarInventaris, low, high);
        quickSortByQuantity(daftarInventaris, low, pi - 1);
        quickSortByQuantity(daftarInventaris, pi + 1, high);
    }
}

// Fungsi untuk partisi quick sort
int partisi(Inventaris** daftarInventaris, int low, int high) {
    int pivot = daftarInventaris[high]->barang.jumlah;
    int i = (low - 1);
    for (int j = low; j <= high - 1; ++j) {
        if (daftarInventaris[j]->barang.jumlah > pivot) {
            ++i;
            Inventaris* temp = daftarInventaris[i];
            daftarInventaris[i] = daftarInventaris[j];
            daftarInventaris[j] = temp;
        }
    }
    Inventaris* temp = daftarInventaris[i + 1];
    daftarInventaris[i + 1] = daftarInventaris[high];
    daftarInventaris[high] = temp;
    return (i + 1);
}

// Fungsi untuk melakukan insertion sort berdasarkan nama barang
void insertionSortByName(Inventaris** daftarInventaris, int totalBarang) {
    for (int i = 1; i < totalBarang; ++i) {
        Inventaris* key = daftarInventaris[i];
        int j = i - 1;
        while (j >= 0 && daftarInventaris[j]->barang.namaBarang > key->barang.namaBarang) {
            daftarInventaris[j + 1] = daftarInventaris[j];
            --j;
        }
        daftarInventaris[j + 1] = key;
    }
    cout << "Data barang sudah diurutkan berdasarkan Nama (Ascending).\n";
}

// Fungsi untuk melakukan interpolation search (ascending)
int interpolationSearchAscending(Inventaris** daftarInventaris, int kiri, int kanan, int target) {
    while (kiri <= kanan && target >= daftarInventaris[kiri]->barang.id_barang && target <= daftarInventaris[kanan]->barang.id_barang) {
        if (kiri == kanan) {
            if (daftarInventaris[kiri]->barang.id_barang == target) {
                return kiri;
            }
            return -1;
        }

        int pos = kiri + ((target - daftarInventaris[kiri]->barang.id_barang) * (kanan - kiri) / (daftarInventaris[kanan]->barang.id_barang - daftarInventaris[kiri]->barang.id_barang));

        if (daftarInventaris[pos]->barang.id_barang == target) {
            return pos;
        }
        if (daftarInventaris[pos]->barang.id_barang < target) {
            kiri = pos + 1;
        } else {
            kanan = pos - 1;
        }
    }
    return -1;
}

// Fungsi untuk melakukan binary search (descending)
int binarySearchDescending(Inventaris** daftarInventaris, int kiri, int kanan, int target) {
    while (kiri <= kanan) {
        int tengah = kiri + (kanan - kiri) / 2;

        if (daftarInventaris[tengah]->barang.id_barang == target) {
            return tengah;
        }
        if (daftarInventaris[tengah]->barang.id_barang < target) {
            kanan = tengah - 1;
        } else {
            kiri = tengah + 1;
        }
    }
    return -1;
}
