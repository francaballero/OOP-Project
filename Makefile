# Makefile para el caso 4 de la LIBRERÍA
# ©2010-14 Inma, Gerardo, Fidel, Juanma, Antonio
#
# --- Parte configurable ---
#
# NOMBREALUMNO es el nombre del directorio donde el alumno guarda las
# prácticas de POO (C++). Dentro de ese directorio debe haber uno para
# cada práctica llamado NOMBREPRACTICA, que será de la forma P<n>,
# siendo <n> el número de práctica: P0, P1, etc.

NOMBREALUMNO   = Caballero_Cerezo_FranciscoJose
NOMBREPRACTICA = P4

# CADENADIR y FECHADIR son los directorios donde están respectivamente
# los módulos objeto y cabeceras de Cadena y Fecha: cadena.{oh} y fecha.{oh}.
DIRFECHACADENA=P1
CADENADIR= ../${DIRFECHACADENA}/Cadena
FECHADIR = ../${DIRFECHACADENA}/Fecha


# ¿Compilador C++ de LLVM (clang++) o de GNU (g++)?
#CXX      = clang++
CXX	 = g++

# ¿Qué estándar seguir?
# Si tu compilador lo admite (GNU C++ v4.7+), puedes usar c++11
# si usas cosas del estándar de 2011.
# Si no usas nada del estándar de 2011 o tu compilador es muy antiguo, cambia
# c++0x o c++11 por -ansi. En este caso, añade a CXXFLAGS: -Dunique_ptr=auto_ptr
# Opciones:
# ansi o c++98 o c++03: estándar de 1998, corregido en 2003
# c++0x: borrador del estándar de 2011
# c++11: estándar actual de 2011
# c++1y: sgute. revisión (¿2014-2017?)
STD=c++11

ifeq (${CXX},clang++)
  CXXFLAGS = -g -Wall -std=${STD} ${INCLUDES}
else
  CXXFLAGS = -g -pedantic -Wall -std=${STD} ${INCLUDES}
endif

# --- Fin parte configurable

INCLUDES  = -I${CADENADIR} -I${FECHADIR}
LOCALLIBS = ${CADENADIR}/cadena.o ${FECHADIR}/fecha.o
EXTLIBS   = -lcrypt
LIBS      = ${LOCALLIBS} ${EXTLIBS}
VPATH     = .:${CADENADIR}:${FECHADIR}

COMM_SRCS = usuario.cpp tarjeta.cpp articulo.cpp pedido.cpp luhn.cpp \
	pedido-articulo.cpp
COMM_HDRS = articulo.h autor.h pedido-articulo.h pedido.h tarjeta.h usuario.h \
	usuario-pedido.h
MAIN_SRCS = test-caso4-consola.cpp
MAIN_OBJS = $(COMM_SRCS:.cpp=.o) $(MAIN_SRCS:.cpp=.o)
MAIN_EXE  = test-caso4-consola
TEST_SRCS = test-caso0-cadena-auto.cpp test-caso0-fecha-auto.cpp \
  test-caso1-auto.cpp test-caso3-auto.cpp test-caso4-auto.cpp test-auto.cpp
TEST_HDRS = test-auto.h fct.h
TEST_OBJS = $(COMM_SRCS:.cpp=.o) $(TEST_SRCS:.cpp=.o)
TEST_EXE  = test-p1_4-auto

SRCS = ${COMM_SRCS} ${TEST_SRCS} ${MAIN_SRCS}
HDRS = ${COMM_HDRS} ${TEST_HDRS} 
NOMBRETAR = ../../${NOMBREALUMNO}.tar.gz
NOMBREDIR = ${NOMBREALUMNO}/${NOMBREPRACTICA}

## OBJETIVOS PRINCIPALES #######################################################

.PHONY: all clean dist distclean test-consola test-auto

all: ${MAIN_EXE} ${TEST_EXE}

test-consola: ${MAIN_EXE}
	./$<

test-auto: ${TEST_EXE}
	./$<

clean:
	${RM} ${RMFLAGS} ${MAIN_EXE} ${MAIN_OBJS} ${TEST_EXE} ${TEST_OBJS} *.d *~ \#*
	(cd ${FECHADIR}; make clean)
	(cd ${CADENADIR}; make clean)

## COMPILACIÓN #################################################################

${MAIN_EXE}: ${MAIN_OBJS} ${LOCALLIBS}
	${CXX} -o $@ ${LDFLAGS} $^ ${EXTLIBS}

${TEST_EXE}: ${TEST_OBJS} ${LOCALLIBS}
	${CXX} -o $@ ${LDFLAGS} $^ ${EXTLIBS}

# Detección automática de dependencias en código fuente C++ con GCC #

%.d: %.cpp
	@$(CXX) -MM $(CXXFLAGS) $< > $@
	@sed -ri 's,($*)\.o[ :]*,\1.o $@ : ,g' $@

-include $(COMM_SRCS:.cpp=.d) $(MAIN_SRCS:.cpp=.d) $(TEST_SRCS:.cpp=.d)

## EMPAQUETADO #################################################################

${NOMBRETAR}: ${SRCS} ${HDRS} Makefile
ifeq ($(strip $(NOMBREALUMNO)),)
	@echo ""
	@echo "ATENCIÓN: debe definir en el Makefile la variable NOMBREALUMNO"
	@echo "con el nombre del directorio superior a este."
	@echo " Vea las instrucciones de entrega de las prácticas."
else
	tar -cvz -C../.. -f ${NOMBRETAR} ${NOMBREDIR} \
				${NOMBREALUMNO}/${DIRFECHACADENA}
endif

# Esto lo deberían usar los alumnos a la hora de la entrega:
# crea el archivo .tar.gz en el directorio padre tras borrar lo sobrante.
dist: clean ${NOMBRETAR}

distclean: clean
	${RM} ${RMFLAGS} ${NOMBRETAR}
