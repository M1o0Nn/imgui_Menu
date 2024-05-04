#pragma once
#include <string>
#include <random>

#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#pragma comment(lib,"d3d11.lib")
#include <d3dx11.h>
#pragma comment(lib,"d3dx11.lib")

#include "other/IconFont.hpp"
#include "other/HitBoxex.h"

#include "myImgui.hpp"

ImFont* icon_font = nullptr;
ImFont* small_font = nullptr;
ImFont* big_font = nullptr;
ImFont* logo_font = nullptr;
ID3D11ShaderResourceView* pTextureView = NULL;

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

void SetStyle()
{
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Button] = ImVec4(0.09f, 0.09f, 0.09f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	
	ImGui::GetStyle().ItemSpacing = { 0.f, 0.f };
	ImGui::GetStyle().WindowPadding = { 0.f, 0.f };

}
using namespace ImGui;

void Legitbot(ImVec2& cursorpos)
{
	myBeginChild("Aimbot", ImVec2(230, 300), &config::legitbot::aim_enable);
	{
		if (config::legitbot::aim_enable)
		{
			static float aa = 15.5;
			AddSliderFloat("Hipfire distance", &config::legitbot::aim_hip_dis, 0, 100, "%.0f");
			AddSliderFloat("Zoom distance", &config::legitbot::aim_zoom_dis, 0, 300, "%.0f");
			AddHotkey("Aim key", &config::legitbot::aim_key_1);
			AddHotkey("Extra key", &config::legitbot::aim_key_2);
		}
		
	}
	myEndChild();

	ImGui::SetCursorPos({ cursorpos.x + 250, cursorpos.y + 60 });
	myBeginChild("Tigerbot", ImVec2(230, 200), &config::legitbot::tig_enable);
	{
		if (config::legitbot::tig_enable)
		{
			AddSliderFloat("Distance", &config::legitbot::tig_dis, 0, 100, "%.0f");
			AddHotkey("Tiger key", &config::legitbot::tig_key);
		}
	}
	myEndChild();

	ImGui::SetCursorPos({ cursorpos.x + 10, cursorpos.y + 370 });
	myBeginChild("Hiebox", ImVec2(230, 200));
	{
		AddCheckBox("Advanced", &config::legitbot::hitbox_adv);
		if (!config::legitbot::hitbox_adv)
		{
			const char* HitBoneIndex[] = { "Head", "Neck", "UpperChest","LowerChest","Stomach","Hip","Auto" };
			AddCombo("Hitbone", &config::legitbot::hitbox_idx, HitBoneIndex, IM_ARRAYSIZE(HitBoneIndex), 125);
		}
	}
	myEndChild();

	ImGui::SetCursorPos({ cursorpos.x + 250, cursorpos.y + 270 });
	myBeginChild("Recoilbot", ImVec2(230, 100), &config::legitbot::rec_enable);
	{
		if(config::legitbot::rec_enable)
		{
			AddSliderFloat("Recoil X", &config::legitbot::recoil_x, 0, 1, "%.2f");
			AddSliderFloat("Recoil Y", &config::legitbot::recoil_y, 0, 1, "%.2f");
		}
	}
	myEndChild();
}

void Visual(ImVec2& cursorpos)
{
	myBeginChild("Glow", { 230,520 });
	{

	}
	myEndChild();

	ImGui::SetCursorPos({ cursorpos.x + 250, cursorpos.y + 60 });
	myBeginChild("Overlap", { 230,520 });
	{

	}
	myEndChild();
}

void Misc(ImVec2& cursorpos)
{
	myBeginChild("Setting", { 230,520 });
	{

	}
	myEndChild();

	ImGui::SetCursorPos({ cursorpos.x + 250, cursorpos.y + 60 });
	myBeginChild("Menu", { 230,520 });
	{
		AddColorEdit3("Theme color", config::menu_color::theme_col);
		AddColorEdit3("Begin title color", config::menu_color::begin_title_col);
		AddColorEdit3("Begin back color", config::menu_color::begin_bgcol);
		AddColorEdit3("Titlebar back color", config::menu_color::begin_left_bgcol);
		AddColorEdit3("Main back color", config::menu_color::begin_right_bgcol);
	}
	myEndChild();
}

