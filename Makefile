GPP=g++
CXXFLAGS=  -fshow-column -fno-diagnostics-show-caret  -g2  -O0    
LDFLAGS=   -lsfml-graphics -lsfml-audio -lsfml-network -lsfml-window -lsfml-system   
OBJS=Debug_Linux/main.o Debug_Linux/Bloque.o Debug_Linux/Grua.o Debug_Linux/Marcador.o Debug_Linux/Juego.o Debug_Linux/Torre.o 

all: Debug_Linux ""Debug_Linux/City Bloxx.bin""

clean:
	rm -rf ${OBJS} ""Debug_Linux/City Bloxx.bin""

""Debug_Linux/City Bloxx.bin"": ${OBJS}
	${GPP} ${OBJS} ${LDFLAGS} -o $@

Debug_Linux:
	mkdir Debug_Linux

Debug_Linux/main.o: main.cpp src/Juego.h src/Grua.h src/Bloque.h src/Torre.h src/Marcador.h
	${GPP} ${CXXFLAGS} -c main.cpp -o $@

Debug_Linux/Bloque.o: src/Bloque.cpp src/Bloque.h src/GestorRecursos.h
	${GPP} ${CXXFLAGS} -c src/Bloque.cpp -o $@

Debug_Linux/Grua.o: src/Grua.cpp src/Grua.h src/Bloque.h src/GestorRecursos.h
	${GPP} ${CXXFLAGS} -c src/Grua.cpp -o $@

Debug_Linux/Marcador.o: src/Marcador.cpp src/Marcador.h src/GestorRecursos.h
	${GPP} ${CXXFLAGS} -c src/Marcador.cpp -o $@

Debug_Linux/Juego.o: src/Juego.cpp src/Juego.h src/Grua.h src/Bloque.h src/Torre.h src/Marcador.h src/GestorRecursos.h
	${GPP} ${CXXFLAGS} -c src/Juego.cpp -o $@

Debug_Linux/Torre.o: src/Torre.cpp src/Torre.h src/Bloque.h
	${GPP} ${CXXFLAGS} -c src/Torre.cpp -o $@

