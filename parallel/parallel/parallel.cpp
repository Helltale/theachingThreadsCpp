#include <iostream>
#include <thread>
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <vector>
using namespace std::chrono;
using namespace std;
static const int N = 1000;
static float m[N][N];
static float n[N][N];
static float o[N][N];

void matrix_multiply(int start, int end) {
    for (int i = start; i < end; i++) {
        o[i % N][i / N] = 0;
        for (int j = 0; j < N; j++) {
            o[i % N][i / N] += m[j][i / N] * n[i % N][j];
        }
    }
}

void matrix_multiply_sequential() {
    for (int i = 0; i < N * N; i++) {
        o[i % N][i / N] = 0;
        for (int j = 0; j < N; j++) {
            o[i % N][i / N] += m[j][i / N] * n[i % N][j];
        }
    }
}

int main() {
    srand(time(0));

    cout << "Matrix rank: " << N << endl;
    //cin>>N;

    for (int i = 0; i < N * N; i++) {
        m[i % N][i / N] = (double)(rand() & 99) + (rand() & 100) / 100.0;
        if (N < 50) {
            if (i % N == 0)
                cout << "|" << m[i % N][i / N] << ", ";
            else if (i % N == N - 1)
                cout << m[i % N][i / N] << "|" << endl;
            else
                cout << m[i % N][i / N] << ", ";
        }
    }
    cout << endl;

    for (int i = 0; i < N * N; i++) {
        n[i % N][i / N] = (double)(rand() & 99) + (rand() & 100) / 100.0;
        if (N < 50) {
            if (i % N == 0)
                cout << "|" << n[i % N][i / N] << ", ";
            else if (i % N == N - 1)
                cout << n[i % N][i / N] << "|" << endl;
            else
                cout << n[i % N][i / N] << ", ";
        }
    }
    cout << endl;

    auto start = high_resolution_clock::now();

    // Определение количества потоков
    int num_threads = thread::hardware_concurrency();
    cout << "Number of threads: " << num_threads << endl;

    // Создание потоков и распределение работы
    vector<thread> threads;
    int chunk_size = N * N / num_threads;
    for (int i = 0; i < num_threads; i++) {
        int start_index = i * chunk_size;
        int end_index = (i == num_threads - 1) ? N * N : (i + 1) * chunk_size;
        threads.push_back(thread(matrix_multiply, start_index, end_index));
    }

    // Ожидание завершения всех потоков
    for (auto& t : threads) {
        t.join();
    }

    auto stop = high_resolution_clock::now();
    if (N < 50) {
        for (int i = 0; i < N * N; i++) {
            if (i % N == 0)
                cout << "|" << o[i % N][i / N] << ", ";
            else if (i % N == N - 1)
                cout << o[i % N][i / N] << "|" << endl;
            else
                cout << o[i % N][i / N] << ", ";
        }
    }

    cout << endl << duration_cast<nanoseconds>(stop - start).count() << " nanoseconds" << endl;
    cout << duration_cast<microseconds>(stop - start).count() << " microseconds" << endl;
    cout << duration_cast<milliseconds>(stop - start).count() << " milliseconds" << endl;
    cout << duration_cast<seconds>(stop - start).count() << " seconds" << endl;


    //==================================================================================================


    for (int i = 0; i < N * N; i++) {
        m[i % N][i / N] = (double)(rand() & 99) + (rand() & 100) / 100.0;
        if (N < 50) {
            if (i % N == 0)
                cout << "|" << m[i % N][i / N] << ", ";
            else if (i % N == N - 1)
                cout << m[i % N][i / N] << "|" << endl;
            else
                cout << m[i % N][i / N] << ", ";
        }
    }
    cout << endl;

    for (int i = 0; i < N * N; i++) {
        n[i % N][i / N] = (double)(rand() & 99) + (rand() & 100) / 100.0;
        if (N < 50) {
            if (i % N == 0)
                cout << "|" << n[i % N][i / N] << ", ";
            else if (i % N == N - 1)
                cout << n[i % N][i / N] << "|" << endl;
            else
                cout << n[i % N][i / N] << ", ";
        }
    }
    cout << endl;

    auto start1 = high_resolution_clock::now();

    matrix_multiply_sequential();

    auto stop1 = high_resolution_clock::now();

    cout << endl;

    if (N < 50) {
        for (int i = 0; i < N * N; i++) {
            if (i % N == 0)
                cout << "|" << o[i % N][i / N] << ", ";
            else if (i % N == N - 1)
                cout << o[i % N][i / N] << "|" << endl;
            else
                cout << o[i % N][i / N] << ", ";
        }
    }

    cout << endl << duration_cast<nanoseconds>(stop1 - start1).count() << " nanoseconds" << endl;
    cout << duration_cast<microseconds>(stop1 - start1).count() << " microseconds" << endl;
    cout << duration_cast<milliseconds>(stop1 - start1).count() << " milliseconds" << endl;
    cout << duration_cast<seconds>(stop1 - start1).count() << " seconds" << endl;



    return 0;
}
