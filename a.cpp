cpt
adscpt
#ifndef INCLUDED_MAIN 
#define INCLUDED_MAIN

#include __FILE__

int main()
{
    ingt N;
    cin >> N;
    return 0;
}

#else

/* define constants */

const int dd = 10; // decimal degits(小数の桁数)

const int INF = 2147483647;
const long long LINF = 9223372036854775807;
const double EPS = 1e-9;

const int MOD = 998244353; // combinationなどで使う

const int C_MAX = 500000; // combinationでnCkのn,kの最大値

/*basis*/
#include <bits/stdc++.h>
using namespace std;

/* accelration */
// 高速バイナリ生成
#pragma GCC target("avx")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
// cin cout の結びつけ解除, stdioと同期しない(入出力非同期化)
// cとstdの入出力を混在させるとバグるので注意
struct Fast {
    Fast()
    {
        std::cin.tie(0);
        ios::sync_with_stdio(false);
        //小数の桁数の出力指定
        cout << fixed << setprecision(dd);
    }
} fast;

/* alias */
using ull = unsigned long long;
using ll = long long;
using vi = vector<int>;
using vl = vector<long>;
using vll = vector<long long>;
using vvi = vector<vi>;
using vvl = vector<vl>;
using vvll = vector<vll>;
using vs = vector<string>;
using pii = pair<int, int>;

/* define short */
#define pb push_back
#define mp make_pair
#define ft first
#define sd second
#define SZ(x) ((int)(x).size())
#define all(obj) (obj).begin(), (obj).end()
#define FILL(x, y) memset(x, y, sizeof(x))
#define YESNO(bool) if (bool) {cout << "YES" << endl;} else {cout << "NO" << endl}
#define yesno(bool) if (bool) {cout << "yes" << endl;} else {cout << "no" << endl;}
#define YesNo(bool) if (bool) {cout << "Yes" << endl;} else {cout << "No" << endl;}

/* REP macro */
#define reps(i, a, n) for (ll i = (a); i < (ll)(n); ++i)
#define rep(i, n) reps(i, 0, n)
#define rrep(i, n) reps(i, 1, n + 1)
#define repd(i, n) for (ll i = n - 1; i >= 0; i--)
#define rrepd(i, n) for (ll i = n; i >= 1; i--)

const int dx[4] = { 1, 0, -1, 0 };
const int dy[4] = { 0, 1, 0, -1 };

/* Prevent duplication */
#define y0 y3487465
#define y1 y8687969
#define j0 j1347829
#define j1 j234892
#define next asdnext
#define prev asdprev

/*input output */

inline int in_int()
{
    int x;
    cin >> x;
    return x;
}
inline ll in_ll()
{
    ll x;
    cin >> x;
    return x;
}
inline string in_str()
{
    string x;
    cin >> x;
    return x;
}

template <typename T>
inline void print(const vector<T>& v, string s = " ")
{
    rep(i, v.size()) cout << v[i] << (i != (ll)v.size() - 1 ? s : "\n");
}
template <typename T, typename S>
inline void print(const pair<T, S>& p)
{
    cout << p.first << " " << p.second << endl;
}
template <typename T>
inline void print(const T& x) {
    cout << x << "\n"; }
        template <typename T, typename S>
        inline void print(const vector<pair<T, S>>& v)
    {
        for (auto&& p : v)
            print(p);
    }

#define debug(x) cerr << "\033[33m(line: " << __LINE__ << ") " << #x << ": " << x << "\033[m" << endl;

/* mathmathic */

// combination nCk

// nCkのnとkの最大値はC_MAX
ll fact[C_MAX], inv_fact[C_MAX], inv[C_MAX];
// mainの中で,combinationを使う前に,実行しておく
void init_combination()
{
  // 初期値設定と1はじまりインデックスに直す
  fact[0] = 1;
  fact[1] = 1;
  inv[0] = 1;
  inv[1] = 1;
  inv_fact[0] = 1;
  inv_fact[1] = 1;
  // メモの計算
  reps(i, 2, C_MAX)
  {
    // 階乗
    fact[i] = fact[i - 1] * i % MOD;
    // 逆元
    inv[i] = MOD - inv[MOD % i] * (MOD / i) % MOD;
    // 逆元の階乗
    inv_fact[i] = inv_fact[i - 1] * inv[i] % MOD;
  }
}
// nCkの計算をする
ll combination(int n, int k)
{
  ll x = fact[n];         // n!の計算
  ll y = inv_fact[n - k]; // (n-k)!の計算
  ll z = inv_fact[k];     // k!の計算
  if (n < k)
    return 0; // 例外処理
  if (n < 0 || k < 0)
    return 0;                       // 例外処理
  return x * ((y * z) % MOD) % MOD; //二項係数の計算
}

#endif