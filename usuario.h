#ifndef USUARIO_H_
#define USUARIO_H_

#include <iostream>
#include <map>
#include <set>
#include "cadena.h"
#include "tarjeta.h"

class Articulo;
class Numero;
class Pedido;

//Declaración de la clase Clave
class Clave {
public:
    enum Razon { CORTA, ERROR_CRYPT };
    class Incorrecta {
        Razon r_;
    public:
        Incorrecta (const Razon& r) : r_(r) {}
        Razon razon() const { return r_; }
    };
    Clave (const char*);
    Cadena clave() const;
    bool verifica (const char*) const;
private:
    Cadena cad_;
};

//Declaración de la clase Usuario
class Usuario {
public:
    class Id_duplicado {
        Cadena c_;
    public:
        Id_duplicado (const Cadena& c);
        Cadena idd() const;
    };
    typedef std::map<Numero, Tarjeta*> Tarjetas;
    typedef std::map<Articulo*, unsigned> Articulos;
    Usuario (const Cadena& id, const Cadena& nombre, const Cadena& apellidos, const Cadena& direccion, const Clave& clave);
    Usuario (const Usuario&) = delete;
    Cadena id() const;
    Cadena nombre() const;
    Cadena apellidos() const;
    Cadena direccion() const;
    const Tarjetas& tarjetas() const;
    void es_titular_de(Tarjeta&);
    void no_es_titular_de(Tarjeta&);
    void compra (Articulo&, unsigned cant = 1);
    const Articulos& compra() const;
    size_t n_articulos() const;
    friend std::ostream& operator << (std::ostream&, const Usuario&);
    ~Usuario();
private:
    Cadena id_;
    Cadena nombre_;
    Cadena apellidos_;
    Cadena direccion_;
    Clave clave_;
    Tarjetas tarjetas_;
    Articulos carrito_;
    static std::set<Cadena> ids_;
};

//Declaración de las funciones externas
void mostrar_carro(std::ostream&, const Usuario&);

//Definición de los métodos inline de la clase Clave
inline Cadena Clave::clave() const {
    return cad_;
}

//Definición de los métodos inline de la clase Usuario
inline Usuario::Id_duplicado::Id_duplicado (const Cadena& c) : c_(c) {}

inline Cadena Usuario::Id_duplicado::idd() const {
    return c_;
}

inline Cadena Usuario::id() const {
    return id_;
}

inline Cadena Usuario::nombre() const {
    return nombre_;
}

inline Cadena Usuario::apellidos() const {
    return apellidos_;
}

inline Cadena Usuario::direccion() const {
    return direccion_;
}

inline const Usuario::Tarjetas& Usuario::tarjetas() const {
    return tarjetas_;
}

inline void Usuario::es_titular_de(Tarjeta& t) {
    tarjetas_.insert (std::make_pair(t.numero(), &t));
}

inline void Usuario::no_es_titular_de(Tarjeta& t) {
    tarjetas_.erase (t.numero());
}

inline const Usuario::Articulos& Usuario::compra() const {
    return carrito_;
}

inline size_t Usuario::n_articulos() const {
    return carrito_.size();
}

#endif
