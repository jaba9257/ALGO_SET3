#include <random>
#include <vector>
#include <algorithm>

std::mt19937 rnd(12346123);

class ArrayGenerator {
public:
  static std::vector<int> GenArrayRnd(int n, int min = -100000, int max = 100000) {
    std::vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
      ans[i] = rnd() % (max - min + 1) + min;
    }
    return ans;
  }
  static std::vector<int> GenArrayRev(int n, int min = -100000, int max = 100000) {
    std::vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
      ans[i] = rnd() % (max - min + 1) + min;
    }
    sort(ans.begin(), ans.end());
    reverse(ans.begin(), ans.end());
    return ans;
  }
  static std::vector<int> GenArrayClose(int n, int min = -100000, int max = 100000) {
    std::vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
      ans[i] = rnd() % (max - min + 1) + min;
    }
    sort(ans.begin(), ans.end());
    for(int i = 0; i < n / 100; ++i) {
      std::swap(ans[rnd() % ans.size()], ans[rnd() % ans.size()]);
    }
    return ans;
  }
private:
  ArrayGenerator() = delete;
};