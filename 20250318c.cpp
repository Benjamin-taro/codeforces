#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<ll> A(n);
        for (int i = 0; i < n; i++){
            cin >> A[i];
        }
 
        // 奇数用：降順（最大奇数を取得するため）
        priority_queue<ll> pqOdd;
        // 偶数用：昇順（最小偶数を取得するため）
        priority_queue<ll, vector<ll>, greater<ll>> pqEven;
        // 偶数用：降順（最大偶数を取得するため、奇数拡張に利用）
        priority_queue<ll> pqEvenDesc;
        // 偶数の出現回数管理（pqEvenDesc の整合性維持用）
        map<ll, ll> evenCount;
 
        for (ll x : A) {
            if(x % 2 == 0) {
                pqEven.push(x);
                pqEvenDesc.push(x);
                evenCount[x]++; 
            } else {
                pqOdd.push(x);
            }
        }
 
        // もしすべて偶数またはすべて奇数なら操作不要
        if(pqEven.empty() || pqOdd.empty()){
            cout << 0 << "\n";
            continue;
        }
 
        ll ans = 0;
 
        // 偶数がなくなるまでシミュレーション
        while(!pqEven.empty()){
            ll largestOdd = pqOdd.top();
            ll smallestEven = pqEven.top();
 
            if(largestOdd > smallestEven){
                // 偶数の方が小さいので、この偶数を奇数に変換
                ll newOdd = largestOdd + smallestEven; // 奇数に変換（偶数+奇数は奇数）
                ans++;
                // pqEven から取り除くと同時に、evenCount を更新
                pqEven.pop();
                evenCount[smallestEven]--;
                // 変換後の奇数を pqOdd に追加
                pqOdd.push(newOdd);
            } else {
                // largestOdd <= smallestEven の場合
                // まず、pqEvenDesc から有効な（まだ残っている）最大偶数を取得
                while(!pqEvenDesc.empty() && evenCount[pqEvenDesc.top()] == 0){
                    pqEvenDesc.pop();
                }
                if(pqEvenDesc.empty()){
                    break; // 理論上ここには来ないはず
                }
                ll candidateEven = pqEvenDesc.top();
                // この操作で奇数側を強化して、後の偶数変換に備える
                ll newOdd = largestOdd + candidateEven;
                ans++;
                pqOdd.pop();
                pqOdd.push(newOdd);
                // ※偶数側はそのまま残す
            }
        }
 
        cout << ans << "\n";
    }
    return 0;
}
