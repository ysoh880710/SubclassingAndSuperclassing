#include <Windows.h>

long long (__stdcall* g_pButtonWndProc)(HWND__* const, const unsigned int, const unsigned long long, const long long) = nullptr;

long long WndProc(HWND__* const _pWindow,
				  const unsigned int _unMessage,
				  const unsigned long long _ullWParam,
				  const long long _llLParam)
{
	switch (_unMessage)
	{
	case WM_COMMAND:
		{
			int a = 10;
		}
		break;
	case WM_DESTROY:
		{
			PostQuitMessage(55555);
			return 0ll;
		}
		break;
	default:
		break;
	}

	return DefWindowProcW(_pWindow, _unMessage, _ullWParam, _llLParam);
}

long long NewWndProc(HWND__* const _pWindow,
					 const unsigned int _unMessage,
					 const unsigned long long _ullWParam,
					 const long long _llLParam)
{
	switch (_unMessage)
	{
	case WM_CREATE:
		{
			int a = 10;
		}
		break;
	case WM_DESTROY:
		{
			int a = 10;
		}
		break;
	default:
		break;
	}

	long long (__stdcall* pWndProc)(HWND__* const, const unsigned int, const unsigned long long, const long long) = (WNDPROC)GetClassLongPtrW(_pWindow, 0);
	return CallWindowProcW(pWndProc, _pWindow, _unMessage, _ullWParam, _llLParam);
}

long long NewButtonWndProc(HWND__* const _pWindow,
						   const unsigned int _unMessage,
						   const unsigned long long _ullWParam,
						   const long long _llLParam)
{
	switch (_unMessage)
	{
	case WM_CREATE:
		{
			int a = 10;
		}
		break;
	case WM_MOUSEMOVE:
		{
			int a = 10;
		}
		break;
	case WM_DESTROY:
		{
			int a = 10;
			return 0ll;
		}
		break;
	default:
		break;
	}

	return CallWindowProcW(g_pButtonWndProc, _pWindow, _unMessage, _ullWParam, _llLParam);
}

int __stdcall wWinMain(HINSTANCE__* const _pInstance,
					   HINSTANCE__* const _pPrevInstance,
					   wchar_t* const _pCmdLine,
					   const int _nCmdShow)
{
	tagWNDCLASSEXW stWNDCLASSEXW
	{
		sizeof(tagWNDCLASSEXW),
		static_cast<unsigned int>(CS_VREDRAW | CS_HREDRAW),
		&WndProc,
		8,
		0,
		_pInstance,
		nullptr,
		static_cast<HICON__*>(LoadImageW(nullptr, static_cast<const wchar_t*>(IDC_ARROW), static_cast<unsigned int>(IMAGE_CURSOR), 0, 0, static_cast<unsigned int>(LR_SHARED))),
		static_cast<HBRUSH__*>(GetStockObject(WHITE_BRUSH)),
		L"MenuName",
		L"ClassName",
		nullptr
	};

	if (RegisterClassExW(&stWNDCLASSEXW) == 0ui16)
	{
		return 0;
	}

	HWND__* pWindow = CreateWindowExW(0ul,
											L"ClassName",
											L"WindowName",
											static_cast<unsigned long>(WS_OVERLAPPEDWINDOW),
											0,
											0,
											1200,
											800,
											nullptr,
											nullptr,
											_pInstance,
											nullptr);
	if (pWindow == nullptr)
	{
		return 0;
	}

	ShowWindow(pWindow, SW_SHOW);

	// Subclassing

	unsigned long long ull0 = SetClassLongPtrW(pWindow, 0, reinterpret_cast<unsigned long long>(&WndProc));
	unsigned long long ull = SetClassLongPtrW(pWindow, GCLP_WNDPROC, reinterpret_cast<unsigned long long>(&NewWndProc));

	DestroyWindow(pWindow);

	pWindow = CreateWindowExW(0ul,
							  L"ClassName",
							  L"WindowName",
							  static_cast<unsigned long>(WS_OVERLAPPEDWINDOW),
							  0,
							  0,
							  1200,
							  800,
							  nullptr,
							  nullptr,
							  _pInstance,
							  nullptr);
	if (pWindow == nullptr)
	{
		return 0;
	}

	ShowWindow(pWindow, SW_SHOW);

	HWND__* const pButton = CreateWindowExW(0ul,
											L"Button",
											L"Button",
											static_cast<unsigned long>(WS_CHILD | BS_PUSHBUTTON),
											100,
											100,
											50,
											50,
											pWindow,
											reinterpret_cast<HMENU__*>(123),
											_pInstance,
											nullptr);
	if (pButton == nullptr)
	{
		return 0;
	}

	ShowWindow(pButton, SW_SHOW);

	// Superclassing

	tagWNDCLASSEXW stButtonWNDCLASSEXW
	{
		sizeof(tagWNDCLASSEXW),
		//static_cast<unsigned int>(CS_VREDRAW | CS_HREDRAW),
		//&WndProc,
		//0,
		//0,
		//_pInstance,
		//nullptr,
		//static_cast<HICON__*>(LoadImageW(nullptr, static_cast<const wchar_t*>(IDC_ARROW), static_cast<unsigned int>(IMAGE_CURSOR), 0, 0, static_cast<unsigned int>(LR_SHARED))),
		//static_cast<HBRUSH__*>(GetStockObject(BLACK_BRUSH)),
		//L"MenuName",
		//L"ButtonClassName",
		//nullptr
	};

	if (GetClassInfoExW(_pInstance,
						L"Button",
						&stButtonWNDCLASSEXW) == 0)
	{
		return 0;
	}

	g_pButtonWndProc = stButtonWNDCLASSEXW.lpfnWndProc;

	stButtonWNDCLASSEXW.lpfnWndProc = &NewButtonWndProc;
	stButtonWNDCLASSEXW.lpszClassName = L"NewButtonClassName";

	if (RegisterClassExW(&stButtonWNDCLASSEXW) == 0ui16)
	{
		return 0;
	}

	HWND__* const pNewButton = CreateWindowExW(0ul,
											   L"NewButtonClassName",
											   L"NewButton",
											   static_cast<unsigned long>(WS_CHILD | BS_PUSHBUTTON),
											   100,
											   200,
											   400,
											   400,
											   pWindow,
											   reinterpret_cast<HMENU__*>(456),
											   _pInstance,
											   nullptr);
	if (pNewButton == nullptr)
	{
		return 0;
	}

	ShowWindow(pNewButton, SW_SHOW);

	HWND__* const pWindow0 = CreateWindowExW(0ul,
											L"ClassName",
											L"WindowName0",
											static_cast<unsigned long>(WS_CHILD | WS_OVERLAPPEDWINDOW),
											100,
											100,
											200,
											200,
											 pNewButton,
											nullptr,
											_pInstance,
											nullptr);
	if (pWindow0 == nullptr)
	{
		return 0;
	}

	ShowWindow(pWindow0, SW_SHOW);

	tagMSG stMSG{};
	
	while (true)
	{
		if (PeekMessageW(&stMSG, nullptr, 0u, 0u, static_cast<unsigned int>(PM_REMOVE)) != 0)
		{
			if (stMSG.message == static_cast<unsigned int>(WM_QUIT))
			{
				DestroyWindow(pWindow);
				break;
			}

			TranslateMessage(&stMSG);
			DispatchMessageW(&stMSG);
		}
		else
		{
		}
	}

	return 0;
}