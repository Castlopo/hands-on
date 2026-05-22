#ifndef MATRIZ_H
#define MATRIZ_H

#include <vector>

class Matriz {
private:
    std::vector<std::vector<double>> datos;
    int filas;
    int columnas;

public:
    Matriz(int filas, int columnas);
    Matriz(const std::vector<std::vector<double>>& datos);

    std::vector<std::vector<double>> getDatos() const;
    int getFilas() const;
    int getColumnas() const;

    void imprimir() const;
    Matriz transponer() const;
    Matriz* multiplicar(const Matriz& otra) const;
    Matriz* invertir() const;
};

#endif


