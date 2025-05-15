#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// Clase abstracta Pieza
class Pieza {
    private:
        char simbolo;
        bool esBlanco;

    public:
        Pieza(char simbolo, bool esBlanco) {
            this->esBlanco = esBlanco;

            if (esBlanco)
                this->simbolo = (char)tolower(simbolo);
            else
                this->simbolo = (char)toupper(simbolo);

        }
        virtual ~Pieza() {}

        virtual bool MovimientoValido(int origenX, int origenY, int destinoX, int destinoY) const = 0;

        char getSimbolo() const { return simbolo; }
        bool getEsBlanco() const { return esBlanco; }
};

// Clase derivada Peon
class Peon : public Pieza {
public:
    Peon(char simbolo, bool esBlanco) : Pieza(simbolo, esBlanco) {}

    bool MovimientoValido(int origenX, int origenY, int destinoX, int destinoY) const override {
        
        // Validación de movimiento del peón: Avanzar una casilla hacia adelante o dos casillas en el primer movimiento
        
        int direccionMovimiento;
        if (getEsBlanco()) {
            (direccionMovimiento = 1);
        } else {
        (direccionMovimiento = -1); //Mueve el peón de color negro una o dos casillas hacia atrás en 
                                                                // el eje de las y
        }

        // Movimiento de una casilla hacia adelante
        if (destinoX == origenX && destinoY == origenY + direccionMovimiento) {
            return true;
        }

        // Movimiento de dos casillas en el primer movimiento
        if (origenY == 1 && destinoX == origenX && destinoY == origenY + 2 * direccionMovimiento) {
            return true;
        }
        
        //origenY == 1: El peón se encuentra en la fila 1 

        //destinoX == origenX: El peón se mueve en la misma columna, 
        //es decir, no se desplaza lateralmente.

        //destinoY == origenY + 2 * direccionMovimiento: El peón se mueve hacia adelante 
        //(o hacia atrás, dependiendo de direccionMovimiento) dos filas desde su posición actual.
        

        return false;
    }
};

//Clase derivada Torre
class Torre : public Pieza {
public:
    Torre(char simbolo, bool esBlanco) : Pieza(simbolo, esBlanco) {}

    bool MovimientoValido(int origenX, int origenY, int destinoX, int destinoY) const override {
           
        // Movimiento lateral o hacia adelante/atrás
        return (origenX == destinoX && origenY != destinoY) || (origenX != destinoX && origenY == destinoY);
           
    }
};

//Clase derivada Caballo
class Caballo : public Pieza {
public:
    Caballo(char simbolo, bool esBlanco) : Pieza(simbolo, esBlanco) {}

    bool MovimientoValido(int origenX, int origenY, int destinoX, int destinoY) const override {
        
        // Movimiento en L
        int deltaX = abs(destinoX - origenX);
        int deltaY = abs(destinoY - origenY);
        return (deltaX == 1 && deltaY == 2) || (deltaX == 2 && deltaY == 1);
        
        
    }
};

//Clase derivada Alfil
class Alfil : public Pieza {
public:
    Alfil(char simbolo, bool esBlanco) : Pieza(simbolo, esBlanco) {}

    bool MovimientoValido(int origenX, int origenY, int destinoX, int destinoY) const override {
        
        // Movimiento diagonal
        return abs(destinoX - origenX) == abs(destinoY - origenY);
        
    }
};

//Clase derivada Dama/Reina
class Dama : public Pieza {
public:
    Dama(char simbolo, bool esBlanco) : Pieza(simbolo, esBlanco) {}

    bool MovimientoValido(int origenX, int origenY, int destinoX, int destinoY) const override {
        
        // Movimiento diagonal o lateral o hacia adelante/atrás
        return (abs(destinoX - origenX) == abs(destinoY - origenY)) || (origenX == destinoX || origenY == destinoY);
        
    }
};

//Clase derivada Rey
class Rey : public Pieza {
public:
    Rey(char simbolo, bool esBlanco) : Pieza(simbolo, esBlanco) {}

