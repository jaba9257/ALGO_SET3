#include <chrono>
#include <vector>
#include <utility>

std::vector<int> MergeSort(std::vector<int> &v, int l, int r);
std::vector<int> MergeAndInsertionSort(std::vector<int> &v, int l, int r);

class SortTester {
public:
  static std::pair<long long, long long> CompareSorts(std::vector<int> &a, int l, int r) {
    return {MergeTime(a, l, r), MergeInsertTime(a, l, r)};
  }

  static long long MergeTime(std::vector<int> &a, int l, int r) {
    auto start = std::chrono::high_resolution_clock::now();
    MergeSort(a, l, r);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long msec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    return msec;
  }

  static long long MergeInsertTime(std::vector<int> &a, int l, int r) {
    auto start = std::chrono::high_resolution_clock::now();
    MergeAndInsertionSort(a, l, r);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long msec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    return msec;
  }
private:
  SortTester() = delete;
};