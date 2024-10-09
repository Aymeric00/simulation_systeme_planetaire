#include "./planet.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h> 

double perihelie(planet_t planet){
    return planet.axis * (1 - planet.excentricity);
}

// fonction pour créer les planètes, les positions initiales sont directemenet calculés ici, et les données qui serviront au calcul aussi
planet_t create_planet(double mass, double axis, double excentricity, double radius, int color)
{
    planet_t planet;

    planet.mass = mass;
    planet.axis = axis;
    planet.excentricity = excentricity;
    planet.radius = radius;
    planet.color = color;
    planet.pos = vec2_create(perihelie(planet), 0);
    planet.prec_pos = planet.pos;
    planet.vit_init = vec2_create_zero();
    planet.pointsList = malloc(sizeof(coordinates) * SIZE_POINT);
    planet.first_pos = planet.pos;
    return planet;
}

// fonction pour calculer la force gravitationnelle entre 2 planètes, seulement il faut encore normarliser les vecteurs et + encore...
vec2 calculate_gravitational_force(planet_t planet1, planet_t planet2)
{
    vec2 r = vec2_sub(planet2.pos, planet1.pos); // Soustraire le vecteur entre les positions des deux planètes
    double r_carre = vec2_norm_sqr(r); // Carré de la distance entre les planètes
    // Si distance nulle => Forces nulles si les planètes sont superposées => Vecteur 0
    if (r_carre == 0.0) {
        return vec2_create_zero(); 
    }
    double interaction_gravitational_force = G * (planet1.mass * planet2.mass / r_carre);  // Loi gravitation universelle Newton => F(A/B) = G×mA×mB/d2
    // Calculer la force gravitationnelle en multipliant le vecteur unitaire par l'interaction de la force gravitationnelle
    vec2 unit_vect = vec2_normalize(r);
    vec2 gravitational_force = vec2_mul(interaction_gravitational_force, unit_vect);
    return gravitational_force;
}

// Fonction pour calculer la force résultante s'exerçant sur une planète 
vec2 calculate_resultant_force_planet(system_t *system, uint32_t planet_index) {
    vec2 resultant_force = vec2_create_zero(); // Initialisation de la force résultante à zéro
    // Calculer la force avec les autres planètes du système
    for (uint32_t i = 0; i < system->nb_planets; i++) {
        if (i != planet_index) {
            vec2 force = calculate_gravitational_force(system->planets[planet_index], system->planets[i]); // Calcul de la force gravitationnelle avec une autre planète
            resultant_force = vec2_add(resultant_force, force); // Addition de la force calculée à la force résultante
        }
    }
    vec2 force_from_sun = calculate_gravitational_force(system->planets[planet_index], system->star); // Calcul de la force gravitationnelle avec le soleil
    resultant_force = vec2_add(resultant_force, force_from_sun); // Addition de la force du soleil à la force résultante
    return resultant_force; 
}


vec2 acceleration(planet_t planet, vec2 resultant_force)
{
    return vec2_div(resultant_force,planet.mass); // F = m*a => a = F/m 
}

void update_pos(planet_t *planet, vec2 acceleration, double delta_t)
{
    vec2 new_pos;

    // formule donnée dans l'énoncé
    new_pos = vec2_add(vec2_mul(2, planet->pos), vec2_sub(vec2_mul(-1, planet->prec_pos), vec2_mul(delta_t * delta_t, acceleration)));

    planet->prec_pos = planet->pos;
    planet->pos = new_pos;
}

vec2 create_vect_perpendiculaire(vec2 vect){
    return vec2_create(-vect.y, vect.x);
}

vec2 init_planet_speed(system_t *system, planet_t planet){
    vec2 vect_pos = vec2_sub(planet.pos, system->star.pos);
    vec2 vect_perpendiculaire = create_vect_perpendiculaire(vect_pos);
    double calc = sqrt((G * system->star.mass * (1 + planet.excentricity)) / (planet.axis * (1 - planet.excentricity)));
    vec2 v0 = vec2_mul(calc, vec2_normalize(vect_perpendiculaire));

    return v0;
}

