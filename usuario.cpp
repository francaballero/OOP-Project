#include <iostream>
#include <iomanip>
#include <unistd.h>
#include "usuario.h"
#include "tarjeta.h"
#include "articulo.h"
#include "cadena.h"

std::set<Cadena> Usuario::ids_;

//Definición de los métodos de la clase Clave
Clave::Clave (const char* c) {
    if (std::strlen(c) < 6) throw Clave::Incorrecta (CORTA);
    const char cv [65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789./";
    srand(time(0));
    const char salt [3] = { cv[rand()%64], cv[rand()%64], '\0'};
    char *p = crypt (c, salt);
    if (!p) throw Clave::Incorrecta (ERROR_CRYPT);
    cad_ = p;
}

bool Clave::verifica (const char* c) const {
    const char* p = crypt (c, cad_.c_str());
    return !std::strcmp (p, cad_.c_str());
}

//Definición de los métodos de la clase Usuario
Usuario::Usuario (const Cadena& id, const Cadena& nombre, const Cadena& apellidos, const Cadena& direccion, const Clave& clave) : id_(id), nombre_(nombre), apellidos_(apellidos), direccion_(direccion), clave_(clave)
{
    if (!ids_.insert (id_).second) throw Usuario::Id_duplicado(id_);
}

void Usuario::compra (Articulo& a , unsigned cant) {
    carrito_.erase(&a);
    if(cant != 0) carrito_.insert (std::make_pair(&a, cant));
}

Usuario::~Usuario() {
    for(auto& i : tarjetas_)
        i.second->anula_titular();
    ids_.erase(id_);
}

//Definición de las funciones externas
std::ostream& operator << (std::ostream& os, const Usuario& u) {
    os << u.id() << " [" << u.clave_.clave() << "] " << u.nombre() << " " << u.apellidos() << std::endl;
    os << u.direccion() << std::endl;
    os << "Tarjetas:" << std::endl;
    for(const auto& i : u.tarjetas()) {
        os << "<" << i.first << ">" << std::endl;
    }
    return os;
}

void mostrar_carro(std::ostream& os, const Usuario& user) {
    os << "Carrito de compra de "<<user.id()<<" [Artículos: "<<user.n_articulos()<<"]" << std::endl;
    os << "     Cant.\tArtículo"<<std::endl;
    for(int i=0; i<59; i++) os<<"=";
    os << std::endl;
    for(const auto& i : user.compra()){
        os << "        " << i.second << " \t";
        os << "[" << (i.first)->referencia() << "] \"";
        os << (i.first)->titulo() << "\", ";
        os << (i.first)->f_publi().anno() << ". ";
        os << std::fixed << std::setprecision(2) << (i.first)->precio() << " €" << std::endl;
    }
    os << std::endl;
}