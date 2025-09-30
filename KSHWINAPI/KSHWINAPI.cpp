// KSHWINAPI.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "KSHWINAPI.h"
#include <string>
#include <crtdbg.h>
#include <vector>
#include <algorithm>
#define _CRTDBG_MAP_ALLOC
#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)
#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

Gdiplus::Point g_AppPosition(1000, 1000);
Gdiplus::Point g_ScreenSize(800, 600);

Gdiplus::Point g_HousePosition(100, 100);
constexpr int g_HouseVerticesCount = 7;
const Gdiplus::Point g_HouseVertices[g_HouseVerticesCount] =
{
    {0,-100},{50,-50},{30,-50},{30,0},{-30,0},{-30,-50},{-50,-50}
};
//bool g_bKeyWasPressed
std::unordered_map<InputDirection, bool> g_KeyWasPressedMap;

Gdiplus::Bitmap* g_BackBuffer = nullptr;    // 백버퍼용 종이
Gdiplus::Graphics* g_BackBufferGraphics = nullptr;  // 백버퍼용 종이에 그리기 위한 도구

Gdiplus::Bitmap* g_PlayerImage = nullptr;   // 플레이어가 그려질 종이
constexpr int PlayerImageSize = 64;


// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
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

    // TODO: 여기에 코드를 입력합니다.
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //GDI+ 초기화
    ULONG_PTR Token;
    Gdiplus::GdiplusStartupInput StartupInput;
    Gdiplus::GdiplusStartup(&Token, &StartupInput,nullptr);




    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_KSHWINAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KSHWINAPI));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }


    //GDI+ 정리
    Gdiplus::GdiplusShutdown(Token);
    return (int) msg.wParam;
}
std::vector<int> vec2;


