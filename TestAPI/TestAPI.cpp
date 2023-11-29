#include <windows.h>
#include <iostream>

void MouseMove(float x, float y) {
  INPUT input;
  ZeroMemory(&input, sizeof(input));
  input.type = INPUT_MOUSE;
  input.mi.mouseData = 0;

  input.mi.dx = x * 65535.0f; // x being coord in pixels
  input.mi.dy = y * 65535.0f; // y being coord in pixels

  input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
  int ret = SendInput(1, &input, sizeof(input));
  if (ret <= 0) {
    int32_t err = (int32_t)GetLastError();
    std::cout << "MouseMove failed, err: " << err;
  }
}



int main()
{
  std::cout << "The cursor will move to center, every 3s!\n";
  while (true) {
    MouseMove(0.5, 0.5);
    Sleep(3000);
  }
  system("pause");
  return 0;
}
