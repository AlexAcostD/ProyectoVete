#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>

#include "facturacion.h"
#include "propietarios.h"

using namespace std;

ComprobantePago emitirComprobante(
    const char numComprobante[],
    const char dniCliente[],
    const char detalle[],
    float monto
)
{
    ComprobantePago comprobante;

    // Inicializar por defecto
    strcpy(comprobante.numeroComprobante, "");
    strcpy(comprobante.fecha, "");
    strcpy(comprobante.dniCliente, "");
    strcpy(comprobante.detalleServicio, "");
    comprobante.montoTotal = 0;

    // Validar propietario
    if (!existePropietario(dniCliente))
    {
        return comprobante;
    }

    // Validar monto
    if (monto <= 0)
    {
        return comprobante;
    }

    // Copiar datos
    strcpy(
        comprobante.numeroComprobante,
        numComprobante
    );

    strcpy(
        comprobante.dniCliente,
        dniCliente
    );

    strcpy(
        comprobante.detalleServicio,
        detalle
    );

    comprobante.montoTotal = monto;

    // Fecha actual
    time_t t = time(NULL);

    tm *fechaActual = localtime(&t);

    sprintf(
        comprobante.fecha,
        "%02d/%02d/%04d",
        fechaActual->tm_mday,
        fechaActual->tm_mon + 1,
        fechaActual->tm_year + 1900
    );

    // Guardar en archivo
    ofstream archivo(
        "comprobantes.dat",
        ios::binary | ios::app
    );

    if (archivo)
    {
        archivo.write(
            reinterpret_cast<char*>(&comprobante),
            sizeof(ComprobantePago)
        );

        archivo.close();
    }

    return comprobante;
}