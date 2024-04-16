#pragma once
#include <string>
#include <random>

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#pragma comment(lib,"d3d11.lib")

#include "fonts/iconFont.hpp"
#include "fonts/IconsFontAwesome4.h"

inline bool bShowMenu = true;
inline bool bMainLoop = true;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;
	switch (msg)
	{
	case WM_CLOSE:
		// 在这里添加主线程控制
		break;
	case WM_SIZE:
		if (wParam == SIZE_MINIMIZED)
			return 0;
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

std::wstring random_wstring_window()
{
	srand((unsigned)time(NULL));
	std::wstring str = L"QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890";
	std::wstring newstr;
	int pos;
	while (newstr.size() != 15)
	{
		pos = ((rand() % (str.size() + 1)));
		newstr += str.substr(pos, 1);
	}
	return newstr;
}

int CreateWnd(HINSTANCE hInst, HWND GamehWnd = nullptr)
{
	std::wstring WndClass = random_wstring_window();
	WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr,WndClass.c_str(), nullptr };
	::RegisterClassExW(&wc);
	HWND hwnd = ::CreateWindowW(wc.lpszClassName, random_wstring_window().c_str(), WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, nullptr, nullptr, wc.hInstance, nullptr);

	// d3d11
	DXGI_SWAP_CHAIN_DESC sd{};
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hwnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;


	constexpr D3D_FEATURE_LEVEL levels[2]
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_0,
	};
	ID3D11Device* device{ nullptr };
	ID3D11DeviceContext* device_context{ nullptr };
	IDXGISwapChain* swap_chain{ nullptr };
	ID3D11RenderTargetView* render_target_view{ nullptr };
	D3D_FEATURE_LEVEL level{};

	HRESULT res = D3D11CreateDeviceAndSwapChain(
		nullptr, D3D_DRIVER_TYPE_HARDWARE, 
		nullptr, 0, levels, 2, 
		D3D11_SDK_VERSION, 
		&sd, 
		&swap_chain,
		&device,
		&level,
		&device_context);

	if (res == DXGI_ERROR_UNSUPPORTED)
		res = D3D11CreateDeviceAndSwapChain(
			nullptr, D3D_DRIVER_TYPE_WARP, 
			nullptr, 0, levels, 2, 
			D3D11_SDK_VERSION,
			&sd,
			&swap_chain,
			&device,
			&level,
			&device_context);
	if (res != S_OK)
		return false;

	ID3D11Texture2D* back_buffer{ nullptr };
	swap_chain->GetBuffer(0, IID_PPV_ARGS(&back_buffer));

	if (back_buffer) {
		device->CreateRenderTargetView(back_buffer, 0, &render_target_view);
		back_buffer->Release();
	}
	else
		return -1;

	ShowWindow(hwnd, SW_HIDE);
	UpdateWindow(hwnd);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
	io.ConfigViewportsNoAutoMerge = true;
	//io.ConfigViewportsNoTaskBarIcon = true;
	//icoFont_compressed_data

	io.Fonts->AddFontDefault();
	ImFontConfig config;
	config.MergeMode = true;
	config.PixelSnapH = true;
	config.OversampleH = 3;
	config.OversampleV = 3;
	static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
	ImFont* icon_font = io.Fonts->AddFontFromMemoryCompressedTTF(iconFont_compressed_data, iconFont_compressed_size, 32.f, &config, icon_ranges);

	ImGui::StyleColorsClassic();

	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(device, device_context);

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	while (bMainLoop)
	{
		MSG msg;
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
				bMainLoop = false;
		}if (!bMainLoop) break;


		static size_t key = 0;
		// 菜单窗口控制
		if (GetAsyncKeyState(key) & 1) {
			bShowMenu = !bShowMenu;
			Sleep(10);
		}

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		if (bShowMenu)
		{
			// 菜单绘制
			ImGui::ShowDemoWindow(&bMainLoop);


			ImGui::Begin("123");
			ImGui::HotKeyButton(&key);
			ImGui::PushFont(icon_font);
			ImGui::Button(ICON_FA_CROSSHAIRS " Aimbot");
			ImGui::Button(ICON_FA_EYE " Visual");
			ImGui::Button(ICON_FA_COG " Setting");
			ImGui::PopFont();
			ImGui::End();
		}

		ImGui::Render();
		const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
		device_context->OMSetRenderTargets(1, &render_target_view, NULL);
		device_context->ClearRenderTargetView(render_target_view, clear_color_with_alpha);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		swap_chain->Present(1, 0);
	}

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	if (render_target_view) { render_target_view->Release(); render_target_view = NULL; }
	if (swap_chain) { swap_chain->Release(); swap_chain = NULL; }
	if (device_context) { device_context->Release(); device_context = NULL; }
	if (device) { device->Release(); device = NULL; }
	::DestroyWindow(hwnd);
	::UnregisterClass(wc.lpszClassName, wc.hInstance);
}