#include <iostream>
#include <fstream>
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
void muatData(Inventaris* daftarInventaris[], int& totalBarang);
int cariIndexBarang(const int& idBarang);
int login(Inventaris* daftarInventaris[]);
int menu();
int menuSorting();
void lihatBarang(Inventaris* daftarInventaris[], int totalBarang);
void tambahBarang(Inventaris* daftarInventaris[], int* totalBarang);
void updateBarang(Inventaris* daftarInventaris[], int* totalBarang);
void hapusBarang(Inventaris* daftarInventaris[], int* totalBarang);
void bubbleSortById(Inventaris* daftarInventaris[], int totalBarang);
void quickSortByQuantity(Inventaris* daftarInventaris[], int low, int high);
int partisi(Inventaris* daftarInventaris[], int low, int high);
void insertionSortByName(Inventaris* daftarInventaris[], int totalBarang);
int interpolationSearchAscending(Inventaris* daftarInventaris[], int kiri, int kanan, int target);
int binarySearchDescending(Inventaris* daftarInventaris[], int kiri, int kanan, int target);

int main() {
    muatData(daftarInventaris, totalBarang);
    login(daftarInventaris);
    return 0;
}

// Fungsi untuk memuat data dari file
void muatData(Inventaris* daftarInventaris[], int& totalBarang) {
    ifstream file("inventaris.txt");
    if (!file) {
        cerr << "Gagal membuka file untuk membaca data." << endl;
        return;
    }

    file >> totalBarang;
    file.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore newline after totalBarang

    for (int i = 0; i < totalBarang; ++i) {
        daftarInventaris[i] = new Inventaris;

        file >> daftarInventaris[i]->barang.id_barang;
        file.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore newline after id_barang

        getline(file, daftarInventaris[i]->barang.namaBarang);
        file >> daftarInventaris[i]->barang.jumlah;
        file.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore newline after jumlah

        getline(file, daftarInventaris[i]->barang.kondisi);
    }

    file.close();
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
int login(Inventaris* daftarInventaris[]) {
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
    cout << "1. Binary Search\n";
    cout << "2. Interpolation Search\n";
    cout << "3. Exit\n";
    cin >> pilihanSearch;

    while (cin.fail() || pilihanSearch < 1 || pilihanSearch > 3) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input tidak valid. Masukkan angka antara 1 dan 3 : ";
        cin >> pilihanSearch;
    }

    switch (pilihanSearch) {
        case 1:
            cout << "Masukkan ID Barang untuk Binary Search: ";
            cin >> targetBinary;
            hasilPencarianBinary = binarySearchDescending(daftarInventaris, 0, totalBarang - 1, targetBinary);
            if (hasilPencarianBinary != -1) {
                cout << "Barang ditemukan pada index " << hasilPencarianBinary << ".\n";
            } else {
                cout << "Barang tidak ditemukan.\n";
            }
            break;
        case 2:
            cout << "Masukkan ID Barang untuk Interpolation Search: ";
            cin >> targetInterpolation;
            hasilPencarianInterpolation = interpolationSearchAscending(daftarInventaris, 0, totalBarang - 1, targetInterpolation);
            if (hasilPencarianInterpolation != -1) {
                cout << "Barang ditemukan pada index " << hasilPencarianInterpolation << ".\n";
            } else {
                cout << "Barang tidak ditemukan.\n";
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

// Fungsi untuk menampilkan daftar barang
void lihatBarang(Inventaris* daftarInventaris[], int totalBarang) {
    menuSorting();
    cout << "Daftar Barang:\n";
    for (int i = 0; i < totalBarang; ++i) {
        cout << "ID Barang: " << daftarInventaris[i]->barang.id_barang << endl;
        cout << "Nama Barang: " << daftarInventaris[i]->barang.namaBarang << endl;
        cout << "Jumlah: " << daftarInventaris[i]->barang.jumlah << endl;
        cout << "Kondisi: " << daftarInventaris[i]->barang.kondisi << endl;
        cout << "-----------------------\n";
    }
}

// Fungsi untuk menambah barang
void tambahBarang(Inventaris* daftarInventaris[], int* totalBarang) {
    if (*totalBarang < maxArray) {
        daftarInventaris[*totalBarang] = new Inventaris;
        cout << "Masukkan ID Barang: ";
        cin >> daftarInventaris[*totalBarang]->barang.id_barang;
        cin.ignore();
        cout << "Masukkan Nama Barang: ";
        getline(cin, daftarInventaris[*totalBarang]->barang.namaBarang);
        cout << "Masukkan Jumlah Barang: ";
        cin >> daftarInventaris[*totalBarang]->barang.jumlah;
        cin.ignore();
        cout << "Masukkan Kondisi Barang: ";
        getline(cin, daftarInventaris[*totalBarang]->barang.kondisi);
        (*totalBarang)++;
    } else {
        cout << "Jumlah barang sudah mencapai batas maksimum.\n";
    }
}

// Fungsi untuk mengupdate barang
void updateBarang(Inventaris* daftarInventaris[], int* totalBarang) {
    int idBarang, index;
    cout << "Masukkan ID Barang yang ingin diubah: ";
    cin >> idBarang;
    index = cariIndexBarang(idBarang);
    if (index != -1) {
        cout << "Masukkan Nama Barang Baru: ";
        cin.ignore();
        getline(cin, daftarInventaris[index]->barang.namaBarang);
        cout << "Masukkan Jumlah Barang Baru: ";
        cin >> daftarInventaris[index]->barang.jumlah;
        cin.ignore();
        cout << "Masukkan Kondisi Barang Baru: ";
        getline(cin, daftarInventaris[index]->barang.kondisi);
    } else {
        cout << "Barang dengan ID tersebut tidak ditemukan.\n";
    }
}

// Fungsi untuk menghapus barang
void hapusBarang(Inventaris* daftarInventaris[], int* totalBarang) {
    int idBarang, index;
    cout << "Masukkan ID Barang yang ingin dihapus: ";
    cin >> idBarang;
    index = cariIndexBarang(idBarang);
    if (index != -1) {
        delete daftarInventaris[index];
        for (int i = index; i < *totalBarang - 1; ++i) {
            daftarInventaris[i] = daftarInventaris[i + 1];
        }
        (*totalBarang)--;
    } else {
        cout << "Barang dengan ID tersebut tidak ditemukan.\n";
    }
}

// Fungsi bubble sort berdasarkan ID
void bubbleSortById(Inventaris* daftarInventaris[], int totalBarang) {
    Inventaris* temp;
    for (int i = 0; i < totalBarang - 1; ++i) {
        for (int j = 0; j < totalBarang - i - 1; ++j) {
            if (daftarInventaris[j]->barang.id_barang > daftarInventaris[j + 1]->barang.id_barang) {
                temp = daftarInventaris[j];
                daftarInventaris[j] = daftarInventaris[j + 1];
                daftarInventaris[j + 1] = temp;
            }
        }
    }
}

// Fungsi partisi untuk quicksort
int partisi(Inventaris* daftarInventaris[], int low, int high) {
    int pivot = daftarInventaris[high]->barang.jumlah;
    int i = (low - 1);
    Inventaris* temp;

    for (int j = low; j < high; ++j) {
        if (daftarInventaris[j]->barang.jumlah >= pivot) {
            ++i;
            temp = daftarInventaris[i];
            daftarInventaris[i] = daftarInventaris[j];
            daftarInventaris[j] = temp;
        }
    }
    temp = daftarInventaris[i + 1];
    daftarInventaris[i + 1] = daftarInventaris[high];
    daftarInventaris[high] = temp;

    return (i + 1);
}

// Fungsi quicksort berdasarkan jumlah
void quickSortByQuantity(Inventaris* daftarInventaris[], int low, int high) {
    if (low < high) {
        int pi = partisi(daftarInventaris, low, high);
        quickSortByQuantity(daftarInventaris, low, pi - 1);
        quickSortByQuantity(daftarInventaris, pi + 1, high);
    }
}

// Fungsi insertion sort berdasarkan nama barang
void insertionSortByName(Inventaris* daftarInventaris[], int totalBarang) {
    Inventaris* key;
    int j;
    for (int i = 1; i < totalBarang; i++) {
        key = daftarInventaris[i];
        j = i - 1;
        while (j >= 0 && daftarInventaris[j]->barang.namaBarang > key->barang.namaBarang) {
            daftarInventaris[j + 1] = daftarInventaris[j];
            j = j - 1;
        }
        daftarInventaris[j + 1] = key;
    }
}

// Fungsi binary search (descending order)
int binarySearchDescending(Inventaris* daftarInventaris[], int kiri, int kanan, int target) {
    int mid;
    while (kiri <= kanan) {
        mid = kiri + (kanan - kiri) / 2;

        if (daftarInventaris[mid]->barang.id_barang == target) {
            return mid;
        } else if (daftarInventaris[mid]->barang.id_barang < target) {
            kanan = mid - 1;
        } else {
            kiri = mid + 1;
        }
    }
    return -1;
}

// Fungsi interpolation search (ascending order)
int interpolationSearchAscending(Inventaris* daftarInventaris[], int kiri, int kanan, int target) {
    int pos;
    while (kiri <= kanan && target >= daftarInventaris[kiri]->barang.id_barang && target <= daftarInventaris[kanan]->barang.id_barang) {
        if (kiri == kanan) {
            if (daftarInventaris[kiri]->barang.id_barang == target) return kiri;
            return -1;
        }

        pos = kiri + (((double)(kanan - kiri) / (daftarInventaris[kanan]->barang.id_barang - daftarInventaris[kiri]->barang.id_barang)) * (target - daftarInventaris[kiri]->barang.id_barang));

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


