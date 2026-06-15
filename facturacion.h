#ifndef FACTURACION_H
#define FACTURACION_H

#include "estructuras.h"

ComprobantePago emitirComprobante(
    const char numComprobante[],
    const char dniCliente[],
    const char detalle[],
    float monto
);

#endif