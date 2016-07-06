#ifndef PEDIDO_ARTICULO_H_
#define PEDIDO_ARTICULO_H_

#include <iostream>
#include <map>
#include "articulo.h"
#include "pedido.h"

//Declaración de la clase LineaPedido
class LineaPedido {
public:
    explicit LineaPedido (double precio_venta, unsigned cantidad = 1);
    double precio_venta() const;
    unsigned cantidad() const;
private:
    double precio_venta_;
    unsigned cantidad_;
};

//Declaración y definición de la clase de objetos función OrdenaArticulos
struct OrdenaArticulos {
    bool operator () (const Articulo* const a1, const Articulo* const a2) const { return a1->referencia() < a2->referencia(); }
};

//Declaración y definición de la clase de objetos función OrdenaPedidos
struct OrdenaPedidos {
    bool operator () (const Pedido* const p1, const Pedido* const p2) const { return p1->numero() < p2->numero(); }
};

//Declaración de la clase de asociación Pedido_articulo
class Pedido_Articulo {
public:
    typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
    typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
    void pedir (Pedido& p, Articulo& a, double precio, unsigned cant = 1);
    void pedir (Articulo& a, Pedido& p, double precio, unsigned cant = 1);
    ItemsPedido& detalle (Pedido&);
    Pedidos& ventas (Articulo&);
    void mostrarDetallePedidos (std::ostream&);
    void mostrarVentasArticulos (std::ostream&);
private:
    std::map<Pedido*, ItemsPedido, OrdenaPedidos> directa;
    std::map<Articulo*, Pedidos, OrdenaArticulos> indirecta;
};

//Declaración de las funciones externas
std::ostream& operator << (std::ostream&, const Pedido_Articulo::ItemsPedido&);
std::ostream& operator << (std::ostream&, const Pedido_Articulo::Pedidos&);
std::ostream& operator << (std::ostream&, const LineaPedido&);

//Definición de los métodos inline de la clase LineaPedido
inline LineaPedido::LineaPedido (double precio_venta, unsigned cantidad) : precio_venta_(precio_venta), cantidad_(cantidad)
{}

inline double LineaPedido::precio_venta() const {
    return precio_venta_;
}

inline unsigned LineaPedido::cantidad() const {
    return cantidad_;
}

inline void Pedido_Articulo::pedir (Articulo& a, Pedido& p, double precio, unsigned cant) {
    pedir (p, a, precio, cant);
}

inline Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle (Pedido& p){
    return directa[&p];
}

inline Pedido_Articulo::Pedidos& Pedido_Articulo::ventas (Articulo& a){
    return indirecta[&a];
}

#endif
