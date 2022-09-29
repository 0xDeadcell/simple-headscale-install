#define UNICODE
#define _UNICODE
#define WINVER 0x0500

#include <Windows.h>
#include <Urlmon.h>
#include <iostream>
#include <string>

using namespace std;
#pragma comment(lib, "urlmon.lib")


int wmain(int argc, wchar_t* argv[])
{
	const char tailscale_file[] = "tailscale-ipn-setup-1.30.2.exe";
	URLDownloadToFileA(NULL, "https://pkgs.tailscale.com/stable/tailscale-ipn-setup-1.30.2.exe", tailscale_file, 0, NULL);
	wstring user_input;

	// Check if the user entered at least one argument
	if (argc > 1)
	{
		user_input = argv[1];
		wcout << "[+] Setting Headscale server to: " << user_input << "\n";
	}
	else
	{
		// If the user didn't provide any command line arguments prompt them for one
		wcout << "What is your headscale LoginURL: ";
		getline(std::wcin, user_input); // get input until enter key is pressed
	}
	

	HKEY hkey;
	wstring widestr = wstring(user_input.begin(), user_input.end());
	const wchar_t* headscale_url = widestr.c_str();
	const wchar_t unattend_mode[] = L"always";

	LSTATUS status = RegCreateKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Tailscale IPN", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hkey, NULL);
	if (status != ERROR_SUCCESS) {
		printf("RegCreateKeyW failed %lu\n", status);
		return 1;
	}
	else
	{
		printf("[+] Successfully created \"\\SOFTWARE\\Tailscale IPN\" registry key.\n");
	}

	status = RegSetValueExW(hkey, L"UnattendedMode", 0, REG_SZ, (BYTE*)unattend_mode, sizeof(unattend_mode));
	if (status != ERROR_SUCCESS) {
		printf("RegSetValueExW('UnattendedMode') failed %lu\n", status);
		return 1;
	}
	else
	{
		wcout << "[+] Successfully set UnattendedMode to: " << unattend_mode << "\n";
	}

	status = RegSetValueExW(hkey, L"LoginURL", 0, REG_SZ, (BYTE*)headscale_url, sizeof(headscale_url)*sizeof(wchar_t*));
	if (status != ERROR_SUCCESS) {
		printf("RegSetValueExW('LoginURL') failed %lu\n", status);
		return 1;
	}
	else
	{
		wcout << "[+] Successfully set LoginURL to: " <<  headscale_url << "\n";
	}
	


	INPUT keyboard;

	// Set up a generic keyboard event.
	keyboard.type = INPUT_KEYBOARD;
	keyboard.ki.wScan = 0; // hardware scan code for key
	keyboard.ki.time = 0;
	keyboard.ki.dwExtraInfo = 0;
	
	std::string start_cmd = "start /MIN cmd /c \"";
	std::string start_tailscale_bg = start_cmd + tailscale_file + "\"";
	cout << start_tailscale_bg << endl;
	system(start_tailscale_bg.c_str());

	Sleep(1500); // Sleep for 1.5 Seconds to give time for the install prompt to come up
	// Press the Enter Key
	keyboard.ki.wVk = 0x0D; // virtual-key code for the "Enter" key
	keyboard.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &keyboard, sizeof(INPUT));

	// Release the "Enter" key
	keyboard.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &keyboard, sizeof(INPUT));
	system("pause");
	
	return 0;
}