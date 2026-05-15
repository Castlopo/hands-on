#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Definición para manejo de matrices
typedef vector<vector<double>> Matrix;

class LSRModel {
private:
    vector<double> beta; // Almacena B0, B1, B2

    // Transpuesta de una matriz
    Matrix transpose(const Matrix& A) {
        Matrix AT(A[0].size(), vector<double>(A.size()));
        for (size_t i = 0; i < A.size(); ++i)
            for (size_t j = 0; j < A[0].size(); ++j)
                AT[j][i] = A[i][j];
        return AT;
    }

    // Multiplicación de matrices
    Matrix multiply(const Matrix& A, const Matrix& B) {
        Matrix C(A.size(), vector<double>(B[0].size(), 0));
        for (size_t i = 0; i < A.size(); ++i)
            for (size_t j = 0; j < B[0].size(); ++j)
                for (size_t k = 0; k < A[0].size(); ++k)
                    C[i][j] += A[i][k] * B[k][j];
        return C;
    }

    // Inversión de matriz 3x3 usando el método de la Adjunta
    Matrix invert3x3(const Matrix& M) {
        double det = M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]) -
                     M[0][1] * (M[1][0] * M[2][2] - M[1][2] * M[2][0]) +
                     M[0][2] * (M[1][0] * M[2][1] - M[1][1] * M[2][0]);

        Matrix inv(3, vector<double>(3));
        double invDet = 1.0 / det;

        inv[0][0] = (M[1][1] * M[2][2] - M[1][2] * M[2][1]) * invDet;
        inv[0][1] = (M[0][2] * M[2][1] - M[0][1] * M[2][2]) * invDet;
        inv[0][2] = (M[0][1] * M[1][2] - M[0][2] * M[1][1]) * invDet;
        inv[1][0] = (M[1][2] * M[2][0] - M[1][0] * M[2][2]) * invDet;
        inv[1][1] = (M[0][0] * M[2][2] - M[0][2] * M[2][0]) * invDet;
        inv[1][2] = (M[1][0] * M[0][2] - M[0][0] * M[1][2]) * invDet;
        inv[2][0] = (M[1][0] * M[2][1] - M[1][1] * M[2][0]) * invDet;
        inv[2][1] = (M[2][0] * M[0][1] - M[0][0] * M[2][1]) * invDet;
        inv[2][2] = (M[0][0] * M[1][1] - M[1][0] * M[0][1]) * invDet;

        return inv;
    }

public:
    void calculate(const Matrix& X, const Matrix& Y) {
        Matrix XT = transpose(X);
        Matrix XTX = multiply(XT, X);
        Matrix XTX_inv = invert3x3(XTX);
        Matrix XTY = multiply(XT, Y);
        Matrix Result = multiply(XTX_inv, XTY);

        for (auto& row : Result) {
            beta.push_back(row[0]);
        }
    }

    void displayResults() {
        cout << fixed << setprecision(4);
        cout << "--- Parametros Optimos Obtenidos ---" << endl;
        cout << "B0 (Intercepto): " << beta[0] << endl;
        cout << "B1 (Pendiente 1): " << beta[1] << endl;
        cout << "B2 (Pendiente 2): " << beta[2] << endl;
        cout << "\nEcuacion: y = " << beta[0] << " + " << beta[1] << "x1 + " << beta[2] << "x2" << endl;
    }
};

int main() {
    // Matriz X (Columna de 1s para B0, x1, x2)
    Matrix X = {
        {1, 41.9, 29.1}, {1, 43.4, 29.3}, {1, 43.9, 29.5}, 
        {1, 44.5, 29.7}, {1, 47.3, 29.9}, {1, 47.5, 30.3},
        {1, 47.9, 30.5}, {1, 50.2, 30.7}, {1, 52.8, 30.8}, {1, 53.2, 30.9}
    };

    // Vector Y (Observaciones)
    Matrix Y = {{251.3}, {251.3}, {248.3}, {267.5}, {273.0}, {276.5}, {270.3}, {274.9}, {285.0}, {290.0}};

    LSRModel regressor;
    regressor.calculate(X, Y);
    regressor.displayResults();

    return 0;
}