#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const double POSITIVE_INFINITY = 9999.99;
//const double POSITIVE_INFINITY = std::numeric_limits<double>::infinity();

// ����ֱ��ϰ��, ��������д�����дȨ��. ��Ȼֱ����pairҲ����, ����������.
struct vertex_information {
  size_t vertex;
  double weight;
};

// ���붨��Ƚ�׼�����ʹ��vertex_information����.
struct cmp_vertex_weight_greater {
  bool operator()(const vertex_information& a,
                  const vertex_information& b) const
  {
  // ����pair���ֵ���, ��������д�ܶ��ж�, ������weightΪ��, ע��pair�������в�ͬ.
  using P = pair<double, size_t>;
  // �ѵ�������Ҫ��weight�ִ��ڡ�С�ں͵��������������������»��ü�������vertex.
  return P(a.weight, a.vertex) > P(b.weight, b.vertex);
  // ʵ���������������ʹ��==�ж�, ��vertex����Ψһ��, ����Ҳ��������д:
  /*
  return (a.weight == b.weight ? a.vertex > b.vertex : a.weight > b.weight);
  */
  // ����д���������ַ����Ƚϴ�С, ���ҵ�����ȵ�λ��.
  // ����һ����������ֻ��<��ϵ, ���ǵ÷������������.
  }
};

void Dijkstra(vector<vector<vertex_information>>& WG, size_t s,
              vector<size_t>& path, vector<double>& length)
{
  size_t V = WG.size();
  // ������ΪV, ������Ҫ��֤path��length���ǳ�ΪV������.
  path.resize(V);
  length.resize(V);
  // ��ʼ��path����, ��������Ԫ�س�ֵ��Ϊs.
  for (auto& x : path)
    x = s;
  // ��ʼ��length����.
  // ��ʱ������length�����е�Ԫ��Ϊ�������.
  for (auto& x : length)
    x = POSITIVE_INFINITY;
  // sλ��·�����ȳ�ֵΪ0, ����������s���ȱ��ҵ�.
  length[s] = 0;
  // ��δѰ�ҵ��Ķ���ŵ����ȼ�����PQ��.
  // ���ʹ��pair<double, size_t>, ����greater<pair<double, size_t>>����PQ.
  priority_queue<vertex_information, vector<vertex_information>,
                 cmp_vertex_weight_greater> PQ;
  // ��ʼ�����ȼ�����.
  PQ.push({s, length[s]});
  for (size_t i = 0; i < V; i++)
  {
    // ȥ���Ѵ�����Ķ���.
    while (length[PQ.top().vertex] < PQ.top().weight)
        PQ.pop();
    // ÿ����δ�ҵ��Ķ��㼯����, Ѱ����sΪ����·��������̵Ķ���.
    // �豾�����ҵ��Ķ���Ϊu, ��Ӧ·�������Ѿ�����length[u]���Բ��ؼ�¼.
    size_t u = PQ.top().vertex;
    PQ.pop();
    // ��u���ڽӱ�Ϊ���ݸ����������.
    for (const auto& neighbor : WG[u])
      if (length[u] + neighbor.weight < length[neighbor.vertex])
      {
        // Ϊ�������, ����ǰ��������Ϊneighbor.vertex���Ϊv.
        size_t v = neighbor.vertex;
        // ��lenght[u] + w(u, v) < length[v],
        // �����path[v]��length[v].
        path[v] = u;
        length[v] = length[u] + neighbor.weight;
        // �������ȼ�������.
        PQ.push({v, length[v]});
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
    {{0, 7}, {2, 4}}
  };
  size_t s = 0;
  vector<size_t> path(WG.size());
  vector<double> length(WG.size());
  Dijkstra(WG, s, path, length);
  for (const auto& x : length)
    cout << x << ' ';
  cout << endl;
  return 0;
}
