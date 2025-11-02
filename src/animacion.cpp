#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/color.hpp>
#include <thread>
#include <chrono>
#include <iostream>
#include <Dibujo.hpp>
#include <GestorDibujos.hpp>
#include <Corral.hpp> 
using namespace ftxui;

int main()
{
    auto screen = Screen::Create(
        Dimension::Fixed(80),
        Dimension::Fixed(24));

    // Elementos de la animacion

    const std::vector<std::u32string> f1_car = {
        U"#%...=##+.....",
        U" -@@@%%%%%%%#=#@#%*"};
    const std::vector<std::u32string> publico1 = {
        U" /o\\ ",
        U"  |  ",
        U" / \\ "};
    const std::vector<std::u32string> bandera_frame1 = {
        U" ^- ",
        U" |o|",
        U" |/ ",
        U" /| "};
    const std::vector<std::u32string> bandera_frame2 = {
        U" -^ ",
        U" |o|",
        U" \\| ",
        U" /| "};
    const std::vector<std::u32string> carretera = {
        std::u32string(80, U'=')};
    const std::vector<std::u32string> texto_titulo = {
        U" _____ _    ____ ____    __  __ _______  _____ ____ ___  ",
        U"|  ___/ |  / ___|  _ \\  |  \\/  | ____\\ \\/ /_ _/ ___/ _ \\ ",
        U"| |_  | | | |  _| |_) | | |\\/| |  _|  \\  / | | |  | | | |",
        U"|  _| | | | |_| |  __/  | |  | | |___ /  \\ | | |__| |_| |",
        U"|_|   |_|  \\____|_|     |_|  |_|_____/_/\\_\\___\____\\___/ "
    };
    GestorDibujos gestor;
    int screen_center_x = screen.dimx() / 2;
    int title_width = texto_titulo[0].size();
    gestor.Agregar(Dibujo(screen_center_x - title_width / 2, 2, texto_titulo, ftxui::Color::White));   
    gestor.Agregar(Dibujo(0, 15, carretera, ftxui::Color::GrayDark)); 
    gestor.Agregar(Dibujo(2, 13, f1_car, ftxui::Color::Red));         
    gestor.Agregar(Dibujo(-15, 13, f1_car, ftxui::Color::Red));      
    gestor.Agregar(Dibujo(5, 18, bandera_frame1, ftxui::Color::White)); 
    gestor.Agregar(Dibujo(25, 17, bandera_frame2, ftxui::Color::White)); 
    gestor.Agregar(Dibujo(15, 20, publico1, ftxui::Color::Green));   
    gestor.Agregar(Dibujo(35, 21, publico1, ftxui::Color::Yellow));  

    // Bucle de animacion 

    int frames = 200; 
    int car_width = f1_car[0].size(); 

    for (int frame = 0; frame < frames; ++frame)
    {
        screen.Clear();
        gestor.dibujos[2].x = frame % (screen.dimx() - car_width); 
        gestor.dibujos[3].x = -15 + (frame % (screen.dimx() - car_width + 15));         
        gestor.dibujos[6].x = 15 + (frame % 7) - 3; 
        gestor.dibujos[7].x = 35 - (frame % 7) + 3; 
        if ((frame % 10) < 5) {
            gestor.dibujos[4].figura = bandera_frame1; 
            gestor.dibujos[5].figura = bandera_frame2; 
        } else {
            gestor.dibujos[4].figura = bandera_frame2; 
            gestor.dibujos[5].figura = bandera_frame1; 
        }
        gestor.DibujarTodos(screen);
        std::cout << screen.ToString();
        std::cout << screen.ResetPosition();
        std::cout << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
}