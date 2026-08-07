#include <bits/stdc++.h>
using namespace std;

class Solution {
    static const int MAXP2 = 47, MAXP3 = 30, MAXP5 = 21, MAXP7 = 18;
    static int minDigits[MAXP2][MAXP3][MAXP5][MAXP7];
    static bool tableBuilt;
    static int dc[10][4];

    static void digitFactors(int d, int &a2, int &a3, int &a5, int &a7) {
        a2 = a3 = a5 = a7 = 0;
        while (d % 2 == 0 && d > 0) { d /= 2; a2++; }
        while (d % 3 == 0 && d > 0) { d /= 3; a3++; }
        while (d % 5 == 0 && d > 0) { d /= 5; a5++; }
        while (d % 7 == 0 && d > 0) { d /= 7; a7++; }
    }

    static void buildTable() {
        if (tableBuilt) return;
        tableBuilt = true;

        for (int dgt = 1; dgt <= 9; dgt++) {
            int a2, a3, a5, a7;
            digitFactors(dgt, a2, a3, a5, a7);
            dc[dgt][0] = a2; dc[dgt][1] = a3; dc[dgt][2] = a5; dc[dgt][3] = a7;
        }

        for (int a = 0; a < MAXP2; a++)
            for (int b = 0; b < MAXP3; b++)
                for (int c = 0; c < MAXP5; c++)
                    for (int d = 0; d < MAXP7; d++)
                        minDigits[a][b][c][d] = -1;

        minDigits[0][0][0][0] = 0;
        queue<array<int,4>> q;
        q.push({0,0,0,0});
        while (!q.empty()) {
            auto cur = q.front(); q.pop();
            int a = cur[0], b = cur[1], c = cur[2], d = cur[3];
            int base = minDigits[a][b][c][d];
            for (int dgt = 1; dgt <= 9; dgt++) {
                int na = min(a + dc[dgt][0], MAXP2 - 1);
                int nb = min(b + dc[dgt][1], MAXP3 - 1);
                int nc = min(c + dc[dgt][2], MAXP5 - 1);
                int nd = min(d + dc[dgt][3], MAXP7 - 1);
                if (minDigits[na][nb][nc][nd] == -1) {
                    minDigits[na][nb][nc][nd] = base + 1;
                    q.push({na, nb, nc, nd});
                }
            }
        }
    }

public:
    string smallestNumber(string num, long long t) {
        buildTable();

        int n = num.size();

        auto factorize = [](long long t, int &p2, int &p3, int &p5, int &p7) -> long long {
            p2 = p3 = p5 = p7 = 0;
            while (t % 2 == 0) { t /= 2; p2++; }
            while (t % 3 == 0) { t /= 3; p3++; }
            while (t % 5 == 0) { t /= 5; p5++; }
            while (t % 7 == 0) { t /= 7; p7++; }
            return t;
        };

        int P2, P3, P5, P7;
        long long rem = factorize(t, P2, P3, P5, P7);
        if (rem > 1) return "-1";

        P2 = min(P2, MAXP2 - 1);
        P3 = min(P3, MAXP3 - 1);
        P5 = min(P5, MAXP5 - 1);
        P7 = min(P7, MAXP7 - 1);

        auto achievable = [&](int r2, int r3, int r5, int r7, long long k) -> bool {
            if (r2 >= MAXP2 || r3 >= MAXP3 || r5 >= MAXP5 || r7 >= MAXP7) return false;
            int mv = minDigits[r2][r3][r5][r7];
            if (mv == -1) return false;
            return mv <= k;
        };

        auto buildSuffix = [&](int r2, int r3, int r5, int r7, long long k) -> string {
            string res;
            res.reserve(k);
            int cr2 = r2, cr3 = r3, cr5 = r5, cr7 = r7;
            for (long long i = 0; i < k; i++) {
                long long remaining = k - i - 1;
                for (int dgt = 1; dgt <= 9; dgt++) {
                    int nr2 = max(0, cr2 - dc[dgt][0]);
                    int nr3 = max(0, cr3 - dc[dgt][1]);
                    int nr5 = max(0, cr5 - dc[dgt][2]);
                    int nr7 = max(0, cr7 - dc[dgt][3]);
                    if (achievable(nr2, nr3, nr5, nr7, remaining)) {
                        res.push_back('0' + dgt);
                        cr2 = nr2; cr3 = nr3; cr5 = nr5; cr7 = nr7;
                        break;
                    }
                }
            }
            return res;
        };

        bool numZeroFree = true;
        for (char c : num) if (c == '0') { numZeroFree = false; break; }

        if (numZeroFree) {
            int cur2 = 0, cur3 = 0, cur5 = 0, cur7 = 0;
            for (char c : num) {
                int dgt = c - '0';
                int a2, a3, a5, a7; digitFactors(dgt, a2, a3, a5, a7);
                cur2 = min(cur2 + a2, MAXP2 - 1);
                cur3 = min(cur3 + a3, MAXP3 - 1);
                cur5 = min(cur5 + a5, MAXP5 - 1);
                cur7 = min(cur7 + a7, MAXP7 - 1);
            }
            if (cur2 >= P2 && cur3 >= P3 && cur5 >= P5 && cur7 >= P7) return num;
        }

        vector<int> pref2(n+1,0), pref3(n+1,0), pref5(n+1,0), pref7(n+1,0);
        vector<bool> prefZeroFree(n+1, true);
        for (int i = 0; i < n; i++) {
            prefZeroFree[i+1] = prefZeroFree[i] && (num[i] != '0');
            int dgt = num[i] - '0';
            int a2=0,a3=0,a5=0,a7=0;
            if (dgt > 0) digitFactors(dgt, a2, a3, a5, a7);
            pref2[i+1] = min(pref2[i] + a2, MAXP2 - 1);
            pref3[i+1] = min(pref3[i] + a3, MAXP3 - 1);
            pref5[i+1] = min(pref5[i] + a5, MAXP5 - 1);
            pref7[i+1] = min(pref7[i] + a7, MAXP7 - 1);
        }

        string ans = "";
        for (int i = n - 1; i >= 0; i--) {
            if (!prefZeroFree[i]) continue;
            int origDigit = num[i] - '0';
            for (int dgt = origDigit + 1; dgt <= 9; dgt++) {
                int a2, a3, a5, a7; digitFactors(dgt, a2, a3, a5, a7);
                int c2 = min(pref2[i] + a2, MAXP2 - 1);
                int c3 = min(pref3[i] + a3, MAXP3 - 1);
                int c5 = min(pref5[i] + a5, MAXP5 - 1);
                int c7 = min(pref7[i] + a7, MAXP7 - 1);
                int r2 = max(0, P2-c2), r3 = max(0, P3-c3), r5 = max(0, P5-c5), r7 = max(0, P7-c7);
                long long k = n - i - 1;
                if (achievable(r2, r3, r5, r7, k)) {
                    string suffix = buildSuffix(r2, r3, r5, r7, k);
                    ans = num.substr(0, i) + char('0' + dgt) + suffix;
                    break;
                }
            }
            if (!ans.empty()) break;
        }

        if (!ans.empty()) return ans;

        int minNeeded = minDigits[P2][P3][P5][P7];
        if (minNeeded == -1) return "-1";
        long long L = max((long long)(n + 1), (long long)minNeeded);

        return buildSuffix(P2, P3, P5, P7, L);
    }
};

int Solution::minDigits[Solution::MAXP2][Solution::MAXP3][Solution::MAXP5][Solution::MAXP7];
bool Solution::tableBuilt = false;
int Solution::dc[10][4];