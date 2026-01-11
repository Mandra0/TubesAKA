#ifndef KOS_H_INCLUDED
#define KOS_H_INCLUDED
#include <iostream>

using namespace std;

struct Kamar {
    int nomor;
    int lantai;
    string status;
};

struct Kos {
    string nama;
    string alamat;
    string tipe_penghuni;
    int jumlah_lantai;
    int jumlah_kamar;
    double harga;
};

typedef struct elemenKamar *adrKamar;
typedef struct elemenKos *adrKos;

struct elemenKamar {
    Kamar info;
    adrKamar next;
};

struct elemenKos {
    Kos info;
    adrKos next;
    adrKamar info_kamar;
};

struct ListKos {
    adrKos first;
};

void createListKos(ListKos &L);
bool isEmptyKos(ListKos L);
adrKos createKos(string nama, string alamat, string tipe, int lantai, int kamar, double harga);
void insertKos(ListKos &L, adrKos p);
adrKos searchKos(ListKos L, string nama);
adrKos getKosByIndex(ListKos L, int index);
void deleteKos(ListKos &L, int index);

bool isEmptyKamar(adrKos p);
adrKamar createKamar(int nomor, int lantai, string status);
void insertKamar(adrKos p, adrKamar q);
adrKamar searchKamar(adrKos p, int nomor);
void deleteKamar(adrKos p, int nomor);

void displayAllKos(ListKos L);
void displayDetailKos(adrKos p);
void displayKamar(adrKos p);
void tampilkanMenu();

int countKos(ListKos L);
int countKamar(adrKos p);
int countKamarByStatus(adrKos p, string status);

#endif // KOS_H_INCLUDED
