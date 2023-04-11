#include "includes.h"
#include <stdlib.h>
#include <stdio.h>
#include "Decryption.h"
#include "Offsets.h"
#include "SDK.h"
#include "Config.h"


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

uintptr_t UWorldXOR;
Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (uMsg == WM_KEYDOWN)
	{
		switch (wParam)
		{
		case Config::ToggleMenu:
			Config::MenuOpen = !Config::MenuOpen;
			break;
		}
	}

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

void Style()
{
	auto style = &ImGui::GetStyle();
	auto colors = style->Colors;
	style->WindowPadding = { 4.f, 4.f };
	style->FramePadding = { 4.f, 2.f };
	style->ItemSpacing = { 4.f, 4.f };
	style->ItemInnerSpacing = { 4.f, 4.f };
	style->TouchExtraPadding = { 0.f, 0.f };
	style->IndentSpacing = 30.f;
	style->ScrollbarSize = 10.f;
	style->GrabMinSize = 6.f;

	style->WindowBorderSize = 0.f;
	style->ChildBorderSize = 1.f;
	style->PopupBorderSize = 1.f;
	style->FrameBorderSize = 1.f;
	style->TabBorderSize = 1.f;

	style->WindowRounding = 0.f;
	style->ChildRounding = 0.f;
	style->FrameRounding = 0.f;
	style->PopupRounding = 0.f;
	style->ScrollbarRounding = 0.f;
	style->GrabRounding = 0.f;
	style->TabRounding = 0.f;

	colors[ImGuiCol_Text] = { 0.86f, 0.86f, 0.86f, 1.00f };
	colors[ImGuiCol_TextDisabled] = { 0.43f, 0.43f, 0.43f, 1.00f };
	colors[ImGuiCol_WindowBg] = { 0.16f, 0.16f, 0.16f, 1.00f };
	colors[ImGuiCol_ChildBg] = { 0.00f, 0.00f, 0.00f, 0.00f };
	colors[ImGuiCol_PopupBg] = { 0.08f, 0.08f, 0.08f, 0.94f };
	colors[ImGuiCol_Border] = { 0.31f, 0.31f, 0.31f, 1.00f };
	colors[ImGuiCol_BorderShadow] = { 0.00f, 0.00f, 0.00f, 0.00f };
	colors[ImGuiCol_FrameBg] = { 0.12f, 0.12f, 0.12f, 1.00f };
	colors[ImGuiCol_FrameBgHovered] = { 0.13f, 0.13f, 0.13f, 1.00f };
	colors[ImGuiCol_FrameBgActive] = { 0.15f, 0.15f, 0.15f, 1.00f };
	colors[ImGuiCol_TitleBg] = { 0.08f, 0.08f, 0.08f, 1.00f };
	colors[ImGuiCol_TitleBgActive] = { 0.09f, 0.09f, 0.09f, 1.00f };
	colors[ImGuiCol_TitleBgCollapsed] = { 0.11f, 0.11f, 0.11f, 1.00f };
	colors[ImGuiCol_MenuBarBg] = { 0.12f, 0.12f, 0.12f, 1.00f };
	colors[ImGuiCol_ScrollbarBg] = { 0.12f, 0.12f, 0.12f, 1.00f };
	colors[ImGuiCol_ScrollbarGrab] = { 0.75f, 0.37f, 0.37f, 1.00f };
	colors[ImGuiCol_ScrollbarGrabHovered] = { 0.78f, 0.41f, 0.41f, 1.00f };
	colors[ImGuiCol_ScrollbarGrabActive] = { 0.82f, 0.45f, 0.45f, 1.00f };
	colors[ImGuiCol_CheckMark] = { 0.75f, 0.37f, 0.37f, 1.00f };
	colors[ImGuiCol_SliderGrab] = { 0.75f, 0.37f, 0.37f, 1.00f };
	colors[ImGuiCol_SliderGrabActive] = { 0.82f, 0.45f, 0.45f, 1.00f };
	colors[ImGuiCol_Button] = { 0.14f, 0.14f, 0.14f, 1.00f };
	colors[ImGuiCol_ButtonHovered] = { 0.75f, 0.37f, 0.37f, 1.00f };
	colors[ImGuiCol_ButtonActive] = { 0.78f, 0.41f, 0.41f, 1.00f };
	colors[ImGuiCol_Header] = { 0.14f, 0.14f, 0.14f, 1.00f };
	colors[ImGuiCol_HeaderHovered] = { 0.75f, 0.37f, 0.37f, 1.00f };
	colors[ImGuiCol_HeaderActive] = { 0.78f, 0.41f, 0.41f, 1.00f };
	colors[ImGuiCol_Separator] = { 0.43f, 0.43f, 0.50f, 0.50f };
	colors[ImGuiCol_SeparatorHovered] = { 0.10f, 0.40f, 0.75f, 0.78f };
	colors[ImGuiCol_SeparatorActive] = { 0.10f, 0.40f, 0.75f, 1.00f };
	colors[ImGuiCol_ResizeGrip] = { 0.26f, 0.59f, 0.98f, 0.25f };
	colors[ImGuiCol_ResizeGripHovered] = { 0.26f, 0.59f, 0.98f, 0.67f };
	colors[ImGuiCol_ResizeGripActive] = { 0.26f, 0.59f, 0.98f, 0.95f };
	colors[ImGuiCol_Tab] = { 0.18f, 0.35f, 0.58f, 0.86f };
	colors[ImGuiCol_TabHovered] = { 0.26f, 0.59f, 0.98f, 0.80f };
	colors[ImGuiCol_TabActive] = { 0.20f, 0.41f, 0.68f, 1.00f };
	colors[ImGuiCol_TabUnfocused] = { 0.07f, 0.10f, 0.15f, 0.97f };
	colors[ImGuiCol_TabUnfocusedActive] = { 0.14f, 0.26f, 0.42f, 1.00f };
	colors[ImGuiCol_PlotLines] = { 0.61f, 0.61f, 0.61f, 1.00f };
	colors[ImGuiCol_PlotLinesHovered] = { 1.00f, 0.43f, 0.35f, 1.00f };
	colors[ImGuiCol_PlotHistogram] = { 0.90f, 0.70f, 0.00f, 1.00f };
	colors[ImGuiCol_PlotHistogramHovered] = { 1.00f, 0.60f, 0.00f, 1.00f };
	colors[ImGuiCol_TextSelectedBg] = { 0.78f, 0.41f, 0.41f, 1.00f };
	colors[ImGuiCol_DragDropTarget] = { 1.00f, 1.00f, 0.00f, 0.90f };
	colors[ImGuiCol_NavHighlight] = { 0.26f, 0.59f, 0.98f, 1.00f };
	colors[ImGuiCol_NavWindowingHighlight] = { 1.00f, 1.00f, 1.00f, 0.70f };
	colors[ImGuiCol_NavWindowingDimBg] = { 0.80f, 0.80f, 0.80f, 0.20f };
	colors[ImGuiCol_ModalWindowDimBg] = { 0.80f, 0.80f, 0.80f, 0.35f };
}

