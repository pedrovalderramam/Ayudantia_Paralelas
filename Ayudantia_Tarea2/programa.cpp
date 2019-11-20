#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

//************************* FUNCIONES *****************************

void multiplica_matriz(int matriz[][3],int matriz2[][3],double multiplicacion[][3])
{
    for(int i=0; i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			for(int k=0;k<3;k++)
			{
	multiplicacion[i][j] =multiplicacion[i][j]+(matriz[i][k]*matriz2[k][j]);
			}
		}
	}
}

string matriz_salida(double matriz[][3]) {
    std::stringstream ss;
    ss << '[' <<matriz[0][0] << ',' <<matriz[0][1] << ',' <<matriz[0][2] << ';' <<matriz[1][0] << ',' <<matriz[1][1] << ',' <<matriz[1][2] << ';' <<matriz[2][0] << ',' <<matriz[2][1] << ',' <<matriz[2][2] << ']' << std::endl;
    return ss.str();
}

void llenar_matriz(string linea,int matriz[3][3])
{
    if (!linea.empty()) {
        std::vector<std::string> arreglo;
        std::stringstream ss(linea);
        std::string temp;
        while (ss >> temp)
        {
            arreglo.push_back(temp);
        }

        for (int i = 0; i < 3; i++)
        {
            std::string fila = arreglo[i];
            std::replace(fila.begin(), fila.end(), ',', ' ');

            std::vector<std::string> columnas;
            std::stringstream sf(fila);
            std::string tmp;
            while (sf >> tmp)
            {
                columnas.push_back(tmp);
            }

            for (int j = 0; j < 3; j++)
            {
                std::string valor = columnas[j];
                int numero = atoi(valor.c_str());
                matriz[i][j] = numero;
            }
        }
    }
}

char* obtener_matriz(char** matriz, int largo) {
    char* archivo = NULL;
    int i = 0, k = 0;

    if (largo > 0) {
        for (i = 0; i < largo; i++) {
            if (strcmp("-m", matriz[i]) == 0) {
                k = i + 1;
                archivo = (char *) calloc(strlen(matriz[k]) + 1, sizeof (char));

                snprintf(archivo, strlen(matriz[k]) + 1, "%s", matriz[k]);
                break;
            }
        }
    }

    return archivo;
}
//************************* MAIN **********************************

int main (int argc, char** argv)
{
if (argc > 0) {
        std::string archivo(obtener_matriz(argv, argc));


        if (!archivo.empty() ) {
            std::ifstream entrada(archivo);
            std::string linea;
	    int matriz[3][3];
      	    int matriz2[3][3];
            while (std::getline(entrada, linea))
 {


        linea.erase(std::remove(linea.begin(), linea.end(), '['), linea.end());
        linea.erase(std::remove(linea.begin(), linea.end(), ']'), linea.end());
        std::replace(linea.begin(), linea.end(), ';', ' ');
	string linea_matriz;
        string linea_matriz2;

	int counta_matriz= linea.find(":");
	linea_matriz=linea.substr(0,counta_matriz);
	linea_matriz2=linea.substr(counta_matriz+1);
        llenar_matriz(linea_matriz,matriz);
	llenar_matriz(linea_matriz2,matriz2);

        double multiplicacion[3][3];
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                multiplicacion[i][j]=0;
            }
        }

        multiplica_matriz(matriz,matriz2,multiplicacion);
        std::string str = matriz_salida(multiplicacion);
        std::cout<<"respuesta="<<str<<endl;
linea.clear();
}entrada.close();
    }

}
    return 0;
}
