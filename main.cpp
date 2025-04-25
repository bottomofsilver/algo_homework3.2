#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int count = 0;
int m, n;

void generate_row(int row, int col, vector<int>& col_masks, vector<bool>& used) {
    if (col == n) {
        if (row + 1 == m) {
            count++;
            return;
        }
        // 准备生成下一行
        vector<bool> new_used(n, false);
        generate_row(row + 1, 0, col_masks, new_used);
        return;
    }

    for (int num = 1; num <= n; num++) {
        if (!used[num - 1] && !(col_masks[col] & (1 << (num - 1)))) {
            used[num - 1] = true;
            col_masks[col] ^= (1 << (num - 1)); // 标记该列已使用num

            generate_row(row, col + 1, col_masks, used);

            col_masks[col] ^= (1 << (num - 1)); // 回溯
            used[num - 1] = false;
        }
    }
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    fin >> m >> n;
    vector<int> col_masks(n, 0);
    vector<bool> used(n, false);

    generate_row(0, 0, col_masks, used);

    fout << count << endl;

    return 0;
}