#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

void fillTable(const vector<int> &data, vector<vector<int>> &sub, vector<vector<int>> &brackets) {
  int n = data.size() - 1;
  for(int i = 0; i < n; i++) {
    sub[i][i] = 0;
    brackets[i][i] = i - 1;
  }
  for(int l = 2; l <= n; l++) {
    for(int i = 0; i <= n - l; i++) {
      int j = i + l - 1;
      int min = INT_MAX;
      for(int k = i; k < j; k++) {
        int tmp = sub[i][k] + sub[k+1][j] + data[i]*data[k+1]*data[j+1];
        if(tmp < min) {
          min = tmp;
          brackets[i][j] = k;
        }
        sub[i][j] = min;
      }
    }
  }
}

void printChain(const vector<vector<int>> &brackets, int i, int j) {
  if(i == j) {
    cout << "A" << i;
  } else {
    cout << "(";
    printChain(brackets, i, brackets[i][j]);
    printChain(brackets, brackets[i][j]+1, j);
    cout << ")";
  }
}

void solution(const vector<int> &data) {
  int n = data.size() - 1;
  vector<vector<int>> sub(n, vector<int>(n, 0));
  vector<vector<int>> brackets(n, vector<int>(n, 0));
  fillTable(data, sub, brackets);
  cout << "The minimum multiplication is " << sub[0][n-1] << endl;
  printChain(brackets, 0, n-1);
  cout << endl;
}

int helper(const vector<int> &data, vector<vector<int>> &memo, vector<vector<int>> &brackets, int i, int j) {
  if(memo[i][j] < INT_MAX) {
    return memo[i][j];
  } else if (i == j) {
    memo[i][j] = 0;
    return memo[i][j];
  } else {
    for(int k = i; k < j; k++) {
      int tmp = helper(data, memo, brackets,i, k) + helper(data, memo, brackets, k+1, j) + data[i]*data[k+1]*data[j+1];
      if(tmp < memo[i][j]) {
        memo[i][j] = tmp;
        brackets[i][j] = k;
      }
    }
    return memo[i][j];
  }
}

void opt_solution(const vector<int> &data) {
  int n = data.size() - 1;
  vector<vector<int>> memo(n, vector<int>(n, INT_MAX));
  vector<vector<int>> brackets(n, vector<int>(n, 0));
  cout << "The minimum multiplication is " << helper(data, memo, brackets, 0, n - 1) << endl;
  printChain(brackets, 0, n-1);
}

int main() {
  int n;
  cin >> n;
  vector<int> data;
  for(int i = 0; i < n + 1; i++) {
    int edge;
    cin >> edge;
    data.push_back(edge);
  }
  solution(data);
  cout << endl;
  opt_solution(data);
  return 0;
}