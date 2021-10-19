
#include "stdafx.h"
#include "core/ChunkyVoxelsEntry.h"
#include "core/ChunkyVoxelsMain.h"
#include "helpers/Globals.h"

#include <io.h>
#include <fcntl.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

#if CV_DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    SetStdOutToNewConsole();
    char buffer[_MAX_U64TOSTR_BASE2_COUNT];
    float elapsedTime = 0.0f;
#endif
    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GAMECORE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAMECORE));

    MSG msg;
    float gameTime = 0.0f;
    myTimer.Reset();
    // Main message loop:
    int i = 0;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        gameTime = myTimer.GetDeltaTime();

        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        ChunkyVoxelsMain::getInstance().tick(gameTime);
#if CV_DEBUG
        elapsedTime += gameTime;
        if (elapsedTime > 1.0f)
        {
            _itoa_s(myTimer.GetFPS(), buffer, _countof(buffer), 10);
            printf("FPS: %s - fDt: %f - Frames: %d\n", buffer, gameTime, i);
            elapsedTime = 0.0f;
            i = 0;
        }
#endif

        myTimer.Update();
        ++i;
    }

    ChunkyVoxelsMain::getInstance().shutdown();

    return (int) msg.wParam;
}

void SetStdOutToNewConsole()
{
    AllocConsole();
    AttachConsole(GetCurrentProcessId());
    FILE* ptr = stdout;
    freopen_s(&ptr, "CON", "w", stdout);

    HANDLE outh = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize = { 160, 51 };
    SetConsoleScreenBufferSize(outh, bufferSize);
    SMALL_RECT consoleSize = { 0, 0, 159, 50 };
    SetConsoleWindowInfo(outh, TRUE, &consoleSize);
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAMECORE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowEx(NULL, szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT, Globals::getInstance().getWindowWidth(),
      Globals::getInstance().getWindowHeight(), NULL, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   ChunkyVoxelsMain::getInstance().initialize(hWnd, hInstance);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        break;
    case WM_PAINT:
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}