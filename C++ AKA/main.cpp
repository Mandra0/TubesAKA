#include <iostream>
#include "kos.h"

using namespace std;

int main() {
    ListKos daftarKos;
    createListKos(daftarKos);
    int pilihan;

    do {
        tampilkanMenu();
        cin >> pilihan;
        cin.ignore();

        switch(pilihan) {
            case 1: {
                string nama, alamat, tipe;
                int lantai, kamar;
                double harga;

                cout << "\nNama Kos: ";
                getline(cin, nama);
                cout << "Alamat: ";
                getline(cin, alamat);
                cout << "Tipe (putra/putri/campuran): ";
                getline(cin, tipe);
                cout << "Jumlah Lantai: ";
                cin >> lantai;
                cout << "Jumlah Kamar: ";
                cin >> kamar;
                cout << "Harga: ";
                cin >> harga;
                cin.ignore();

                adrKos kosBaru = createKos(nama, alamat, tipe, lantai, kamar, harga);
                insertKos(daftarKos, kosBaru);
                cout << "Kos berhasil ditambahkan!" << endl;
                break;
            }

            case 2: {
                if (isEmptyKos(daftarKos)) {
                    cout << "Belum ada kos!" << endl;
                    break;
                }

                cout << "\nDaftar Kos:" << endl;
                displayAllKos(daftarKos);

                int pilihKos;
                cout << "Pilih nomor kos: ";
                cin >> pilihKos;

                adrKos kosTerpilih = getKosByIndex(daftarKos, pilihKos - 1);
                if (kosTerpilih == nullptr) {
                    cout << "Kos tidak ditemukan!" << endl;
                    break;
                }

                int nomor, lantaiKamar;
                string status;

                cout << "Nomor Kamar: ";
                cin >> nomor;
                cout << "Lantai Kamar: ";
                cin >> lantaiKamar;
                cin.ignore();
                cout << "Status (kosong/terisi): ";
                getline(cin, status);

                adrKamar kamarBaru = createKamar(nomor, lantaiKamar, status);
                insertKamar(kosTerpilih, kamarBaru);
                cout << "Kamar berhasil ditambahkan!" << endl;
                break;
            }

            case 3: {
                if (isEmptyKos(daftarKos)) {
                    cout << "Belum ada data kos!" << endl;
                    break;
                }

                displayAllKos(daftarKos);

                int pilihDetail;
                cout << "\nPilih nomor kos untuk detail (0 untuk kembali): ";
                cin >> pilihDetail;

                if (pilihDetail == 0) break;

                adrKos kosDetail = getKosByIndex(daftarKos, pilihDetail - 1);
                if (kosDetail == nullptr) {
                    cout << "Kos tidak ditemukan!" << endl;
                    break;
                }

                displayDetailKos(kosDetail);
                break;
            }

            case 4: {
                if (isEmptyKos(daftarKos)) {
                    cout << "Belum ada data kos!" << endl;
                    break;
                }

                displayAllKos(daftarKos);

                int pilihHapus;
                cout << "\nPilih nomor kos yang akan dihapus: ";
                cin >> pilihHapus;

                if (pilihHapus < 1 || pilihHapus > countKos(daftarKos)) {
                    cout << "Nomor tidak valid!" << endl;
                    break;
                }

                char konfirmasi;
                cout << "Yakin hapus? (y/n): ";
                cin >> konfirmasi;

                if (konfirmasi == 'y' || konfirmasi == 'Y') {
                    deleteKos(daftarKos, pilihHapus - 1);
                    cout << "Kos berhasil dihapus!" << endl;
                }
                break;
            }

            case 5: {
                if (isEmptyKos(daftarKos)) {
                    cout << "Belum ada data kos!" << endl;
                    break;
                }

                cout << "\nDaftar Kos:" << endl;
                displayAllKos(daftarKos);

                int pilihKos;
                cout << "Pilih nomor kos: ";
                cin >> pilihKos;

                adrKos kosTarget = getKosByIndex(daftarKos, pilihKos - 1);
                if (kosTarget == nullptr) {
                    cout << "Kos tidak ditemukan!" << endl;
                    break;
                }

                if (isEmptyKamar(kosTarget)) {
                    cout << "Kos ini belum memiliki kamar!" << endl;
                    break;
                }

                displayKamar(kosTarget);

                int nomorKamar;
                cout << "Masukkan nomor kamar yang akan dihapus: ";
                cin >> nomorKamar;

                deleteKamar(kosTarget, nomorKamar);
                cout << "Kamar berhasil dihapus!" << endl;
                break;
            }

            case 0:
                cout << "Terima kasih!" << endl;
                break;

            default:
                cout << "Pilihan salah!" << endl;
        }

    } while(pilihan != 0);

    return 0;
}
