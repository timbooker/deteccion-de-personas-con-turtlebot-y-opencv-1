#!bin/bash

# PRUEBAS VARIANDO EL TAMAÑO DEL KERNEL DE BLUR

# Parámetros
DH_ESCALA_INICIAL=1.3
DH_PASOESCALA=1.05
DH_UMBRALAGRUPAMIENTO=2
DH_HIT_THRESHOLD=0
DH_SETSVMDETECTOR=getDefaultPeopleDetector
DH_CONVERTIR_A_GRIS=true
DH_ECUALIZAR_HISTOGRAMA=true
# DH_BLUREAR=false
#DH_TAMANIO_BLUR=3
DH_FILTRO_ENFOQUE=false
DH_FILTRO_REPUJADO=false
DH_FILTRO_ENFOQUE_Y_REPUJADO=false
DH_FILTRO_REPUJADO_Y_ENFOQUE=false
DH_USAR_PROFUNDIDAD=false



####################################################################################
#			PRUEBA 01
NOMBRE_RESULTADOS=01

DH_BLUREAR=false
DH_TAMANIO_BLUR=3

funcion_detector_hog
funcion_csv_headers
funcion_csv_normal


####################################################################################
#			PRUEBA 02
NOMBRE_RESULTADOS=02

DH_BLUREAR=true
DH_TAMANIO_BLUR=3

funcion_detector_hog
funcion_csv_normal


####################################################################################
#			PRUEBA 03
NOMBRE_RESULTADOS=03

DH_BLUREAR=true
DH_TAMANIO_BLUR=5

funcion_detector_hog
funcion_csv_normal


####################################################################################
#			PRUEBA 04
NOMBRE_RESULTADOS=04

DH_BLUREAR=true
DH_TAMANIO_BLUR=7

funcion_detector_hog
funcion_csv_normal


####################################################################################
#			PRUEBA 05
NOMBRE_RESULTADOS=05

DH_BLUREAR=true
DH_TAMANIO_BLUR=9

funcion_detector_hog
funcion_csv_normal

