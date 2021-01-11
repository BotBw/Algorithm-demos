#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
#include <climits>

using namespace std;

struct job {
  int val;
  int begin;
  int end;
};

struct cmp {
  bool operator()(const job &j1, const job &j2) {
    return j1.end < j2.end;
  }
};

int getPrev(const vector<job> &jobs, int i) {
  int maxEnd = 0;
  int rank = -1;
  for(int j = 0; j < i; j++) {
    if(jobs[j].end <= jobs[i].begin && jobs[j].end > maxEnd) {
      maxEnd = jobs[j].end;
      rank = j;
    }
  }
  return rank;
}


int maxProfit(vector<job> &jobs) {                        // dp by "nth job"
  if(jobs.size() < 1) return 0;
  sort(jobs.begin(), jobs.end(), cmp());
  vector<int> opt(jobs.size(), -1);
  vector<int> prev(jobs.size(), 200);
  for(int i = 0; i < prev.size(); i++) {
    prev[i] = getPrev(jobs, i);
  }
  opt[0] = jobs[0].val;
  for(int i = 1; i < opt.size(); i++) {
    if(prev[i] == -1) {
      opt[i] = max(opt[i - 1], jobs[i].val);
    } else {
      opt[i] = max(jobs[i].val + opt[prev[i]], opt[i - 1]);
    }
  }
  return opt.back();
}
vector<job> getAvailable(const vector<job> &jobs, int i) {
  vector<job> ans;
  for(auto it : jobs) {
    if(it.end <= i) {
      ans.push_back(it);
    }
  }
  return ans;
}

int helper(const vector<job> &jobs, vector<int>& memo, int i) {
  if(memo[i] >= 0) { return memo[i]; }
  if(i == 0) { return memo[i] = 0; }
  vector<job> ava = getAvailable(jobs, i);
  if(ava.size() < 1) return 0;
  int max = 0;
  for(auto it : ava) {
    int tmp = helper(jobs, memo, it.begin) + it.val;
    if(tmp > max) {
      max = tmp;
    }
  }
  memo[i] = max;
  return memo[i];
}

int solution(const vector<job> &jobs, int length) {                   // dp by "time"
  vector<int> memo(length + 1, INT_MIN);
  return helper(jobs, memo, length);
}




int main() {
  int n;
  cin >> n;
  vector<job> jobs;
  for(int i = 0; i < n; i++) {
    int val, begin, end;
    cin >> val;
    cin >> begin;
    cin >> end;
    jobs.push_back(job{val, begin, end});
  }
  int length = -1;
  for(auto it : jobs) {
    if(it.end > length)
      length = it.end;
  }
  cout << solution(jobs, length) << endl;
  cout << maxProfit(jobs) << endl;
 
  return 0;
}
