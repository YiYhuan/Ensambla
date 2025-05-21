#include <Renderer.hpp>
#include <iostream>

Renderer::Renderer() : window(nullptr), renderer(nullptr),
  width(WINDOW_WIDTH), height(WINDOW_HEIGHT) {
  SDL_Rect temp;
  for (int i = 0; i < 11; ++i) {
    menuItemBounds.push_back(temp);
  }
}

Renderer::~Renderer() {
  this->clean();
}

bool Renderer::startSDL() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
    return false;
  }
  // Create the game window
  this->window = SDL_CreateWindow("roguex86", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, this->width,
                                  this->height, SDL_WINDOW_SHOWN);
  if (!this->window) {
    std::cerr << "Error creating the window: " << SDL_GetError() << std::endl;
    return false;
  }
  // Create the renderer
  this->renderer = SDL_CreateRenderer(this->window, -1,
                                       SDL_RENDERER_ACCELERATED);
  if (!this->renderer) {
    std::cerr << "Error creating the renderer: " << SDL_GetError()
      << std::endl;
    return false;
  }
  // Init TTF
  if (TTF_Init() == -1) {
    std::cerr << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
    return false;
  }
  // Load fonts
  this->loadFonts();
  return true;
}

void Renderer::clean() {
  for (TTF_Font* font : this->fonts) {
    if (font) TTF_CloseFont(font);
  }
  if (this->renderer) SDL_DestroyRenderer(this->renderer);
  if (this->window) SDL_DestroyWindow(this->window);
  TTF_Quit();
  SDL_Quit();
}

void Renderer::loadFonts() {
  this->fonts.push_back(loadFont(FONT_PATH, FONT_SIZE_MAIN_MENU));
  this->fonts.push_back(loadFont(FONT_PATH, FONT_SIZE_SUBTITLE));
  this->fonts.push_back(loadFont(FONT_PATH, FONT_SIZE_INSTRUCTION));
  this->fonts.push_back(loadFont(FONT_PATH, FONT_SIZE_PAUSE_MENU));
}

TTF_Font* Renderer::loadFont(const char* fontPath, const int size) {
  TTF_Font* font = TTF_OpenFont(fontPath, size);
  if (!font) {
    std::cerr << "Error loading the font: " << TTF_GetError() << std::endl;
    return nullptr;
  }
  return font;
}

SDL_Texture* Renderer::renderText(const char* message, int font,
                                  SDL_Color color) {
  // Create a surface to render the texture
  SDL_Surface* surface = TTF_RenderText_Solid(this->fonts[font], message,
                                              color);
  if (!surface) {
      std::cout << "Error creating the text surface: " << TTF_GetError()
      << std::endl;
      return nullptr;
  }
  // Render the texture
  SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer, surface);
  SDL_FreeSurface(surface);
  if (!texture) {
      std::cout << "Error creating the text texture: " << SDL_GetError()
      << std::endl;
  }
  return texture;
}

void Renderer::showLoginMenu() {
    
  SDL_Color textColor = {255, 255, 255, 255}; // White color
  // Create the texts to display
  SDL_Texture* title = this->renderText("Refugio", MAIN_MENU_FONT, textColor);
  SDL_Texture* userName = this->renderText("USERNAME", MAIN_MENU_FONT,
                                          textColor);
  SDL_Texture* password = this->renderText("PASSWORD", MAIN_MENU_FONT,
                                          textColor);
  SDL_Texture* login = this->renderText("LOGIN", MAIN_MENU_FONT, textColor);

  SDL_Texture* forgotPassword = this->renderText("Forgot password?", MAIN_MENU_FONT, textColor);
  // Exit if any of them fails
  if (!title || !userName || !password || !login || forgotPassword) return;
  int texW, texH;
  // Centered title
int main(){
  SDL_QueryTexture(title, nullptr, nullptr, &texW, &texH);
  SDL_Rect dstTitle = { (this->width - texW) / 2, MENU_TITLE_Y, texW, texH };
  // Horizontal options
  // "options"
  SDL_QueryTexture(userName, nullptr, nullptr, &texW, &texH);
  SDL_Rect dstUserName = { MENU_LEFT_X, MENU_MIDDLE_Y, texW, texH };
  // "new game"
  SDL_QueryTexture(password, nullptr, nullptr, &texW, &texH);
  SDL_Rect dstPassword = { MENU_MIDDLE_X, MENU_MIDDLE_Y, texW, texH };
  // "EXIT"
  SDL_QueryTexture(login, nullptr, nullptr, &texW, &texH);
  SDL_Rect dstLogin = { MENU_RIGHT_X, MENU_MIDDLE_Y, texW, texH };

  SDL_QueryTexture(forgotPassword, nullptr, nullptr, &texW, &texH);
  SDL_Rect dstForgotPassword = { MENU_RIGHT_X, MENU_MIDDLE_Y, texW, texH };
  // So the InputHandler knows where the buttons are
  storeMenuItemBounds(MENU_ITEM_OPTIONS, dstUserName);
  storeMenuItemBounds(MENU_ITEM_NG, dstPassword);
  storeMenuItemBounds(MENU_ITEM_EXIT, dstLogin);
  storeMenuItemBounds(MENU_ITEM_EXIT, dstForgotPassword);

  SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255); // Black background
  SDL_RenderClear(this->renderer);
  // Draw each option
  SDL_RenderCopy(this->renderer, title, nullptr, &dstTitle);
  SDL_RenderCopy(this->renderer, userName, nullptr, &dstUserName);
  SDL_RenderCopy(this->renderer, password, nullptr, &dstPassword);
  SDL_RenderCopy(this->renderer, login, nullptr, &dstLogin);
  SDL_RenderCopy(this->renderer, forgotPassword, nullptr, &dstForgotPassword);

  // Render the whole thing
  SDL_RenderPresent(this->renderer);
  // Free all the textures
  SDL_DestroyTexture(title);
  SDL_DestroyTexture(userName);
  SDL_DestroyTexture(password);
  SDL_DestroyTexture(login);
  SDL_DestroyTexture(forgotPassword);
}
