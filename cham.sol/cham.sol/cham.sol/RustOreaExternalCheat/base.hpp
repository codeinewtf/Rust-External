#pragma once
#include "include.hpp"
#include "function.hpp"
#include "driver.hpp"


void baseAddressGoGetter()
{
	function.setup();
	if (function.setup())
		std::cout << "successfully set up function\n";
	if (!driver.is_mapped()) std::cout << _("[-] Driver Is Not Mapped or Is Not Mapped Properly\n").c_str(); // map driver here
	else std::cout << _("[+] Driver Mapped | Loaded\n").c_str();

	std::cout << _("Please Launch Rust\n").c_str();
	
	while (driver.get_pid() == NULL) {
		driver.set_pid(_("RustClient.exe").c_str());
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	printf(_("Found Game | PID %u\n").c_str(), driver.get_pid());
	Sleep(2000);
	system("cls");

}