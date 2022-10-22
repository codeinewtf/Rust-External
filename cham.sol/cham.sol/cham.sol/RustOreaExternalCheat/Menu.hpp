#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include <d3d11.h>
#include <random>
#include <dwmapi.h>
#include "glob.h"
#include "imgui/imgui_impl_win32.h"
#include "mainfun.h"
#include "D2DHelper.h"
#include "Misc For A nigger.h"
#include "imgui/imgui_internal.h"
#define safe_str
bool b_Shutdown = false;
HWND h_Game;
bool is_menu = false;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);




void ToggleButton(const char* str_id, bool* v)
{
    ImVec2 p = ImGui::GetCursorScreenPos();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    float height = ImGui::GetFrameHeight();
    float width = height * 1.55f;
    float radius = height * 0.50f;
    if (ImGui::InvisibleButton(str_id, ImVec2(width, height)))
        *v = !*v;
    ImU32 col_bg;
    if (ImGui::IsItemHovered())
        col_bg = *v ? IM_COL32(145 + 20, 211, 68 + 20, 255) : IM_COL32(218 - 20, 218 - 20, 218 - 20, 255);
    else
        col_bg = *v ? IM_COL32(145, 211, 68, 255) : IM_COL32(218, 218, 218, 255);
    draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
    draw_list->AddCircleFilled(ImVec2(*v ? (p.x + width - radius) : (p.x + radius), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));
}

namespace draw
{
    HWND h_hWnd;
    WNDCLASSEX wc;

    ID3D11Device* g_pd3dDevice = NULL;
    ID3D11DeviceContext* g_pd3dDeviceContext = NULL;
    IDXGISwapChain* g_pSwapChain = NULL;
    ID3D11RenderTargetView* g_mainRenderTargetView = NULL;

    int selected;

    void UpdateWND()
    {
        while (true)
        {
            if (GetAsyncKeyState(VK_INSERT) != 0)
                is_menu = !is_menu;

            long style = GetWindowLongPtr(h_hWnd, GWL_EXSTYLE);
            FunctionsMain();



            if (is_menu)
            {
                style &= ~WS_EX_LAYERED;
                SetWindowLongPtr(h_hWnd, GWL_EXSTYLE, style);
            }
            else
            {
                style |= WS_EX_LAYERED;
                SetWindowLongPtr(h_hWnd, GWL_EXSTYLE, style);
            }
            Sleep(100);
        }
    }

    void draw_box(ImVec2 p1, ImVec2 p2, ImDrawList* draw_list)
    {
        draw_list->AddRect(p1, p2, ImGui::ColorConvertFloat4ToU32(ImVec4(colors::boxcolor1, colors::boxcolor2, colors::boxcolor3, 1)), 0.f, 0, 1.5);
    }

    auto CleanupRenderTarget() -> void
    {
        if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
    }

    auto CleanupDeviceD3D() -> void
    {
        CleanupRenderTarget();
        if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
        if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
        if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
    }

    void CreateRenderTarget()
    {
        ID3D11Texture2D* pBackBuffer;
        g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
        g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
        pBackBuffer->Release();
    }

    float fovcolor[4] = { 3.10f, 0.09f, 2.12f, 1.00f };

    float fovamount = 120;

    ImU32 __fastcall FtIM2(float* color) {
        return ImGui::ColorConvertFloat4ToU32(ImVec4(color[0], color[1], color[2], color[3]));
    }

    bool CreateDeviceD3D()
    {
        /* setup swap chain */
        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.BufferCount = 2;
        sd.BufferDesc.Width = 0;
        sd.BufferDesc.Height = 0;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 300;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = h_hWnd;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;
        sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        UINT createDeviceFlags = 0;
        D3D_FEATURE_LEVEL featureLevel;
        const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
        if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
            return false;

        CreateRenderTarget();
        return true;
    }

    void Shutdown()
    {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
        CleanupDeviceD3D();
        DestroyWindow(h_hWnd);
        UnregisterClass(wc.lpszClassName, wc.hInstance);
        std::exit(0);
    }

    LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
            return true;

