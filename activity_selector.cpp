#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// �����Ϊpair<int, int>.
using activity = pair<int, int>;

void activity_selector(const vector<activity>& S, vector<activity>& A)
{
  if (S.size() == 0)
    return;
  A.clear();
  // ʹ��̰���㷨���, ��ǰ���ݼ����еĽ���ʱ��ΪA.back().second.
  A.push_back(S[0]);
  for (size_t i = 1; i < S.size(); ++i)
    if (S[i].first >= A.back().second)
      A.push_back(S[i]);
}

int main()
{
  vector<activity> S = {{6, 10}, {8, 11}, {8, 12}, {3, 9}, {5, 9}, {2, 14},
                        {12, 16}, {3, 5}, {0, 6}, {5, 7}};
  vector<activity> A;
  // ���ս���ʱ������.
  sort(S.begin(), S.end(), [](activity a, activity b)
      { return a.second < b.second; });
  activity_selector(S, A);
  for (const auto& x : A)
    cout << x.first << ", " << x.second << endl;
  return 0;
}
