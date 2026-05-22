#include "RegresionLineal.h"
#include <iostream>

RegresionLineal::RegresionLineal(const std::vector<std::vector<double>>& datosX, const std::vector<std::vector<double>>& datosY)
    : X(datosX), Y(datosY), beta(nullptr) {}

RegresionLineal::~RegresionLineal() {
    delete beta; // Liberamos memoria dinámica
}

void RegresionLineal::calcularParametros() {
    Matriz xTranspuesta = X.transponer();

    Matriz* xTx = xTranspuesta.multiplicar(X);
    if (!xTx) return;

    Matriz* inversa = xTx->invertir();
    delete xTx; // Liberar intermediario
    if (!inversa) return;

    Matriz* xTy = xTranspuesta.multiplicar(Y);
    if (!xTy) {
        delete inversa;
        return;
    }

    this->beta = inversa->multiplicar(*xTy);

    // Limpieza de memoria local síncrona
    delete inversa;
    delete xTy;
}

void RegresionLineal::imprimirEcuacion() const {
    std::cout << "Los parametros optimos (Beta) son:\n";
    std::cout << "Los parametros optimos (Beta) son:\n";
    if (beta != nullptr) {
        beta->imprimir();
    } else {
        std::cout << "Error: Beta no ha sido calculado o hubo un error en la matriz.\n";
    }
}
