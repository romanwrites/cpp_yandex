#include <iostream>
#include <vector>

using namespace std;

class Matrix {
public:
    Matrix() : rows(0), cols(0) {}
    Matrix(int num_rows, int num_cols) : rows(num_rows), cols(num_cols) {
        if (num_rows < 0 || num_cols < 0)
            throw out_of_range("Out of range");
        matrix.resize(rows);
        for (auto &row : matrix) {
            row.resize(cols);
        }
    }
    ~Matrix() {}

    void    Reset(int num_rows, int num_cols) {
        if (num_rows < 0 || num_cols < 0)
            throw out_of_range("Out of range");
        rows = num_rows;
        cols = num_cols;
        matrix.clear();
        matrix.resize(rows);
        for (auto &row : matrix) {
            row.resize(cols);
        }
    }

    int At(int row, int col) const {
        if (row < 0 || row >= rows || col < 0 || col >= cols)
            throw out_of_range("Out of range");
        return matrix[row][col];
    }

    int &At(int row, int col) {
        if (row < 0 || row >= rows || col < 0 || col >= cols)
            throw out_of_range("Out of range");
        return matrix[row][col];
    }

    int GetNumRows() const {
        return rows;
    }

    int GetNumColumns() const {
        return cols;
    }

    bool	operator==(Matrix const &rhs) const {
        if ((rows == 0 || cols == 0) && (rhs.GetNumRows() == 0 || rhs.GetNumColumns() == 0)) {
            return true;
        }
        if (rows != rhs.GetNumRows() || cols != rhs.GetNumColumns())
            return false;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (matrix[i][j] != rhs.At(i, j))
                    return false;
            }
        }
        return true;
    }

    Matrix	operator+(Matrix const &rhs) const {
        if ((rows == 0 || cols == 0) && (rhs.GetNumRows() == 0 || rhs.GetNumColumns() == 0)) {
            Matrix sum;
            return sum;
        }
        if (rows != rhs.GetNumRows() || cols != rhs.GetNumColumns())
            throw invalid_argument("bad arg");
        Matrix sum(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                auto &cell = sum.At(i, j);
                cell = matrix[i][j] + rhs.At(i, j);
            }
        }
        return sum;
    }

private:
    int rows;
    int cols;
    vector< vector<int> > matrix;
};

ostream &operator<<(ostream &out, Matrix const &obj) {
    int rows = obj.GetNumRows();
    int cols = obj.GetNumColumns();
    out << rows << " " << cols << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (j + 1 == cols) {
                out << obj.At(i, j);
                if (i + 1 < rows)
                    out << endl;
            } else {
                out << obj.At(i, j) << " ";
            }
        }
    }

    return out;
}

istream &operator>>(istream &in, Matrix &obj) {
    if (in) {
        int rows;
        int	cols;
        in >> rows >> cols;
        if (!in.fail() && !in.eof()) {
            obj.Reset(rows, cols);
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    auto &cell = obj.At(i, j);
                    in >> cell;
                }
            }
        }
    }
    return in;
}

int main() {
    try {
        Matrix one;
        Matrix two;

        cin >> one >> two;
        cout << one + two << endl;
    } catch (out_of_range &ex) {
        cout << ex.what() << endl;
    } catch (invalid_argument &ex) {
        cout << ex.what() << endl;
    }

    return 0;
}
