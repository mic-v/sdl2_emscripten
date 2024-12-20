#include <SDL2/SDL.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

struct Context 
{
        SDL_Renderer* renderer;
};

void emscripten_loop(void* arg)
{
        Context* context = static_cast<Context*>(arg);
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
                if(event.type == SDL_QUIT)
                {
                        exit(0);
                }
        }
        SDL_SetRenderDrawColor(context->renderer, 9, 20, 33, 255);
        SDL_RenderClear(context->renderer);
        SDL_RenderPresent(context->renderer);
}

void main_loop(void* arg)
{
        Context* context = static_cast<Context*>(arg);
        SDL_Event event;
        while(true)
        {
                while(SDL_PollEvent(&event))
                {
                        if(event.type == SDL_QUIT)
                        {
                                exit(0);
                        }
                }
                SDL_SetRenderDrawColor(context->renderer, 9, 20, 33, 255);
                SDL_RenderClear(context->renderer);
                SDL_RenderPresent(context->renderer);
        }

}

int main(int argc, char** argv) 
{
        SDL_Init(SDL_INIT_EVERYTHING);

        Context context;
        SDL_Window* window = NULL;
        window = SDL_CreateWindow(
                "SDL2 It's Work!",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        640, 480,
        SDL_WINDOW_SHOWN
        );
        SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
        context.renderer = renderer;
        
        #ifdef __EMSCRIPTEN__
                emscripten_set_main_loop_arg(emscripten_loop, &context, -1, 1);
        #else
                main_loop(&context);
        #endif

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
  //SDL_Quit();
        return 0;
}
