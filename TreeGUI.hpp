#ifndef TREEGUI_H
#define TREEGUI_H

#include "Node.hpp"  
using namespace ariel;

#include <SDL2/SDL.h>    // SDL2 library for graphics
#include <SDL2/SDL_ttf.h>  // SDL2_ttf library for text rendering

#include <string>
#include <sstream>

template <typename T>
class TreeGUI
{
private:
    Node<T> *root;    
    SDL_Window *window;   // SDL window for displaying graphics
    SDL_Renderer *renderer;  // SDL renderer for drawing graphics
    TTF_Font *font;       // Font for text rendering
    SDL_Color textColor;  // Color for text rendering
    int width;            // Width of the window
    int height;           // Height of the window
    int nodeRadius;       
    int nodeSpacing;      // Spacing between tree nodes
    int heightSpacing = 30;  // Vertical spacing between tree levels

    // Function to draw the circle at point (x,y)
    void drawCircle(int x, int y, int radius)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Set color to black
        for (int i = 0; i < radius * 2; i++) // Draw circle using midpoint circle algorithm
        {
            for (int j = 0; j < radius * 2; j++)
            {
                int dx = radius - i; // distance from -radius to +radius in x axis 
                int dy = radius - j; // distance from -radius to +radius in y axis
                if ((dx * dx + dy * dy) <= (radius * radius)) // Check if point is inside circle
                {
                    SDL_RenderDrawPoint(renderer, x + dx, y + dy);  // Draw pixel
                }
            }
        }
    }

    // Function to add text at point(x,y)
    void addText(int x, int y, const std::string &text)
    {
        SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), textColor);  // Render text surface
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);  // Creates texture from the surface to show in renderer
        SDL_Rect rect = {x, y, surface->w, surface->h};  // Creates a rect at position (x,y) with width and height of surface for rendering text
        SDL_RenderCopy(renderer, texture, nullptr, &rect);  // Copy texture to renderer at rect position
        SDL_FreeSurface(surface);  // Free surface memory
        SDL_DestroyTexture(texture);  // Destroy texture memory
    }

    // Function to recursively draw the tree starting from a node
    void drawTree(Node<T> *node, int depth, int left, int right)
    {
        int x = (left + right) / 2;  // Calculate x-coordinate for node
        int y = depth * (nodeRadius * 2 + nodeSpacing) + nodeRadius + heightSpacing;  // Calculate y-coordinate for node

        drawCircle(x, y, nodeRadius);  // Draw node circle

        // Convert node value to string
        std::stringstream ss;
        ss << node->getValue();
        std::string text = ss.str();

        int textWidth, textHeight;
        TTF_SizeText(font, text.c_str(), &textWidth, &textHeight);  // Get text size
        addText(x - textWidth / 2, y - textHeight - nodeRadius, text);  // Add text above node

        // Draw lines to children nodes and recursively draw children
        for (int i = 0; i < node->getChildren().size(); i++)
        {
            int childLeft = left + (right - left) * i / (int)node->getChildren().size();
            int childRight = left + (right - left) * (i + 1) / (int)node->getChildren().size();
            SDL_RenderDrawLine(renderer, x, y, (childLeft + childRight) / 2, y + nodeSpacing + nodeRadius * 2);  // Draw line to child node
            drawTree(node->getChildren()[size_t(i)], depth + 1, childLeft, childRight);  // Recursively draw child node
        }
    }

public:
    // Constructor initializes SDL, SDL_ttf, window, renderer, and font
    TreeGUI(Node<T> *root)
    {
        this->root = root;  
        width = 1024;  
        height = 768;  
        nodeRadius = 15;  
        nodeSpacing = 20;  // node spacing between nodes used for levels differnce
        textColor = {0, 0, 0, 255};  // Set text color (black)

        /*  Initialize SDL.
            SDL_INIT_VIDEO flag is used to initialize SDL video mode. in case we want to support live tree changes.
        */
        if (SDL_Init(SDL_INIT_VIDEO) != 0) // couldn't initialize SDL
        {
            std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
            exit(1);
        }

        // Initialize SDL_ttf
        if (TTF_Init() != 0) // couldn't initialize SDL_ttf
        {
            std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
            exit(1);
        }

        // Create SDL window
        window = SDL_CreateWindow("Tree", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
        if (window == nullptr) // couldn't create the window
        {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            exit(1);
        }

        // Create SDL renderer
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == nullptr) // couldn't create the renderer
        {
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl; 
            exit(1); 
        }

        // Open font for text rendering
        font = TTF_OpenFont("arial.ttf", 24);  //  "arial.ttf" must be in the directory of the program
        if (font == nullptr) // couldn't open the font
        {
            std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
            exit(1);
        }
    };

    // Destructor cleans up SDL and SDL_ttf resources
    ~TreeGUI()
    {
        TTF_CloseFont(font);  // Close font
        SDL_DestroyRenderer(renderer);  // Destroy renderer
        SDL_DestroyWindow(window);  // Destroy window
        TTF_Quit();  // Quit SDL_ttf
        SDL_Quit();  // Quit SDL
    };

    // Draw the tree on the renderer and present it
    void draw()
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Set background color to white
        SDL_RenderClear(renderer);  // clearing the renderer with white color (background)
        drawTree(root, 0, 0, width);  // Draw tree starting from root (using recursive function)
        SDL_RenderPresent(renderer);  // Show the tree
    }

    // Display the tree and handle events until quit
    void display()
    {
        bool quit = false; // condition the quit the loop
        SDL_Event event;  // event to to handle the user input

        draw();  // Initial tree drawing

        while (!quit)
        {
            while (SDL_PollEvent(&event))  // wait for event
            {
                if (event.type == SDL_QUIT)  // if user press the close button
                {
                    quit = true;  // Set quit flag to true and return
                }
            }
        }
    }

    // Set the root of the tree
    void setRoot(Node<T> *root)
    {
        this->root = root;  
    }

    // Set the width of the window
    void setWidth(int width)
    {
        this->width = width; 
    }

    // Set the height of the window
    void setHeight(int height)
    {
        this->height = height;  
    }
};

#endif // TREEGUI_H

