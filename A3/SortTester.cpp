#include <chrono>
#include <vector>
#include <utility>

void QuickSort(std::vector<int> &v, int l, int r);
void IntroSort(std::vector<int> &v, int l, int r, int depth);

class SortTester {
public:
  static std::pair<long long, long long> CompareSorts(std::vector<int> &a, int l, int r, int depth) {
    return {QuickTime(a, l, r), IntroTime(a, l, r, depth)};
  }

  static long long QuickTime(std::vector<int> &a, int l, int r) {
    std::vector<int> changes(r -l);
    for(int i = 0; i < r - l; ++i) {
      changes[i] = a[i + l];
    }
    auto start = std::chrono::high_resolution_clock::now();
    QuickSort(a, l, r);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    for(int i = 0; i < r - l; ++i) {
      a[i + l] = changes[i];
    }
    long long msec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    return msec;
  }

  static long long IntroTime(std::vector<int> &a, int l, int r, int depth) {
    std::vector<int> changes(r - l);
    for(int i = 0; i < r - l; ++i) {
      changes[i] = a[i + l];
    }
    auto start = std::chrono::high_resolution_clock::now();
    IntroSort(a, l, r, depth);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    for(int i = 0; i < r - l; ++i) {
      a[i + l] = changes[i];
    }
    long long msec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    return msec;
  }
private:
  SortTester() = delete;
};