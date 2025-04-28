#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <queue>
#include <array>
#include <climits>
#include <cmath>
#include <set>
#include <unordered_set>
#include <map>
#include <bitset>
#include <deque>
#include <numeric>
#include <assert.h>
#include <stack>
#include <unordered_map>
#include <type_traits> // For std::is_floating_point
#include <cmath> // For std::ceil
#include <cstring>
#include <iomanip>  // 追加: 出力精度を指定するため
#include <tuple>
#include <chrono>
#include <random>
#include <functional>
#include <iterator>
#include <cctype>
#include <limits>
#include <cassert>
#include <complex>
#include <sstream>
#define REP(i, n) for (int i = 0; (i) < (int)(n); ++ (i))
#define REP3(i, m, n) for (int i = (m); (i) < (int)(n); ++ (i))
#define REP_R(i, n) for (int i = (int)(n) - 1; (i) >= 0; -- (i))
#define REP3R(i, m, n) for (int i = (int)(n) - 1; (i) >= (int)(m); -- (i))
#define ALL(x) ::std::begin(x), ::std::end(x)
using namespace std;
//文字配列の二次元配列みたいなやつを回転させる。
vector<string> rotate90(const vector<string>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    vector<string> rotated(m, string(n, '.'));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            rotated[j][n - 1 - i] = matrix[i][j];
        }
    }
    return rotated;
}

// Data structures and algorithms for disjoint set union problems
struct dsu {
  public:
    dsu() : _n(0) {}
    explicit dsu(int n) : _n(n), parent_or_size(n, -1) {}

    int merge(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        int x = leader(a), y = leader(b);
        if (x == y) return x;
        if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x, y);
        parent_or_size[x] += parent_or_size[y];
        parent_or_size[y] = x;
        return x;
    }

    bool same(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        return leader(a) == leader(b);
    }

    int leader(int a) {
        assert(0 <= a && a < _n);
        if (parent_or_size[a] < 0) return a;
        return parent_or_size[a] = leader(parent_or_size[a]);
    }

    int size(int a) {
        assert(0 <= a && a < _n);
        return -parent_or_size[leader(a)];
    }

    std::vector<std::vector<int>> groups() {
        std::vector<int> leader_buf(_n), group_size(_n);
        for (int i = 0; i < _n; i++) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        std::vector<std::vector<int>> result(_n);
        for (int i = 0; i < _n; i++) {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < _n; i++) {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(
            std::remove_if(result.begin(), result.end(),
                           [&](const std::vector<int>& v) { return v.empty(); }),
            result.end());
        return result;
    }

  private:
    int _n;
    // root node: -1 * component size
    // otherwise: parent
    std::vector<int> parent_or_size;
};

class PrimeSieve {
public:
    PrimeSieve(int max_num) : max_num(max_num), is_prime(max_num + 1, true) {
        run_sieve();
    }

    // 素数判定
    bool isPrime(int num) const {
        if (num < 0 || num > max_num) return false;
        return is_prime[num];
    }

    // 素数のリストを取得
    std::vector<int> getPrimes() const {
        std::vector<int> primes;
        for (int i = 2; i <= max_num; i++) {
            if (is_prime[i]) primes.push_back(i);
        }
        return primes;
    }

private:
    int max_num;
    std::vector<bool> is_prime;

    // エラトステネスの篩を実行
    void run_sieve() {
        is_prime[0] = is_prime[1] = false;
        for (int i = 2; i * i <= max_num; i++) {
            if (is_prime[i]) {
                for (int j = i * i; j <= max_num; j += i) {
                    is_prime[j] = false;
                }
            }
        }
    }
};


// bigPrefix(p) = (p/n)* sumA + prefixA[p % n]
long long bigPrefix(long long p, long long sumA, const vector<long long> &prefixA){
    // p が 0 なら 0, p>0 なら計算する。p in [0..n*k]
    long long base = (p / (long long)(prefixA.size()-1)) * sumA;
    long long remIdx = p % (prefixA.size()-1);
    return base + prefixA[remIdx];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--){
        long long n, k, x;
        cin >> n >> k >> x;
        vector<long long> a(n);
        for(int i=0; i<(int)n; i++){
            cin >> a[i];
        }
        // prefixA (size = n+1), prefixA[0] = 0, prefixA[i] = a[0]+...+a[i-1]
        vector<long long> prefixA(n+1, 0LL);
        for(int i=0; i<n; i++){
            prefixA[i+1] = prefixA[i] + a[i];
        }
        long long sumA = prefixA[n]; // 1周ぶんの合計

        // 全体和が < x なら 0
        long long total = sumA * k;
        if(total < x){
            cout << 0 << "\n";
            continue;
        }

        long long target = total - x; 
        long long low = 0;
        long long high = n*k; 
        while(low < high){
            long long mid = (low + high + 1) / 2; 
            if( bigPrefix(mid, sumA, prefixA) <= target ){
                low = mid;
            }
            else{
                high = mid - 1;
            }
        }
        if(bigPrefix(low, sumA, prefixA) <= target){
            long long ans = min<long long>(low+1, n*k);
            cout << ans << "\n";
        }
    }
    return 0;
}
