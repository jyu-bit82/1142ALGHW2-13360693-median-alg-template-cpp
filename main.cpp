#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// 用來同時儲存數值與權重
struct Item {
    int x;
    double w;
};

// 印出排序後資料
void printSortedValues(const vector<Item>& items) {
    cout << "Sorted data (x, w):\n";
    for (const auto& item : items) {
        cout << "(" << item.x << ", " << fixed << setprecision(2) << item.w << ") ";
    }
    cout << "\n\n";
}

// ------------------------------
// 1. 求中位數 (標準版)
// ------------------------------
double findMedian(vector<int> values) {
    if (values.empty()) return 0.0;

    // 1. 將 values 由小到大排序
    sort(values.begin(), values.end());

    // 2. 取得資料筆數 n
    size_t n = values.size();

    // 3. 判斷奇偶數
    if (n % 2 != 0) {
        // 奇數：回傳正中間的值
        return (double)values[n / 2];
    } else {
        // 偶數：回傳中間兩個值的平均
        return (values[n / 2 - 1] + values[n / 2]) / 2.0;
    }
}

// ------------------------------
// 2. 求加權中位數
// ------------------------------
int findWeightedMedian(vector<Item> items) {
    if (items.empty()) return -1;

    // 1. 將 items 依照 x 由小到大排序
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.x < b.x;
    });

    // 2. 顯示排序結果
    printSortedValues(items);

    // 3. 累積權重
    double cumulativeWeight = 0.0;
    cout << left << setw(5) << "x" << setw(10) << "w" << "Cumulative" << "\n";
    cout << "-----------------------------\n";

    // 4. 逐一走訪排序後的 items
    for (const auto& item : items) {
        cumulativeWeight += item.w;
        
        cout << left << setw(5) << item.x 
             << setw(10) << fixed << setprecision(2) << item.w 
             << fixed << setprecision(2) << cumulativeWeight << "\n";

        // 核心邏輯：找第一個累積權重 >= 0.5 的元素
        if (cumulativeWeight >= 0.5) {
            return item.x;
        }
    }

    return -1;
}

int main() {
    // 題目資料
    vector<int> x = {4, 3, 8, 5, 7, 10, 0, 9, 2, 11};
    vector<double> w = {0.05, 0.12, 0.08, 0.15, 0.14, 0.09, 0.10, 0.10, 0.06, 0.11};

    // 組合成 (x, w)
    vector<Item> items;
    for (size_t i = 0; i < x.size(); i++) {
        items.push_back({x[i], w[i]});
    }

    cout << "Original x values:\n";
    for (int v : x) cout << v << " ";
    cout << "\n\n";

    // 計算普通中位數
    double median = findMedian(x);
    cout << "Standard Median = " << fixed << setprecision(1) << median << "\n\n";

    // 計算加權中位數
    int weightedMedian = findWeightedMedian(items);
    cout << "\nFinal Weighted Median = " << weightedMedian << "\n";

    return 0;
}
