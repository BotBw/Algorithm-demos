#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <climits>

using namespace std;

struct item {
  int len;
  int val;
};

int solution(const vector<item> &items, int l) {                             // dp by "considering the nth item"
  vector<vector<int>> V(items.size(), vector<int>(l + 1, 0));                // the table is developed line by line
  for(int j = 0; j < l + 1; j++) {
    V[0][j] = (j/items[0].len)*items[0].val;
  }
  for(int i = 1; i < items.size(); i++) {
    for(int j = items[i].len; j < l + 1; j++) {
      if(j >= items[i].len) { 
        V[i][j] = max(V[i-1][j], V[i][j - items[i].len] + items[i].val);
      } else {
        V[i][j] = V[i-1][j];
      }
    }
  }
  if(l == 10) {
    cout << endl;
    for(int i = 0; i < items.size(); i++) {
      for(int j = 0; j < l+1; j++) {
        cout << V[i][j] << ' ';
      }
      cout << endl;
    }
  }
  return V.back().back();
}

int opt_solution(const vector<item> &items, int l) {                      // dp by "considering the capacity of knapsack"
  vector<int> V(l + 1, 0);                                                // the table is developed column by column, only stored the max value of the column
  for(int i = 1; i < l + 1; i++) {
    int max = 0;
    for(int j = 0; j < items.size() ; j++) {
      if(i - items[j].len >= 0) {
        if(V[i - items[j].len] + items[j].val > max) { max = V[i - items[j].len] + items[j].val; }
      } 
    }
    V[i] = max;
  }
  if(l==10) {
    cout << endl;
    for(auto it : V) {
      cout << it << ' ';
    }
  }
  return V.back();
}

int main() {
  int n, l;
  cin >> n;
  vector<item> items;
  for(int i = 0; i < n; i++) {
    int len;
    int val;
    cin >> len >> val;
    items.push_back(item{len, val});
  }
  for(l = 0; l < 11; l++)
  {cout << solution(items, l) << ' ' << opt_solution(items, l) << endl;}
  return 0;
}