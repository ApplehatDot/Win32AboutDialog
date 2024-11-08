#include <windows.h>
#include "AboutDiag.h"

// Definitions

#define wWidth 500
#define wHeight 400
#define IDC_MYBUTTON 1

HBITMAP hBanner;
HFONT hFont;
HWND Banner, hText, hButton, hLicense;
LPCWSTR ImagePath = L"assets\\Banner.bmp";

extern "C" __declspec(dllexport) void ShowAboutDialog(HINSTANCE hInstance, HWND hwndParent);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void AddControl(HWND);
// end of definitions

extern "C" __declspec(dllexport) void ShowAboutDialog(HINSTANCE hInstance, HWND hwndParent){
	const wchar_t CLASS_NAME[] = L"WndAboutDialog";
	
	WNDCLASSW wc = {0};
	wc.lpfnWndProc = WindowProc;
	wc.lpszClassName = CLASS_NAME;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	
	RegisterClassW(&wc);
	
	HWND hwnd = CreateWindowExW(
		0,
		CLASS_NAME,
		L"About",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		wWidth, wHeight,
		hwndParent,
		NULL,
		hInstance,
		NULL);
		
	if (hwnd == NULL) {
        return;
    }
	
	// Set an icon
	if (hwnd != NULL) {
		HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
		SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
	}

    ShowWindow(hwnd, SW_SHOW);
    SetWindowTextW(hwnd, L"About");

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	switch (uMsg){
		case WM_CREATE{
			AddControl(hwnd);
			break;
		}
		
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
			
		case WM_COMMAND:
			if (LOWORD(wParam) == IDC_MYBUTTON) {
                		DestroyWindow(hwnd);
            		}
			break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
};

void AddControl(HWND hwnd){
	
	Banner = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 0, 0, 0, 0, hwnd, NULL, NULL, NULL);
	
	hBanner = (HBITMAP)LoadImageW(NULL, ImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		
	if(hBanner == NULL){
		MessageBoxW(hwnd, L"Can't find the banner - No Banner Found", L"Where Bitmap?", MB_OK | MB_ICONERROR);
		return;
	}
	
	SendMessageW(Banner, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hBanner);
	
	hText = CreateWindowExW(
		0,
		L"EDIT", 
		L"",
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
		40, 110, 
		400, 210,	 // the size of the text area, feel free to change
		hwnd, NULL, NULL, NULL);
	
	SetWindowTextW(
		hText,
		L"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Quis ipsum suspendisse ultrices gravida. Risus commodo viverra maecenas accumsan lacus vel facilisis."
		);

	
	// Download system default font	
	hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	
	SendMessageW(hText, WM_SETFONT, (WPARAM)hFont, TRUE);
		
	hButton = CreateWindowExW(
                0,
                L"BUTTON",
                L"OK",
                WS_CHILD | WS_VISIBLE,
                150, 340, 100, 25,
                hwnd,
                (HMENU)IDC_MYBUTTON,
                NULL,
                NULL
            );
			
	SendMessageW(hButton, WM_SETFONT, (WPARAM)hFont, TRUE);
	
	

}
