#include <iostream>
#include <iomanip>
#include "fecha.h"
#include "tarjeta.h"
#include "articulo.h"
#include "pedido.h"
#include "usuario.h"
#include "pedido-articulo.h"
#include "usuario-pedido.h"

//Inicialización de los atributos estáticos
int Pedido::N_pedidos = 0;

//Definición de los métodos de la clase Pedido
Pedido::Pedido (Usuario_Pedido& up, Pedido_Articulo& pa, Usuario& u, const Tarjeta& t, const Fecha& f) : num_(N_pedidos + 1), tarjeta_(&t), fecha_(f), total_(0) {
    if (t.caducidad() < f) throw Tarjeta::Caducada(t.caducidad());
    if (&u != t.titular()) throw Pedido::Impostor(u);
    Fecha actual = Fecha();
    for(auto& i : u.compra()) {
        if (LibroDigital* ld = dynamic_cast<LibroDigital*> (i.first)) {
            if (ld->f_expir() < actual)
                u.compra(*ld, 0);
        }
        else {
            ArticuloAlmacenable* pa = dynamic_cast<ArticuloAlmacenable*> (i.first);
            if (i.second > pa->stock()){
                Articulo& aux = *(i.first);
                vaciar_carrito(u);
                throw Pedido::SinStock(aux);
            }
        }
    }
    if (u.n_articulos() == 0) throw Pedido::Vacio(u);
    for(auto& i : u.compra()) {
        if (ArticuloAlmacenable* aa = dynamic_cast<ArticuloAlmacenable*> (i.first)){
            aa->stock() = aa->stock() - 1;
        }
        pa.pedir (*this, *(i.first), (i.first)->precio(), i.second);
        total_ += (i.first)->precio() * i.second;
        u.compra (*(i.first), 0);
    }
    up.asocia(u, *this);
    N_pedidos++;
}

void Pedido::vaciar_carrito(Usuario& u) {
    for(auto& i: u.compra())
        u.compra (*(i.first), 0);
}

//Declaración de las funciones externas
std::ostream& operator << (std::ostream& os, const Pedido& p) {
    os << "    Núm. pedido: " << p.numero() << std::endl;
    os << "    Fecha\"--->MUTACION<---\":       " << p.fecha() << std::endl;
    Pedido p1 = p;
    os << "    Pagado con:  " << p1.tarjeta()->numero() << std::endl;
    os << "    Importe:     " << std::fixed << std::setprecision(2) << p.total() << " €" << std::endl;
    return os;
}