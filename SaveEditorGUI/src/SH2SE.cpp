#include <Windows.h>
#include <iostream>

#include "Application/Application.h"

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow )
{
    try
    {
        SH2SaveEdtitor::Application::getInstance().run();
    } catch (const std::exception& e) {
        MessageBoxA(NULL, e.what(), "Ooops", MB_OK);
        return 1;
    }

    return 0;
}