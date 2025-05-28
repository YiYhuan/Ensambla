#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>

const int WIDTH = 800;
const int HEIGHT = 600;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
TTF_Font* font = nullptr;
SDL_Texture* logoTexture = nullptr;

SDL_Color white = {255, 255, 255, 255};
SDL_Color gray = {200, 200, 200, 255};
SDL_Color blue = {32, 79, 191, 255};

void drawText(const std::string& message, int x, int y, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Blended(font, message.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dst = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &dst);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void drawLoginUI() {
    SDL_SetRenderDrawColor(renderer, blue.r, blue.g, blue.b, blue.a);
    SDL_RenderClear(renderer);

    // Mostrar logo centrado arriba
    if (logoTexture) {
        SDL_Rect logoRect;
        logoRect.w = 80;
        logoRect.h = 80;
        logoRect.x = (WIDTH - logoRect.w) / 2;
        logoRect.y = 60;
        SDL_RenderCopy(renderer, logoTexture, nullptr, &logoRect);
    }

    // Cuadros de texto
    SDL_Rect username = {WIDTH / 2 - 150, 200, 300, 40};
    SDL_Rect password = {WIDTH / 2 - 150, 260, 300, 40};
    SDL_Rect loginBtn = {WIDTH / 2 - 150, 320, 300, 45};

    SDL_SetRenderDrawColor(renderer, white.r, white.g, white.b, white.a);
    SDL_RenderDrawRect(renderer, &username);
    SDL_RenderDrawRect(renderer, &password);

    SDL_RenderFillRect(renderer, &loginBtn);
    SDL_SetRenderDrawColor(renderer, blue.r, blue.g, blue.b, blue.a);
    SDL_RenderDrawRect(renderer, &loginBtn);

    // Textos
    drawText("USERNAME", username.x + 10, username.y + 10, gray);
    drawText("PASSWORD", password.x + 10, password.y + 10, gray);
    drawText("LOGIN", loginBtn.x + 110, loginBtn.y + 10, blue);
    drawText("Forgot password?", loginBtn.x + 85, loginBtn.y + 60, white);
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);

    window = SDL_CreateWindow("Login UI", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    font = TTF_OpenFont("/home/yiyhuan/Desktop/Ensambla/Ensambla/GUI/Roboto/Roboto-Italic-VariableFont_wdth,wght.ttf", 18);
    if (!font) {
        SDL_Log("Error loading font: %s", TTF_GetError());
        return 1;
    }

    SDL_Surface* logoSurface = IMG_Load("/home/yiyhuan/Desktop/Ensambla/Ensambla/GUI/black-dog-logo-vector_10577271.png");
    if (!logoSurface) {
        SDL_Log("Error loading logo.png: %s", IMG_GetError());
    } else {
        logoTexture = SDL_CreateTextureFromSurface(renderer, logoSurface);
        SDL_FreeSurface(logoSurface);
    }

    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
        }

        drawLoginUI();
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    if (logoTexture) SDL_DestroyTexture(logoTexture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}