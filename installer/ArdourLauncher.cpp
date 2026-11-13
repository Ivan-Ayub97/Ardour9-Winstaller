#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <filesystem>
#include <string>
#include <cwchar>

namespace fs = std::filesystem;

static std::wstring quote_argument(const std::wstring& value)
{
    std::wstring result = L"\"";
    unsigned int backslashes = 0;
    for (wchar_t ch : value) {
        if (ch == L'\\') {
            ++backslashes;
        } else if (ch == L'"') {
            result.append(backslashes * 2 + 1, L'\\');
            result.push_back(ch);
            backslashes = 0;
        } else {
            result.append(backslashes, L'\\');
            backslashes = 0;
            result.push_back(ch);
        }
    }
    result.append(backslashes * 2, L'\\');
    result.push_back(L'"');
    return result;
}

static void set_path(const wchar_t* name, const fs::path& path)
{
    SetEnvironmentVariableW(name, path.c_str());
}

static void prepend_path(const fs::path& path)
{
    DWORD size = GetEnvironmentVariableW(L"PATH", nullptr, 0);
    std::wstring old_path(size ? size : 1, L'\0');
    if (size) {
        GetEnvironmentVariableW(L"PATH", old_path.data(), size);
        old_path.resize(wcslen(old_path.c_str()));
    } else {
        old_path.clear();
    }
    const std::wstring value = path.native() + L";" + old_path;
    SetEnvironmentVariableW(L"PATH", value.c_str());
}

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR command_line, int)
{
    wchar_t module[MAX_PATH];
    const DWORD length = GetModuleFileNameW(nullptr, module, MAX_PATH);
    if (!length || length >= MAX_PATH) {
        MessageBoxW(nullptr, L"Could not locate the Ardour installation folder.", L"Ardour", MB_OK | MB_ICONERROR);
        return ERROR_PATH_NOT_FOUND;
    }

    const fs::path root = fs::path(module).parent_path();
    const fs::path lib = root / L"lib" / L"ardour9";
    const fs::path share = root / L"share" / L"ardour9";
    const fs::path app = lib / L"ardour-9.10.16.exe";

    if (!fs::exists(app)) {
        MessageBoxW(nullptr, L"Ardour files are missing. Please reinstall Ardour.", L"Ardour", MB_OK | MB_ICONERROR);
        return ERROR_FILE_NOT_FOUND;
    }

    prepend_path(lib);
    prepend_path(lib / L"backends");
    prepend_path(lib / L"panners");
    prepend_path(lib / L"surfaces");
    prepend_path(lib / L"vamp");
    prepend_path(lib / L"LV2");
    prepend_path(lib / L"engines");
    set_path(L"ARDOUR_ROOT", root);
    set_path(L"GTK_PATH", share.native() + L";" + lib.native());
    set_path(L"ARDOUR_DATA_PATH", share);
    set_path(L"ARDOUR_CONFIG_PATH", share);
    set_path(L"ARDOUR_DLL_PATH", lib);
    set_path(L"ARDOUR_BACKEND_PATH", lib / L"backends");
    set_path(L"ARDOUR_SURFACES_PATH", lib / L"surfaces");
    set_path(L"ARDOUR_PANNER_PATH", lib / L"panners");
    set_path(L"ARDOUR_THEMES_PATH", share / L"themes");
    set_path(L"ARDOUR_EXPORT_FORMATS_PATH", share / L"export");
    set_path(L"ARDOUR_MIDI_PATCH_PATH", share / L"patchfiles");

    DWORD vamp_size = GetEnvironmentVariableW(L"VAMP_PATH", nullptr, 0);
    std::wstring old_vamp(vamp_size ? vamp_size : 1, L'\0');
    if (vamp_size) {
        GetEnvironmentVariableW(L"VAMP_PATH", old_vamp.data(), vamp_size);
        old_vamp.resize(wcslen(old_vamp.c_str()));
    } else {
        old_vamp.clear();
    }
    set_path(L"VAMP_PATH", lib / L"vamp");
    if (!old_vamp.empty()) {
        const std::wstring value = (lib / L"vamp").native() + L";" + old_vamp;
        SetEnvironmentVariableW(L"VAMP_PATH", value.c_str());
    }

    SetCurrentDirectoryW(root.c_str());
    std::wstring command = quote_argument(app.native());
    if (command_line && *command_line) {
        command.push_back(L' ');
        command.append(command_line);
    }

    STARTUPINFOW startup{};
    startup.cb = sizeof(startup);
    PROCESS_INFORMATION process{};
    if (!CreateProcessW(app.c_str(), command.data(), nullptr, nullptr, FALSE, CREATE_NO_WINDOW, nullptr, root.c_str(), &startup, &process)) {
        const DWORD error = GetLastError();
        const std::wstring message = L"Ardour could not be started (Windows error " + std::to_wstring(error) + L").";
        MessageBoxW(nullptr, message.c_str(), L"Ardour", MB_OK | MB_ICONERROR);
        return static_cast<int>(error);
    }

    CloseHandle(process.hThread);
    CloseHandle(process.hProcess);
    return 0;
}
