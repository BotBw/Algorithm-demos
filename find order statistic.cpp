#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

int partition(vector<int> &data, int lo, int hi) {
  if(lo == hi - 1) return lo;
  srand(time(0));
  int rdm = lo + rand() % (hi - lo);
  int pivot = data[rdm];
  swap(data[lo], data[rdm]);
  int i = lo + 1, j = lo + 1;
  for(; i < hi; i++) {
    if(data[i] < pivot) {
      swap(data[j], data[i]);
      j++;
    }
  }
  swap(data[lo], data[j - 1]);
  return j - 1;
}

int select(vector<int> &data, int lo, int hi, int i) {
  int mi = partition(data, lo, hi);
  if(mi == i) return data[i];
  else if(i < mi) return select(data, lo, mi, i);
  else return select(data, mi + 1, hi, i);
}

void quickSort(vector<int> &data, int lo, int hi) {
  if(lo >= hi - 1) return;
  int mi = partition(data, lo, hi);
  quickSort(data, lo, mi);
  quickSort(data, mi + 1, hi);
}

void quickSort(vector<int> &data) {
  quickSort(data, 0, data.size());
}

int select(vector<int> &data, int i) {
  return select(data, 0, int(data.size()), i);
}

int main() {
  int n, k;
  cin >> n;
  cin >> k;
  vector<int> data(n, -1);
  for(auto &it : data) {
    cin >> it;
  }
  cout << select(data, k) << endl;
  quickSort(data);
  for(auto it : data) {
    cout << it << ' ';
  }
  cout << endl;
  return 0;
}