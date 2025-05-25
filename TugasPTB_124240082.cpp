#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <conio.h>

using namespace std;

struct Mahasiswa {
    int nim;
    char nama[50];
    Mahasiswa* kiri;
    Mahasiswa* kanan;
};

Mahasiswa* buatNode(int nim, const char nama[]) {
    Mahasiswa* baru = new Mahasiswa;
    baru->nim = nim;
    strcpy(baru->nama, nama);
    baru->kiri = baru->kanan = nullptr;
    return baru;
}

Mahasiswa* sisip(Mahasiswa* akar, int nim, const char nama[]) {
    if (akar == nullptr) {
        return buatNode(nim, nama);
    }

    if (nim < akar->nim) {
        akar->kiri = sisip(akar->kiri, nim, nama);
    } else if (nim > akar->nim) {
        akar->kanan = sisip(akar->kanan, nim, nama);
    } else {
        cout << "NIM sudah ada.\n";
    }

    return akar;
}

void inorder(Mahasiswa* akar) {
    if (akar == nullptr) return;
    inorder(akar->kiri);
    cout << "NIM  : " << akar->nim << endl;
    cout << "Nama : " << akar->nama << endl;
    cout << endl;
    inorder(akar->kanan);
}

Mahasiswa* cari(Mahasiswa* akar, int nim) {
    if (akar == nullptr || akar->nim == nim)
        return akar;

    if (nim < akar->nim)
        return cari(akar->kiri, nim);
    else
        return cari(akar->kanan, nim);
}

Mahasiswa* bantu(Mahasiswa* akar) {
    while (akar && akar->kiri != nullptr)
        akar = akar->kiri;
    return akar;
}

Mahasiswa* hapus(Mahasiswa* akar, int nim) {
    if (akar == nullptr)
        return akar;

    if (nim < akar->nim) {
        akar->kiri = hapus(akar->kiri, nim);
    } else if (nim > akar->nim) {
        akar->kanan = hapus(akar->kanan, nim);
    } else {
        if (akar->kiri == nullptr) {
            Mahasiswa* temp = akar->kanan;
            delete akar;
            return temp;
        } else if (akar->kanan == nullptr) {
            Mahasiswa* temp = akar->kiri;
            delete akar;
            return temp;
        }

        Mahasiswa* temp = bantu(akar->kanan);
        akar->nim = temp->nim;
        strcpy(akar->nama, temp->nama);
        akar->kanan = hapus(akar->kanan, temp->nim);
    }

    return akar;
}

void simpanKeFile(Mahasiswa* akar, FILE* file) {
    if (akar != nullptr) {
        simpanKeFile(akar->kiri, file);
        fwrite(akar, sizeof(Mahasiswa), 1, file);
        simpanKeFile(akar->kanan, file);
    }
}

void bacaDariFile(Mahasiswa*& akar, const char* namaFile) {
    FILE* file = fopen(namaFile, "rb");
    if (!file) {
        file = fopen(namaFile, "wb");
        if (file) fclose(file);
        return;
    }

    Mahasiswa temp;
    while (fread(&temp, sizeof(Mahasiswa), 1, file)) {
        akar = sisip(akar, temp.nim, temp.nama);
    }

    fclose(file);
}

int main() {
    Mahasiswa* akar = nullptr;
    int pilihan, nim;
    char nama[50];
    const char* namaFile = "mahasiswa.dat";

    bacaDariFile(akar, namaFile);

    do {
        system("cls");
        cout << "\n=================== Menu ===================" << endl;
        cout << "1. Tambah Mahasiswa" << endl;
        cout << "2. Cari Mahasiswa" << endl;
        cout << "3. Tampilkan Mahasiswa" << endl;
        cout << "4. Hapus Mahasiswa" << endl;
        cout << "5. Keluar dan Simpan" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                system("cls");
                cout << "=============== Masukkan Data Mahasiswa ===============" << endl;
                cout << "Masukkan NIM : ";
                cin >> nim;
                cin.ignore();
                cout << "Masukkan Nama: ";
                cin.getline(nama, 50);
                akar = sisip(akar, nim, nama);
                cout << "Data berhasil ditambahkan.\n";
                getch();
                break;

            case 2:
                system("cls");
                cout << "=============== Pencarian Data Mahasiswa ===============" << endl;
                cout << "Masukkan NIM yang dicari: ";
                cin >> nim;
                {
                    Mahasiswa* hasil = cari(akar, nim);
                    if (hasil){
                        cout << "Data ditemukan" << endl;
                        cout << "NIM  : " << hasil->nim;
                        cout << endl;
                        cout << "Nama : " << hasil->nama;
                    }else {
                        cout << "Mahasiswa tidak ditemukan.\n";
                    }
                }
                getch();
                break;

            case 3:
                system("cls");
                cout << "=============== Data Mahasiswa (Inorder Traversal) ===============" << endl;
                if (akar == nullptr) {
                    cout << "Belum ada data mahasiswa.\n";
                } else {
                    inorder(akar);
                }
                cout << "\nTekan tombol apapun untuk kembali ke menu";
                getch();
                break;

            case 4:
                system("cls");
                cout << "=============== Hapus Data Mahasiswa ===============" << endl;
                cout << "Masukkan NIM yang ingin dihapus: ";
                cin >> nim;
                akar = hapus(akar, nim);
                cout << "Data berhasil dihapus\n";
                getch();
                break;

            case 5:
                {
                    FILE* file = fopen(namaFile, "wb");
                    if (file) {
                        simpanKeFile(akar, file);
                        fclose(file);
                        cout << "Data berhasil disimpan. Terima kasih.\n";
                    } else {
                        cout << "Gagal menyimpan file.\n";
                    }
                }
                break;

            default:
                cout << "Pilihan tidak valid.\n";
                getch();
        }

    } while (pilihan != 5);

    return 0;
}
