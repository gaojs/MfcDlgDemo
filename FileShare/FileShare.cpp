#include <stdio.h>
#include <windows.h>

int main() {
  HANDLE hFile;
  HANDLE hAppend;
  DWORD dwBytesRead, dwBytesWritten, dwPos;
  BYTE buff[4096] = {0};

  // Open the existing file.
  hFile = CreateFile(TEXT("1.txt"),  // open One.txt
                     GENERIC_READ,          // open for reading
                     0,                     // do not share
                     NULL,                  // no security
                     OPEN_EXISTING,         // existing file only
                     FILE_ATTRIBUTE_NORMAL, // normal file
                     NULL);                 // no attr. template
  if (hFile == INVALID_HANDLE_VALUE) {
    printf("Could not open 1.txt.\n");
    system("pause");
    return -1;
  }

  // Open the existing file, or if the file does not exist,
  // create a new file.
  hAppend = CreateFile(TEXT("2.txt"), // open Two.txt
                       FILE_APPEND_DATA |
                       FILE_GENERIC_READ, // open for appending and locking
                       FILE_SHARE_READ,       // allow multiple readers
                       NULL,                  // no security
                       OPEN_ALWAYS,           // open or create
                       FILE_ATTRIBUTE_NORMAL, // normal file
                       NULL);                 // no attr. template
  if (hAppend == INVALID_HANDLE_VALUE) {
    printf("Could not open 2.txt.\n");
    CloseHandle(hFile);
    system("pause");
    return -1;
  }

  // Append the first file to the end of the second file.
  // Lock the second file to prevent another process from
  // accessing it while writing to it. Unlock the
  // file when writing is complete.
  ReadFile(hFile, buff, sizeof(buff), &dwBytesRead, NULL);
  long i = LONG_MAX;
  while (i > 0) { // 接近死循环，模拟无响应
    dwPos = SetFilePointer(hAppend, 0, NULL, FILE_END);
    if (!LockFile(hAppend, dwPos, 0, dwBytesRead, 0)) {
      printf("Could not lock 2.txt\n");
      system("pause");
    }
    WriteFile(hAppend, buff, dwBytesRead, &dwBytesWritten, NULL);
    UnlockFile(hAppend, dwPos, 0, dwBytesRead, 0);
    Sleep(10);
    i--;
  }

  // Close both files.
  CloseHandle(hFile);
  CloseHandle(hAppend);
  system("pause");
  return 0;
}