void Config(ImVec2& cursorpos)
{
	auto ZhanW = [](ImVec2 tmp1, ImVec2 tmp2){ImGui::SetCursorPos(ImVec2(tmp1.x + tmp2.x, tmp1.y + tmp2.y)); };
	myBeginChild("Config list", { 230,520 });
	{

	}
	myEndChild();

	ImGui::SetCursorPos({ cursorpos.x + 250, cursorpos.y + 60 });
	myBeginChild("Config setting", { 230,520 });
	{
		ZhanW(ImGui::GetCursorPos(), { 10.f,15.f });
		AddIconButton(ICON_SAVE,"Save", ICON_SAVE " Save",IM_COL32(255, 255, 255, 255), []() {
			// 保存参数
			});

		ZhanW(ImGui::GetCursorPos(), { 10.f,15.f });
		AddIconButton(ICON_FILE, "Load", ICON_FILE " Load", IM_COL32(255, 255, 255, 255), []() {
			// 保存参数
			});

		ZhanW(ImGui::GetCursorPos(), { 10.f,15.f });
		AddIconButton(ICON_FOLD, "Open config folder", ICON_FOLD " Open config folder", IM_COL32(255, 255, 255, 255), []() {
			// 保存参数
			});
	}
	myEndChild();
}

void Hitboxex(ImVec2& mainBeginSize)
{
	static float current_states_hitboxex_x{};
	current_states_hitboxex_x = Lerp(current_states_hitboxex_x, config::legitbot::hitbox_adv ? 340.f : 0.f, 0.1f);
	ImGui::PushFont(big_font);
	if (current_states_hitboxex_x > 32.000000001f)
	{
		ImGui::SetNextWindowSize(ImVec2(current_states_hitboxex_x, 600.f));
		ImGui::SetNextWindowPos(ImVec2(mainBeginSize.x + 673, mainBeginSize.y));
		ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(30, 30, 30, 255));
		ImGui::Begin("test", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
		{
			const char* HitBoneChar[] = { "Head", "Neck", "UpperChest", "LowerChest", "Stomach", "Hip" };
			const ImVec2 HitBoneVec2[] = { ImVec2(172.f,100.f), ImVec2(172.f,140.f), ImVec2(172.f,182.f), ImVec2(172.f,222.f), ImVec2(172.f,265.f), ImVec2(172.f,310.f) };
			static bool HitBoneBool[6] = {  };
			AddHitBoxex(HitBoneChar, HitBoneVec2, HitBoneBool, IM_ARRAYSIZE(HitBoneChar));
		}
		ImGui::End();
		ImGui::PopStyleColor();
	}
	ImGui::PopFont();
}

