#include <stdio.h>
#include <time.h>

#include <Windows.h>
#include <wingdi.h>
#include <WinUser.h>

#define GRAPH_SIZE		10
#define GRAPH_WIDTH		50
#define GRAPH_HEIGHT		50
#define GRAPH_DELAY		100
#define BUFFER_SIZE		200

#define ID(x,y) ((y)*(GRAPH_WIDTH)+(x))

#define NOGRAPH 0
#define GRAPH 1

typedef unsigned char life_t;
typedef unsigned long tick_t;

LPCSTR szMyWindowApplicationName = "LifeTheGame";

HINSTANCE	hMainInstance;
HWND		hMainWindow, hConsole;
HBITMAP		hBmpCanvas;

BOOL bPaused = FALSE;

tick_t ticks = (tick_t)0ul;

life_t life[GRAPH_WIDTH][GRAPH_HEIGHT];

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndPaint(HWND hWnd, HDC hDC, PAINTSTRUCT ps, RECT rcClient)
{
	Rectangle(hDC, rcClient.left, rcClient.top, rcClient.right, rcClient.bottom);

	HPEN hPen = CreatePen(PS_SOLID,1,RGB(100,100,100));
	SelectObject(hDC,hPen);

	for(int i = 1;i < GRAPH_HEIGHT;i++)
	{
		int y = rcClient.top + i * GRAPH_SIZE;
		MoveToEx(hDC, rcClient.left,y, NULL);
		LineTo(hDC, rcClient.right,y);
	}

	for(int i = 1;i < GRAPH_WIDTH; i++)
	{
		int x = rcClient.left + i * GRAPH_SIZE;
		MoveToEx(hDC, x,rcClient.top, NULL);
		LineTo(hDC,x, rcClient.bottom);
	}

	SIZE sizeText;
	char buffer[BUFFER_SIZE];

	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkMode(hDC, TRANSPARENT);
	SelectObject(hDC,GetStockObject(DEFAULT_GUI_FONT));

	HBRUSH hBrush = CreateSolidBrush(RGB(0,0,0));
	SelectObject(hDC,hBrush);

	for(int x = 0;x < GRAPH_WIDTH;x++)
		for(int y = 0;y < GRAPH_HEIGHT;y++)
			if(life[x][y] == GRAPH)
				Rectangle(hDC,rcClient.left + x * GRAPH_SIZE,rcClient.top + y * GRAPH_SIZE,rcClient.left + (x + 1) * GRAPH_SIZE,rcClient.top + (y+1) * GRAPH_SIZE);

	SetTextColor(hDC, RGB(0, 0, 0));

	snprintf(buffer,BUFFER_SIZE, "DELAY: %d ms", GRAPH_DELAY);
	GetTextExtentPoint32A(hDC, buffer, strlen(buffer), &sizeText);
	TextOutA(hDC, rcClient.left + 5, rcClient.top + 5, buffer, strlen(buffer));
	
	snprintf(buffer,BUFFER_SIZE, "TICKS: %d", ticks);
	GetTextExtentPoint32A(hDC, buffer, strlen(buffer), &sizeText);
	TextOutA(hDC, rcClient.left + 5, rcClient.top + 25, buffer, strlen(buffer));
	
	if(bPaused)
	{
		snprintf(buffer,BUFFER_SIZE, "PAUSED");
		GetTextExtentPoint32A(hDC, buffer, strlen(buffer), &sizeText);
		TextOutA(hDC, rcClient.left + 5, rcClient.top + 45, buffer, strlen(buffer));
	}

	DeleteObject(hPen);
	DeleteObject(hBrush);

	return 0;
}

LRESULT WndThink(HWND hWnd)
{			
	InvalidateRect(hWnd,NULL,FALSE);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPCSTR lpCmdLine, int nCmdShow)
{
	hMainInstance = hInstance;
	hConsole = GetConsoleWindow();

	WNDCLASSEXA wcex;
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIconA(wcex.hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursorA(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOWFRAME);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = "LifeTheGameApp";
	wcex.hIconSm = LoadIconA(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassExA(&wcex))
	{
		MessageBoxA(NULL,
			"Registration window class failed!",
			szMyWindowApplicationName,
			MB_ICONSTOP | MB_OK);
		
		return EXIT_FAILURE;
	}

	RECT windowSize;
	windowSize.top = windowSize.left = 0;
	windowSize.right = GRAPH_WIDTH * GRAPH_SIZE;
	windowSize.bottom = GRAPH_HEIGHT * GRAPH_SIZE;

	AdjustWindowRectEx(&windowSize,WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,FALSE,WS_EX_OVERLAPPEDWINDOW);
	
	hMainWindow = CreateWindowExA(
		WS_EX_OVERLAPPEDWINDOW,
		wcex.lpszClassName,
		szMyWindowApplicationName,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,
		windowSize.right-windowSize.left, windowSize.bottom-windowSize.top,
		NULL,
		NULL,
		wcex.hInstance,
		NULL
	);

	if (hMainWindow == NULL)
	{
		MessageBoxA(NULL,
			TEXT("Creating window failed!"),
			szMyWindowApplicationName,
			MB_ICONSTOP | MB_OK);

		return EXIT_FAILURE;
	}

	ShowWindow(hMainWindow, nCmdShow);
	UpdateWindow(hMainWindow);

	MSG msg;

	while (GetMessageA(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
	
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HINSTANCE hInstance = (HINSTANCE)GetWindowLongPtrA(hWnd, GWLP_HINSTANCE);

	switch (message)
	{
		case WM_CREATE:
		{
			SetTimer(hWnd,1,GRAPH_DELAY,NULL);

			life[3][2] = GRAPH;
			life[3][3] = GRAPH;
			life[3][4] = GRAPH;

			return 0;
		}

		case WM_COMMAND:
		{
			return 0;
		}

		case WM_PAINT:
		{
			RECT rect;
			GetClientRect(hWnd, &rect);

			PAINTSTRUCT ps;

			HDC hDC = BeginPaint(hWnd, &ps);
			HDC memDC = CreateCompatibleDC(hDC);
			HBITMAP bmp = CreateCompatibleBitmap(hDC, rect.right - rect.left, rect.bottom - rect.top);
			SelectObject(memDC, bmp);

			LRESULT result = WndPaint(hWnd, memDC, ps, rect);

			BitBlt(hDC, 0, 0, rect.right - rect.left, rect.bottom - rect.top, memDC, 0, 0, SRCCOPY);

			DeleteObject(bmp);
			DeleteDC(memDC);

			EndPaint(hWnd, &ps);

			return result;
		}

		case WM_TIMER:
		{
			return bPaused ? 0 : WndThink(hWnd);
		}

		case WM_MBUTTONDOWN:
		{
			bPaused = !bPaused;

			InvalidateRect(hWnd,NULL,FALSE);

			return 0;
		}

		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MOUSEMOVE:
		{
			if(wParam & MK_LBUTTON || wParam & MK_RBUTTON)
			{
				POINTS points = MAKEPOINTS(lParam);
				
				int x = min(points.x / GRAPH_SIZE,GRAPH_WIDTH);
				int y = min(points.y / GRAPH_SIZE,GRAPH_HEIGHT);

				if(wParam & MK_LBUTTON)
					life[x][y] = GRAPH;
				else if(wParam & MK_RBUTTON)
					life[x][y] = NOGRAPH;

				InvalidateRect(hWnd,NULL,FALSE);
			}

			return 0;
		}

		case WM_DESTROY:
		{
			PostQuitMessage(EXIT_SUCCESS);

			return 0;
		}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}