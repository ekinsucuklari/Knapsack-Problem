#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

// Knapsack problemini çözen fonksiyon
vector<int> knapsack(int capacity, const vector<int>& values, const vector<int>& weights) {
    int N = values.size();
    vector<vector<int>> dp(N + 1, vector<int>(capacity + 1, 0));

    // Knapsack problemi çözümü
    for (int i = 1; i <= N; ++i) {
        for (int w = 1; w <= capacity; ++w) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            }
            else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Seçilen eşyaları bul
    vector<int> selected_items(N, 0);
    int total_value = dp[N][capacity];
    for (int i = N, w = capacity; i > 0 && total_value > 0; --i) {
        if (total_value != dp[i - 1][w]) {
            selected_items[i - 1] = 1;
            total_value -= values[i - 1];
            w -= weights[i - 1];
        }
    }

    return selected_items;
}

// Veri setini dosyadan oku
vector<vector<int>> read_dataset(const string& file_path) {
    vector<vector<int>> datasets;
    ifstream file(file_path);
    if (file.is_open()) {
        int N, capacity;
        while (file >> N >> capacity) {
            vector<int> values(N), weights(N);
            for (int i = 0; i < N; ++i) {
                file >> values[i];
            }
            for (int i = 0; i < N; ++i) {
                file >> weights[i];
            }
            datasets.push_back({ N, capacity });
            datasets.back().insert(datasets.back().end(), values.begin(), values.end());
            datasets.back().insert(datasets.back().end(), weights.begin(), weights.end());
        }
        file.close();
    }
    return datasets;
}

int main() {
    string input_file_path = "C:\\"; //add path here

    auto start = high_resolution_clock::now();

    // Veri setini oku
    vector<vector<int>> datasets = read_dataset(input_file_path);

    // Her bir dataset için Knapsack problemini çöz
    for (const auto& dataset : datasets) {
        int N = dataset[0];
        int capacity = dataset[1];
        vector<int> values(dataset.begin() + 2, dataset.begin() + N + 2);
        vector<int> weights(dataset.begin() + N + 2, dataset.end());

        vector<int> selected_items = knapsack(capacity, values, weights);

        // Çıktıyı ekrana yaz
        int total_value = 0;
        cout << "Secilen ogelerin indexleri (0/1): ";
        for (int i = 0; i < N; ++i) {
            cout << selected_items[i] << " ";
            if (selected_items[i]) {
                total_value += values[i];
            }
        }
        cout << endl;
        cout << "Toplam deger: " << total_value << endl;
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);

    cout << "Program calisma suresi: " << duration.count() << " saniye" << endl;

    return 0;
}
