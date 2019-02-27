#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const double POSITIVE_INFINITY = numeric_limits<double>::infinity();

struct vertex_information {
  size_t vertex;
  double weight;
};

bool Bellman_Ford_Moore(const vector<vector<vertex_information>>& WG, size_t s,
                        vector<vertex_information>& path)
{
  size_t V = WG.size();
  path.resize(V);
  for (auto& x : path)
    x = {s, POSITIVE_INFINITY};
  path[s].weight = 0;
  vector<size_t> L(V, 0);
  queue<size_t> Q;
  // ��ʼ���붥��s, ��������Ϊ1.
  Q.push(s);
  L[s] = 1;
  // �𲽵��������·������, ����V - 1��.
  while (!Q.empty())
  {
    // ����Ԫ�ض�Ӧ����Ϊu.
    size_t u = Q.front();
    // ������γ���V, ��Ȼ���ڸ���.
    if (L[u] > V)
      return false;
    Q.pop();
    // ������ǰ���������εı߽�ֵ, ��Ϊ�п��ܴ����Ա�. ��1��Ŀ����Ϊ�������ڵ�ǰ���еĲ��.
    size_t bound = L[u]--;
    for (const auto& x : WG[u])
      if (path[u].weight + x.weight < path[x.vertex].weight)
      {
        // Ϊ�������, ����ǰ����������Ϊv.
        size_t v = x.vertex;
        path[v] = {u, path[u].weight + x.weight};
        // ��v���ڶ����������, ע����������bound����һ���.
        if (L[v] < bound)
        {
          Q.push(v);
          L[v] = bound + 1;
        }
      }
  }
  return true;
}

int main()
{
  vector<vector<vertex_information>> WG = {
    {{1, 6}, {3, 7}},
    {{2, 5}, {3, 8}, {4, -4}},
    {{1, -2}},
    {{2, -3}, {4, 9}},
    {{0, 2}, {2, 7}}
  };
  size_t s = 0;
  vector<vertex_information> path(WG.size());
  bool has_shortest_path = Bellman_Ford_Moore(WG, s, path);
  if (has_shortest_path)
  {
    for (const auto& x : path)
      cout << x.weight << ' ';
    cout << endl;
  }
  return 0;
}
