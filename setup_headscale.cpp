#define UNICODE
#define _UNICODE

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
	wstring auth_key;

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

	if (argc > 2)
	{
		auth_key = argv[2];
		wcout << "[+] Setting pre-auth key to: " << auth_key << "\n";
	}
	

	HKEY key;
	wstring widestr = wstring(user_input.begin(), user_input.end());
	const wchar_t* headscale_url = widestr.c_str();
	const wchar_t unattend_mode[] = L"always";

	LSTATUS status = RegCreateKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Tailscale IPN", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &key, NULL);
	if (status != ERROR_SUCCESS) {
		printf("RegCreateKeyW failed %lu\n", status);
		return 1;
	}
	else
	{
		printf("[+] Successfully created \"\\SOFTWARE\\Tailscale IPN\" registry key.\n");
	}

	status = RegSetValueExW(key, L"UnattendedMode", 0, REG_SZ, (BYTE*)unattend_mode, sizeof(unattend_mode));
	if (status != ERROR_SUCCESS) {
		printf("RegSetValueExW('UnattendedMode') failed %lu\n", status);
		return 1;
	}
	else
	{
		wcout << "[+] Successfully set UnattendedMode to: " << unattend_mode << "\n";
	}

	status = RegSetValueExW(key, L"LoginURL", 0, REG_SZ, (BYTE*)headscale_url, sizeof(headscale_url)*sizeof(wchar_t*));
	if (status != ERROR_SUCCESS) {
		printf("RegSetValueExW('LoginURL') failed %lu\n", status);
		return 1;
	}
	else
	{
		wcout << "[+] Successfully set LoginURL to: " <<  headscale_url << "\n";
	}
	


	std::string start_cmd = "start /MIN cmd /c \"";
	std::string start_tailscale_bg = start_cmd + tailscale_file + "\"";
	cout << start_tailscale_bg << endl;
	system(start_tailscale_bg.c_str());
	Sleep(30000); // Sleep for half a minute to give time for the program to install
	if (argc > 2)
	{
		// string tailscale_up_command = string(tailscale_login) + wstring_to_string(user_input) + string(tailscale_auth_key) + wstring_to_string(auth_key);

		std::string str_user_input(user_input.begin(), user_input.end());
		std::string str_auth_key(auth_key.begin(), auth_key.end());
		cout << str_user_input << " " << str_auth_key << "\n";

		const char * tailscale_login = "tailscale up --login-server ";
		const char * tailscale_auth_key = " --authkey ";
		const char * unattend_reset = " --unattended --reset";
		string tailscale_up_command = (tailscale_login + str_user_input + tailscale_auth_key + str_auth_key + unattend_reset);
		cout << tailscale_up_command << "\n";
		system((tailscale_up_command).c_str());
		Sleep(5000);
		system("pause");
	}
	return 0;
}