void update_initial_position(system_t *system, double delta_t)
{
    for (uint32_t i = 0; i < system->nb_planets; i++)
    {
        // Calcul de la vitesse initiale à la périhélie
        vec2 vitesse_init = init_planet_speed(system, system->planets[i]);

        // Calcul de la force résultante et de l'accélération
        vec2 force_res = calculate_resultant_force_planet(system, i);
        vec2 acc = vec2_mul(1.0 / system->planets[i].mass, force_res);

        // Mise à jour de la position à t + Δt en utilisant
        vec2 deplacement = vec2_mul(delta_t, vitesse_init);
        vec2 terme_acceleration = vec2_mul(0.5 * pow(delta_t, 2), acc);
        system->planets[i].pos = vec2_add(vec2_add(system->planets[i].pos, deplacement), terme_acceleration);
    }
}

system_t create_system(double mass[], double axis[], double excentricity[], double radius[], int color[], double delta_t)
{
    system_t system;
    system.nb_planets = NB_PLANETS;

    system.planets = malloc(sizeof(planet_t) * (system.nb_planets));

    for (uint32_t i = 0; i < system.nb_planets + 1; i++) // i in [0, nb_planets + 1[ -> car on créer le soleil 
    {
        if (0 == i)
        {
            system.star = create_planet(mass[i], axis[i], excentricity[i], radius[i], color[i]);
        }
        else{
            system.planets[i - 1] = create_planet(mass[i], axis[i], excentricity[i], radius[i], color[i]);
        }
    }

    update_initial_position(&system, delta_t);
    return system;
}

void addPoint(coordinates ptn, planet_t *planet, int index){
    if (index < SIZE_POINT - 1){
        planet->pointsList[index] = ptn;
    }
    else{
        for(int i = 0; i < SIZE_POINT - 1; i++)
        {
            planet->pointsList[i] = planet->pointsList[i + 1];
        }
        planet->pointsList[index] = ptn;
    }
}

void show_system(struct gfx_context_t *ctxt, system_t *system, int width, int height, int ind) {
    // Display the sun
    coordinates coordinates_sun = vec2_to_coordinates(system->star.pos, width, height);
    draw_full_circle(ctxt, coordinates_sun.column, coordinates_sun.row, system->star.radius, system->star.color);

    // Display the planets
    for (uint32_t i = 0; i < system->nb_planets; i++) {
        coordinates coordinates_planet = vec2_to_coordinates(vec_to_position_display(system->planets[i].pos, RS), width, height);
        addPoint(coordinates_planet, &(system->planets[i]), ind);
        draw_full_circle(ctxt, coordinates_planet.column, coordinates_planet.row, system->planets[i].radius, system->planets[i].color);
    }
}

void show_trajectory_point_methods(struct gfx_context_t *ctxt, system_t *system, int ind){
    // display the trajectory of each planets
    for (uint32_t i = 0; i < system->nb_planets; i++) {
        for (int32_t a = 0; a < ind; a++){
            gfx_putpixel(ctxt, system->planets[i].pointsList[a].column, system->planets[i].pointsList[a].row, system->planets[i].color);
        }
    }
}

void update_system(system_t *system, double delta_t)
{
    for (uint32_t i = 0; i < system->nb_planets; i++)
    {
        vec2 force_res = calculate_resultant_force_planet(system, i);

        vec2 acc = acceleration(system->planets[i], force_res);

        update_pos(&system->planets[i], acc, delta_t);
    }
}

void free_system(system_t *system)
{
    for (uint16_t i = 0; i < system->nb_planets; i++)
    {
        free(system->planets[i].pointsList);
        system->planets[i].pointsList = NULL;
    }
    free(system->star.pointsList);
    free(system->planets);
    system->planets = NULL;
}

void calcRevolution(system_t *sys, long *tab, long it){
    if (CALCULATE_REV == 1){
        int start = 100; // permet d'augmenter la précision
        for (uint32_t i = 0; i < sys->nb_planets; i++)
        {
            if (it <= start){
                sys->planets[i].first_pos = sys->planets[i].pos;
            }
            else{
                if (vec2_is_approx_equal(sys->planets[i].pos, sys->planets[i].first_pos, 80000000) && tab[i] == -1){
                    tab[i] = it - start;
                    break;
                }
            }
        }
    }
}

double calcAverage(int tableau[], int taille) {
    double somme = 0.0;
    for (int i = 0; i < taille; i++) {
        somme += tableau[i];
    }
    return somme / taille;
}