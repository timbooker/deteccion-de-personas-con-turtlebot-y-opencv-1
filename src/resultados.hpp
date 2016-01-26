#ifndef DP_RESULTADOS_H
#define DP_RESULTADOS_H

#include <iostream>

// Estructura de resultados. Versión 1.0
// Contiene información referida a una detección de persona en una imagen
// determinada. Usar un objeto por cada detección. Se supone que el detector
// entrega un rectángulo que contiene a la persona detectada.
struct struct_resultados
{
	unsigned int set = 1;		// Set al que corresponde la imagen
	unsigned int img = 1;		// Número de imagen
	unsigned int prof = 1;		// Profundidad [ 16 / 8 ]
	unsigned int comp = 0;		// Si está la persona completa o no [ 1 / 0 ]
	float tiempo = 0;			// Tiempo que tardó en detectarse, en milisegundos
	unsigned int arr_izq_x = 0;	// Coordenadas de la esquina superior izquierda [px]
	unsigned int arr_izq_y = 0;	//
	unsigned int arr_der_x = 0;	// Coordenadas de la esquina superior derecha
	unsigned int arr_der_y = 0;	//
	unsigned int aba_izq_x = 0;	// Coordenadas de la esquina inferior izquierda
	unsigned int aba_izq_y = 0;	//
	unsigned int aba_der_x = 0;	// Coordenadas de la esquina inferior derecha
	unsigned int aba_der_y = 0;	//
};

// Función de escritura
std::ostream& operator<<( std::ostream& os, const struct_resultados& res );

#endif // DP_RESULTADOS_H
