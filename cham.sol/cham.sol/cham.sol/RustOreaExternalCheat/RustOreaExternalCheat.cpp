#include <windows.h>
#include <iostream>
#include "Menu.hpp"
#include <thread>
#include <string>
#include "driver.hpp"
#include "function.hpp"
#include "include.hpp"
#include "base.hpp"
#include "mainfun.h"

//      .-'''-.                                        .-'''-.     
//     '   _    \                                     '   _    \   
//   /   /` '.   \                  __.....__       /   /` '.   \  
//  .   |     \  '              .-''         '.    .   |     \  '  
//  |   '      |  ' .-,.--.    /     .-''"'-.  `.  |   '      |  ' 
//  \    \     / /  |  .-. |  /     /________\   \ \    \     / /  
//   `.   ` ..' /   | |  | |  |                  |  `.   ` ..' /   
//      '-...-'`    | |  | |  \    .-------------'     '-...-'`    
//                  | |  '-    \    '-.____...---.                 
//                  | |         `.             .'                  
//                  | |           `''-...... -'                    
//                  |_|                                            
// 


int main()
{

	SetConsoleTitleA("Orea Rust External");
	system("color 3");
	std::cout << "Welcome To Chams Rust External\n";
	std::cout << "\n Status: Undetected\n\n";
	baseAddressGoGetter();
	


	driver.get_module_base(_("GameAssembly.dll").c_str());
	functionbase::g_assembly = driver.get_base();  
	Sleep(1000);



	Sleep(1000);
	std::cout << "UnityPlayer Module Base [ 0x" << std::hex << functionbase::g_unityplayer << " ] \n";
	std::cout << "Assembly Module Base [ 0x" << std::hex << functionbase::g_assembly << " ] \n";
	Sleep(5000);
	system("cls");

		for (;;) {
			if (GetAsyncKeyState(VK_INSERT) != 0)
				break;
			Sleep(1);
		}

		while (true)
		{
			draw::Initialize();
		}
}

