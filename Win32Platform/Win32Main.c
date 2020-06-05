//#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <strsafe.h>

#include <stdint.h>
#include <stdbool.h>

#include "rendering.h"

#include "../Engine/engine.h"

//   1000
//p1 ud00
//p2 00up
//   0000
int input = 0;

typedef struct
{
    HMODULE gameCodeDLL;
    FILETIME DLLLastWriteTime;
    start *Start;
    update *Update;
} win32_engine_code;

//todo: this should come from the engine
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

InputComponent Win32GetInput() {
	InputComponent ic = { 0 };
	ic.keyboard = input;
	return ic;
}

void checkres(HRESULT hr)
{
	if (FAILED(hr))
	{
		switch (hr)
		{
		case DXGI_ERROR_NOT_CURRENTLY_AVAILABLE:
			OutputDebugStringA("DXGI_ERROR_NOT_CURRENTLY_AVAILABLE");
			break;
		case D3D11_ERROR_FILE_NOT_FOUND:
			OutputDebugStringA("D3D11_ERROR_FILE_NOT_FOUND");
			break;
		case D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS:
			OutputDebugStringA("D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS");
			break;
		case D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS:
			OutputDebugStringA("D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS");
			break;
		case D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD:
			OutputDebugStringA("D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD");
			break;
		case E_FAIL:
			OutputDebugStringA("E_FAIL");
			break;
		case E_INVALIDARG:
			OutputDebugStringA("E_INVALIDARG");
			break;
		case E_OUTOFMEMORY:
			OutputDebugStringA("E_OUTOFMEMORY");
			break;
		case E_NOTIMPL:
			OutputDebugStringA("E_NOTIMPL");
			break;
		case S_FALSE:
			OutputDebugStringA("S_FALSE");
			break;
		default:
			OutputDebugStringA("??");
			break;
		}
	}
	else
	{
		OutputDebugStringA("SUCCES!!!");
	}
}

void_pChar(Win32Print)
{
    OutputDebugStringA(message);
	OutputDebugStringA("\n");
}

LRESULT CALLBACK
Win32MainWindowCallback(HWND Window,
	UINT Message,
	WPARAM WParam,
	LPARAM LParam)
{
	LRESULT Result = 0;
	switch (Message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	break;
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
	case WM_KEYDOWN:
	case WM_KEYUP:
	{
		input = 0;
		uint32_t VKCode = WParam;
		bool wasdown = ((LParam & (1 << 30)) != 0);
		bool isdown = ((LParam & (1 << 31)) == 0);
		switch (VKCode)
		{
		case 'W':
			input |= 1<< 3; // 1000
			break;
		case 'A':
			break;
		case 'S':
			input |= 1 << 2; // 0100
			break;
		case 'D':
			break;
		case 'Q':
			break;
		case 'E':
			break;
		case VK_UP:
			input |= 1 << 1; // 0010
			break;
		case VK_LEFT:
			break;
		case VK_DOWN:
			input |= 1; // =0001
			break;
		case VK_RIGHT:
			break;
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
		case VK_SPACE:
			break;
		default:
			break;
		}
	}
	break;
	}
	// todo if I close the window manually its failing here?
	return DefWindowProc(Window, Message, WParam, LParam);
}

inline FILETIME Win32GetLastWriteTime(char *Filename)
{
    FILETIME lastWriteTime = {0};
    WIN32_FIND_DATA FindData;
    HANDLE FindHandle = FindFirstFile(Filename, &FindData);
    if(FindHandle != INVALID_HANDLE_VALUE)
    {
	lastWriteTime = FindData.ftLastWriteTime;
	FindClose(FindHandle);
    }
    return (lastWriteTime);
}

void ErrorExit(LPTSTR lpszFunction) 
{ 
    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
	FORMAT_MESSAGE_ALLOCATE_BUFFER | 
	FORMAT_MESSAGE_FROM_SYSTEM |
	FORMAT_MESSAGE_IGNORE_INSERTS,
	NULL,
	dw,
	MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
	(LPTSTR) &lpMsgBuf,
	0, NULL );

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
	(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR)); 
    StringCchPrintf((LPTSTR)lpDisplayBuf, 
	LocalSize(lpDisplayBuf) / sizeof(TCHAR),
	TEXT("%s failed with error %d: %s"), 
	lpszFunction, dw, lpMsgBuf); 
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
    ExitProcess(dw); 
}

static win32_engine_code Wind32LoadGame(void)
{
    win32_engine_code engineMethods = {0};

    LPCTSTR SourceDLLName = L"Engine.dll";
    LPCTSTR TempDLLName = L"engine_temp.dll";

    engineMethods.DLLLastWriteTime = Win32GetLastWriteTime(SourceDLLName);
    if(CopyFile(SourceDLLName, TempDLLName, false)) {
	OutputDebugStringA("success copy engine_temp dll\n");
	} else {
		ErrorExit(TEXT("CopyFile"));
	}

    engineMethods.gameCodeDLL = LoadLibrary(TempDLLName);
    if (engineMethods.gameCodeDLL)
    {
	engineMethods.Start = (start *)GetProcAddress(engineMethods.gameCodeDLL, "Start");
		engineMethods.Update = (update *)GetProcAddress(engineMethods.gameCodeDLL, "Update");
    } else {
		ErrorExit(TEXT("load engine lib"));
    }

    if (engineMethods.Start != NULL)
    {
		OutputDebugStringA("success loaded render function\n");
    } else {
		ErrorExit(TEXT("load start method"));
    }

    return (engineMethods);
}

