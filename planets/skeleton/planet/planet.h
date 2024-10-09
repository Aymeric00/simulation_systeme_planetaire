#ifndef _PLANET_H_
#define _PLANET_H_

#include "../vec2/vec2.h"
#include "../gfx/gfx.h"
#include <time.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

#define G 6.67e-11
#define NB_PLANETS 6 // max 6
#define SCENERIO 1 // Changer 

// Masse des étoiles RAPPORT
#define M_SOLEIL 1.989e30
#define M_MERCURE 3.285e23
#define M_VENUS 4.867e24
#define M_TERRE 5.972e24
#define M_MARS 6.39e23 
#define M_ATLAS 3 * M_TERRE
#define M_VIBRANIUM M_VENUS / 2
// #define M_JUPYTER 1.898e27
// #define M_SATURNE 5.683e26


#define DISPLAY_EARTH 10
#define R_SOLEIL DISPLAY_EARTH * 1.3  // The sun is approximately 109 times the radius of Earth
#define R_MERCURE DISPLAY_EARTH * 0.383  // Mercury is approximately 0.383 times the radius of Earth
#define R_VENUS DISPLAY_EARTH * 0.949  // Venus is approximately 0.949 times the radius of Earth
#define R_TERRE DISPLAY_EARTH  // Earth's display size
#define R_MARS DISPLAY_EARTH * 0.532  // Mars is approximately 0.532 times the radius of Earth
#define R_ATLAS DISPLAY_EARTH * 1.85
#define R_VIBRANIUM DISPLAY_EARTH * 0.4745
// #define R_JUPITER DISPLAY_EARTH * 0.421  // Jupiter is approximately 11.21 times the radius of Earth
// #define R_SATURNE DISPLAY_EARTH * 0.945  // Saturn is approximately 9.45 times the radius of Earth

// Voir ressources fiches planètes
#define E_SOLEIL 0 // Car c'est l'étoile du systeme
#define E_MERCURE 0.20563069
#define E_VENUS 0.00677323
#define E_TERRE 0.01671022
#define E_MARS 0.09341233
#define E_ATLAS 0.21
#define E_VIBRANIUM 0.24
// #define E_JUPITER 0.04839266
// #define E_SATURNE 0.05415060

#define DA_SOLEIL 0 // En m
#define DA_MERCURE 57.909e9
#define DA_VENUS 108.209e9
#define DA_TERRE 149.596e9
#define DA_MARS 227.923e9
#define DA_ATLAS 420e9
#define DA_VIBRANIUM 580e9
// #define DA_JUPITER 778.570e9
// #define DA_SATURNE 300e9

#define RS DA_VIBRANIUM * 1.25

#define SIZE_POINT 25000

#define CALCULATE_REV 0 // 1 pour le faire

typedef struct _planet
{
    double mass;   ///// pour calculer les forces gravitationnelles
    vec2 pos;      ///// x(t)
    vec2 prec_pos; ///// x(t - dt)
    double axis;    ///// demi-grand axe, distance moyenne d'une planète au soleil
    double excentricity; ///// pour la forme de l'orbite, 0 = circulaire, < 0 = elliptique
    double radius;  ///// pour la mise à l'échelle
    vec2 vit_init; ///// vitesse initiale, que l'on utilisera seulement une fois pour la composante y au debut
    int color;   ///// pour la couleur sur le gfx
    coordinates *pointsList;
    vec2 first_pos;
} planet_t;

typedef struct _system
{
    planet_t star;       // ex. The sun
    uint32_t nb_planets; // The number of orbiting planets
    planet_t *planets;   // An array of orbiting planets
} system_t;

// Those function are not mandatory to implement,
// it's rather a hint of what you should have.
planet_t create_planet(double mass, double axis, double excentricity, double radius, int color); // plus besoin des vec2 car calculés avec paramètres
system_t create_system(double mass[], double axis[], double excentricity[], double radius[], int color[], double delta_t);
void show_system(struct gfx_context_t *ctxt, system_t *system, int width, int height, int ind);
void update_system(system_t *system, double delta_t);
void free_system(system_t *system);
/* vec2 planet_position_initiale(planet_t *planet,double delta_t *system); */
vec2 acceleration(planet_t planet, vec2 force_res);
//vec2 vitesse_initial(planet_t planet, system_t *system);
void update_pos(planet_t *planet, vec2 acceleration, double delta_t); //fonction pour rendre la fonction update_system + lisible LOOL
vec2 calculate_gravitational_force(planet_t planet1, planet_t planet2); //force gravitationnelle entre 2 planètes par exemple
vec2 calculate_resultant_force_planet(system_t *system, uint32_t planet_index); //somme des forces exercées par toutes les planètes ainsi que le soleil
/* void initialisation_pos(int nb_planets, system_t *system, double delta_t);*/
vec2 init_planet_speed(system_t *system, planet_t planet);
void update_initial_position(system_t *system, double delta_t);
vec2 create_vect_perpendiculaire(vec2 vect);
void show_trajectory_point_methods(struct gfx_context_t *ctxt, system_t *system, int ind);
void addPoint(coordinates ptn, planet_t *planet, int index);
void calcRevolution(system_t *sys, long *tab, long it);
double calcAverage(int tableau[], int taille);
#endif