#include <iostream>
#include <iomanip>
#include "articulo.h"
#include "autor.h"
#include "cadena.h"
#include "fecha.h"

//Definición de los métodos de la clase Articulo
Articulo::Articulo (const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& f_publi, double precio) : autores_(autores), referencia_(referencia), titulo_(titulo), f_publi_(f_publi), precio_(precio)
{
    if (autores_.empty()) throw Articulo::Autores_vacios();
}

//Definición de los métodos de la clase ArticuloAlmacenable
ArticuloAlmacenable::ArticuloAlmacenable (const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& f_publi, double precio, unsigned stock) : Articulo(autores, referencia, titulo, f_publi, precio), stock_(stock) {}

//Definición de los métodos de la clase Libro
Libro::Libro (const Autores& autores, const Cadena& referencia, const Cadena& titulo1, const Fecha& f_publi, double precio, unsigned n_pag, unsigned stock1) : ArticuloAlmacenable(autores, referencia, titulo1, f_publi, precio, stock1), n_pag_(n_pag) {}

//Definición de los métodos de la clase Cederron
Cederron::Cederron (const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& f_publi, double precio, unsigned tam, unsigned stock) : ArticuloAlmacenable(autores, referencia, titulo, f_publi, precio, stock), tam_(tam) {}

//Definición de los métodos de la clase LibroDigital
LibroDigital::LibroDigital (const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& f_publi, double precio, const Fecha& f_expir) : Articulo(autores, referencia, titulo, f_publi, precio), f_expir_(f_expir) {}

//Definición de las funciones externas
std::ostream& operator<<(std::ostream& os, const Articulo& a) {
    os << "[" << a.referencia() << "] \"" << a.titulo() << "\", de ";
    auto i = a.autores().begin();
    auto j = a.autores().begin();
    j++;
    if (!a.autores().empty()) {
        while (j != a.autores().end()) {
            os << (*i)->apellidos() << ", ";
            i++; j++;
        }
    }
    os << (*i)->apellidos() << ". ";
    os << a.f_publi().anno() << ". " << std::fixed << std::setprecision(2) << a.precio() << " €" << std::endl;
	a.imp_esp(os);
    return os;
}
