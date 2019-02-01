#include <iostream>
#include <vector>

using namespace std;

void print_optimal_solution(const vector<vector<size_t>>& s, size_t i, size_t j)
{
  if (i == j)
    cout << "A" << i;
  else
  {
    cout << "(";
    print_optimal_solution(s, i, s[i][j]);
    print_optimal_solution(s, s[i][j] + 1, j);
    cout << ")";
  }
}

int main()
{
  // ����ߴ�����.
  vector<int> p = {30, 35, 15, 5, 10, 20, 25};
  if (p.size() <= 1)
    return 0;

  // ����n������.
  size_t n = p.size() - 1;
  // ��ά����, �����±�0λ�ò���.
  vector<vector<int>> m(n + 1);     // �������ų˷�����.
  vector<vector<size_t>> s(n + 1);  // ���Ż���λ��.
  // ��ά����ÿά�ĳߴ�ָ��Ϊn + 1������ֵ.
  for (size_t i = 1; i <= n; ++i)
  {
    m[i].resize(n + 1, 0);
    s[i].resize(n + 1, i);
  }

  //��̬�滮���.
  for (size_t d = 1; d < n; ++d)
    for (size_t i = 1; i + d <= n; ++i)
    {
      m[i][i + d] = m[i][i] + m[i + 1][i + d] + p[i - 1] * p[i] * p[i + d];
      // s[i][i + d]�Ѿ�������ֵi.
      for (size_t k = i + 1; k < i + d; ++k)
      {
        int cost = m[i][k] + m[k + 1][i + d] + p[i - 1] * p[k] * p[i + d];
        if (cost < m[i][i + d])
        {
          m[i][i + d] = cost;
          s[i][i + d] = k;
        }
      }
    }
  cout << "���ٳ˷�����: " << m[1][n] << endl;
  print_optimal_solution(s, 1, n);
  cout << endl;
  return 0;
}
