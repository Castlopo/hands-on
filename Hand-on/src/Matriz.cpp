#include "Matriz.h"
#include <iostream>

Matriz::Matriz(int filas, int columnas) {
    this->filas = filas;
    this->columnas = columnas;
    this->datos = std::vector<std::vector<double>>(filas, std::vector<double>(columnas, 0.0));
}

Matriz::Matriz(const std::vector<std::vector<double>>& datos) {
    this->datos = datos;
    this->filas = datos.size();
    this->columnas = datos.empty() ? 0 : datos[0].size();
}

std::vector<std::vector<double>> Matriz::getDatos() const { return datos; }
int Matriz::getFilas() const { return filas; }
int Matriz::getColumnas() const { return columnas; }

void Matriz::imprimir() const {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            std::cout << datos[i][j] << " ";
        }
        std::cout << "\n";
    }
}

Matriz Matriz::transponer() const {
    std::vector<std::vector<double>> nuevaMatriz(columnas, std::vector<double>(filas));
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            nuevaMatriz[j][i] = datos[i][j];
        }
    }
    return Matriz(nuevaMatriz);
}

Matriz* Matriz::multiplicar(const Matriz& otra) const {
    if (this->columnas != otra.getFilas()) {
        return nullptr;
    }

    std::vector<std::vector<double>> nuevaMatriz(this->filas, std::vector<double>(otra.getColumnas(), 0.0));

    for (int i = 0; i < this->filas; i++) {
        for (int j = 0; j < otra.getColumnas(); j++) {
            double suma = 0;
            for (int k = 0; k < this->columnas; k++) {
                suma += this->datos[i][k] * otra.getDatos()[k][j];
            }
            nuevaMatriz[i][j] = suma;
        }
    }
    return new Matriz(nuevaMatriz);
}

Matriz* Matriz::invertir() const {
    if (this->filas != this->columnas) {
        return nullptr;
    }

    int n = this->filas;
    std::vector<std::vector<double>> copia = this->datos;
    std::vector<std::vector<double>> inversa(n, std::vector<double>(n, 0.0));

    for (int i = 0; i < n; i++) {
        inversa[i][i] = 1.0;
    }

    for (int i = 0; i < n; i++) {
        double pivote = copia[i][i]; // Asumiendo pivote != 0 igual que en tu Java

        for (int k = 0; k < n; k++) {
            copia[i][k] /= pivote;
            inversa[i][k] /= pivote;
        }

        for (int j = 0; j < n; j++) {
            if (i != j) {
                double factor = copia[j][i];
                for (int k = 0; k < n; k++) {
                    copia[j][k] -= factor * copia[i][k];
                    inversa[j][k] -= factor * inversa[i][k];
                }
            }
        }
    }
    return new Matriz(inversa);
}
