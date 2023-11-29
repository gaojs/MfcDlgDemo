#include <windows.h>
#include <iostream>

void MouseMove(float x, float y) {
  INPUT input;
  ZeroMemory(&input, sizeof(input));
  input.type = INPUT_MOUSE;
  input.mi.mouseData = 0;

  input.mi.dx = LONG(x * 65535.0f); // x being coord in pixels
  input.mi.dy = LONG(y * 65535.0f); // y being coord in pixels

  input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
  int ret = SendInput(1, &input, sizeof(input));
  std::cout << "MouseMove ret: " << ret << std::endl;
  if (ret <= 0) {
    DWORD err = GetLastError();
    std::cout << "MouseMove failed, err: " << err << std::endl;
  }
}

void FocusDesktopWindow() {
  HWND deskWin = GetDesktopWindow();
  if (deskWin == NULL) {
    return;
  }
  std::cout << "GetDesktopWindow deskWin: " << deskWin << std::endl;

  HWND retWin = SetActiveWindow(deskWin);
  std::cout << "GetActiveWindow: " << GetActiveWindow() << std::endl;
  if (retWin == NULL) {
    DWORD err = GetLastError();
    std::cout << "SetActiveWindow failed, err: " << err << std::endl;
    return;
  }
  std::cout << "SetActiveWindow retWin: " << retWin << std::endl;
  {
    HWND retWin = SetFocus(deskWin);
    std::cout << "GetFocus: " << GetFocus() << std::endl;
    if (retWin == NULL) {
      DWORD err = GetLastError();
      std::cout << "SetFocus failed, err: " << err << std::endl;
      return;
    }
    std::cout << "SetFocus retWin: " << retWin << std::endl;
  }
}

void ShowDesktopWindow() {
  system("explorer shell:::{3080F90D-D7AD-11D9-BD98-0000947B0257}");
  HWND deskWin = GetDesktopWindow();
  if (deskWin != NULL) { // after SetForeground, then cursor can move
    if (!SetForegroundWindow(deskWin)) {
      DWORD err = GetLastError();
      std::cout << "SetForegroundWindow failed, err: " << err << std::endl;
    }
  }
}

int main()
{
  std::cout << "The cursor will move to center, every 3s!\n";
  while (true) {
    std::string str = "d";
    // std::cout << "d: show desktop; Please input: ";
    // std::cin >> str;
    if (str == "d") {
      // FocusDesktopWindow(); // 无效，Error=5：拒绝访问
      ShowDesktopWindow(); // 可以显示桌面
    }
    MouseMove(0.5, 0.5);
    Sleep(3000);
  }
  system("pause");
  return 0;
}
