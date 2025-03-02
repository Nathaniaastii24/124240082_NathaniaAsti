#include <iostream>
#include <string>
#include <conio.h>
#include <iomanip>

using namespace std;

struct Barang
{
    string nama;
    int jumlah;
    float harga;
};

void input_data(Barang data_barang[], int &jumlah_barang)
{
    int jmlBRNG;

    cout << setfill('=') << setw(20) << "" << " Toko Kelontong 2-B " << setw(21) << "" << endl;
    cout << setfill('=') << setw(21) << "" << " Input Data Barang " << setw(21) << "" << endl;
    cout << endl;
    cout << "\nBerapa Data Barang yang Ingin di Masukkan : ";
    cin >> jmlBRNG;
    cout << endl;

    // Input data barang baru
    for (int i = 0; i < jmlBRNG; i++)
    {
        cout << (i + 1) << ".  Nama   : ";
        cin >> data_barang[jumlah_barang + i].nama;
        cout << "    Jumlah : ";
        cin >> data_barang[jumlah_barang + i].jumlah;
        cout << "    Harga  : ";
        cin >> data_barang[jumlah_barang + i].harga;
        cout << endl;
    }

    jumlah_barang += jmlBRNG; // Update jumlah barang
}

void tampilkan_data(Barang data_barang[], int jumlah_barang)
{
    if (jumlah_barang == 0)
    {
        cout << "Tidak ada data barang." << endl;
        return;
    }

    // Mengurutkan data berdasarkan nama menggunakan bubble sort
    for (int i = 0; i < jumlah_barang - 1; i++)
    {
        for (int j = 0; j < jumlah_barang - i - 1; j++)
        {
            if (data_barang[j].nama > data_barang[j + 1].nama)
            {
                Barang temp = data_barang[j];
                data_barang[j] = data_barang[j + 1];
                data_barang[j + 1] = temp;
            }
        }
    }

    cout << setfill('=') << setw(20) << "" << " Toko Kelontong 2-B " << setw(21) << "" << endl;
    cout << setfill('=') << setw(24) << "" << " Data Barang " << setw(24) << "" << endl;
    cout << endl;
    cout << "\nNo " << " Nama" << setfill(' ') << setw(30) << "Jumlah " << " Harga (Rp) " << endl;
    for (int i = 0; i < jumlah_barang; i++)
    {
        cout << left << setw(4) << (i + 1) << setw(27) << data_barang[i].nama << setw(8) << data_barang[i].jumlah << data_barang[i].harga << endl;
    }
}

int binary_search(Barang data_barang[], int jumlah_barang, const string &nama)
{
    int low = 0;
    int high = jumlah_barang - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (data_barang[mid].nama == nama)
        {
            return mid;
        }
        else if (data_barang[mid].nama < nama)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return -1;
}

void sequential_search(Barang data_barang[], int jumlah_barang, float harga)
{
    bool found = false;

    for (int i = 0; i < jumlah_barang; i++)
    {
        if (data_barang[i].harga == harga)
        {
            cout << left << setw(30) << data_barang[i].nama << setw(10) << data_barang[i].jumlah << setw(15) << data_barang[i].harga << endl;
            cout << endl;
            found = true;
        }
    }
    if (!found)
    {
        cout << "Barang tidak ditemukan." << endl;
    }
}

void pencarian_data(Barang data_barang[], int jumlah_barang)
{
    int pilihan;

    cout << setfill('=') << setw(20) << "" << " Toko Kelontong 2-B " << setw(21) << "" << endl;
    cout << setfill('=') << setw(24) << "" << " Menu Search " << setw(24) << "" << endl;
    cout << "1. Berdasarkan Harga (Sequential Search)" << endl;
    cout << "2. Berdasarkan Nama (Binary Search) " << endl;
    cout << "3. Kembali" << endl;
    cout << "Masukkan pilihan : ";
    cin >> pilihan;
    system("cls");

    if (pilihan == 1)
    {
        float harga;
        cout << "Masukkan harga barang yang dicari: ";
        cin >> harga;
        system("cls");
        cout << setfill('=') << setw(20) << "" << " Toko Kelontong 2-B " << setw(21) << "" << endl;
        cout << setfill('=') << setw(21) << "" << " Pencarian Barang " << setw(22) << "" << endl;
        cout << setfill('=') << setw(61) << "=" << setfill(' ') << endl;
        cout << left << setw(30) << "Nama" << setw(10) << "Jumlah" << setw(15) << "Harga (Rp)" << endl;
        sequential_search(data_barang, jumlah_barang, harga);
    }
    else if (pilihan == 2)
    {
        string nama;
        cout << "Masukkan nama barang yang dicari: ";
        cin >> nama;
        system("cls");
        int index = binary_search(data_barang, jumlah_barang, nama);
        if (index != -1)
        {
            cout << setfill('=') << setw(20) << "" << " Toko Kelontong 2-B " << setw(21) << "" << endl;
            cout << setfill('=') << setw(21) << "" << " Pencarian Barang " << setw(22) << "" << endl;
            cout << setfill('=') << setw(61) << "=" << setfill(' ') << endl;
            cout << left << setw(30) << "Nama" << setw(10) << "Jumlah" << setw(15) << "Harga (Rp)" << endl;
            cout << left << setw(30) << data_barang[index].nama << setw(10) << data_barang[index].jumlah << setw(15) << data_barang[index].harga << endl;
            cout << endl;
        }
        else
        {
            cout << "Barang tidak ditemukan." << endl;
        }
    }
    else if (pilihan == 3)
    {
        return;
    }
    else
    {
        cout << "Pilihan tidak valid" << endl;
    }
}

int main()
{
    Barang data_barang[9999];
    int jumlah_barang = 0;
    int pilihan;
    char pilih;

        do
        {
            cout << setfill('=') << setw(20) << "" << " Toko Kelontong 2-B " << setw(20) << "" << endl;
            cout << setfill('=') << setw(27) << "" << " Menu " << setw(27) << "" << endl;
            cout << "1. Input Data" << endl;
            cout << "2. Tampilkan Data" << endl;
            cout << "3. Pencarian Data" << endl;
            cout << "4. Keluar" << endl;
            cout << "Masukkan pilihan : "; cin >> pilihan;
            system("cls");

            switch (pilihan)
            {
            case 1:
                input_data(data_barang, jumlah_barang);
                cout << "\nApakah Anda Ingin Kembali ke Menu Awal ? (y/t)";
                cin >> pilih;
                system("cls");
                break;
            case 2:
                tampilkan_data(data_barang, jumlah_barang);
                cout << "\nApakah Anda Ingin Kembali ke Menu Awal ? (y/t)";
                cin >> pilih;
                system("cls");
                break;
            case 3:
                pencarian_data(data_barang, jumlah_barang);
                cout << "\nApakah Anda Ingin Kembali ke Menu Awal ? (y/t)";
                cin >> pilih;
                system("cls");
                break;
            case 4:
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            }
        } while (pilihan != 4 && pilih == 'y' || pilih == 'Y');
        cout << "Terimakasih telah berkunjung ke Toko Kelontong 2-B" << endl;
}