    bool MovimientoValido(int origenX, int origenY, int destinoX, int destinoY) const override {
        
        // Avanzar una casilla en cualquier dirección
        int deltaX = abs(destinoX - origenX);
        int deltaY = abs(destinoY - origenY);
        return (deltaX <= 1 && deltaY <= 1) && (deltaX + deltaY > 0);  // No permite quedarse en la misma posición
    
    }
};

// Clase Tablero
class Tablero {
private:
    vector<vector<Pieza*>> tablero;
    vector<string> movimientos;

public:

    vector<string>& ObtenerHistorial() {
        return movimientos;
    }
    
    
    Tablero() {
        InicializarTablero();
    }

    void InicializarTablero() {
        // Inicializar el tablero con punteros nulos (casillas vacías)
        tablero.resize(8, vector<Pieza*>(8, nullptr));

        // TODO: Colocar las piezas blancas en sus posiciones iniciales
        for (int i = 0; i < 8; i++) {
        tablero[i][1] = new Peon('P', true);  // Peones blancos en la fila 2
    }

    tablero[0][0] = new Torre('T', true);     // Torre blanca en la esquina superior izquierda
    tablero[1][0] = new Caballo('C', true);   // Caballo blanco en la fila 1, columna 2
    tablero[2][0] = new Alfil('A', true);     // Alfil blanco en la fila 1, columna 3
    tablero[3][0] = new Dama('D', true);      // Dama blanca en la fila 1, columna 4
    tablero[4][0] = new Rey('R', true);       // Rey blanco en la fila 1, columna 5
    tablero[5][0] = new Alfil('A', true);     // Alfil blanco en la fila 1, columna 6
    tablero[6][0] = new Caballo('C', true);   // Caballo blanco en la fila 1, columna 7
    tablero[7][0] = new Torre('T', true);     // Torre blanca en la esquina superior derecha
        
    }

    void MostrarTablero() const {
        // Mostrar el encabezado del tablero (letra columna)
        cout << endl << "\ta b c d e f g h" << endl << endl;

        for (int fila = 7; fila >= 0; fila--) {
            cout << fila + 1 << "\t"; // Número de fila

            for (int columna = 0; columna < 8; columna++) {
                Pieza* pieza = tablero[columna][fila];

                if (pieza) {
                    char simbolo = pieza->getSimbolo();
                    cout << simbolo << " ";
                } else {
                    cout << ". "; // Casilla vacía
                }
            }

            cout << "\t" << fila + 1 << endl; // Número de fila
        }

    // Mostrar el encabezado del tablero (letra columna)
    cout << endl << "\ta b c d e f g h" << endl << endl;
    }

    vector<int> TraducirInput(string origen, string destino) {
        /* Recibe el input del usuario (ejemplo: "b2", "b3") y
        lo traduce a coordenadas X y Y. */
        map<string, int> letrasTablero = {{"a",0} , {"b",1}, {"c",2}, {"d",3}, {"e",4}, {"f",5}, {"g",6}, {"h",7}};
        vector<int> coordenadas;
        int origenX = letrasTablero[origen.substr(0, 1)];
        int origenY = stoi(origen.substr(1, 1))-1;
        int destinoX = letrasTablero[destino.substr(0, 1)];
        int destinoY = stoi(destino.substr(1, 1))-1;

        coordenadas.push_back(origenX);
        coordenadas.push_back(origenY);
        coordenadas.push_back(destinoX);
        coordenadas.push_back(destinoY);

        return coordenadas; // coordenadas = [origenX, origenY, destinoX, destinoY]
    }

