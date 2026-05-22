#ifndef REGRESIONLINEAL_H
#define REGRESIONLINEAL_H

#include "Matriz.h"

class RegresionLineal {
private:
    Matriz X;
    Matriz Y;
    Matriz* beta;

public:
    RegresionLineal(const std::vector<std::vector<double>>& datosX, const std::vector<std::vector<double>>& datosY);
    ~RegresionLineal(); // Destructor para liberar memoria de beta

    void calcularParametros();
    void imprimirEcuacion() const;
};

#endif