int CALLBACK
WinMain(HINSTANCE Instance,
	HINSTANCE PrevInstance,
	LPSTR CommandLine,
	int ShowCode)
{
	HWND WindowHandle;
	WNDCLASSEX wnd;
	ZeroMemory(&wnd, sizeof(WNDCLASSEX));

	wnd.cbSize = sizeof(WNDCLASSEX);
	wnd.style = CS_HREDRAW | CS_VREDRAW;
	wnd.lpfnWndProc = Win32MainWindowCallback;
	wnd.hInstance = Instance;
	wnd.hCursor = LoadCursor(0, IDC_ARROW);
	wnd.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wnd.lpszClassName = L"Window Class";
	RegisterClassEx(&wnd);

	RECT wr = { 0, 0, 1920, 1080 };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

	WindowHandle = CreateWindowEx(
		0,
		L"Window Class",
		L"Windows Programming",
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		NULL,
		NULL,
		Instance,
		NULL);

	if (WindowHandle == NULL)
	{
		system("PAUSE");
		return -1;
	}

	IDXGIFactory* factory;
	IDXGIAdapter* adapter;
	IDXGIOutput* output;
	DXGI_OUTPUT_DESC od;

	CreateDXGIFactory(&IID_IDXGIFactory, &factory);
	factory->lpVtbl->EnumAdapters(factory, 0, &adapter);
	adapter->lpVtbl->EnumOutputs(adapter, 0, &output);
	output->lpVtbl->GetDesc(output, &od);
	output->lpVtbl->Release(output);

	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = WindowHandle;
	scd.SampleDesc.Count = 4;
	scd.Windowed = TRUE;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	D3D_FEATURE_LEVEL FeatureLevelsRequested = D3D_FEATURE_LEVEL_11_0;
	UINT numLevelsRequested = 1;
	D3D_FEATURE_LEVEL FeatureLevelsSupported;
	HRESULT hr;
	hr = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&sc,
		&d3ddev,
		NULL,
		&d3dctx);


	hr = sc->lpVtbl->GetBuffer(sc, 0, &IID_ID3D11Texture2D, (void**)&d3dbb);
	if (FAILED(hr))
	{
		OutputDebugStringA("GetBuffer FAILED");
		return;
	}

	D3D11_RENDER_TARGET_VIEW_DESC vd;
	D3D11_VIEWPORT vp;
	vd.Format = DXGI_FORMAT_UNKNOWN;
	vd.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	vd.Texture2D.MipSlice = 0;
	hr = d3ddev->lpVtbl->CreateRenderTargetView(d3ddev, d3dbb, NULL, &view);

	d3dctx->lpVtbl->OMSetRenderTargets(d3dctx, 1, &view, NULL);
	vp.Width = SCREEN_WIDTH;
	vp.Height = SCREEN_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	d3dctx->lpVtbl->RSSetViewports(d3dctx, 1, &vp);

	ID3D10Blob* VS, * PS;
	ID3D10Blob* msg = NULL;
	hr = D3DCompileFromFile(L"shader.shader", 0, 0, "VShader", "vs_4_0", 0, 0, &VS, &msg);
	hr = D3DCompileFromFile(L"shader.shader", 0, 0, "PShader", "ps_4_0", 0, 0, &PS, &msg);

	hr = d3ddev->lpVtbl->CreateVertexShader(d3ddev, VS->lpVtbl->GetBufferPointer(VS), VS->lpVtbl->GetBufferSize(VS), NULL, &pVS);
	d3ddev->lpVtbl->CreatePixelShader(d3ddev, PS->lpVtbl->GetBufferPointer(PS), PS->lpVtbl->GetBufferSize(PS), NULL, &pPS);

	d3dctx->lpVtbl->VSSetShader(d3dctx, pVS, 0, 0);
	d3dctx->lpVtbl->PSSetShader(d3dctx, pPS, 0, 0);

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	d3ddev->lpVtbl->CreateInputLayout(d3ddev, ied, 2, VS->lpVtbl->GetBufferPointer(VS), VS->lpVtbl->GetBufferSize(VS), &m_layout);
	d3dctx->lpVtbl->IASetInputLayout(d3dctx, m_layout);

	ShowWindow(WindowHandle, ShowCode);

	InitMatrixTransform();

	GameMemory gameMemory = {0};
	gameMemory.Print = Win32Print;
	gameMemory.CreateIndexBuffer = CreateIndexBuffer;
	gameMemory.CreateVertexBuffer = CreateVertexBuffer;
	gameMemory.SetBuffers = SetBuffers;
	gameMemory.getInput = Win32GetInput;

	win32_engine_code engineMethods = {0};
	engineMethods = Wind32LoadGame();

	engineMethods.Start(&gameMemory);

	MSG Message = { 0 };
	while (true)
	{
		if (PeekMessage(&Message, 0, 0, 0, PM_REMOVE) > 0)
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
			if (Message.message == WM_QUIT)
			{
				break;
			}
		}

		float color[4] = {0.0f, 0.0f, 0.0f, 255};
		d3dctx->lpVtbl->ClearRenderTargetView(d3dctx, view, color);

		engineMethods.Update(&gameMemory);

		HRESULT res = sc->lpVtbl->Present(sc, 0, 0);

		Sleep(1);
	}

	sc->lpVtbl->SetFullscreenState(sc, FALSE, NULL);

    pVS->lpVtbl->Release(pVS);
    pPS->lpVtbl->Release(pPS);

    sc->lpVtbl->Release(sc);
    view->lpVtbl->Release(view);
    d3ddev->lpVtbl->Release(d3ddev);
    d3dctx->lpVtbl->Release(d3dctx);

}
