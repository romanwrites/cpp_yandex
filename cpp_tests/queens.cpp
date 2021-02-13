#include <iostream>
#include <vector>
using namespace std;

bool queens(int y, int N, vector<int> &x_arr, vector<int> &y_arr, vector<int> &diag1, vector<int> &diag2) {
    if (y == N) {
        cout << "array: ";
        for (int i : y_arr) {
            cout << i << " ";
        }
        cout << endl << "map: " << endl;
        for (int i : y_arr) {
            for (int j = 0; j < y_arr.size(); j++) {
                if (i == j)
                    cout << j << " ";
                else
                    cout << ". ";
            }
            cout << endl;
        }
        return true;
    } else {
        for (int x = 0; x < N; x++) {
            if (x_arr[x] == 1 || diag1[x + y] == 1 || diag2[x - y + N - 1] == 1) {
                continue ;
            }
            y_arr[y] = x;
            x_arr[x] = 1;
            diag1[x + y] = 1;
            diag2[x - y + N - 1] = 1;
            if (!(queens(y + 1, N, x_arr, y_arr, diag1, diag2))) {
                y_arr[y] = 0;
                x_arr[x] = 0;
                diag1[x + y] = 0;
                diag2[x - y + N - 1] = 0;
            } else {
                return true;
            }
        }
        return false;
    }
}

void testQueens(int N) {
    vector<int> x_arr(N, 0);
    vector<int> y_arr(N, 0);
    vector<int> diag1(N + N - 1, 0);
    vector<int> diag2(N + N - 1, 0);

    cout << "For " << N << " queens: " << endl;
    if (!queens(0, N, x_arr, y_arr, diag1, diag2)) {
        cout << "There are no solutions" << endl;
    }
    cout << endl;
}

int main() {
    testQueens(1); // 0
    testQueens(2); // No solutions
    testQueens(3); // No solutions
    testQueens(4); // 1 3 0 2
    testQueens(8); // 0 4 7 5 2 6 1 3 and second coord is pos in array
    testQueens(10); // 0 2 5 7 9 4 8 1 3 6 and second coord is pos in array
    testQueens(16); // 0 2 4 1 12 8 13 11 14 5 15 6 3 10 7 9 and second coord is pos in array
    return 0;
}
