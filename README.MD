# Sistema de Control de Atención en una Veterinaria

## Descripción

Este proyecto es una aplicación desarrollada en C++ que permite gestionar las operaciones básicas de una veterinaria. El sistema administra la información de propietarios, mascotas, consultas médicas, vacunaciones y procesos de facturación.

Entre sus principales funcionalidades se encuentran:

- Registro de propietarios.
- Registro de mascotas.
- Gestión de consultas veterinarias.
- Control de vacunaciones.
- Emisión de comprobantes de facturación.
- Consulta de información almacenada.

El objetivo del proyecto es aplicar conceptos de programación estructurada y modular mediante la implementación de diferentes módulos especializados.

---

## Estructura del Proyecto

- `main.cpp` → Menú principal y control general del sistema.
- `propietarios.cpp` → Gestión de propietarios.
- `mascotas.cpp` → Gestión de mascotas.
- `consultas.cpp` → Registro y consulta de atenciones veterinarias.
- `vacunas.cpp` → Control de vacunaciones.
- `facturacion.cpp` → Emisión de comprobantes y facturación.

---

## Requisitos

- Compilador GCC/G++ compatible con C++.
- Sistema operativo Windows.

---

## Compilación

Ejecutar el siguiente comando desde la carpeta del proyecto:

```bash
g++ main.cpp propietarios.cpp mascotas.cpp consultas.cpp vacunas.cpp facturacion.cpp -o main
```

---

## Ejecución

Una vez compilado el proyecto, ejecutar:

```powershell
.\main
```

---

## Autor

Proyecto académico desarrollado para el curso de Programación.