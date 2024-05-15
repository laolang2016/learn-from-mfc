#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

/**
 * 窗口处理函数.
 *
 * \param hWnd
 * \param message
 * \param wParam
 * \param lParam
 * \return
 */
LRESULT CALLBACK Wndproc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

/**
 * .
 *
 * \param hInstance 称为“实例句柄”或“模块句柄”。操作系统使用此值在内存中加载可执行文件时标识可执行文件(EXE) 。 某些Windows函数需要实例句柄，例如加载图标或位图。
 * \param hPrevInstance 没有意义。 它在 16 位Windows中使用，但现在始终为零。
 * \param szCmdLine 包含命令行参数作为 Unicode 字符串。
 * \param iCmdShow 是一个标志，指示主应用程序窗口是最小化、最大化还是正常显示。
 * \return
 */
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR szCmdLine, _In_ int iCmdShow)
{
	// MessageBox(NULL, TEXT("第一个窗口"), TEXT("提示"), MB_OK | MB_ICONINFORMATION);

	const wchar_t windowTitle[] = L"第一个窗口";
	const wchar_t windowClassName[] = L"WND_CLASS_MAIN";

	// 生命窗口数据结构
	WNDCLASS wndclass = { 0 };

	wndclass.cbClsExtra = 0; // 缓冲区
	wndclass.cbWndExtra = 0; // 缓冲区
	// wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // 窗口背景色 , 指定为白色
	wndclass.hbrBackground = (HBRUSH)COLOR_WINDOW; // 窗口背景色 , 默认
	wndclass.hCursor = NULL; // 默认鼠标
	wndclass.hIcon = NULL; // 默认图标
	wndclass.hInstance = hInstance; // 窗口实例句柄
	wndclass.lpfnWndProc = Wndproc; // 窗口处理函数
	wndclass.lpszClassName = windowClassName;
	wndclass.lpszMenuName = NULL; // 无菜单
	wndclass.style = CS_HREDRAW | CS_VREDRAW; //水平或垂直方向变化时重新绘制

	// 注册窗口类
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("窗口注册失败"), windowClassName, MB_OK | MB_ICONERROR);
		return 0;
	}

	// 创建窗口
	HWND hwnd = CreateWindow(windowClassName, // 窗口类型
		windowTitle,  // 窗口标题
		WS_OVERLAPPEDWINDOW,  // 窗口风格
		CW_USEDEFAULT, // x 坐标
		CW_USEDEFAULT, // y 坐标
		CW_USEDEFAULT, // 宽度
		CW_USEDEFAULT, // 高度
		NULL,  // 父窗口
		NULL,  // 菜单
		hInstance, // 程序实例句柄 
		NULL); // 创建参数

	// 显示窗口
	ShowWindow(hwnd, SW_SHOW);

	// 窗口重绘
	UpdateWindow(hwnd);

	// 消息循环
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); // 翻译消息
		DispatchMessage(&msg); // 将消息交给窗口处理函数处理
	}

	return 0;
}


LRESULT CALLBACK Wndproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	switch (message)
	{
	case WM_PAINT: {
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		DrawText(hdc, TEXT("第一个 win32 窗口程序"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hwnd, &ps);
		break;
	}
	case WM_DESTROY: {
		PostQuitMessage(0);
		return 0;
		break;
	}
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}