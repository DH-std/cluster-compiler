#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

int main() {
  //int i = 2;
  vector<unsigned long long> ts;
  unsigned long long t;

  while (cin >> t) {
    ts.push_back(t);
  }

  sort(ts.begin(), ts.end());
  //assert(ts.size() > i);
  assert(!ts.empty());

  //unsigned long long sum = 0;
  //t = ts[i];

  //for (int j = ts.size() - i - 1; j > i; --j) {
    //sum += ts[j] - t;
  //}

  //t += sum / (ts.size() - i - i - 1);
  cout << ts[0] << endl;

  return 0;
}
