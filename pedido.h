#ifndef PEDIDO_H_
#define PEDIDO_H_

#include <iostream>

class LineaPedido;
class Usuario_Pedido;
class Articulo;
class Pedido_Articulo;
class Tarjeta;
class Fecha;

//Declaración de la clase Pedido
class Pedido {
public:
    class Vacio {
        const Usuario* u_;
    public:
        explicit Vacio (const Usuario& u) : u_(&u) {}
        const Usuario& usuario () const { return *u_; }
    };
    class Impostor {
        const Usuario* u_;
    public:
        explicit Impostor (const Usuario& u) : u_(&u) {}
        const Usuario& usuario () const { return *u_; }
    };
    class SinStock {
        const Articulo* a_;
    public:
        explicit SinStock (const Articulo& a) : a_(&a) {}
        const Articulo& articulo () const { return *a_; }
    };
    Pedido (Usuario_Pedido& up, Pedido_Articulo& pa, Usuario& u, const Tarjeta& t, const Fecha& f = Fecha());
    int numero() const;
    const Tarjeta* tarjeta() const;
    Fecha fecha() const;
    double total() const;
    static int n_total_pedidos();
private:
    int num_;
    const Tarjeta*  tarjeta_;
    Fecha fecha_;
    double total_;
    static int N_pedidos;
    void vaciar_carrito(Usuario& u);
};

//Declaración de las funciones externas
std::ostream& operator << (std::ostream&, const Pedido&);

//Definición de las funciones inline
inline int Pedido::numero() const {
    return num_;
}

inline const Tarjeta* Pedido::tarjeta() const{
    return tarjeta_;
}

inline Fecha Pedido::fecha() const {
    return fecha_;
}

inline double Pedido::total() const {
    return total_;
}

inline int Pedido::n_total_pedidos() {
    return N_pedidos;
}

#endif
