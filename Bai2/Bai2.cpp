// Bai2.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Bai2.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HMENU Main;
// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_BAI2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BAI2));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BAI2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName = NULL;
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
   Main = LoadMenu(hInst, MAKEINTRESOURCE(IDC_BAI2));
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, Main, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

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
    static HPEN hPen = CreatePen(PS_SOLID, 1, 0);
    static HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
    static HDC hdcDraw;
    static int Hinh, xLeft, yTop, xRight, yBottom;
    switch (message)
    {
    case WM_LBUTTONDOWN:
    {
        xLeft = LOWORD(lParam);
        yTop = HIWORD(lParam);
    }
    break;
    case WM_LBUTTONUP:
    {
        xRight = LOWORD(lParam);
        yBottom = HIWORD(lParam);
        POINT pt[4];
        hdcDraw = GetDC(hWnd);
        SelectObject(hdcDraw, hBrush);
        SelectObject(hdcDraw, hPen);
        switch (Hinh)
        {
        case ID_SHAPE_TRIA:
            pt[0].x = xLeft + (xRight - xLeft) / 2;
            pt[0].y = yTop;
            pt[1].x = xLeft;
            pt[1].y = yBottom;
            pt[2].x = xRight;
            pt[2].y = yBottom;
            Polygon(hdcDraw, pt, 3);
            break;
        case ID_SHAPE_REC:
            Rectangle(hdcDraw, xLeft, yTop, xRight, yBottom);
            break;
        case ID_SHAPE_ELL:
            Ellipse(hdcDraw, xLeft, yTop, xRight, yBottom);
            break;
        case ID_SHAPE_RHO:
            pt[0].x = xLeft + (xRight - xLeft) / 2;
            pt[0].y = yTop;
            pt[1].x = xLeft;
            pt[1].y = yTop + (yBottom - yTop) / 2;
            pt[2].x = xLeft + (xRight - xLeft) / 2;
            pt[2].y = yBottom;
            pt[3].x = xRight;
            pt[3].y = yTop + (yBottom - yTop) / 2;
            Polygon(hdcDraw, pt, 4);
            break;
        default:
            break;
        }
    }
    break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case ID_SHAPE_TRIA:
                CheckMenuItem(Main, ID_SHAPE_TRIA, MF_CHECKED);
                CheckMenuItem(Main, ID_SHAPE_REC, MF_UNCHECKED);
                CheckMenuItem(Main, ID_SHAPE_ELL, MF_UNCHECKED);
                CheckMenuItem(Main, ID_SHAPE_RHO, MF_UNCHECKED);
                Hinh = ID_SHAPE_TRIA;
                break;
            case ID_SHAPE_REC:
                CheckMenuItem(Main, ID_SHAPE_TRIA, MF_UNCHECKED);
                CheckMenuItem(Main, ID_SHAPE_REC, MF_CHECKED);
                CheckMenuItem(Main, ID_SHAPE_ELL, MF_UNCHECKED);
                CheckMenuItem(Main, ID_SHAPE_RHO, MF_UNCHECKED);
                Hinh = ID_SHAPE_REC;
                break;
            case ID_SHAPE_ELL:
                CheckMenuItem(Main, ID_SHAPE_TRIA, MF_UNCHECKED);
                CheckMenuItem(Main, ID_SHAPE_REC, MF_UNCHECKED);
                CheckMenuItem(Main, ID_SHAPE_ELL, MF_CHECKED);
                CheckMenuItem(Main, ID_SHAPE_RHO, MF_UNCHECKED);
                Hinh = ID_SHAPE_ELL;
                break;
            case ID_SHAPE_RHO:
                CheckMenuItem(Main, ID_SHAPE_TRIA, MF_UNCHECKED);
                CheckMenuItem(Main, ID_SHAPE_REC, MF_UNCHECKED);
                CheckMenuItem(Main, ID_SHAPE_ELL, MF_UNCHECKED);
                CheckMenuItem(Main, ID_SHAPE_RHO, MF_CHECKED);
                Hinh = ID_SHAPE_RHO;
                break;
            case ID_COLOR_BLUE:
                CheckMenuItem(Main, ID_COLOR_BLUE, MF_CHECKED);
                CheckMenuItem(Main, ID_COLOR_RED, MF_UNCHECKED);
                hPen = CreatePen(PS_SOLID, 1, (0, 0, 255));
                break;
            case ID_COLOR_RED:
                CheckMenuItem(Main, ID_COLOR_RED, MF_CHECKED);
                CheckMenuItem(Main, ID_COLOR_BLUE, MF_UNCHECKED);
                hPen = CreatePen(PS_SOLID, 1, (255, 0, 0));
                break;
            case ID_COLOR_YELLOW:
                CheckMenuItem(Main, ID_COLOR_YELLOW, MF_CHECKED);
                CheckMenuItem(Main, ID_COLOR_GREEN, MF_UNCHECKED);
                hBrush = CreateSolidBrush(RGB(255, 255, 0));
                break;
            case ID_COLOR_GREEN:
                CheckMenuItem(Main, ID_COLOR_GREEN, MF_CHECKED);
                CheckMenuItem(Main, ID_COLOR_YELLOW, MF_UNCHECKED);
                hBrush = CreateSolidBrush(RGB(0, 255, 0));
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