    void Mover(string origen, string destino) {
        vector<int> coordenadas = TraducirInput(origen, destino);
        int origenX = coordenadas[0];
        int origenY = coordenadas[1];
        int destinoX = coordenadas[2];
        int destinoY = coordenadas[3];
	
	
	// Verifica si hay una pieza en la posición de origen
    Pieza* pieza = tablero[origenX][origenY];
    if (pieza == nullptr) {
        cout << "No hay una pieza en la posición de origen." << endl;
        return;
    }

    // Verifica si el movimiento es válido según las reglas de la pieza
    if (!pieza->MovimientoValido(origenX, origenY, destinoX, destinoY)) {
        cout << "Movimiento no válido para la pieza." << endl;
        return;
    }

    // Verifica si hay una pieza en la posición de destino
    Pieza* piezaDestino = tablero[destinoX][destinoY];
    if (piezaDestino != nullptr && pieza->getEsBlanco() == piezaDestino->getEsBlanco()) {
        cout << "No puedes capturar tu propia pieza." << endl;
        return;
    }

    // Realiza el movimiento y actualiza el tablero
    delete tablero[destinoX][destinoY]; // Libera la memoria de la pieza en destino si hay una
    tablero[destinoX][destinoY] = tablero[origenX][origenY];
    tablero[origenX][origenY] = nullptr;
    
    cout << "Movimiento realizado con exito." << endl;
    
    }
		
		
	void MostrarHistorial() const {
        // Muestra el historial de movimientos
        cout << "\nHistorial de movimientos exitosos:\n";
        for (const string& movimiento : movimientos) {
                cout << movimiento << endl;
            
        }
    
    }

};

void test(Tablero &tablero) {
	// Funcion para probar el funcionamiento del programa.
	
    /*tablero.Mover("b2", "b7"); // invalido
    tablero.Mover("b2", "b3");
    tablero.Mover("b1", "c5"); // invalido
    tablero.Mover("b1", "c3");
    tablero.Mover("c3", "a5"); // invalido
    tablero.Mover("c3", "a4");
    tablero.Mover("c1", "a2"); // invalido
    tablero.Mover("c1", "a3");
    tablero.Mover("a3", "d5"); // invalido
    tablero.Mover("a3", "d6");
    tablero.Mover("e2", "e5"); // invalido
    tablero.Mover("e2", "e4");
    tablero.Mover("d1", "g5"); // invalido
    tablero.Mover("d1", "h5");
    tablero.Mover("h2", "h5"); // invalido
    tablero.Mover("h2", "h4");
    tablero.Mover("h1", "g3"); // invalido
    tablero.Mover("h1", "h3");
    tablero.Mover("h3", "d4"); // invalido
    tablero.Mover("h3", "c3");
    tablero.Mover("c3", "d7"); // invalido
    tablero.Mover("c3", "c7");
    tablero.Mover("e4", "e6"); // invalido
    tablero.Mover("e4", "e5");
    tablero.Mover("f1", "a7"); // invalido
    tablero.Mover("f1", "a6");
    tablero.MostrarTablero();*/
}

int main() {
   
    char menu;
    do{
        
        cout << "Presione '1' para jugar o '2' para salir" << endl;
        cout << "1. Jugar" << endl; 
        cout << "2. Exit" << endl;
        cin >> menu;
        
        if (menu == '1'){
            
            Tablero tablero;
            tablero.MostrarTablero();

            while (true) {
                // Mostrar el estado actual del tablero
                tablero.MostrarTablero();

                // Entrada del jugador blanco
                string origen, destino;
                cout << "\nTurno del jugador blanco. Ingrese su movimiento"; 
                cout << "\n(por ejemplo, 'a2 a4' o 'salir'): ";
                cin >> origen;

                // Salir del bucle si el jugador ingresa "salir"
                if (origen == "salir") {
                    break;
                }

                cin >> destino;

                // Realizar el movimiento en el tablero
                tablero.Mover(origen, destino);
                
                // Agregar el movimiento al historial
                string movimiento = origen + " " + destino;
                tablero.ObtenerHistorial().push_back(movimiento);
            }
            
            
            // Mostrar historial al salir del programa
            tablero.MostrarHistorial();
            
        }
        
        
    } while (menu !='2');
        
        cout << endl;
        cout << "¡Gracias por jugar!\n";
    

    return 0;
}
