#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

const int Size = 100;

int solution(const vector<pair<int, int>> &item, int Table[][Size], int I[][Size], int b) {
  int n = item.size();
  for(int w = 0; w <= b; w++) {
    Table[1][w] = (w/item[0].second)*item[0].first;
    I[1][w] = (w >= item[0].second) ? 1 : 0;
  }

  for(int i = 2; i <= n; i++) {
    for(int w = 0; w <= b; w++) {
      if(w-item[i - 1].second >= 0) {
        Table[i][w] = max(Table[i-1][w], Table[i][w-item[i - 1].second] + item[i - 1].first);
        I[i][w] = (Table[i-1][w] > Table[i][w-item[i - 1].second] + item[i - 1].first) ? I[i-1][w] : i;
      } else {
        Table[i][w] = Table[i-1][w];
        I[i][w] = I[i-1][w];
      }
    }
  }
  return Table[n][b];
}

int main() {
  int V[Size][Size] = {0};
  int I[Size][Size] = {0};
  int n;
  int b;
  cin >> n >> b;
  vector<pair<int, int>> item;
  for(int i = 0; i < n; i++) {
    int v, w;
    cin >> v >> w;
    item.push_back(make_pair(v, w));
  }
  cout << solution(item, V, I, b) << endl;
  return 0;
}