#include <iostream>
#include <vector>
#include <set>
#include <limits>

using namespace std;

const double POSITIVE_INFINITY = numeric_limits<double>::infinity();

// ����ֱ��ϰ��, ��������д�����дȨ��. ��Ȼֱ����pairҲ����, ����������.
struct vertex_information {
  size_t vertex;
  double weight;
};

// ���붨��Ƚ�׼�����ʹ��vertex_information����.
struct cmp_vertex_weight {
  bool operator()(const vertex_information& a,
                  const vertex_information& b) const
  {
    // ����pair���ֵ���, ��������д�ܶ��ж�, ������weightΪ��, ע��pair�������в�ͬ.
    using P = pair<double, size_t>;
    // �ѵ�������Ҫ��weight�ִ��ڡ�С�ں͵��������������������»��ü�������vertex.
    return P(a.weight, a.vertex) < P(b.weight, b.vertex);
  }
};

/*
ʵ���Ͽ���ʹ��vector<double>ֱ�Ӵ��·������, ��double*ָ����뼯��,
���û���������Ԫ�ص����ƫ���˽��䶥����, ������Ͳ��ô���ô����Ϣ��.
*/

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
  // ��δѰ�ҵ��Ķ��㼯��ΪNS.
  set<vertex_information, cmp_vertex_weight> NS;
  // �����ڼ���NS�е�λ�ô���vertex_position��.
  vector<set<vertex_information>::iterator> vertex_position(V);
  for (size_t u = 0; u < V; u++)
    vertex_position[u] = NS.insert({u, length[u]}).first;
  for (size_t i = 0; i < V; i++)
  {
    // ÿ����δ�ҵ��Ķ��㼯����, Ѱ����sΪ����·��������̵Ķ���.
    // �豾�����ҵ��Ķ���Ϊu, ��Ӧ·�������Ѿ�����length[u]���Բ��ؼ�¼.
    size_t u = NS.begin()->vertex;
    // u���ҵ�, �����NS��ɾ��.
    NS.erase(NS.begin());
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
        // ͨ��ɾ�������²���ı�NS�е���Ӧȡֵ������λ��.
        NS.erase(vertex_position[v]);
        vertex_position[v] = NS.insert({v, length[v]}).first;
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
