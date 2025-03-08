const int maxp = 100000;
#include <pe>

const int m = 4;
const int n = 2; // this code only work for n = 2
const int maxcol = (m + 2) * 2;

typedef Point3D<int> Pt;

vector<Pt> left_col;

SL int check_is(int value, int dest)
{
  if (value == -1) return 1;
  return value == dest;
}

int cid[256];
int oid[256];
int idx[256];
int cc[256];
int oc[256];

void dfs(int col, vector<Pt>& vec, int l2, const vector<Pt>& last, int64 each, map<vector<Pt>, int64>& next)
{
  if (l2 > m) return;
  const int size = sz(last);
#if 1
// This check is covered by the check when adding a shape
  for (int i = 0; i < size; ++i)
  {
    const int start = last[i].x;
    if (last[i].z == 3 && !check_is(cc[start], 4)) return;
    if (last[i].z == 5 && !check_is(cc[start], 6)) return;
    if (last[i].z == 4)
    {
      if (!check_is(cc[start], 3) && !check_is(cc[start], 2) && !check_is(cc[start], 0)) return;
    }
    if (last[i].z == 6)
    {
      if (!check_is(cc[start], 5) && !check_is(cc[start], 2) && !check_is(cc[start], 0)) return;
    }
    if (last[i].z == 1)
    {
      if (!check_is(cc[start], 0)) return;
      if (!check_is(cc[start+1], 0)) return;
      if (!check_is(cid[start], oid[start])) return;
      if (!check_is(cid[start+1], oid[start+1])) return;
    }
    if (last[i].z == 0)
    {
      int t = 0;
      if (start > 0) t = t || check_is(cc[start-1], 0) && check_is(cc[start], 0) &&
        check_is(cid[start-1], oid[start]) && check_is(cid[start], oid[start+1]) && (cc[start+1] == -1 || cc[start+1] != 3 && cc[start+1] != 4 && cc[start+1] != 6);
      t = t || check_is(cc[start], 1) && check_is(cc[start+1], 1) &&
        check_is(cid[start], oid[start]) && check_is(cid[start+1], oid[start+1]);
      if (start+2 <= maxcol - 1) t = t || check_is(cc[start+1], 0) && check_is(cc[start+2], 0) &&
        check_is(cid[start+1], oid[start]) && check_is(cid[start+2], oid[start+1]) && (cc[start] == -1 || cc[start] != 5 && cc[start] != 4 && cc[start] != 6);
      if (t == 0) return;
    }
    if (last[i].z == 2)
    {
      if (!check_is(cc[start], 3) && !check_is(cc[start], 2) && !check_is(cc[start], 0)) return;
      if (!check_is(cc[start+1], 5) && !check_is(cc[start+1], 2) && !check_is(cc[start+1], 0)) return;
    }
  }
#endif
  const int n = sz(vec);
  if (n > 0 && vec[n-1].y == maxcol && l2 == m)
  {
    next[vec] += each;
  }
  else
  {
    const int start = n > 0 ? vec[n-1].y : 0;
    vec.pb({start, 0, 0});
    if (start + 2 <= maxcol)
    {
      vec[n].y = start + 2;
      for (int type = 0; type <= 0; ++type)
      {
        int can = 0;
        can = can || oc[start] == 1 && oc[start+1] == 1 && oid[start] == l2 && oid[start+1] == l2;
        can = can || start - 1 >= 0 && oc[start-1] == 0 && oc[start] == 0 && oid[start-1] == l2 && oid[start] == l2 && oc[start+1] != 3 && oc[start+1] != 5 && oc[start+1] != 6;
        can = can || start + 2 <= maxcol - 1 && oc[start+1] == 0 && oc[start+2] == 0 && oid[start+1] == l2 && oid[start+2] == l2 && oc[start] != 3 && oc[start] != 4 && oc[start] != 5;
        if (!can) continue;
        vec[n].z = type;
        cc[start] = cc[start+1] = type;
        cid[start] = cid[start+1] = l2;
        dfs(col, vec, l2 + 1, last, each, next);
        cc[start] = cc[start+1] = -1;
        cid[start] = cid[start+1] = -1;
      }
      for (int type = 1; type <= 1; ++type)
      {
        int can = 0;
        can = can || oc[start] == 0 && oc[start+1] == 0 && oid[start] == l2 && oid[start+1] == l2;
        if (!can) continue;
        vec[n].z = type;
        cc[start] = cc[start+1] = type;
        cid[start] = cid[start+1] = l2;
        dfs(col, vec, l2 + 1, last, each, next);
        cc[start] = cc[start+1] = -1;
        cid[start] = cid[start+1] = -1;
      }
      for (int type = 2; type <= 2; ++type)
      {
        int canup = 0;
        int candown = 0;
        canup = canup || start - 1 >= 0 && oc[start-1] == 0 && oc[start] == 0 && oid[start-1] == oid[start] && idx[start] == 1;
        canup = canup || oc[start] == 6;
        canup = canup || start - 1 >= 0 && oc[start-1] == 2 && oc[start] == 2 && oid[start-1] == oid[start] && idx[start] == 1;
        
        candown = candown || start + 2 <= maxcol - 1 && oc[start+1] == 0 && oc[start+2] == 0 && oid[start+1] == oid[start+2];
        candown = candown || oc[start+1] == 4;
        candown = candown || start + 2 <= maxcol - 1 && oc[start+1] == 2 && oc[start+2] == 2 && oid[start+1] == oid[start+2];

        if (!canup || !candown) continue;
        vec[n].z = type;
        cc[start] = cc[start+1] = type;
        dfs(col, vec, l2, last, each, next);
        cc[start] = cc[start+1] = -1;
      }
    }
    if (start + 1 <= maxcol)
    {
      vec[n].y = start + 1;
      for (int type = 3; type < 7; ++type)
      {
        if (type == 4 && oc[start] != 3) continue;
        if (type == 6 && oc[start] != 5) continue;
        if (type == 5 && oc[start] != 6 && oc[start] != 0 && !(oc[start] == 2 && idx[start] == 1)) continue;
        if (type == 3 && oc[start] != 4 && oc[start] != 0 && !(oc[start] == 2 && idx[start] == 0)) continue;
        vec[n].z = type;
        cc[start] = type;
        dfs(col, vec, l2, last, each, next);
        cc[start] = -1;
      }
    }
    vec.pop_back();
  }
}

