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
    string username;
    string password;
};

// Struct untuk menyimpan data inventory gudang
struct InventoryGudang {
    Barang barang;
    Login login;
};

// Nilai tetap untuk array
const int maxArray = 50;

// Deklarasi array pointer InventoryGudang untuk menyimpan data inventory gudang
InventoryGudang* daftarInventoryGudang[maxArray];
int totalBarang = 0, totalLogin = 0, pilihan;

// Prototype fungsi dan prosedur
int cariIndexBarang(const int& idBarang);
int login(InventoryGudang** daftarInventoryGudang);
int menu();
int menuSorting();
void lihatBarang(InventoryGudang** daftarInventoryGudang, int totalBarang);
void tambahBarang(InventoryGudang** daftarInventoryGudang, int* totalBarang);
void updateBarang(InventoryGudang** daftarInventoryGudang, int* totalBarang);
void hapusBarang(InventoryGudang** daftarInventoryGudang, int* totalBarang);
void bubbleSortById(InventoryGudang** daftarInventoryGudang, int totalBarang);
void quickSortByQuantity(InventoryGudang** daftarInventoryGudang, int low, int high);
int partisi(InventoryGudang** daftarInventoryGudang, int low, int high);
void insertionSortByName(InventoryGudang** daftarInventoryGudang, int totalBarang);
int interpolationSearchAscending(InventoryGudang** daftarInventoryGudang, int kiri, int kanan, int target);
int binarySearchDescending(InventoryGudang** daftarInventoryGudang, int kiri, int kanan, int target);
int menuSearch();

