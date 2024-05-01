
#pragma once

#include <application.hpp>
#include <shader/shader.hpp>
#include <texture/texture2d.hpp>
#include <texture/texture-utils.hpp>
#include <material/material.hpp>
#include <mesh/mesh.hpp>

#include <functional>
#include <array>

#include "menu-state.hpp"

class MainMenuState : public our::State{

    std::vector<our::Texture2D*> main_menu_tex;
    our::Texture2D* main_menu_logo;
    our::Texture2D* button_style;
    ImFont* genhsinFont;
    int main_menu_index = 0;
    float accumaltedTime = 0;

    void onInitialize() override {
        for(int i = 0; i < 50; i++) {
            std::string path = "assets/textures/main_menu/frame_" + std::to_string(i);
            path += "_delay-0.1s.png";
            main_menu_tex.push_back(our::texture_utils::loadImage(path));
        }
        main_menu_logo = our::texture_utils::loadImage("assets/textures/main_menu/main_menu.png");
        button_style = our::texture_utils::loadImage("assets/textures/button_style.png");
        ImGuiIO& io = ImGui::GetIO();

        // Load default font (optional, for fallback)
        io.Fonts->AddFontDefault();

        // Load a custom font from a file
        const char* font_filename = "assets/fonts/genshin.ttf";
        genhsinFont = io.Fonts->AddFontFromFileTTF(font_filename, 13.0f); // 16 pixels size

        // Build the font atlas (important for rendering)
        io.Fonts->Build();

        ImGuiStyle& style = ImGui::GetStyle();
        style.FrameRounding = 100.0f;
    }

    void onImmediateGui() override {

        static float tempx = 0;
        static float tempy = 0;
        static float posx = 0;
        static float posy = 0;
        auto key = getApp()->getKeyboard();
        if(key.isPressed(GLFW_KEY_1)) {
            tempx +=0.5f;
            std::cout<<"sizex=" <<tempx<<std::endl;
        }
        if(key.isPressed(GLFW_KEY_2)) {
            tempy +=0.5f;
            std::cout<<"sizey=" <<tempy<<std::endl;
        }
        if(key.isPressed(GLFW_KEY_3)) {
            tempx -=0.5f;
            std::cout<<"sizex=" <<tempx<<std::endl;
        }
        if(key.isPressed(GLFW_KEY_4)) {
            tempy -=0.5f;
            std::cout<<"sizey=" <<tempy<<std::endl;
        }
        if(key.isPressed(GLFW_KEY_5)) {
            posx +=0.5f;
            std::cout<<"posx=" <<posx<<std::endl;
        }
        if(key.isPressed(GLFW_KEY_6)) {
            posy +=0.05f;
            std::cout<<"posy=" <<posy<<std::endl;
        }
        if(key.isPressed(GLFW_KEY_7)) {
            posx -=0.5f;
            std::cout<<"posx=" <<posx<<std::endl;
        }
        if(key.isPressed(GLFW_KEY_8)) {
            posy -=0.05f;
            std::cout<<"posy=" <<posy<<std::endl;
        }

        ImGui::PushFont(genhsinFont);
        ImGui::Begin("main_menu" , nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollWithMouse
            | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar
            | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground);
        ImGui::SetWindowFontScale(3);
        ImGui::SetWindowSize({1280,720});
        ImGui::SetWindowPos({0,0});

        GLuint id = main_menu_tex[main_menu_index < 50 ? main_menu_index : 99 - main_menu_index]->getOpenGLName();
        ImGui::SetCursorPos({0,0});
        ImGui::Image((void*)id,{1280,720},{0,1},{1,0});

        GLuint logo_id = main_menu_logo->getOpenGLName();
        ImGui::SetCursorPos({0,0});
        ImGui::Image((void*)logo_id,{1280,720},{0,1},{1,0});

        ImGui::SetCursorPos({1280/2 - 140/2,500});

        if(ImGui::Button("Start",{140,0})) {
            getApp()->changeState("play");
        }

        GLuint style_id = button_style->getOpenGLName();

        ImGui::SetCursorPos({1280/2 - 140/2 + 100,500 - 16});
        ImGui::Image((void*)style_id,{50.0f,50.0f},{0,1},{1,0});

        ImGui::SetCursorPos({1280/2 - 140/2,500 + 80});

        if(ImGui::Button("Exit",{140,0})) {
            getApp()->close();
        }

        ImGui::SetCursorPos({1280/2 - 140/2 + 100,500 + 80 - 16});
        ImGui::Image((void*)style_id,{50.0f,50.0f},{0,1},{1,0});


        ImGui::End();
        ImGui::PopFont();
    }

    void onDraw(double deltaTime) override {
        accumaltedTime += deltaTime;
        if(accumaltedTime > 0.1f) {
            accumaltedTime = 0.0f;
            main_menu_index++;
            main_menu_index %= 100;
        }
    }

    void onDestroy() override {

    }
};