void solve()
{
  map<vector<Pt>, int64> curr;
  curr[left_col] = 1;
  for (int i = 1; i <= maxcol; ++i)
  {
    dbg(i);
    dbg(sz(curr));
    map<vector<Pt>, int64> next;
    for (auto& iter: curr)
    {
      vector<Pt> vec;
      fill(cc, cc+32, -1);
      fill(cid, cid+32, -1);
      fill(oid, oid+32, -1);
      fill(idx, idx+32, -1);
      int j = 0;
      int mid = 100;
      for (int i = 0; i < sz(iter.first); ++i)
      {
        oc[iter.first[i].x] = iter.first[i].z;
        idx[iter.first[i].x] = 0;
        if (iter.first[i].z < 3)
        {
          oc[iter.first[i].x+1] = iter.first[i].z;
          idx[iter.first[i].x+1] = 1;
        }
        if (iter.first[i].z < 2)
        {
          oid[iter.first[i].x] = oid[iter.first[i].x+1] = j++;
        }
        if (iter.first[i].z == 2)
        {
          oid[iter.first[i].x] = oid[iter.first[i].x+1] = mid++;
        }
      }
      assert(j == m);
      dfs(i, vec, 0, iter.first, iter.second, next);
    }
    next.swap(curr);
  }
  
  int64 ans = 0;
  for (auto& iter: curr)
  {
    if (1)
    {
      vector<Pt> dest = iter.first;
      if (sz(dest) != 4 + m) continue;
      if (dest[0].z != 4) continue;
      if (dest[1].z != 3) continue;
      int ok = 1;
      for (int i = 2; i < 2 + m; ++i)
      {
        if (dest[i].z != 0) {ok = 0; break;}
      }
      if (!ok) continue;
      if (dest[2+m].z != 5) continue;
      if (dest[3+m].z != 6) continue;
    }
    ans += iter.second;
  }
  dbg(ans);
}

int main()
{
  dbg(n);
  dbg(m);
  dbg(maxcol);
  left_col.resize(m+4);
  
  left_col[0].x = 0;
  left_col[0].y = 1;
  left_col[0].z = 5;

  left_col[1].x = 1;
  left_col[1].y = 2;
  left_col[1].z = 6;

  for (int i = 2; i < 2 + m; ++i)
  {
    left_col[i].x = i * 2 - 2;
    left_col[i].y = i * 2;
    left_col[i].z = 0;
  }

  left_col[2+m].x = maxcol - 2;
  left_col[2+m].y = maxcol - 1;
  left_col[2+m].z = 4;
  
  left_col[2+m+1].x = maxcol - 1;
  left_col[2+m+1].y = maxcol;
  left_col[2+m+1].z = 3;

  solve();
  return 0;
}