void Menu()
{
	// 菜单绘制
	//ImGui::ShowDemoWindow();

	//static ImVec2 WindSize = ImVec2(679, 600);
	//static const char* LogoTitle = "   CLOUD   ";
	static ImVec2 WindSize = ImVec2(670, 600);
	static const char* LogoTitle = "PARTICLE";
	ImGui::PushFont(logo_font);
	static auto LogoTextSize = ImGui::CalcTextSize(LogoTitle);
	static auto LeftWid = LogoTextSize.x + 30;
	ImGui::PopFont();

	ImGui::SetNextWindowSize(WindSize);
	ImGui::Begin("main", (bool*)0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
	{
		static int PageIdx = 0;
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(config::menu_color::begin_left_bgcol[0], config::menu_color::begin_left_bgcol[1], config::menu_color::begin_left_bgcol[2], 1.00f));
		ImGui::BeginChild("Left", { LeftWid,WindSize.y },ImGuiChildFlags_AlwaysAutoResize);
		ImGui::PopStyleColor();
		{
			ImGui::PushFont(logo_font);
			ImGui::SetCursorPos({ 15.f,20.f });
			AddLogoTitle(LogoTitle, ImGui::ColorConvertFloat4ToU32(ImVec4(config::menu_color::theme_col[0], config::menu_color::theme_col[1], config::menu_color::theme_col[2], 0.8f)));
			ImGui::PopFont();

			{
				const char* PageTitleChar[] = { "Legitbot", "Visual", "Misc", "Config" };
				const char* PageTitleICon[] = { ICON_MOUSE, ICON_EARTH, ICON_MISC, ICON_GEAR };
				AddPageTitle(&PageIdx, PageTitleICon, PageTitleChar, IM_ARRAYSIZE(PageTitleChar));
			}
		}
		ImGui::EndChild();

		ImGui::SetCursorPos({ LeftWid,0 });
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(config::menu_color::begin_right_bgcol[0], config::menu_color::begin_right_bgcol[1], config::menu_color::begin_right_bgcol[2], 1.00f));
		ImGui::BeginChild("Right", { WindSize.x - LeftWid,WindSize.y });
		ImGui::PopStyleColor();
		{
			ImVec2 cursorpos = ImGui::GetCursorPos();
			//ImGui::PushStyleColor(ImGuiColor)
			ImGui::SetCursorPos({ cursorpos.x + 17.f, cursorpos.y + 12 });
			AddIconButton(ICON_SAVE, "Save Config", ICON_SAVE " Save Config", IM_COL32(100, 100, 100, 255), []() {
				// 保存参数
				});

			ImGui::SetCursorPos({ cursorpos.x, cursorpos.y + 50 });
			ImGui::Separator();

			ImGui::SetCursorPos({ cursorpos.x + 10, cursorpos.y + 60 });
			switch (PageIdx)
			{
			case 0:
				Legitbot(cursorpos);
				break;
			case 1:
				Visual(cursorpos);
				break;
			case 2:
				Misc(cursorpos);
				break;
			case 3:
				Config(cursorpos);
				break;
			break;
			break;
			break;
			default:
				break;
			}
			
		}
		ImGui::EndChild();
	}
	auto mainBeginSize = ImGui::GetWindowPos();
	ImGui::End();

	Hitboxex(mainBeginSize);
}

int CreateWnd(HINSTANCE hInst, bool* bEnalbe, HWND hGamehWnd = nullptr)
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
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\arialbd.ttf", 17.0f, nullptr, io.Fonts->GetGlyphRangesChineseFull());
	io.Fonts->AddFontDefault();

	logo_font = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\ariblk.ttf", 38.0f);
	io.Fonts->AddFontDefault();

	float baseFontSize = 17.0f;
	float iconFontSize = baseFontSize * 2.0f / 1.8f;
	ImFontConfig config;
	config.MergeMode = true;
	config.PixelSnapH = true;
	config.GlyphMinAdvanceX = iconFontSize;
	static const ImWchar icon_ranges[] = { ICON_MIN, ICON_MAX, 0 };
	icon_font =  io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\arialbd.ttf", baseFontSize, nullptr, io.Fonts->GetGlyphRangesChineseFull());
	io.Fonts->AddFontFromMemoryCompressedTTF(IconFont_compressed_data, IconFont_compressed_size, iconFontSize, &config, icon_ranges);	

	io.Fonts->AddFontDefault();
	small_font = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\arialbd.ttf", 13.0f, nullptr, io.Fonts->GetGlyphRangesChineseFull());

	io.Fonts->AddFontDefault();
	baseFontSize = 28.0f;
	iconFontSize = baseFontSize * 2.0f / 1.8f;
	big_font = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\arialbd.ttf", 22.f, nullptr, io.Fonts->GetGlyphRangesChineseFull());
	io.Fonts->AddFontFromMemoryCompressedTTF(IconFont_compressed_data, IconFont_compressed_size, iconFontSize, &config, icon_ranges);

	ImGui::StyleColorsDark();
	SetStyle();

	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(device, device_context);

	ID3D11Resource* resource;
	D3DX11CreateTextureFromMemory(device, HitBoxex, HitBoxex_size, NULL, NULL, &resource, NULL);
	device->CreateShaderResourceView(resource, NULL, &pTextureView);

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	static bool bShowMenu = true;
	while (*bEnalbe)
	{
		MSG msg;
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
				*bEnalbe = false;
		}if (!*bEnalbe) break;


		static size_t key = 0;
		// 菜单窗口控制
		if (GetAsyncKeyState(key) & 0x1) {
			bShowMenu = !bShowMenu;
			Sleep(10);
		}

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		if (bShowMenu)
		{
			Menu();
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