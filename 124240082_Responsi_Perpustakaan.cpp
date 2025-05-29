#include <iostream>
#include <cstring>
#include <conio.h>
using namespace std;

struct Buku {
    char judul[100];
    char pengarang[100];
    int tahun;
    Buku* kiri;
    Buku* kanan;
};

struct Undo {
    char aksi[10]; // "tambah" atau "hapus"
    Buku data;
    Undo* next;
};

Buku* akar = nullptr;
Undo* undoStack = nullptr;

Buku* buatBuku(const char* jdl, const char* pgr, int thn) {
    Buku* baru = new Buku;
    strcpy(baru->judul, jdl);
    strcpy(baru->pengarang, pgr);
    baru->tahun = thn;
    baru->kiri = baru->kanan = nullptr;
    return baru;
}

void simpanUndo(const char* aksi, Buku* baru) {
    Undo* balik = new Undo;
    strcpy(balik->aksi, aksi);
    balik->data = *baru;
    balik->next = undoStack;
    undoStack = balik;
}

void tambahBukuPTB(Buku* baru) {
    if (akar == nullptr) {
        akar = baru;
        return;
    }

    Buku* sekarang = akar;
    while (true) {
        if (strcmp(baru->judul, sekarang->judul) < 0) {
            if (sekarang->kiri == nullptr) {
                sekarang->kiri = baru;
                return;
            }
            sekarang = sekarang->kiri;
        } else if (strcmp(baru->judul, sekarang->judul) > 0) {
            if (sekarang->kanan == nullptr) {
                sekarang->kanan = baru;
                return;
            }
            sekarang = sekarang->kanan;
        } else {
            cout << "Judul sudah ada.\n";
            delete baru;
            return;
        }
    }
}

void tambahBuku() {
    char judul[100], pengarang[100];
    int tahun;
    cout << "========================= Tambah Buku =========================" << endl;
    cout << "Judul    : ";
    cin.ignore();
    cin.getline(judul, 100);
    cout << "Pengarang: ";
    cin.getline(pengarang, 100);
    cout << "Tahun    : ";
    cin >> tahun;

    Buku* baru = buatBuku(judul, pengarang, tahun);
    tambahBukuPTB(baru);
    simpanUndo("tambah", baru);
    cout << "Buku ditambahkan.\n";
    system("cls");
}

void tampil(Buku* node) {
    if (node == nullptr) return;
    tampil(node->kanan);
    cout << node->judul << " - " << node->pengarang << " - " << node->tahun << endl;
    tampil(node->kiri);
}

void bukuTampil() {
    cout << "========================= Daftar Buku =========================" << endl;
    tampil(akar);
    getch();
    system("cls");
}

Buku* cariTerkiri(Buku* node) {
    while (node->kiri != nullptr) node = node->kiri;
    return node;
}

Buku* hapusBukuPTB(Buku* node, const char* judul, bool& ditemukan, Buku& backup) {
    if (node == nullptr) return nullptr;

    if (strcmp(judul, node->judul) < 0) {
        node->kiri = hapusBukuPTB(node->kiri, judul, ditemukan, backup);
    } else if (strcmp(judul, node->judul) > 0) {
        node->kanan = hapusBukuPTB(node->kanan, judul, ditemukan, backup);
    } else {
        ditemukan = true;
        backup = *node;

        if (!node->kiri && !node->kanan) {
            delete node;
            return nullptr;
        } else if (!node->kiri) {
            Buku* temp = node->kanan;
            delete node;
            return temp;
        } else if (!node->kanan) {
            Buku* temp = node->kiri;
            delete node;
            return temp;
        } else {
            Buku* pengganti = cariTerkiri(node->kanan);
            strcpy(node->judul, pengganti->judul);
            strcpy(node->pengarang, pengganti->pengarang);
            node->tahun = pengganti->tahun;
            node->kanan = hapusBukuPTB(node->kanan, pengganti->judul, ditemukan, backup);
        }
    }
    return node;
}

void hapusBuku() {
    char judul[100];
    cout << "========================= Hapus Buku =========================" << endl;
    cout << "Judul yang ingin dihapus: ";
    cin.ignore();
    cin.getline(judul, 100);

    bool ditemukan = false;
    Buku backup;
    akar = hapusBukuPTB(akar, judul, ditemukan, backup);

    if (ditemukan) {
        simpanUndo("hapus", &backup);
        cout << "Buku berhasil dihapus\n";
    } else {
        cout << "Buku tidak ditemukan\n";
    }
    getch();
    system("cls");
}

void undo() {
    if (!undoStack) {
        cout << "Tidak ada yang bisa di-undo." << endl;
        return;
    }

    Undo* balik = undoStack;
    undoStack = undoStack->next;

    if (strcmp(balik->aksi, "tambah") == 0) {
        bool dummy = false;
        Buku temp;
        akar = hapusBukuPTB(akar, balik->data.judul, dummy, temp);
    } else if (strcmp(balik->aksi, "hapus") == 0) {
        Buku* baru = buatBuku(balik->data.judul, balik->data.pengarang, balik->data.tahun);
        tambahBukuPTB(baru);
    }
    delete balik;
}

int main() {
    int pilih;
    do {
        cout << "^^^^^^^^^^^^^^^SELAMAT DATANG DI PERPUSTAKAAN^^^^^^^^^^^^^^^" << endl;
        cout << "========================= Menu ============================" << endl;
        cout << "1. Tambah Buku" << endl;
        cout << "2. Tampilkan Buku" << endl; 
        cout << "3. Hapus Buku" << endl;
        cout << "4. Undo" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih)
        {
        case 1:
            system("cls");
            tambahBuku();
            break;
        case 2:
            system("cls");
            bukuTampil();
            break;
        case 3:
            system("cls");
            hapusBuku();
            break;
        case 4:
            system("cls");
            undo();
            break;

        default:
            break;
        }
        
    } while (pilih != 0);

    cout << "Terimakasih telah menggunakan perpustakaan";
    return 0;
}
