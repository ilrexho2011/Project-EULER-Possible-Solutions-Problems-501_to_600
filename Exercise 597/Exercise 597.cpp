const int maxp = 1000000;
#include <pe>

const int n = 13;
const int l = 1800;

struct Tree
{
  int root;
  int p, v;
  vector<Tree> children;
};

map<vi, vector<Tree> > mem;

vector<Tree> get_tree(int* labels, int n);

void dfs(int* labels, int n, int root, vector<Tree>& children, vector<Tree>& result)
{
  if (n == 0)
  {
    Tree x;
    x.root = root;
    x.children = children;
    result.push_back(x);
  }
  else
  {
    for (int i = 1; i <= n; ++i)
    {
      auto possible = get_tree(labels, i);
      for (auto& iter: possible)
      {
        children.push_back(iter);
        dfs(labels+i, n-i, root, children, result);
        children.pop_back();
      }
    }
  }
}

vector<Tree> get_tree(int* labels, int n)
{
  vector<int> key(labels, labels+n);
  auto where = mem.find(key);
  if (where != mem.end()) return where->second;
  vector<Tree> children, result;
  dfs(labels, n-1, labels[n-1], children, result);
  return mem[key] = result;
}

void cal(Tree& tree)
{
  int p = 1;
  int v = 0;
  for (auto& iter: tree.children)
  {
    cal(iter);
    p += iter.p;
    v += iter.v;
  }
  tree.p = p;
  tree.v = v + p - 1;
}

double length[n+1];

double compute(map<pair<double, double>, double>& m)
{
  double result = 0;
  for (auto& iter: m)
  {
    double value = iter.first.second + 1;
    result += iter.second / value;
  }
  return result;
}
void dp_on_tree(Tree& tree, map<pair<double, double>, double> (&dp)[n+1])
{
  for (auto& child: tree.children)
  {
    dp_on_tree(child, dp);
  }
  auto& children = tree.children;
  const int size = sz(children);
  map<pair<double, double>, double> from;
  from[{0., 0.}] = 1;
  for (int i = size-1; i >= 0; --i)
  {
    map<pair<double, double>, double> X;
    map<pair<double, double>, double> Y;
    
    if (i < size - 1)
    {
      // from's second variable integrate
      // from 0 to x^((AR-BR)/AR) * v^(BR/AR)
      double A = length[children[i].root];
      double B = length[children[i+1].root];
      double R = length[tree.root];
      double AR = A-R;
      double BR = B-R;
      double s = (AR-BR)/AR;
      double t = BR/AR;
      for (const auto& iter: from)
      {
        double value = iter.first.second + 1;
        X[{iter.first.first + s * value, t*value}] += iter.second / value;
      }
    }
    else
    {
      X[{0., 0.}] = 1;
    }
    if (sz(children[i].children) > 0)
    {
      // from's second variable integrate
      // from 0 to x^(-BA/AR)*v^((AR+BA)/AR)
      double A = length[children[i].root];
      double B = length[children[i].children[0].root];
      double R = length[tree.root];
      double AR = A-R;
      double BA = B-A;
      double s = -BA/AR;
      double t = (AR+BA)/AR;
      for (const auto& iter: dp[children[i].root])
      {
        double value = iter.first.second + 1;
        Y[{s*value, iter.first.first + t*value}] += iter.second / value;
      }
    }
    else
    {
      Y[{0., 0.}] = 1;
    }
    map<pair<double, double>, double> to;
    for (const auto& iter1: X) for (const auto& iter2: Y)
      to[{iter1.first.first+iter2.first.first, iter1.first.second+iter2.first.second}] += iter1.second * iter2.second;
    from.swap(to);
  }
  dp[tree.root] = from;
}

int main()
{
  int data[123];
  for (int i = 0; i <= n; ++i) data[i] = i;
  auto trees = get_tree(data, n+1);
  for (int i = 0; i < n; ++i) length[i] = l - i * 40;
  length[n] = 0;
  cout << sz(trees) << endl;
  int idx = 0;
  const int cnt = sz(trees);
  double ans = 0;
  //#pragma omp parallel for reduction(+:ans) schedule(dynamic, 100) num_threads(13)
  for (int i = 0; i < cnt; ++i)
  {
    //if (++idx % 1000 == 0) cerr << idx << " " << cnt << " " << clock() << endl;
    auto& tree = trees[i];

    cal(tree);
    int permutations = tree.v - (tree.p - 1);
    if (permutations % 2 == 1) continue;
    map<pair<double, double>, double> dp[n+1];
    dp_on_tree(tree, dp);
    double temp = compute(dp[tree.root]);
    ans += temp;
  }
  printf("%.16f\n", 56./135);
  printf("%.16f\n", ans);
  return 0;
}