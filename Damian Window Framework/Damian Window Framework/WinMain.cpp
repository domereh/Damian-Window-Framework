#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>

LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	// Register the window class.
	const wchar_t CLASS_NAME[] = L"Main Window Class";

	WNDCLASS wc = {};					// set the WNDCLASS structure members to zero

	wc.lpfnWndProc = MainWindowProc;		// lpfnWndProc is a pointer to an application - defined function 
											// called the window procedure or "window proc." The window procedure defines most of the behavior of the window
	wc.hInstance = hInstance;			// hInstance is the handle to the application instance
	wc.lpszClassName = CLASS_NAME;		// lpszClassName is a string that identifies the window class.

	RegisterClass(&wc);					// RegisterClass function registers the window class with the operating system.


										// adjusting window size and resolution

										/*
										RECT wr;
										wr.left = 350;
										wr.right = Graphics::ScreenWidth + wr.left;
										wr.top = 100;
										wr.bottom = Graphics::ScreenHeight + wr.top;
										AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
										*/


										// Create the window.

	HWND hwnd = CreateWindowEx(			// asign window(wnd) handle(h) to veriable hwnd 
										// that uniquely identifies the window
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		L"Learn to Program Windows",    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

										// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	// check if the window is created successfully

	if (hwnd == NULL)
	{
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);		// The nCmdShow parameter can be used to minimize or maximize a window.
									// The operating system passes this value to the program through the wWinMain function.

									// Run the message loop.

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);	// the DispatchMessage function indirectly causes Windows
								// to invoke the WindowProc function, once for each message
	}

	return 0;
}

// window procedure - this procedure deals with mesages from system like mouse clicks
// the operating system calls window procedure inside DispatchMessage

LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);
	}
	return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}