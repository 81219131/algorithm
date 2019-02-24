#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const double POSITIVE_INFINITY = numeric_limits<double>::infinity();

struct vertex_information {
  size_t vertex;
  double weight;
};

void sink(vector<vertex_information>& H, size_t i, vector<size_t>& vertex_index)
{
  // �ݴ�H[i]����, ע����������Ǻ�H[0]�Ƚ�.
  H[0] = H[i];
  // �����Һ��ӱ��.
  size_t rChildNo = 2 * i + 1;
  // �Һ��Ӵ���(�����Һ��Ӿ�����)ʱ���³�.
  while (rChildNo < H.size())
  {
    // MINΪ��С���ı��, ע�����ֵΪ0.
    size_t MIN = 0;
    // �Һ��ӽ�С��MIN��Ϊ�Һ��ӱ��.
    if (H[rChildNo].weight < H[MIN].weight)
      MIN = rChildNo;
    // ���ӽ�С��MIN��Ϊ���ӱ��.
    if (H[rChildNo - 1].weight < H[MIN].weight)
      MIN = rChildNo - 1;
    // ����: ����Ҫ�������³�����.
    if (MIN == 0)
      break;
    // ��Ҫ����ʱ�Ƚ���С�ĺ��Ӵ���iλ��.
    H[i] = H[MIN];
    vertex_index[H[i].vertex] = i;
    // ���������ж�.
    i = MIN;
    rChildNo = 2 * i + 1;
  }
  // �����������: ����������������Ҫ�����³�.
  if (rChildNo == H.size() && H[rChildNo - 1].weight < H[0].weight)
  {
    // ��Ҫ����ʱ�Ƚ����Ӵ���iλ��.
    H[i] = H[rChildNo - 1];
    vertex_index[H[i].vertex] = i;
    // �������ͣ��λ��.
    i = rChildNo - 1;
  }
  // ����ʼ��㴦�����ݴ����³���������ͣ����λ��.
  H[i] = H[0];
  vertex_index[H[i].vertex] = i;
}

/*
��ʵ·�����Ȳ�����path�д��, ����Ҳ�����һ�ݸ���.
���Ƕ�����״̬�Ƚ�����, �����������໹���б�Ҫ��.
*/

void swim(vector<vertex_information>& H, size_t i, vector<size_t>& vertex_index)
{
  // ��H[0]�������ڱ�����ֹѭ��, �������ʼ���i��������.
  H[0] = H[i];
  // ���H[0]С��iλ�õĸ��׽��ֵH[i / 2]�򲻶���iλ���ϸ�,
  // ����ʼ��㴦�������ݲ�����, ��ֵ�Դ���H[0].
  while (H[0].weight < H[i / 2].weight)
  {
    H[i] = H[i / 2];
    vertex_index[H[i].vertex] = i;
    i = i / 2;
  }
  // ����ʼ��㴦�����ݴ����ϸ���������ͣ����λ��.
  H[i] = H[0];
  vertex_index[H[i].vertex] = i;
}

void Dijkstra(vector<vector<vertex_information>> & WG, size_t s,
              vector<vertex_information>& path)
{
  size_t V = WG.size();
  path.resize(V);
  for (auto& x : path)
    x = {s, POSITIVE_INFINITY};
  path[s].weight = 0;
  // ��H����Ѱ����СȨ�صĶ���, ע����λ�������ڱ�, ������V + 1.
  vector<vertex_information> H(V + 1);
  vector<size_t> vertex_index(V);
  for (size_t i = 1; i < H.size(); ++i)
  {
    H[i] = {i - 1, path[i - 1].weight};
    vertex_index[i - 1] = i;
  }
  swim(H, vertex_index[s], vertex_index);
  for (size_t i = 0; i < V; ++i)
  {
    size_t u = H[1].vertex;
    H[1] = H.back();
    sink(H, 1, vertex_index);
    H.pop_back();
    for (const auto& neighbor : WG[u])
      if (path[u].weight + neighbor.weight < path[neighbor.vertex].weight)
      {
        size_t v = neighbor.vertex;
        path[v] = {u, path[u].weight + neighbor.weight};
        H[vertex_index[v]].weight = path[v].weight;
        swim(H, vertex_index[v], vertex_index);
      }
  }
}

int main()
{
  vector<vector<vertex_information>> WG = {
    {{1, 10}, {3, 5}},
    {{2, 1}, {3, 2}},
    {{4, 4}},
    {{1, 3}, {2, 9}, {4, 2}},
    {{0, 7}, {2, 4}},
    {}
  };
  size_t s = 0;
  // �������д��, ��·���е���һ�����·�����ȴ���һ��.
  vector<vertex_information> path(WG.size());
  Dijkstra(WG, s, path);
  vector<size_t> real_path;
  real_path.reserve(WG.size());
  for (size_t i = 0; i < path.size(); ++i)
  {
    cout << s << " to " << i << ", ";
    if (path[i].weight == POSITIVE_INFINITY)
    {
      cout << "Unreachable => Length: POSITIVE_INFINITY." << endl;
      continue;
    }
    real_path.resize(0);
    size_t x = i;
    while (x != s)
    {
      real_path.push_back(x);
      x = path[x].vertex;
    }
    if (real_path.size() != 0)
    {
      cout << "Path: " << s << ' ';
      for (auto riter = real_path.rbegin(); riter != real_path.rend(); ++riter)
        cout << *riter << ' ';
    }
    else
      cout << "Empty path ";
    cout << "=> Length: " << path[i].weight << '.';
    cout << endl;
  }
  return 0;
}
