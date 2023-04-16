# DaddyKermitsVAL_SDK
This is a simple ImGui Internal SDK for VALORANT

for people using hookloader you need to add this code above dllmain

extern "C" __declspec(dllexport) int NextHook(int code, WPARAM wParam, LPARAM lParam) {
	return CallNextHookEx(NULL, code, wParam, lParam);
}
