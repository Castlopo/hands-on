#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

typedef vector<vector<double>> Matrix;

class LSR_Regressor {
private:
    vector<double> beta;

    Matrix transpose(const Matrix& A) {
        Matrix AT(A[0].size(), vector<double>(A.size()));
        for (size_t i = 0; i < A.size(); ++i)
            for (size_t j = 0; j < A[0].size(); ++j)
                AT[j][i] = A[i][j];
        return AT;
    }

    Matrix multiply(const Matrix& A, const Matrix& B) {
        Matrix C(A.size(), vector<double>(B[0].size(), 0));
        for (size_t i = 0; i < A.size(); ++i)
            for (size_t j = 0; j < B[0].size(); ++j)
                for (size_t k = 0; k < A[0].size(); ++k)
                    C[i][j] += A[i][k] * B[k][j];
        return C;
    }

    Matrix invert2x2(const Matrix& M) {
        double det = M[0][0] * M[1][1] - M[0][1] * M[1][0];
        Matrix inv(2, vector<double>(2));
        double invDet = 1.0 / det;
        inv[0][0] = M[1][1] * invDet;
        inv[0][1] = -M[0][1] * invDet;
        inv[1][0] = -M[1][0] * invDet;
        inv[1][1] = M[0][0] * invDet;
        return inv;
    }

public:
    void train(const Matrix& X, const Matrix& Y) {
        Matrix XT = transpose(X);
        Matrix XTX = multiply(XT, X);
        Matrix XTX_inv = invert2x2(XTX);
        Matrix XTY = multiply(XT, Y);
        Matrix Result = multiply(XTX_inv, XTY);

        beta.clear();
        for (auto& row : Result) beta.push_back(row[0]);
    }

    void printModel() {
        cout << fixed << setprecision(2);
        cout << "--- Hands-On 3: Modelo Predictivo ---" << endl;
        cout << "B0 (Intercepto): " << beta[0] << endl;
        cout << "B1 (Time): " << beta[1] << endl;
        cout << "Ecuacion resultante: y = " << beta[0] << " + " << beta[1] << "x" << endl;
    }
};

int main() {
    // Matriz X: Columna de 1s para intercepto y valores de Time
    Matrix X = {
        {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, 
        {1, 6}, {1, 7}, {1, 8}, {1, 9}
    };

    // Matriz Y: Valores de Yield
    Matrix Y = {{2.1}, {4.2}, {6.3}, {8.4}, {10.5}, {12.6}, {14.7}, {16.8}, {18.9}};

    LSR_Regressor myModel;
    myModel.train(X, Y);
    myModel.printModel();

    return 0;
}