bool init = false;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)& pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)& pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

	if (!pSwapChain)
	{
		MessageBoxA(0, "this msg box means pSwapChain is not working something is wrong", "ERROR!!!", 0);
		return 0;
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	Style();

	auto& io = ImGui::GetIO();
	const ImVec2 screen_size(io.DisplaySize);
	const ImVec2 screen_center(screen_size[0] * 0.5f, screen_size[1] * 0.5f);

	const ImVec2 window_size(540.f, 320.f);
	const ImVec2 window_center(screen_center[0] - (window_size[0] * 0.5f), screen_center[1] - (window_size[1] * 0.5f));

	if (Config::MenuOpen)
	{
		ImGui::Begin("DaddyKermits VALORANT ImGui SDK", nullptr, ImGuiWindowFlags_NoResize);
		{
			ImGui::Text("Obama");
			ImGui::Text("Check console for more info");
			ImGui::Text("");
			ImGui::Text("Built on: (" __DATE__ ", " __TIME__ ")");
		}
		ImGui::End();
	}

	ImGui::Render();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
	uintptr_t Obama;
	Obama = (uintptr_t)GetModuleHandleA(0);
	uintptr_t WorldKey = *(uintptr_t*)(Obama + Offsets::Key);
	printf("\nWorldKey:%p\n", WorldKey);
	State StateKey = *(State*)(Obama + Offsets::State);
	printf("StateKey:%p\n", StateKey);
	UWorldXOR = Decryption::Decrypt_UWorld(WorldKey, (uintptr_t*)&StateKey);
	printf("UWorldXOR:%p\n", UWorldXOR);
	printf("If any of these are 0x00000000 offsets are either wrong or your injector is not working");
	MessageBoxA(0, "This is not a fully working cheat you need to add stuff yourself\n you need to implment the pointer yourself\n I will also keep this updated and \nwork on this some more", "", 0);
	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)& oPresent, hkPresent);
			init_hook = true;
		}
	} while (!init_hook);
	return TRUE;
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		AllocConsole();
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);
		DisableThreadLibraryCalls(hMod);
		printf("HModule: %p", hMod);
		CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}