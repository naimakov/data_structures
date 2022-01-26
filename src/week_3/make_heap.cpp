#include <assert.h>

#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::make_pair;
using std::pair;
using std::swap;
using std::vector;

time_t t_start, t_end;

/**
 * Convert array into heap
 * Implement bulding a heap from an array step of HeapSort algorithm.
 * Input:
 *      integer n
 *      n space-separated integers a_i
 * Output:
 *      integer m - total number of swaps, 0 <= m <= 4n
 *      pair of integers (i,j) - m swaps of indices of elements
 * Constraints:
 *      1 <= n <= 10^5, 0 <= i,j <= n-1, 0 <= a_i <= 10^9, a_i != a_j for i != j
 * Time limit: 1 sec
 * Memory limit: 512 mb
 */

void tic(int mode = 0) {
  if (mode == 0)
    t_start = time(0);
  else {
    t_end = time(0);
    cout << "Elapsed time is " << difftime(t_end, t_start) << " seconds\n";
  }
}
void toc() { tic(1); }

class HeapBuilder {
 private:
  vector<int> data_;
  vector<pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for (int i = 0; i < n; ++i) cin >> data_[i];
  }

  void SiftDown(int i) {
    int minId = i;
    int l = 2 * i + 1, r = 2 * i + 2;
    if (l < data_.size() && data_[l] < data_[minId]) {
      minId = l;
    }
    if (r < data_.size() && data_[r] < data_[minId]) {
      minId = r;
    }
    if (i != minId) {
      swap(data_[i], data_[minId]);
      swaps_.push_back(make_pair(i, minId));
      SiftDown(minId);
    }
  }

  void GenerateSwaps() {
    swaps_.clear();
    // The following naive implementation just sorts
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap,
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
    for (int i = 0; i < data_.size(); ++i)
      for (int j = i + 1; j < data_.size(); ++j) {
        if (data_[i] > data_[j]) {
          swap(data_[i], data_[j]);
          swaps_.push_back(make_pair(i, j));
        }
      }
  }
  void GenerateSwapsHeap() {
    swaps_.clear();
    // The following implementation builds heap out of
    // the given sequence and saves the resulting sequence of swaps.
    for (int i = (data_.size() - 1) / 2; i >= 0; --i) {
      SiftDown(i);
    }
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwapsHeap();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
