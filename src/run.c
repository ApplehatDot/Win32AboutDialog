#include <windows.h>
#include <stdio.h>

// Definicja typu funkcji ShowAboutDialog
typedef void (__stdcall *ShowAboutDialogFunc)(HINSTANCE, HWND);

int main() {
    // Ładujemy bibliotekę DLL
    HINSTANCE hLib = LoadLibraryW(L"AboutDialog.dll");
    if (!hLib) {
        printf("Nie można załadować AboutDialog.dll\n");
        return 1;
    }

    // Znajdujemy funkcję ShowAboutDialog
    ShowAboutDialogFunc ShowAboutDialog = (ShowAboutDialogFunc)GetProcAddress(hLib, "ShowAboutDialog");
    if (!ShowAboutDialog) {
        printf("Nie można znaleźć funkcji ShowAboutDialog w AboutDialog.dll\n");
        FreeLibrary(hLib);
        return 1;
    }

    // Wywołujemy funkcję ShowAboutDialog
    HINSTANCE hInstance = GetModuleHandle(NULL);
    HWND hwndParent = NULL; // NULL oznacza brak okna rodzica
    ShowAboutDialog(hInstance, hwndParent);

    // Zwolnienie biblioteki DLL
    FreeLibrary(hLib);

    return 0;
}
