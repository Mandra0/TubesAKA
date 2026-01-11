#include "kos.h"

void createListKos(ListKos &L) {
    L.first = nullptr;
}

bool isEmptyKos(ListKos L) {
    return L.first == nullptr;
}

adrKos createKos(string nama, string alamat, string tipe, int lantai, int kamar, double harga) {
    adrKos p = new elemenKos;
    p->info.nama = nama;
    p->info.alamat = alamat;
    p->info.tipe_penghuni = tipe;
    p->info.jumlah_lantai = lantai;
    p->info.jumlah_kamar = kamar;
    p->info.harga = harga;
    p->next = nullptr;
    p->info_kamar = nullptr;
    return p;
}

void insertKos(ListKos &L, adrKos p) {
    if (isEmptyKos(L)) {
        L.first = p;
    } else {
        adrKos last = L.first;
        while (last->next != nullptr) {
            last = last->next;
        }
        last->next = p;
    }
}

adrKos searchKos(ListKos L, string nama) {
    adrKos current = L.first;
    while (current != nullptr) {
        if (current->info.nama == nama) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

adrKos getKosByIndex(ListKos L, int index) {
    if (index < 0) return nullptr;

    adrKos current = L.first;
    int i = 0;
    while (current != nullptr && i < index) {
        current = current->next;
        i++;
    }
    return current;
}

void deleteKos(ListKos &L, int index) {
    if (isEmptyKos(L) || index < 0) return;

    adrKos toDelete = nullptr;

    if (index == 0) {
        toDelete = L.first;
        L.first = toDelete->next;
    } else {
        adrKos prev = getKosByIndex(L, index - 1);
        if (prev == nullptr || prev->next == nullptr) return;
        toDelete = prev->next;
        prev->next = toDelete->next;
    }

    if(toDelete != nullptr){
        adrKamar kamar = toDelete->info_kamar;
        while (kamar != nullptr) {
            adrKamar nextKamar = kamar->next;
            kamar = nextKamar;
            delete kamar;
        }
        delete toDelete;
    }
}

// ==============================================
// IMPLEMENTASI OPERASI KAMAR
// ==============================================

bool isEmptyKamar(adrKos p) {
    return p->info_kamar == nullptr;
}

adrKamar createKamar(int nomor, int lantai, string status) {
    adrKamar q = new elemenKamar;
    q->info.nomor = nomor;
    q->info.lantai = lantai;
    q->info.status = status;
    q->next = nullptr;
    return q;
}

void insertKamar(adrKos p, adrKamar q) {
    if (isEmptyKamar(p)) {
        p->info_kamar = q;
    } else {
        adrKamar last = p->info_kamar;
        while (last->next != nullptr) {
            last = last->next;
        }
        last->next = q;
    }
}

adrKamar searchKamar(adrKos p, int nomor) {
    adrKamar current = p->info_kamar;
    while (current != nullptr) {
        if (current->info.nomor == nomor) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void deleteKamar(adrKos p, int nomor) {
    if (isEmptyKamar(p)) return;

    if (p->info_kamar->info.nomor == nomor) {
        adrKamar temp = p->info_kamar;
        p->info_kamar = temp->next;
        delete temp;
        return;
    }

    adrKamar prev = p->info_kamar;
    while (prev->next != nullptr && prev->next->info.nomor != nomor) {
        prev = prev->next;
    }

    if (prev->next == nullptr) return;

    adrKamar toDelete = prev->next;
    prev->next = toDelete->next;
    delete toDelete;
}

// ==============================================
// IMPLEMENTASI TAMPILAN DATA
// ==============================================

void displayAllKos(ListKos L) {
    if (isEmptyKos(L)) {
        cout << "Belum ada data kos." << endl;
        return;
    }

    adrKos current = L.first;
    int i = 1;
    while (current != nullptr) {
        cout << i << ". " << current->info.nama << endl;
        cout << "   Alamat : " << current->info.alamat << endl;
        cout << "   Tipe   : " << current->info.tipe_penghuni << endl;
        cout << "   Harga  : Rp " << current->info.harga << endl;
        cout << "   ---------------------" << endl;
        current = current->next;
        i++;
    }
}

void displayDetailKos(adrKos p) {
    cout << "\n=== DETAIL KOS ===" << endl;
    cout << "Nama     : " << p->info.nama << endl;
    cout << "Alamat   : " << p->info.alamat << endl;
    cout << "Tipe     : " << p->info.tipe_penghuni << endl;
    cout << "Lantai   : " << p->info.jumlah_lantai << endl;
    cout << "Kamar    : " << p->info.jumlah_kamar << " kamar" << endl;
    cout << "Harga    : Rp " << p->info.harga << endl;
    cout << "-------------------" << endl;
    displayKamar(p);
}

void displayKamar(adrKos p) {
    if (isEmptyKamar(p)) {
        cout << "Belum ada kamar." << endl;
        return;
    }

    adrKamar current = p->info_kamar;
    cout << "Daftar Kamar:" << endl;
    while (current != nullptr) {
        cout << "- Kamar " << current->info.nomor
             << " (Lt. " << current->info.lantai
             << ") - " << current->info.status << endl;
        current = current->next;
    }
}

// ==============================================
// IMPLEMENTASI UTILITY
// ==============================================

int countKos(ListKos L) {
    int count = 0;
    adrKos current = L.first;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

int countKamar(adrKos p) {
    int count = 0;
    adrKamar current = p->info_kamar;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

int countKamarByStatus(adrKos p, string status) {
    int count = 0;
    adrKamar current = p->info_kamar;
    while (current != nullptr) {
        if (current->info.status == status) {
            count++;
        }
        current = current->next;
    }
    return count;
}

void tampilkanMenu() {
    cout << "\n=== SISTEM KOS ===" << endl;
    cout << "1. Tambah Kos" << endl;
    cout << "2. Tambah Kamar" << endl;
    cout << "3. Tampilkan Kos" << endl;
    cout << "4. Hapus Kos" << endl;
    cout << "5. Hapus Kamar" << endl;
    cout << "0. Keluar" << endl;
    cout << "Pilih: ";
}
