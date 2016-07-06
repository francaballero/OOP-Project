#ifndef USUARIO_PEDIDO_H_
#define USUARIO_PEDIDO_H_

class Usuario;
class Pedido;

//Declaración de la clase de asociación Usuario_Pedido
class Usuario_Pedido {
public:
    typedef std::set<Pedido*> Pedidos;
    void asocia (Usuario&, Pedido&);
    void asocia (Pedido&, Usuario&);
    Pedidos pedidos(Usuario&);
    Usuario* cliente(Pedido&);
private:
    std::map<Usuario*, Pedidos> directa;
    std::map<Pedido*, Usuario*> indirecta;
};

//Definición de los métodos inline de la clase Usuario_Pedido
inline void Usuario_Pedido::asocia (Usuario& u, Pedido& p) {
    directa[&u].insert(&p);
    indirecta[&p] = &u;
}

inline void Usuario_Pedido::asocia (Pedido& p, Usuario& u) {
    asocia (u, p);
}

inline Usuario_Pedido::Pedidos Usuario_Pedido::pedidos(Usuario& u) {
    return directa[&u];
}

inline Usuario* Usuario_Pedido::cliente(Pedido& p) {
    return indirecta[&p];
}


#endif