        switch (msg)
        {
        case WM_SYSCOMMAND:
            if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application Render
                return 0;
            break;
        case WM_DESTROY:
            ::PostQuitMessage(0);
            return 0;
        default: break;
        }

        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    /**
     * initializes the renderer
     */
    bool Initialize()
    {
        WINDOWPLACEMENT g_wpPrev;
        DWORD dwStyle = GetWindowLong(h_Game, GWL_STYLE);
        MONITORINFO mi = { sizeof(mi) };
        if (GetWindowPlacement(h_Game, &g_wpPrev) &&
            GetMonitorInfo(MonitorFromWindow(h_Game,
                MONITOR_DEFAULTTOPRIMARY), &mi)) {
            SetWindowLong(h_Game, GWL_STYLE,
                dwStyle & ~WS_OVERLAPPEDWINDOW);
            SetWindowPos(h_Game, HWND_TOP,
                mi.rcMonitor.left, mi.rcMonitor.top,
                mi.rcMonitor.right - mi.rcMonitor.left,
                mi.rcMonitor.bottom - mi.rcMonitor.top,
                SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
        }

        // Create application window
        wc = { sizeof(WNDCLASSEX),ACS_TRANSPARENT, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, ("Windows Task Assistant"), NULL };
        RegisterClassEx(&wc);
        h_hWnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE | WS_EX_LAYERED, wc.lpszClassName, (""), WS_POPUP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), NULL, NULL, wc.hInstance, NULL);
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)UpdateWND, 0, 0, 0);
        MARGINS margins = { -1 };
        DwmExtendFrameIntoClientArea(h_hWnd, &margins);
        ImGui::CreateContext();
        SetLayeredWindowAttributes(h_hWnd, 0, 1.0f, LWA_ALPHA);
        SetLayeredWindowAttributes(h_hWnd, 0, RGB(0, 0, 0), LWA_COLORKEY);

        // Initialize Direct3D
        if (!CreateDeviceD3D())
        {
            CleanupDeviceD3D();
            UnregisterClass(wc.lpszClassName, wc.hInstance);
            return 1;
        }

        ShowWindow(h_hWnd, SW_SHOWDEFAULT);
        UpdateWindow(h_hWnd);

        SetForegroundWindow(h_hWnd);

        //IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.IniFilename = nullptr;
        io.Fonts->AddFontDefault();
        ImFont* mdFont1 = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\tahoma.ttf", 16.f);
        ImFont* mdFont = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Verdana.ttf", 16.f);

        ImGui_ImplWin32_Init(h_hWnd);
        ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

        MSG msg;
        ZeroMemory(&msg, sizeof(msg));

        while (msg.message != WM_QUIT)
        {
            if (b_Shutdown)
                break;

            if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
                continue;
            }

            struct options {
                const char* cheatoptions;
                std::string Status;
            };

            std::vector<options> option =
            {
                {"Esp"},
                {"Aimbot"},
                {"Exploits"},
                {"Misc"},
                {"Colors"}
            };

            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();
            if (miscoptions::viewplayers == true)
            {

                ImGui::SetNextWindowSize(ImVec2(180, 270));
                ImGui::Begin("Chams-> Info", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoResize | WS_EX_TOPMOST | CS_CLASSDC | ImGuiWindowFlags_NoBringToFrontOnFocus | WS_EX_TOPMOST | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);
                {
                    ImGui::Text("Chams-> Info");
                    ImGui::End();
                }

            }
            if (aimbot::ciclefov == true)
            {
                ImGui::Begin("##CIRCLE", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                    ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar);
                auto draw = ImGui::GetBackgroundDrawList();
                draw->AddCircle(ImVec2(GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN) / 2), fovamount, FtIM2(fovcolor), 100, 1.0f);
                ImGui::PushFont(mdFont);
                static float r = 1.00f, g = 0.00f, b = 1.00f;
                static int cases = 0;
                switch (cases)
                {
                case 0: { r -= 0.005f; if (r <= 0) cases += 1; break; }
                case 1: { g += 0.005f; b -= 0.005f; if (g >= 1) cases += 1; break; }
                case 2: { r += 0.005f; if (r >= 1) cases += 1; break; }
                case 3: { b += 0.005f; g -= 0.005f; if (b >= 1) cases = 0; break; }
                default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
                }
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(10.0f, 0.0f, 0.0f, 255.f));
                ImGui::Text ("Chams.solution", D2D1::ColorF::Red);
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 255.0f, 0.0f, 255.f));
                ImGui::Text("Status UD [" __DATE__ "]", D2D1::ColorF::LightGreen);
                ImGui::End();
            }
            ImGui::PopFont;
            ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
            POINT mPos;
            GetCursorPos(&mPos);
            ImVec2 window_size = ImVec2(680, 470);
            ImGui::SetNextWindowSize(ImVec2(window_size.x, window_size.y));
            ImGui::SetNextWindowPos(ImVec2(GetSystemMetrics(SM_CXSCREEN) / 2 - window_size.x / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - window_size.y / 2), ImGuiCond_Once);
            ImGui::SetNextWindowSize(ImVec2(680, 470));
            if (is_menu)
            {
                ImGui::Begin("Chams.solution", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoResize | WS_EX_TOPMOST | CS_CLASSDC | ImGuiWindowFlags_NoBringToFrontOnFocus | WS_EX_TOPMOST | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);
                {
                    ImGui::PushFont(mdFont1);
                    ImGui::SetNextWindowSize(ImVec2(680, 470));
                    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 1.f, 1.f, 1.f));
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.f, 0.f, 1.f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.00, 0.30, 0.f, 1.f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.612, 0.f, 0.f, 1.f));
                    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.075, 0.078, 0.094, 1.f));
                    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(118.f, 0.f, 0.f, 1.f));
                    ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(166, 0.f, 0.f, 255.f));
                    ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.612, 0.f, 0.f, 1.f));
                    ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.687, 0.f, 0.f, 1.f));
                    ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.612, 0.f, 0.f, 1.f));
                    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0, 0.f, 0.f, 255.f));
                    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0, 0.f, 0.f, 255.f));
                    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0, 0.f, 0.f, 255.f));
                    ImGui::PushStyleColor(ImGuiCol_CheckMark, ImVec4(166, 0.f, 0.f, 255.f));
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(255.f, 255.f, 255.f, 255.f));
                    ImGui::Text("                                 Chams.solution");
                    ImGui::BeginChild("##LeftSide", ImVec2(ImGui::GetContentRegionAvail().x, 50), true);
                    ImGui::SameLine();
                    ImGui::Spacing();
                    ImGui::SameLine();

                    if (ImGui::Button("Aimbot", ImVec2(100.0f, 30.0f)))
                    {
                        menu::Aimbot = 1;
                        menu::misc = 0;
                        menu::ESP = 0;
                        menu::Settings = 0;
                        menu::misc = 0;
                        menu::info = 0;

                    }
                    ImGui::SameLine();
                    ImGui::Spacing();
                    ImGui::SameLine();
                    if (ImGui::Button("Misc", ImVec2(100.0f, 30.0f)))
                    {
                        menu::Aimbot = 0;
                        menu::misc = 1;
                        menu::ESP = 0;
                        menu::Settings = 0;
                        menu::info = 0;

                    }
                    ImGui::SameLine();
                    ImGui::Spacing();
                    ImGui::SameLine();

                    if (ImGui::Button("Visuals", ImVec2(100.0f, 30.0f)))
                    {
                        menu::Aimbot = 0;
                        menu::misc = 0;
                        menu::ESP = 1;
                        menu::Settings = 0;
                        menu::misc = 0;
                        menu::info = 0;

                    }
                    ImGui::SameLine();
                    ImGui::Spacing();
                    ImGui::SameLine();

                    if (ImGui::Button("Settings", ImVec2(100.0f, 30.0f)))
                    {
                        menu::Aimbot = 0;
                        menu::misc = 0;
                        menu::ESP = 0;
                        menu::Settings = 1;
                        menu::misc = 0;
                        menu::info = 0;

                    }
                    ImGui::SameLine();
                    ImGui::Spacing();
                    ImGui::SameLine();

                    if (ImGui::Button("Config", ImVec2(100.0f, 30.0f)))
                    {
                        menu::Aimbot = 0;
                        menu::misc = 0;
                        menu::ESP = 0;
                        menu::Settings = 0;
                        menu::misc = 0;
                        menu::info = 1;
                    }
                    ImGui::EndChild();


                    if (menu::Aimbot)
                    {
                        ImGui::SetCursorPos(ImVec2(10.0f, 100.0f));
                        ImGui::Checkbox("Enable PSilent", &aimbot::pSilent);
                        ImGui::SetCursorPos(ImVec2(140.0f, 100.0f));
                        ImGui::Checkbox("Enable AimBot", &aimbot::aimbot);
                        ImGui::SetCursorPos(ImVec2(10.0f, 130.0f));
                        ImGui::Checkbox("Prediction", &aimbot::prediction);
                        ImGui::SetCursorPos(ImVec2(10.0f, 160.0f));
                        ImGui::Checkbox("Head Only", &aimbot::HeadOnly);
                        ImGui::SetCursorPos(ImVec2(10.0f, 190.0f));
                        ImGui::Checkbox("Smoothing", &aimbot::Smoothing);
                        ImGui::SetCursorPos(ImVec2(10.0f, 220.0f));
                        ImGui::Checkbox("Anti Team", &aimbot::AntiTeam);
                        ImGui::SetCursorPos(ImVec2(10.0f, 250.0f));
                        ImGui::Checkbox("Anti Down", &aimbot::AntiDown);
                        ImGui::SetCursorPos(ImVec2(10.0f, 280.0f));
                        ImGui::SliderFloat("Aimbot Distance", &floatsliders::aimbotdistance, 1.0f, 500.0f);ImGui::SetCursorPos(ImVec2(140.0f, 280.0f)); ImGui::Text("Aimbot Distance");
                        ImGui::SetCursorPos(ImVec2(10.0f, 310.0f));
                        ImGui::SliderFloat("Aimbot Fov", &fovamount, 12.0f, 500.0f); ImGui::SetCursorPos(ImVec2(140.0f, 310.0f)); ImGui::ColorEdit4(safe_str("AimBot Fov Color"), fovcolor, ImGuiColorEditFlags_NoInputs);

                        ImGui::EndChild();
                    }
                    if (menu::misc)
                    {
                        ImGui::SetCursorPos(ImVec2(10.0f, 100.0f));
                        ImGui::Checkbox("Spider Man", &exploits::SpiderMan);
                        ImGui::SetCursorPos(ImVec2(10.0f, 130.0f));
                        ImGui::Checkbox("Inf Jump", &exploits::infjump);
                        ImGui::SetCursorPos(ImVec2(10.0f, 160.0f));
                        ImGui::Checkbox("Insta Bow", &exploits::instabow);
                        ImGui::SetCursorPos(ImVec2(10.0f, 190.0f));
                        ImGui::Checkbox("Super Eoka", &exploits::supereoka);
                        ImGui::SetCursorPos(ImVec2(10.0f, 220.0f));
                        ImGui::Checkbox("Super Knife", &exploits::superknife);
                        ImGui::SetCursorPos(ImVec2(10.0f, 250.0f));
                        ImGui::KeyBind("Fly", KeyBinds::fly, ImVec2(45, 26));
                        ImGui::SetCursorPos(ImVec2(10.0f, 280.0f));
                        ImGui::Checkbox("Fly Bypass", &exploits::flybypass);
                        ImGui::SetCursorPos(ImVec2(10.0f, 310.0f));
                        ImGui::Checkbox("Night Time Mode", &exploits::nightime);
                        ImGui::SetCursorPos(ImVec2(10.0f, 340.0f));
                        ImGui::Checkbox("Spin Bot", &exploits::spingbot);
                        ImGui::SetCursorPos(ImVec2(10.00f, 370.0f));
                        ImGui::Checkbox("Time Changer", &exploits::timechanger);

                        ImGui::SetCursorPos(ImVec2(275.00f, 100.0f));
                        ImGui::Checkbox("Insta-Suicide", &exploits::instasuicide);
                        ImGui::SetCursorPos(ImVec2(275.00f, 130.0f));
                        ImGui::Checkbox("Fat Bullet", &exploits::FatBullet);
                        ImGui::SetCursorPos(ImVec2(275.00f, 160.0f));
                        ImGui::KeyBind("gravity (High Jump)", KeyBinds::gravity, ImVec2(45, 26));
                        ImGui::SetCursorPos(ImVec2(275.00f, 190.0f));
                        ImGui::KeyBind("long Neck", KeyBinds::longneck, ImVec2(45, 26));
                        ImGui::SetCursorPos(ImVec2(275.00f, 220.0f));
                        ImGui::Checkbox("No Recoil", &miscoptions::norecoil);
                        ImGui::SetCursorPos(ImVec2(275.00f, 250.0f));
                        ImGui::Checkbox("View Player Hotbar", &miscoptions::viewplayers);
                        ImGui::SetCursorPos(ImVec2(275.00f, 280.0f));
                        ImGui::Checkbox("No Sway", &miscoptions::nosway);
                        ImGui::SetCursorPos(ImVec2(275.00f, 310.0f));
                        ImGui::Checkbox("Admin Commands", &miscoptions::Admin);
                        ImGui::SetCursorPos(ImVec2(275.00f, 340.0f));
                        ImGui::Checkbox("Debug Camera", &miscoptions::debug);
                        ImGui::SetCursorPos(ImVec2(275.00f, 370.0f));
                        ImGui::Checkbox("Fov Changer", &miscoptions::fovChanger);
                    }

                    if (menu::ESP)
                    {
                        ImGui::SetCursorPos(ImVec2(10.0f, 100.0f));
                        ImGui::Checkbox("Full Box", &espoptions::NoramlBox);
                        ImGui::SetCursorPos(ImVec2(10.0f, 130.0f));
                        ImGui::Checkbox("Cornor Box", &espoptions::CornorBox);
                        ImGui::SetCursorPos(ImVec2(10.0f, 160.0f));
                        ImGui::Checkbox("Head Dot", &espoptions::PlayerHeadDot);
                        ImGui::SetCursorPos(ImVec2(10.0f, 190.0f));
                        ImGui::Checkbox("Player Chams", &espoptions::PlayerChams);
                        ImGui::SetCursorPos(ImVec2(10.0f, 220.0f));
                        ImGui::Checkbox("Player Name", &espoptions::PlayerName);
                        ImGui::SetCursorPos(ImVec2(10.0f, 250.0f));
                        ImGui::Checkbox("Player Health", &espoptions::PlayerHealth);
                        ImGui::SetCursorPos(ImVec2(10.0f, 280.0f));
                        ImGui::Checkbox("Lines From CrossHair", &espoptions::LinesFromCrossHair);
                        ImGui::SetCursorPos(ImVec2(10.0f, 310.0f));
                        ImGui::Checkbox("Sleeper Esp", &espoptions::SleeperEsp);
                        ImGui::SetCursorPos(ImVec2(10.0f, 340.0f));
                        ImGui::SetCursorPos(ImVec2(275.00f, 100.0f));
                        ImGui::Checkbox("Stone", &oreesp::Stone);
                        ImGui::SetCursorPos(ImVec2(275.00f, 130.0f));
                        ImGui::Checkbox("Metal", &oreesp::Metal);
                        ImGui::SetCursorPos(ImVec2(275.00f, 160.0f));
                        ImGui::Checkbox("Sulfer", &oreesp::sulf);
                        ImGui::SetCursorPos(ImVec2(275.00f, 190.0f));
                        ImGui::Checkbox("Hemp (Cloth)", &oreesp::cloth);
                        ImGui::SetCursorPos(ImVec2(275.00f, 220.0f));
                        ImGui::Checkbox("Pick Able", &oreesp::pickable);
                        ImGui::SetCursorPos(ImVec2(275.00f, 250.0f));
                        ImGui::Checkbox("Wood", &oreesp::wood);
                        ImGui::SetCursorPos(ImVec2(500.0f, 100.0f));
                        ImGui::Checkbox("Barrel", &lootesp::barrel);
                        ImGui::SetCursorPos(ImVec2(500.0f, 130.0f));
                        ImGui::Checkbox("Create", &lootesp::creates);
                        ImGui::SetCursorPos(ImVec2(500.0f, 160.0f));
                        ImGui::Checkbox("Green Create", &lootesp::greencrate);
                        ImGui::SetCursorPos(ImVec2(500.0f, 190.0f));
                        ImGui::Checkbox("Elite Create", &lootesp::elitecrate);
                        ImGui::SetCursorPos(ImVec2(500.0f, 220.0f));
                        ImGui::Checkbox("Mini", &lootesp::Mini);
                        ImGui::SetCursorPos(ImVec2(500.0f, 250.0f));
                        ImGui::Checkbox("Boat", &lootesp::boat);

                    }


                    if (menu::Settings)
                    {
                        ImGui::SetCursorPos(ImVec2(10.0f, 100.0f));
                        ImGui::SliderFloat("Fov Changer Value", &floatsliders::FovSlider, 1.0f, 150.0f); ImGui::SetCursorPos(ImVec2(140.0f, 100.0f)); ImGui::Text("Fov Changer");
                        ImGui::SetCursorPos(ImVec2(10.0f, 130.0f));
                        ImGui::SliderFloat("Recoil x Axis", &recoil::xrecoil, 1.0f, 100.0f); ImGui::SetCursorPos(ImVec2(140.0f, 130.0f)); ImGui::Text("Recoil X");
                        ImGui::SetCursorPos(ImVec2(10.0f, 160.0f));
                        ImGui::SliderFloat("Recoil y Axis", &recoil::yrecoil, 1.0f, 100.0f);  ImGui::SetCursorPos(ImVec2(140.0f, 160.0f)); ImGui::Text("Recoil Y");
                        ImGui::SetCursorPos(ImVec2(10.00f, 190.0f));
                        ImGui::SliderFloat("Time Changer Value", &floatsliders::Time, 1.0f, 24.0f); ImGui::SetCursorPos(ImVec2(140.0f, 190.0f)); ImGui::Text("Time Changer Value");
                        ImGui::SetCursorPos(ImVec2(10.00f, 220.0f));
                        ImGui::SliderFloat("Gravity Changer Value", &floatsliders::gravity_distancee, 1.0f, 5.0f); ImGui::SetCursorPos(ImVec2(140.0f, 220.0f)); ImGui::Text("Gravity Changer Value");
                        ImGui::SetCursorPos(ImVec2(10.0f, 250.0f));
                        ImGui::SliderFloat("Aimbot Smoothing", &floatsliders::aimbotsmoothing, 1.0f, 10.0f);     ImGui::SetCursorPos(ImVec2(140.0f, 250.0f)); ImGui::Text("Aimbot Smoothing");
                        ImGui::SetCursorPos(ImVec2(10.0f, 280.0f));
                        ImGui::SliderFloat("Loot Distance", &floatsliders::lootdistance, 1.0f, 500.0f); ImGui::SetCursorPos(ImVec2(140.0f, 280.0f)); ImGui::Text("Loot Distance");
                        ImGui::SetCursorPos(ImVec2(10.0f, 310.0f));
                        ImGui::SliderFloat("Esp Distance", &floatsliders::espdistance, 1.0f, 500.0f); ImGui::SetCursorPos(ImVec2(140.0f, 310.0f)); ImGui::Text("Esp Distance");
                        ImGui::SetCursorPos(ImVec2(10.0f, 340.0f));
                        ImGui::SliderFloat(("FlyHack Speed Value"), &exploits::flyhackspeed, 0, 1, "% .3f"); ImGui::SetCursorPos(ImVec2(140.0f, 340.0f)); ImGui::Text("FlyHack Speed Value");
                    }
                    if (menu::info)
                    {
                        ImGui::SetCursorPos(ImVec2(10.0f, 80.0f));
                        ImGui::Text("Config Coming Soon");
                    }

                }
                ImGui::PopStyleColor(12);
                ImGui::End();
            }

            ImDrawList* draw_list = ImGui::GetForegroundDrawList();

            ImGui::EndFrame();

            g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);

            ImVec4 clear_color = ImVec4(0, 0, 0, 0);
            g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, (float*)&clear_color);

            ImGui::Render();
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

            g_pSwapChain->Present(0, 0);
        }
        Shutdown();
        return 0;
    }
}