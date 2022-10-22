#pragma once
#define DIRECTINPUT_VERSION 0x0800
// windows headers
#include <msxml.h>    
#include <atomic>
#include <mutex>
#include <Windows.h>
#include <TlHelp32.h>
#include <cstdint>
#include <vector>
#include <random>
#include <memoryapi.h>
#include <string>
#include <thread>
#include <chrono>
#include <iostream>
#include <string_view>
#include <mutex>
#include <chrono>
#include <functional>
#include <dwmapi.h>
#include <dinput.h>
#include <d3d9.h>
#include <WinSock.h>
#include <cstdint>
#include <d3d11.h>
#include <dinput.h>
#include <tchar.h>
#include <Dwmapi.h>
#include <Windows.h>
#include <Tlhelp32.h>
#include <string>
#include <windef.h>
#include <DirectXMath.h>
#include <cmath>
#include <windef.h>
#include <Psapi.h> 
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <mutex>
#include <iostream>
#include <vector>
#include <D3D11.h> 
#include <D3D11Shader.h> 

#include <d3d9types.h>
#include <map>

#include "D2DHelper.h"
// libs
#pragma comment(lib, "Dwmapi.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

using Callback = std::function<void()>;