#include <iostream>
#include <vector>

using namespace std;

struct Block {
    uint64_t w;
    uint64_t h;
    uint64_t d;
};

int main() {
    try {
        uint64_t n, density;
        uint64_t res = 0;
        cin >> n >> density;
        if (n < 0 || density < 0)
            throw out_of_range("");
        vector<Block> v(n);
        for (auto &i : v) {
            cin >> i.w >> i.h >> i.d;
            if (i.w < 0 || i.h < 0 || i.d < 0)
                throw out_of_range("");
        }
        uint64_t sumWeight = 0;
        for (auto const &i : v) {
            uint64_t tmp = i.w * i.h * i.d;
            res += tmp * density;
        }
        cout << res << endl;
    } catch (out_of_range &ex) {
        cout << ex.what() << endl;
    }

    return 0;
}