//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KSHWINAPI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName = nullptr;//MAKEINTRESOURCEW(IDC_KSHWINAPI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
                                           //프로그램 타이틀      //전체기능에서        최대화            화면조절기능 해제
   HWND hWnd = CreateWindowW(szWindowClass, L"KSH_WINAPI", WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
      CW_USEDEFAULT, 0, 400, 300, nullptr, nullptr, hInstance, nullptr);
           //시작지점     //화면크기
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
bool isPush = false;
Gdiplus::Point point1(200, 100);
Gdiplus::Point point2(150, 100);
Gdiplus::Point point3(250, 50);
Gdiplus::Point point4(350, 100);
Gdiplus::Point point5(300, 100);
Gdiplus::Point points[5] = { point1, point2,point3,point4,point5 };
int positionWidth = 200;
int positionHeight = 100;
int Width = 100;
int Height = 100;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        // 윈도우가 생성되었을때 날아오는 메시지
        g_BackBuffer = new Gdiplus::Bitmap(g_ScreenSize.X, g_ScreenSize.Y, PixelFormat32bppARGB);
        g_BackBufferGraphics = Gdiplus::Graphics::FromImage(g_BackBuffer);
        if (!g_BackBufferGraphics)
        {
            // 혹시 안만들어졌을 때를 대비한 에러 출력
            MessageBox(hWnd, L"백 버퍼 그래픽스 생성 실패", L"오류", MB_OK | MB_ICONERROR);
        }

        g_PlayerImage = new Gdiplus::Bitmap(L"./images/ship.png"); // 플레이어 이미지 로딩
        if (g_PlayerImage->GetLastStatus() != Gdiplus::Ok)
        {
            // 정상적으로 파일 로딩이 안됬다.
            delete g_PlayerImage;       // 실패했으면 즉시 해제
            g_PlayerImage = nullptr;
            MessageBox(hWnd, L"플레이어 이미지 로드 실패", L"오류", MB_OK | MB_ICONERROR);
        }
        break;
    case WM_DESTROY:
        // 윈도우가 삭제되었을 때 날아오는 메세지
        delete g_BackBufferGraphics;
        g_BackBufferGraphics = nullptr;
        delete g_BackBuffer;
        g_BackBuffer = nullptr;
        PostQuitMessage(0);
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        if (g_BackBufferGraphics)   // g_BackBufferGraphics 필수
        {
            g_BackBufferGraphics->Clear(Gdiplus::Color(255, 0, 0, 0));
            Gdiplus::SolidBrush GreenBrush(Gdiplus::Color(255, 0, 255, 0));
            Gdiplus::SolidBrush BlueBrush(Gdiplus::Color(255, 0, 0, 255));
            Gdiplus::SolidBrush YelloBrush(Gdiplus::Color(255, 255, 255, 0));

            for (int y = 0; y < 2; y++)
            {
                for (int x = 0; x < 10; x++)
                {
                    g_BackBufferGraphics->FillRectangle(&YelloBrush, 30 + 70 * x, 50 + 70 * y, 60, 60);
                }
            }

            Gdiplus::Pen GreenPen(Gdiplus::Color(255, 0, 255, 0), 2.0f);
            Gdiplus::Point Positions[g_HouseVerticesCount];
            for (int i = 0; i < g_HouseVerticesCount; i++)
            {
                Positions[i] = g_HousePosition + g_HouseVertices[i];
            }
            g_BackBufferGraphics->DrawPolygon(&GreenPen, Positions, g_HouseVerticesCount);
            //g_BackBufferGraphics->FillPolygon(&GreenBrush, Positions, g_HouseVerticesCount);
            if (g_PlayerImage) {
                //g_PlayerImage가 로딩되어 있다.
                g_BackBufferGraphics->DrawImage(
                    g_PlayerImage, // 그려질 이미지
                    100, 100, // 그려질 위치
                    PlayerImageSize, PlayerImageSize);
            }
            else {
                Gdiplus::SolidBrush RedBrush(Gdiplus::Color(255, 255, 0, 0));
                g_BackBufferGraphics->FillEllipse(
                    &RedBrush,
                    100, 100,
                    PlayerImageSize, PlayerImageSize
                );
            }
            
            Gdiplus::Graphics GraphicsInstance(hdc);    // Graphics객체 만들기(hdc에 그리기 위한 도구 만들기)
            GraphicsInstance.DrawImage(g_BackBuffer, 0, 0);
        }

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_ERASEBKGND:
        // 화면을 지워야 할 때 날라온 메시지
        return 1;   // 배경지우기 방지(백버퍼 사용하고 있기 때문에)
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_LEFT:
            if (!isPush) {
                OutputDebugStringW(L"왼쪽키를 눌렀다.\n");
                positionWidth -= 50;
                points[0].X -= 50;
                points[1].X -= 50;
                points[2].X -= 50;
                points[3].X -= 50;
                points[4].X -= 50;
                GraphicsInstance.FillRectangle(&GreenBrush, 0, 0, 400, 300);
                GraphicsInstance.FillRectangle(&RedBrush, positionWidth, positionHeight, Width, Height);
                GraphicsInstance.FillPolygon(&RedBrush, points, 5);
                InvalidateRect(hWnd, nullptr, TRUE);
                isPush = true;
            }
            break;
        case VK_RIGHT:
            if (!isPush) {
                OutputDebugStringW(L"오른쪽키를 눌렀다.\n");
                positionWidth += 50;
                points[0].X += 50;
                points[1].X += 50;
                points[2].X += 50;
                points[3].X += 50;
                points[4].X += 50;
                GraphicsInstance.FillRectangle(&RedBrush, positionWidth, positionHeight, Width, Height);
                GraphicsInstance.FillPolygon(&RedBrush, points, 5);
                InvalidateRect(hWnd, nullptr, TRUE);
                isPush = true;
            }
            
            break;
        case VK_DOWN:
            if (!isPush) {
                OutputDebugStringW(L"아래쪽키를 눌렀다.\n");
                positionHeight += 50;
                points[0].Y += 50;
                points[1].Y += 50;
                points[2].Y += 50;
                points[3].Y += 50;
                points[4].Y += 50;
                GraphicsInstance.FillRectangle(&RedBrush, positionWidth, positionHeight, Width, Height);
                GraphicsInstance.FillPolygon(&RedBrush, points, 5);
                InvalidateRect(hWnd, nullptr, TRUE);
                isPush = true;
            }
            break;
        case VK_UP:
            if (!isPush) {
                OutputDebugStringW(L"위쪽키를 눌렀다.\n");
                positionHeight -= 50;
                points[0].Y -= 50;
                points[1].Y -= 50;
                points[2].Y -= 50;
                points[3].Y -= 50;
                points[4].Y -= 50;
                GraphicsInstance.FillRectangle(&RedBrush, positionWidth, positionHeight, Width, Height);
                GraphicsInstance.FillPolygon(&RedBrush, points, 5);
                InvalidateRect(hWnd, nullptr, TRUE);
                isPush = true;
            }
            break;
        case VK_ESCAPE:
            DestroyWindow(hWnd);
            break;
        default:
            break;
        }
        break;
    case WM_DESTROY:
        EndPaint(hWnd, &ps);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
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
