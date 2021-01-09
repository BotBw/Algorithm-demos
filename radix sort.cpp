#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

using namespace std;

vector<int> getBits(const vector<int> &data, int bit) {
  vector<int> bits(data.size(), -1);
  for(int i = 0; i < bits.size(); i++) {
    bits[i] = data[i] / pow(10, bit);
    bits[i] %= 10;
  }
  return bits;
}

void countingSort(vector<int> &data, int bit) {
  int buckets[10] = {0};
  vector<int> result(data.size(), -1);
  vector<int> bits = getBits(data, bit);
  for(int i = 0; i < bits.size(); i++) {
    buckets[bits[i]]++;
  }
  for(int i = 1; i < 10; i++) {
    buckets[i] += buckets[i-1];
  }
  for(int i = bits.size() - 1; i >= 0; i--) {
    result[buckets[bits[i]] - 1] = data[i];
    buckets[bits[i]]--;
  }
  data = result;
}



int main() {
  int n;
  cin >> n;
  vector<int> data(n, -1);
  int max = 0;
  for(auto &it : data) {
    cin >> it;
    if(it < 0) {
      cerr << "data cannot be less than 0" << endl;
      exit(-1);
    }
    if(it > max) max = it;
  }
  int bit = 0;
  while(max /= 10) {
    bit++;
  }
  for(int i = 0; i <= bit; i++) {
    countingSort(data, i);
  }
  for(auto it : data) {
    cout << it << ' ';
  }
  return 0;
}