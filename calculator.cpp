#include <windows.h>
#include <stdio.h>
#include<string>
#include <stdlib.h>
#include <tchar.h> 
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch(Message) {
        case WM_CREATE: {
            // Create a static text control
            HWND hStatic = CreateWindow("STATIC", "Please input two numbers", WS_VISIBLE | WS_CHILD, 20, 20, 180, 20, hwnd, NULL, NULL, NULL);
            HWND hEdit1 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT, 50, 50, 120, 20, hwnd, (HMENU) 1, NULL, NULL);	 
            HWND hEdit2 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT, 50, 80, 120, 20, hwnd, (HMENU) 2, NULL, NULL);	   
            HWND hButtonPlus = CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 50, 115, 30, 30, hwnd, (HMENU) 3, NULL, NULL);
            HWND hButtonMinus = CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 90, 115, 30, 30, hwnd, (HMENU) 4, NULL, NULL);
            HWND hButtonMultiply = CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 130, 115, 30, 30, hwnd, (HMENU) 5, NULL, NULL);
            HWND hButtonDivide = CreateWindow("BUTTON", "/", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 170, 115, 30, 30, hwnd, (HMENU) 6, NULL, NULL);
            break;
        }
        case WM_COMMAND: {
            int wmId = LOWORD(wParam);
            if (wmId >= 3 && wmId <= 6) {
                HWND hEdit1 = GetDlgItem(hwnd, 1);
                HWND hEdit2 = GetDlgItem(hwnd, 2);
                char num1Str[100];
                char num2Str[100];
                GetWindowText(hEdit1, num1Str, 100);
                GetWindowText(hEdit2, num2Str, 100);
                double num1 = atof(num1Str);
                double num2 = atof(num2Str);
                double result = 0;
                switch (wmId) {
                    case 3: 
                        result = num1 + num2;
                        break;
                    case 4: 
                        result = num1 - num2;
                        break;
                    case 5: 
                        result = num1 * num2;
                        break;
                    case 6: 
                        if (num2 != 0) {
                            result = num1 / num2;
                        } else {
                            MessageBox(hwnd, "Cannot divide by zero!", "Error", MB_OK | MB_ICONERROR);
                            break;
                        }
                        break;
                }
                char t[250];
                sprintf(t, "Result: %f", result);
                MessageBox(hwnd, t, "Result", MB_OK);
            }
            break;
        }
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground =  (HBRUSH)(CreateSolidBrush(RGB(0, 255, 0)));
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
	

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",(WS_VISIBLE|WS_OVERLAPPEDWINDOW)& ~(WS_MAXIMIZEBOX | WS_MINIMIZEBOX),
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);
		

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
