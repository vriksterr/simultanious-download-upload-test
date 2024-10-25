#include <windows.h>
#include <iostream>
#include <vector>
#include <string>

void runCommand(const std::string& command) {
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Start the first process
    if (!CreateProcessA(NULL, const_cast<LPSTR>(command.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        std::cerr << "CreateProcess failed for command: " << command << " Error: " << GetLastError() << std::endl;
        return;
    }

    // Close process and thread handles. 
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

int main() {
    // Commands to run
    std::string command1 = ".\\iperf3.exe -c 10.10.10.27 -t 30 -p 5002 -P 1 -b 850M";
    std::string command2 = ".\\iperf3.exe -c 10.10.10.27 -R -t 30 -p 5003 -P 1 -b 850M";

    // Run commands simultaneously
    runCommand(command1);
    runCommand(command2);

    // Wait for user input before closing
    std::cout << "Press Enter to exit..." << std::endl;
    std::cin.get();

    return 0;
}
