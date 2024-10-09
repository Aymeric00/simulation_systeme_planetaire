#include "gfx/gfx.h"
#include "vec2/vec2.h"
#include "planet/planet.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

double m_soleil;
double m_terre;
double m_mars;
double m_atlas;
long it = 0;

int main()
{   
    int index = 0;
    
    // Gestion des scénarios voir rapport
    if (1 == SCENERIO){
        m_soleil = 1.989e30;
        m_terre = 5.972e24;
        m_mars = 6.39e23;
        m_atlas = 3 * m_terre;
    }
    else if (2 == SCENERIO){
        m_soleil = 0;
        m_terre = 5.972e24;
        m_mars = 6.39e23;
        m_atlas = 3 * m_terre;
    }
    else{
        m_soleil = 1.989e30;
        m_terre = 6.39e27;
        m_mars = 6.39e27;
        m_atlas = 3 * m_terre;
    }

    double mass[] = {m_soleil, M_MERCURE, M_VENUS, m_terre, m_mars, m_atlas, M_VIBRANIUM};
    double demi_axes[] = {DA_SOLEIL, DA_MERCURE, DA_VENUS, DA_TERRE, DA_MARS, DA_ATLAS, DA_VIBRANIUM};
    double excentricites[] = {E_SOLEIL, E_MERCURE, E_VENUS, E_TERRE, E_MARS, E_ATLAS, E_VIBRANIUM};
    double radius[] = {R_SOLEIL, R_MERCURE, R_VENUS, R_TERRE, R_MARS, R_ATLAS, R_VIBRANIUM};
    int couleurs[] = {COLOR_GOLDEN_ROD, COLOR_BROWN, COLOR_LIGHT_SALMON, COLOR_BLUE, COLOR_ORANGE_RED, COLOR_DARK_CYAN, COLOR_GREEN};
    double delta_t = 10000;

    struct gfx_context_t *ctxt = gfx_create("Planetary system", SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!ctxt)
    {
        fprintf(stderr, "Graphics initialization failed!\n");
        return EXIT_FAILURE;
    }

    system_t solar_system;
    solar_system = create_system(mass, demi_axes, excentricites, radius, couleurs, delta_t);
    long tab[] = {-1, -1, -1, -1, -1, -1, -1};

    while (true)
    {
        show_system(ctxt, &solar_system, SCREEN_WIDTH, SCREEN_HEIGHT, index);
        update_system(&solar_system, delta_t);
        gfx_present(ctxt);
        gfx_clear(ctxt, COLOR_BLACK);
        show_trajectory_point_methods(ctxt, &solar_system, index);
        it++;
        calcRevolution(&solar_system, tab, it);
        
        if (SIZE_POINT - 1 > index){
            index++;
        }
        if (gfx_keypressed() == SDLK_ESCAPE)
        {
            if (CALCULATE_REV == 1){
                for (uint32_t i = 0; i < solar_system.nb_planets; i++)
                {
                    printf("%ld | ", tab[i]);
                }
            }
            break;
        }
    }
    free_system(&solar_system);
    gfx_destroy(ctxt);
    return EXIT_SUCCESS;
}