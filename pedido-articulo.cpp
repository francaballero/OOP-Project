#include <iostream>
#include <iomanip>
#include "usuario.h"
#include "tarjeta.h"
#include "pedido-articulo.h"
#include "articulo.h"
#include "pedido.h"

//Definición de los métodos de la clase Pedido_Articulo
void Pedido_Articulo::pedir (Pedido& p, Articulo& a, double precio, unsigned cant){
    LineaPedido lp (precio, cant);
    directa[&p].insert (std::make_pair(&a, lp));
    indirecta[&a].insert (std::make_pair(&p, lp));
}

void Pedido_Articulo::mostrarDetallePedidos (std::ostream& os) {
    double precio_parcial;
    double precio_total = 0;
     for(const auto& i : directa) {
         precio_parcial = 0;
         os << "Pedido núm. " << (i.first)->numero() << std::endl;
         os << "Cliente: " << (i.first)->tarjeta()->titular()->id() << "	   ";
         os << "Fecha: " << (i.first)->fecha() << std::endl;
         for(int i=0; i<59; i++) os << "="; os << std::endl;
         os << "  PVP	Cantidad   Artículo" << std::endl;
         for(int i=0; i<59; i++) os << "="; os << std::endl;
         for(const auto& j : i.second) {
             os << std::fixed << std::setprecision(2) << j.second.precio_venta() << " € ";
             os << j.second.cantidad() << "\t   ";
             os << "[" << (j.first)->referencia() << "] \"" << (j.first)->titulo() << "\"" << std::endl;
             precio_parcial += j.second.precio_venta() * j.second.cantidad();
         }
         for(int i=0; i<59; i++) os << "="; os << std::endl;
         precio_total += precio_parcial;
         os << "Total   " << precio_parcial << " €\n\n" << std::endl;
     }
    os << "TOTAL VENTAS        " << precio_total << " €\n" << std::endl;
}

void Pedido_Articulo::mostrarVentasArticulos (std::ostream& os) {
    for(const auto& i : indirecta) {
        os << "Ventas de " << "[" << (i.first)->referencia() << "] \"" << (i.first)->titulo() << "\"  [Pedidos: " << i.second.size() << "]" << std::endl;
        os << i.second << std::endl << std::endl;
    }
}

//Definición de las funciones externas
std::ostream& operator << (std::ostream& os, const Pedido_Articulo::ItemsPedido& itemspedido){
    for(const auto& i : itemspedido) {
        os << std::fixed << std::setprecision(2) << i.second.precio_venta() << " € ";
        os << i.second.cantidad() << "\t   ";
        os << *(i.first) << std::endl;
    }
    return os;
}

std::ostream& operator << (std::ostream& os, const Pedido_Articulo::Pedidos& pedidos){
    int cantidad_total = 0;
    double precio_total = 0;
    for(int i=0; i<59; i++) os << "="; os << std::endl;
    os << "  PVP 	  Cantidad	   Fecha de venta" << std::endl;
    for(int i=0; i<59; i++) os << "="; os << std::endl;
    for(const auto& i : pedidos) {
        os << std::fixed << std::setprecision(2) << i.second.precio_venta() << " €\t";
        os << i.second.cantidad() << "		";
        os << (i.first)->fecha() << std::endl;
        precio_total += i.second.precio_venta() * i.second.cantidad();
        cantidad_total += i.second.cantidad();
    }
    os << std::endl;
    for(int i=0; i<59; i++) os << "="; os << std::endl;
    os << std::fixed << std::setprecision(2) << precio_total << " €\t" << cantidad_total;
    return os;
}

std::ostream& operator << (std::ostream& os, const LineaPedido& lp) {
    os << std::fixed << std::setprecision(2) << lp.precio_venta() << " €\t" << lp.cantidad();
    return os;
}