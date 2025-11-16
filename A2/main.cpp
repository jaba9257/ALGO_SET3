#include <bits/stdc++.h>
#include "ArrayGenerator.cpp"
#include "SortTester.cpp"

using namespace std;

int ins_time = 32;

vector<int> Merge(vector<int> a, vector<int> b) {
  vector<int> ans;
  int i = 0, j = 0;
  int n = a.size(), m = b.size();
  while (i + j < n + m) {
    if (i == n) {
        ans.push_back(b[j]);
        ++j;
    } else if (j == m) {
        ans.push_back(a[i]);
        ++i;
    } else if (a[i] < b[j]) {
        ans.push_back(a[i]);
        ++i;
    } else {
        ans.push_back(b[j]);
        ++j;
    }
  }
  return ans;
}

vector<int> MergeSort(vector<int> &v, int l, int r) {
    if(l + 1 == r) {
        return {v[l]};
    }
    return Merge(MergeSort(v, l, (l + r) / 2), MergeSort(v, (l + r) / 2, r));
}

vector<int> InsertionSort(vector<int> &v, int l, int r) {
    vector<int> ans(r - l);
    int n = r - l;
    for(int i = l; i < r; ++i) {
        ans[i - l] = v[i];
    }
    for(int i = 1; i < n; ++i) {
        int j = i - 1;
        while(j >= 0 && ans[j] > ans[j + 1]) {
            swap(ans[j], ans[j + 1]);
            --j;
        }
    }
    return ans;
}

vector<int> MergeAndInsertionSort(vector<int> &v, int l, int r) {
    if(r - l < ins_time) {
        return InsertionSort(v, l, r);
    }
    return Merge(MergeAndInsertionSort(v, l, (l + r) / 2), MergeAndInsertionSort(v, (l + r) / 2, r));
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  vector<int> v_rnd = ArrayGenerator::GenArrayRnd(100000, 0, 6000);
  vector<int> v_rev = ArrayGenerator::GenArrayRev(100000, 0, 6000);
  vector<int> v_close = ArrayGenerator::GenArrayClose(100000, 0, 6000);
  ofstream out_rnd, out_rev, out_close;
  out_rnd.open("random.txt");
  out_rev.open("reverse.txt");
  out_close.open("close.txt");
  int n = 100000;
  for(int i = 500; i <= 100000; i += 100) {
    int l = rnd() % (n - i + 1), r = l + i;
    out_rnd << '{' << i << ", " << SortTester::MergeTime(v_rnd, l, r) << ", " << SortTester::MergeInsertTime(v_rnd, l, r) << "}\n";
    out_rev << '{' << i << ", " << SortTester::MergeTime(v_rev, l, r) << ", " << SortTester::MergeInsertTime(v_rev, l, r) << "}\n";
    out_close << '{' << i << ", " << SortTester::MergeTime(v_close, l, r) << ", " << SortTester::MergeInsertTime(v_close, l, r) << "}\n";
  }
  vector<int> v = ArrayGenerator::GenArrayRnd(1000000);
  auto ans = SortTester::CompareSorts(v, 0, v.size());
  cout << "random big " << ans.first << ' ' << ans.second <<'\n';
  v = ArrayGenerator::GenArrayRev(1000000);
  ans = SortTester::CompareSorts(v, 0, v.size());
  cout << "reverse big " << ans.first << ' ' << ans.second <<'\n';
  v = ArrayGenerator::GenArrayClose(1000000);
  ans = SortTester::CompareSorts(v, 0, v.size());
  cout << "Almost sorted big " << ans.first << ' ' << ans.second <<'\n';
}