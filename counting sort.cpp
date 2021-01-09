#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

int main() {
  int n;
  int k;
  cout << "Enter the num and range of data: " << endl;
  cin >> n;
  cin >> k;
  vector<int> data(n, -1);
  vector<int> bucket(k + 1, 0);
  vector<int> result(n, -1);
  cout << "Input " << n << " data: " << endl;

  for(auto& it : data) {
    cin >> it;
    if(!(0 <= it && it <= k)) {
      cerr << "data exceeds range" << endl;
      exit(-1);
    }
  }
  for(auto it : data) {
    bucket[it]++;
  }

  int tmp = bucket.size() - 1;
  for(int i = 0; i < tmp; i++) {
    bucket[i+1] += bucket[i];
  }

  for(int i = data.size() - 1; i >= 0; i--) {
    result[bucket[data[i]] - 1] = data[i];
    bucket[data[i]]--;
  }

  for(auto it : result) {
    cout << it << ' ';
  }
  return 0;
}
