#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>

#define PI 3.14159265358979323846
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const double g = 9.78;

double toRadians(double degrees)
{
    return degrees * PI / 180.0;
}

void drawCircle(SDL_Renderer *renderer, int cx, int cy, int radius)
{
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, cx + dx, cy + dy);
            }
        }
    }
}

int main()
{
    double altura_cm, angulo_graus;
    std::cout << "Digite a altura do plano (cm): ";
    std::cin >> altura_cm;
    std::cout << "Digite o ângulo de inclinação (graus): ";
    std::cin >> angulo_graus;

    double altura_m = altura_cm / 100.0;
    double angulo_rad = toRadians(angulo_graus);
    double comprimento = altura_m / sin(angulo_rad);
    double aceleracao = g * sin(angulo_rad);
    double tempo_total = sqrt(2 * comprimento / aceleracao);
    double velocidade_final = aceleracao * tempo_total;

    std::cout << "\n--- Resultados ---\n";
    std::cout << "Comprimento do plano: " << comprimento << " m\n";
    std::cout << "Aceleração: " << aceleracao << " m/s²\n";
    std::cout << "Tempo de descida: " << tempo_total << " s\n";
    std::cout << "Velocidade final: " << velocidade_final << " m/s\n";

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Simulação Plano Inclinado",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int x0 = 100, y0 = 500;
    int x1 = x0 + 600 * cos(angulo_rad);
    int y1 = y0 - 600 * sin(angulo_rad);

    int start_x = x1, start_y = y1;
    int end_x = x0, end_y = y0;

    double t = 0;
    double dt = 0.01;
    bool running = true;
    bool simulacao_terminada = false;

    while (running)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                running = false;
        }

        if (!simulacao_terminada && t <= tempo_total)
        {
            double s = 0.5 * aceleracao * t * t;
            double frac = s / comprimento;
            int obj_x = start_x + frac * (end_x - start_x);
            int obj_y = start_y + frac * (end_y - start_y);

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawLine(renderer, x0, y0, x1, y1);

            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            drawCircle(renderer, obj_x, obj_y, 10);

            SDL_RenderPresent(renderer);
            SDL_Delay(10);

            t += dt;
        }
        else
        {
            if (!simulacao_terminada)
            {
                simulacao_terminada = true;
                std::cout << "\nSimulação concluída! Feche a janela para sair.\n";
            }

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawLine(renderer, x0, y0, x1, y1);

            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            drawCircle(renderer, end_x, end_y, 10);

            SDL_RenderPresent(renderer);
            SDL_Delay(50);
        }
    }

    SDL_DestroyRenderer(renderer);
    return 0;
}