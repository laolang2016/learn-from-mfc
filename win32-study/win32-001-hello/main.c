#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

/**
 * ���ڴ�����.
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
 * \param hInstance ��Ϊ��ʵ���������ģ������������ϵͳʹ�ô�ֵ���ڴ��м��ؿ�ִ���ļ�ʱ��ʶ��ִ���ļ�(EXE) �� ĳЩWindows������Ҫʵ��������������ͼ���λͼ��
 * \param hPrevInstance û�����塣 ���� 16 λWindows��ʹ�ã�������ʼ��Ϊ�㡣
 * \param szCmdLine ���������в�����Ϊ Unicode �ַ�����
 * \param iCmdShow ��һ����־��ָʾ��Ӧ�ó��򴰿�����С������󻯻���������ʾ��
 * \return
 */
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR szCmdLine, _In_ int iCmdShow)
{
	// MessageBox(NULL, TEXT("��һ������"), TEXT("��ʾ"), MB_OK | MB_ICONINFORMATION);

	const wchar_t windowTitle[] = L"��һ������";
	const wchar_t windowClassName[] = L"WND_CLASS_MAIN";

	// �����������ݽṹ
	WNDCLASS wndclass = { 0 };

	wndclass.cbClsExtra = 0; // ������
	wndclass.cbWndExtra = 0; // ������
	// wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // ���ڱ���ɫ , ָ��Ϊ��ɫ
	wndclass.hbrBackground = (HBRUSH)COLOR_WINDOW; // ���ڱ���ɫ , Ĭ��
	wndclass.hCursor = NULL; // Ĭ�����
	wndclass.hIcon = NULL; // Ĭ��ͼ��
	wndclass.hInstance = hInstance; // ����ʵ�����
	wndclass.lpfnWndProc = Wndproc; // ���ڴ�����
	wndclass.lpszClassName = windowClassName;
	wndclass.lpszMenuName = NULL; // �޲˵�
	wndclass.style = CS_HREDRAW | CS_VREDRAW; //ˮƽ��ֱ����仯ʱ���»���

	// ע�ᴰ����
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("����ע��ʧ��"), windowClassName, MB_OK | MB_ICONERROR);
		return 0;
	}

	// ��������
	HWND hwnd = CreateWindow(windowClassName, // ��������
		windowTitle,  // ���ڱ���
		WS_OVERLAPPEDWINDOW,  // ���ڷ��
		CW_USEDEFAULT, // x ����
		CW_USEDEFAULT, // y ����
		CW_USEDEFAULT, // ���
		CW_USEDEFAULT, // �߶�
		NULL,  // ������
		NULL,  // �˵�
		hInstance, // ����ʵ����� 
		NULL); // ��������

	// ��ʾ����
	ShowWindow(hwnd, SW_SHOW);

	// �����ػ�
	UpdateWindow(hwnd);

	// ��Ϣѭ��
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); // ������Ϣ
		DispatchMessage(&msg); // ����Ϣ�������ڴ���������
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
		DrawText(hdc, TEXT("��һ�� win32 ���ڳ���"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
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