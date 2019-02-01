#include <iostream>
#include <vector>

using namespace std;

int look_up(vector<vector<int>>& m, const vector<int>& p, size_t i, size_t j)
{
  // Ҫ��i <= j��ǰ������.
  if (m[i][j] != -1)
    return m[i][j];
  if (i == j)
    return 0;
  else
  {
    // �˴���Ȼ��i < j, �ȸ�m[i][j]�ĳ�ֵ.
    m[i][j] = look_up(m, p, i, i) + look_up(m, p, i + 1, j)
            + p[i - 1] * p[i] * p[j];
    for (size_t k = i + 1; k < j; ++k)
    {
      int cost = look_up(m, p, i, k) + look_up(m, p, k + 1, j)
               + p[i - 1] * p[k] * p[j];
      if (cost < m[i][j])
        m[i][j] = cost;
    }
  }
  return m[i][j];
}

int memoized_matrix_chain(const vector<int>& p)
{
  if (p.size() <= 1)
    return 0;
  size_t n = p.size() - 1;
  vector<vector<int>> m(n + 1);
  for (size_t i = 1; i < m.size(); ++i)
    m[i].resize(n + 1, -1);
  return look_up(m, p, 1, n);
}

int main()
{
  // ����ߴ�����.
  vector<int> p = {30, 35, 15, 5, 10, 20, 25};
  cout << "���ٳ˷�����: " << memoized_matrix_chain(p) << endl;
  return 0;
}
