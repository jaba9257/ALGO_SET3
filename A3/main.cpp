#include <bits/stdc++.h>
#include "ArrayGenerator.cpp"
#include "SortTester.cpp"

using namespace std;

int ins_time = 16;

void print(vector<int> &v) {
  for (int i = 0; i < v.size(); ++i) {
    cout << v[i] << ' ';
  }
  cout << endl;
}

void InsertionSort(vector<int> &v, int l, int r) {
  if (r - l < 2) {
    return;
  }
  for (int i = l; i < r; ++i) {
    int j = i - 1;
    while (j >= l && v[j] > v[j + 1]) {
      swap(v[j], v[j + 1]);
      --j;
    }
  }
}

void heapify(vector<int> &v, int i, int n, int l) {
  int root = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < n && v[l + root] < v[l + left]) {
    root = left;
  }
  if (right < n && v[l + root] < v[l + right]) {
    root = right;
  }
  if (root != i) {
    swap(v[l + root], v[l + i]);
    heapify(v, root, n, l);
  }
}

void buildMaxHeap(vector<int> &v, int l, int r) {
  int n = r - l;
  for (int i = n / 2 - 1; i >= 0; --i) {
    heapify(v, i, n, l);
  }
}

void HeapSort(vector<int> &v, int l, int r) {
  int n = r - l;
  if (n <= 1) {
    return;
  }
  buildMaxHeap(v, l, r);
  for (int i = r - 1; i > l; --i) {
    swap(v[l], v[i]);
    heapify(v, 0, i - l, l);
  }
}

int Replace(vector<int> &v, int l, int r) {
  int mid = r - 1;
  int pivot = v[mid];
  swap(v[mid], v[r - 1]);
  int i = l;
  for (int j = l; j < r - 1; j++) {
    if (v[j] <= pivot) {
      swap(v[i], v[j]);
      i++;
    }
  }
  swap(v[i], v[r - 1]);
  return i;
}

void QuickSort(vector<int> &v, int l, int r) {
  if (l + 1 >= r) {
    return;
  }
  if (l + 2 == r) {
    if (v[l] > v[l + 1]) {
      swap(v[l], v[l + 1]);
    }
    return;
  }

  int q = Replace(v, l, r);
  QuickSort(v, l, q);
  QuickSort(v, q + 1, r);
}

void IntroSort(vector<int> &v, int l, int r, int depth) {
  if (r - l <= ins_time) {
    InsertionSort(v, l, r);
    return;
  }
  if (depth == 0) {
    HeapSort(v, l, r);
    return;
  }
  int q = Replace(v, l, r);
  IntroSort(v, l, q, depth - 1);
  IntroSort(v, q + 1, r, depth - 1);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n = 100000;
  //vector<int> v = ArrayGenerator::GenArrayRnd(10000000, -1000000, 1000000);
  /*cout << SortTester::IntroTime(v, 0, 10000000, 24) << '\n';
  for(int i = 0; i < 500; ++i) {
    cout << v[i] << endl;
  }*/
  vector<int> v_rnd = ArrayGenerator::GenArrayRnd(n, 0, 6000);
  vector<int> v_rev = ArrayGenerator::GenArrayRev(n, 0, 6000);
  vector<int> v_close = ArrayGenerator::GenArrayClose(n, 0, 6000);
  ofstream out_rnd, out_rev, out_close;
  out_rnd.open("random.txt");
  out_rev.open("reverse.txt");
  out_close.open("close.txt");
  for(int i = 500; i <= n; i += 100) {
    int l = rnd() % (n - i + 1), r = l + i;
    int j = i;
    int depth = 0;
    while(j > 0) {
        j /= 2;
        depth++;
    }
    out_rnd << '{' << i << ", " << SortTester::QuickTime(v_rnd, l, r) << ", " << SortTester::IntroTime(v_rnd, l, r, depth) << "}\n";
    out_rev << '{' << i << ", " << SortTester::QuickTime(v_rev, l, r) << ", " << SortTester::IntroTime(v_rev, l, r, depth) << "}\n";
    out_close << '{' << i << ", " << SortTester::QuickTime(v_close, l, r) << ", " << SortTester::IntroTime(v_close, l, r, depth) << "}\n";
    //print(v_rnd);
  }
}
