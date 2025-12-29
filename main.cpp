#include "hybridsort.h"
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>
#include <iomanip>

int main()
{
    int maxN, step, k; // Tambahin k di sini
    cout << "=== Simulasi Skalabilitas Algoritma ===" << endl;
    cout << "Masukkan batas maksimal N: ";
    cin >> maxN;
    cout << "Masukkan kelipatan kenaikan (step): ";
    cin >> step;
    cout << "Masukkan nilai Threshold K (misal 32): "; // Input k biar valid
    cin >> k;

    // Header disesuaikan, tambah kolom Hybrid
    cout << "\n" << left << setw(10) << "N";
    cout << setw(20) << "Insertion (ms)";
    cout << setw(20) << "Merge (ms)";
    cout << "Hybrid (ms)" << endl;
    cout << string(65, '-') << endl;

    random_device rd;
    mt19937 g(rd());

    for (int n = step; n <= maxN; n += step) {
        vector<int> base_data(n);
        for (int i = 0; i < n; i++) base_data[i] = i;
        shuffle(base_data.begin(), base_data.end(), g);

        vector<int> d1 = base_data;
        vector<int> d2 = base_data;
        vector<int> d3 = base_data; // Deklarasiin d3-nya!

        // Hitung Insertion Sort
        auto s1 = chrono::high_resolution_clock::now();
        insertionSort(d1, 0, n - 1);
        auto e1 = chrono::high_resolution_clock::now();
        double dur1 = chrono::duration<double, milli>(e1 - s1).count();

        // Hitung Merge Sort
        auto s2 = chrono::high_resolution_clock::now();
        mergeSort(d2, 0, n - 1);
        auto e2 = chrono::high_resolution_clock::now();
        double dur2 = chrono::duration<double, milli>(e2 - s2).count();

        // Hitung Hybrid sort
        auto s3 = chrono::high_resolution_clock::now();
        hybridSort(d3, 0, n - 1, k); // Sekarang k dan d3 udah ada
        auto e3 = chrono::high_resolution_clock::now();
        double t3 = chrono::duration<double, milli>(e3 - s3).count();

        // Tampilan HARUS nampilin ketiganya biar studinya terbukti
        cout << left << setw(10) << n
             << setw(20) << fixed << setprecision(3) << dur1
             << setw(20) << dur2
             << t3 << endl; // Munculin t3 di sini!
    }

    return 0;
}
