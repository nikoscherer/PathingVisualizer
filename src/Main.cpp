#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <Python.h>
#include <filesystem>
#include <queue>
#include <iostream>
#include "../include/common/Map.h"
#include "../include/common/Node.h"
#include "../include/algorithms/AStar.h"
#include "../include/common/Utils.h"
#include "../include/common/OSMWrapper.h"

// Settings
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 1280;


// Constants
Color YELLOW = Color(255, 255, 0, 255);
Color WHITE = Color(200, 200, 200, 255);

Color DARK_GRAY = Color(50, 50, 50, 255);


std::vector<Node> n;
std::vector<Node*> nodes;
Map map;


OSMWrapper osmWrapper;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;


bool search = false;

bool initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("PathingVisualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        printf("Window could not be created! SDL_Error %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void DrawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w; // Horizontal distance from center
            int dy = radius - h; // Vertical distance from center
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
            }
        }
    }
}

void render() {
    SDL_SetRenderDrawColor(renderer, WHITE.red(), WHITE.green(), WHITE.blue(), WHITE.alpha());

    while (!map.updatedNodes.empty()) {
        Node* vert = map.updatedNodes.front();
        std::vector<int> vertCoords = map.calculateScreenCoordinates(vert->x, vert->y);

        for (auto id = vert->neighbors.begin(); id != vert->neighbors.end(); ++id) {
            Node* neighbor = map.vertMap[*id];

            std::vector<int> neighborCoords = map.calculateScreenCoordinates(neighbor->x, neighbor->y);
            SDL_RenderDrawLine(renderer, vertCoords[0], vertCoords[1], neighborCoords[0], neighborCoords[1]);
        }

        if (map.algorithm.visited.count(vert->id)) {
            SDL_SetRenderDrawColor(renderer, YELLOW.red(), YELLOW.green(), YELLOW.blue(), YELLOW.alpha());
        }
        DrawCircle(renderer, vertCoords[0], vertCoords[1], 2);

        map.updatedNodes.pop();
        SDL_SetRenderDrawColor(renderer, WHITE.red(), WHITE.green(), WHITE.blue(), WHITE.alpha());
    }

    SDL_RenderPresent(renderer);
}

void update() {
    render();

    if (search) {
        std::cout << "Searching" << std::endl;
    }

    SDL_Delay(10);
}

int main(int argc, char* args[])
{
    std::vector<double> location = { -93.222570, 45.057988 };
    std::vector<double> bbox = { 0.001, 0.001 };

    osmWrapper.init();

    n = osmWrapper.getRoadData(location[0], location[1], bbox);

    bool running = true;

    SDL_Event event;

    for (auto& node : n) {
        nodes.push_back(&node);
    }

    map = Map(nodes, { SCREEN_WIDTH, SCREEN_HEIGHT }, bbox, location);
    
    if (!initSDL()) {
        std::cout << "SDL Failed to Initialize!" << std::endl;
        return -1;
    }

    SDL_SetRenderDrawColor(renderer, DARK_GRAY.red(), DARK_GRAY.green(), DARK_GRAY.blue(), DARK_GRAY.alpha());
    SDL_RenderClear(renderer);

    while (running) {
        
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_MOUSEMOTION) {
             /*   Move map with mouse
                int newMouseX = 0;
                int newMouseY = 0;

                SDL_GetMouseState(&newMouseX, &newMouseY);

                map.setCenterX(map.center[0] + double(newMouseX - mouseX) / 10000);
                map.setCenterY(map.center[1] - double(newMouseY - mouseY) / 10000);

                std::vector<double> mapCoords = map.calculateMapCoordinates(mouseX, mouseY);
                std::vector<int> screenCoords = map.calculateScreenCoordinates(mapCoords[0], mapCoords[1]);
                mapCoords = map.calculateMapCoordinates(screenCoords[0], screenCoords[1]);
                screenCoords = map.calculateScreenCoordinates(mapCoords[0], mapCoords[1]);

                mouseX = newMouseX;
                mouseY = newMouseY;*/
            }
            else if (event.type == SDL_MOUSEWHEEL) {
                //    Zoom in and out map
                //map.MAP_SIZE[0] = map.MAP_SIZE[0] - event.wheel.y * (map.MAP_SIZE[0] * 0.05);
                //map.MAP_SIZE[1] = map.MAP_SIZE[1] - event.wheel.y * (map.MAP_SIZE[1] * 0.05);
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_SPACE) {
                    search = true;
                }
                else if (event.key.keysym.sym == SDLK_ESCAPE) {
                    SDL_SetRelativeMouseMode(SDL_FALSE);
                    SDL_SetWindowGrab(window, SDL_FALSE);
                }
            }
        }


        update();

        if (search) {
            map.runAlgorithm();
        }
    }

    SDL_SetRelativeMouseMode(SDL_FALSE);
    SDL_SetWindowGrab(window, SDL_FALSE);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

	return 0;
}