int main() {
    login(daftarInventoryGudang);
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
            lihatBarang(daftarInventoryGudang, totalBarang);
            break;
        case 2:
            tambahBarang(daftarInventoryGudang, &totalBarang);
            break;
        case 3: 
            updateBarang(daftarInventoryGudang, &totalBarang);
            break;
        case 4:
            hapusBarang(daftarInventoryGudang, &totalBarang);
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
int login(InventoryGudang** daftarInventoryGudang) {
    for (int i = 0; i < maxArray; ++i) {
        daftarInventoryGudang[i] = new InventoryGudang;
    }

    totalBarang = 0;
    totalLogin = 0;

    while (totalLogin < 3) {
        cout << "\n===== LOGIN =====\n";
        cout << "Username : ";
        cin >> daftarInventoryGudang[totalLogin]->login.username;
        cout << "Password : ";
        cin >> daftarInventoryGudang[totalLogin]->login.password;

        // Cek login menggunakan username dan password yang baru
        if ((daftarInventoryGudang[totalLogin]->login.username == "kelompok4") && daftarInventoryGudang[totalLogin]->login.password == "uas4") {
            cout << "Login berhasil!\n";
            cout << "\nSELAMAT DATANG DI INVENTORY GUDANG\n";
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
        if (daftarInventoryGudang[i]->barang.id_barang == idBarang) {
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
            bubbleSortById(daftarInventoryGudang, totalBarang);
            break;
        case 2:
            quickSortByQuantity(daftarInventoryGudang, 0, totalBarang - 1);
            break;
        case 3: 
            insertionSortByName(daftarInventoryGudang, totalBarang);
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

            hasilPencarianInterpolation = interpolationSearchAscending(daftarInventoryGudang, 0, totalBarang - 1, targetInterpolation);
            if (hasilPencarianInterpolation != -1) {
                cout << "Data ditemukan pada indeks : " << hasilPencarianInterpolation << endl;
                cout << "ID Barang : " << daftarInventoryGudang[hasilPencarianInterpolation]->barang.id_barang << "| Nama Barang : " << daftarInventoryGudang[hasilPencarianInterpolation]->barang.namaBarang << " | Jumlah Barang : " << daftarInventoryGudang[hasilPencarianInterpolation]->barang.jumlah << " | Kondisi Barang : " << daftarInventoryGudang[hasilPencarianInterpolation]->barang.kondisi << endl;
            } else {
                cout << "Data tidak ditemukan. Data harus terurut secara Ascending dahulu" << endl;
            }
            break;

        case 2:
            cout << "Masukkan ID barang yang ingin dicari : ";
            cin >> targetBinary;

            hasilPencarianBinary = binarySearchDescending(daftarInventoryGudang, 0, totalBarang - 1, targetBinary);
            if (hasilPencarianBinary != -1) {
                cout << "Data ditemukan pada indeks : " << hasilPencarianBinary << endl;
                cout << "ID Barang : " << daftarInventoryGudang[hasilPencarianBinary]->barang.id_barang << "| Nama Barang : " << daftarInventoryGudang[hasilPencarianBinary]->barang.namaBarang << " | Jumlah Barang : " << daftarInventoryGudang[hasilPencarianBinary]->barang.jumlah << " | Kondisi Barang : " << daftarInventoryGudang[hasilPencarianBinary]->barang.kondisi << endl;
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
void lihatBarang(InventoryGudang** daftarInventoryGudang, int totalBarang) {
    string pilihanSort, pilihanSearch;
    if (totalBarang > 0) {
        cout << "\n===== DATA BARANG DI INVENTORY GUDANG ===== \n";
        for (int i = 0; i < totalBarang; i++) {
            cout << "ID Barang : " << daftarInventoryGudang[i]->barang.id_barang << "| Nama Barang : " << daftarInventoryGudang[i]->barang.namaBarang << " | Jumlah Barang : " << daftarInventoryGudang[i]->barang.jumlah << " | Kondisi Barang : " << daftarInventoryGudang[i]->barang.kondisi << endl;
        }

        cout << "\nApakah ingin menampilkan metode Sorting (Y/N) ? ";
        cin >> pilihanSort;

        if (pilihanSort == "Y" || pilihanSort == "y") {
            menuSorting();
            cout << "Hasil setelah dilakukan Sorting : " << endl;
            for (int i = 0; i < totalBarang; i++) {
                cout << "ID Barang : " << daftarInventoryGudang[i]->barang.id_barang << "| Nama Barang : " << daftarInventoryGudang[i]->barang.namaBarang << " | Jumlah Barang : " << daftarInventoryGudang[i]->barang.jumlah << " | Kondisi Barang : " << daftarInventoryGudang[i]->barang.kondisi << endl;
            }
        }

        cout << "\nApakah ingin menampilkan metode Searching (Y/N) ? ";
        cin >> pilihanSearch;

        if (pilihanSearch == "Y" || pilihanSearch == "y") {
            menuSearch();
        }
    } else {
        cout << "\nTidak ada data barang dalam inventory gudang.\n";
    }
}

// Prosedur untuk menambah barang ke inventory gudang
void tambahBarang(InventoryGudang** daftarInventoryGudang, int* totalBarang) {
    if (*totalBarang < maxArray) {
        InventoryGudang* inventoryBaru = new InventoryGudang;

        cout << "\nMasukkan ID barang : ";
        cin >> inventoryBaru->barang.id_barang;
        cin.ignore();

        cout << "Masukkan nama barang : ";
        getline(cin, inventoryBaru->barang.namaBarang);

        cout << "Masukkan kondisi barang : ";
        getline(cin, inventoryBaru->barang.kondisi);

        cout << "Masukkan jumlah barang : ";
        cin >> inventoryBaru->barang.jumlah;

        daftarInventoryGudang[*totalBarang] = inventoryBaru;
        (*totalBarang)++;

        cout << "Barang berhasil ditambahkan ke inventory gudang.\n";
    } else {
        cout << "Inventory gudang penuh. Tidak bisa menambah barang lagi.\n";
    }
}

// Prosedur untuk memperbarui data barang
void updateBarang(InventoryGudang** daftarInventoryGudang, int* totalBarang) {
    int idBarang;
    cout << "\nMasukkan ID barang yang ingin diperbarui : ";
    cin >> idBarang;

    int indexBarang = cariIndexBarang(idBarang);
    if (indexBarang != -1) {
        cout << "Masukkan nama barang baru : ";
        cin.ignore();
        getline(cin, daftarInventoryGudang[indexBarang]->barang.namaBarang);

        cout << "Masukkan kondisi barang baru : ";
        getline(cin, daftarInventoryGudang[indexBarang]->barang.kondisi);

        cout << "Masukkan jumlah barang baru : ";
        cin >> daftarInventoryGudang[indexBarang]->barang.jumlah;

        cout << "Data barang berhasil diperbarui.\n";
    } else {
        cout << "Barang dengan ID tersebut tidak ditemukan.\n";
    }
}

// Prosedur untuk menghapus data barang
void hapusBarang(InventoryGudang** daftarInventoryGudang, int* totalBarang) {
    int idBarang;
    cout << "\nMasukkan ID barang yang ingin dihapus : ";
    cin >> idBarang;

    int indexBarang = cariIndexBarang(idBarang);
    if (indexBarang != -1) {
        delete daftarInventoryGudang[indexBarang];

        for (int i = indexBarang; i < (*totalBarang) - 1; ++i) {
            daftarInventoryGudang[i] = daftarInventoryGudang[i + 1];
        }
        (*totalBarang)--;

        cout << "Barang berhasil dihapus dari inventory gudang.\n";
    } else {
        cout << "Barang dengan ID tersebut tidak ditemukan.\n";
    }
}

// Prosedur untuk melakukan bubble sort berdasarkan ID barang secara ascending
void bubbleSortById(InventoryGudang** daftarInventoryGudang, int totalBarang) {
    for (int i = 0; i < totalBarang - 1; ++i) {
        for (int j = 0; j < totalBarang - i - 1; ++j) {
            if (daftarInventoryGudang[j]->barang.id_barang > daftarInventoryGudang[j + 1]->barang.id_barang) {
                swap(daftarInventoryGudang[j], daftarInventoryGudang[j + 1]);
            }
        }
    }
}

// Prosedur untuk melakukan quick sort berdasarkan jumlah barang secara descending
void quickSortByQuantity(InventoryGudang** daftarInventoryGudang, int low, int high) {
    if (low < high) {
        int pi = partisi(daftarInventoryGudang, low, high);

        quickSortByQuantity(daftarInventoryGudang, low, pi - 1);
        quickSortByQuantity(daftarInventoryGudang, pi + 1, high);
    }
}

int partisi(InventoryGudang** daftarInventoryGudang, int low, int high) {
    int pivot = daftarInventoryGudang[high]->barang.jumlah;
    int i = (low - 1);

    for (int j = low; j <= high - 1; ++j) {
        if (daftarInventoryGudang[j]->barang.jumlah >= pivot) {
            ++i;
            swap(daftarInventoryGudang[i], daftarInventoryGudang[j]);
        }
    }
    swap(daftarInventoryGudang[i + 1], daftarInventoryGudang[high]);
    return (i + 1);
}

// Prosedur untuk melakukan insertion sort berdasarkan nama barang secara ascending
void insertionSortByName(InventoryGudang** daftarInventoryGudang, int totalBarang) {
    for (int i = 1; i < totalBarang; ++i) {
        InventoryGudang* key = daftarInventoryGudang[i];
        int j = i - 1;

        while (j >= 0 && daftarInventoryGudang[j]->barang.namaBarang > key->barang.namaBarang) {
            daftarInventoryGudang[j + 1] = daftarInventoryGudang[j];
            --j;
        }
        daftarInventoryGudang[j + 1] = key;
    }
}

// Fungsi untuk melakukan interpolation search secara ascending berdasarkan ID barang
int interpolationSearchAscending(InventoryGudang** daftarInventoryGudang, int kiri, int kanan, int target) {
    while (kiri <= kanan && target >= daftarInventoryGudang[kiri]->barang.id_barang && target <= daftarInventoryGudang[kanan]->barang.id_barang) {
        if (kiri == kanan) {
            if (daftarInventoryGudang[kiri]->barang.id_barang == target) {
                return kiri;
            }
            return -1;
        }

        int pos = kiri + (((double)(kanan - kiri) / (daftarInventoryGudang[kanan]->barang.id_barang - daftarInventoryGudang[kiri]->barang.id_barang)) * (target - daftarInventoryGudang[kiri]->barang.id_barang));

        if (daftarInventoryGudang[pos]->barang.id_barang == target) {
            return pos;
        }

        if (daftarInventoryGudang[pos]->barang.id_barang < target) {
            kiri = pos + 1;
        } else {
            kanan = pos - 1;
        }
    }
    return -1;
}

// Fungsi untuk melakukan binary search secara descending berdasarkan ID barang
int binarySearchDescending(InventoryGudang** daftarInventoryGudang, int kiri, int kanan, int target) {
    while (kiri <= kanan) {
        int tengah = kiri + (kanan - kiri) / 2;

        if (daftarInventoryGudang[tengah]->barang.id_barang == target) {
            return tengah;
        }

        if (daftarInventoryGudang[tengah]->barang.id_barang > target) {
            kiri = tengah + 1;
        } else {
            kanan = tengah - 1;
        }
    }
    return -1;
}