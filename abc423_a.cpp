#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, R; 
    cin >> N >> R;
    vector<int> L(N + 1); 
    for (int i = 1; i <= N; ++i) cin >> L[i];


    vector<int> pref1(N + 1, 0);
    int zeros_total = 0;
    for (int i = 1; i <= N; ++i) {
        pref1[i] = pref1[i - 1] + (L[i] == 1);
        if (L[i] == 0) zeros_total++;
    }

    if (zeros_total == 0) {
        cout << 0 << '\n';
        return 0;
    }

    int Lidx = -1, Uidx = -1;
    for (int i = 1; i <= N; ++i) if (L[i] == 0) { Lidx = i; break; }
    for (int i = N; i >= 1; --i) if (L[i] == 0) { Uidx = i; break; }

    auto ones_in = [&](int a, int b) -> int { 
        if (a > b) return 0;
        return pref1[b] - pref1[a - 1];
    };

    long long crossed_closed = 0;
    if (R < Lidx) {
        crossed_closed = ones_in(R + 1, Uidx);
    } else if (R > Uidx) {
        crossed_closed = ones_in(Lidx, R);
    } else {
        crossed_closed = ones_in(Lidx, Uidx);
    }

    long long ans = (long long)zeros_total + 2LL * crossed_closed;
    cout << ans << '\n';
    return 0;
}
