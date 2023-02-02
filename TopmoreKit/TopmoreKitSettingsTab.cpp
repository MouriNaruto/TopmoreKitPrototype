#include "TopmoreKitSettingsTab.h"

#include <winrt/base.h>

#include <Wbemidl.h>
//#pragma comment(lib, "wbemuuid.lib")

#include <dxdiag.h>
#pragma comment(lib, "dxguid.lib")

#include <cwchar>
#include <format>

namespace winrt
{
    struct bstr_traits
    {
        using type = BSTR;

        static void close(type value) noexcept
        {
            ::SysFreeString(value);
        }

        static constexpr type invalid() noexcept
        {
            return nullptr;
        }
    };

    using bstr = handle_type<bstr_traits>;
}

BOOL OpenUriWithDefaultWebBrowser(
    _In_ LPCWSTR Uri)
{
    SHELLEXECUTEINFOW Info = { 0 };
    Info.cbSize = sizeof(SHELLEXECUTEINFOW);
    Info.lpVerb = L"open";
    Info.lpFile = Uri;
    Info.nShow = SW_SHOWNORMAL;
    return ::ShellExecuteExW(&Info);
}

USHORT GetNativeMachineTypeFromX86Process()
{
    USHORT NativeMachineType = IMAGE_FILE_MACHINE_UNKNOWN;

    decltype(::IsWow64Process2)* pIsWow64Process2 =
        reinterpret_cast<decltype(::IsWow64Process2)*>(::GetProcAddress(
            ::GetModuleHandleW(L"kernel32.dll"),
            "IsWow64Process2"));
    if (pIsWow64Process2)
    {
        USHORT ProcessMachine = IMAGE_FILE_MACHINE_I386;
        USHORT NativeMachine = IMAGE_FILE_MACHINE_I386;
        if (pIsWow64Process2(
            ::GetCurrentProcess(),
            &ProcessMachine,
            &NativeMachine))
        {
            NativeMachineType = NativeMachine;
        }
    }

    if (NativeMachineType == IMAGE_FILE_MACHINE_UNKNOWN)
    {
        BOOL Wow64Process;
        if (::IsWow64Process(::GetCurrentProcess(), &Wow64Process))
        {
            NativeMachineType = Wow64Process
                ? IMAGE_FILE_MACHINE_AMD64
                : IMAGE_FILE_MACHINE_I386;
        }
    }

    return NativeMachineType;
}

std::wstring GetPropertyValueFromWbemClassObject(
    winrt::com_ptr<IWbemClassObject> const& WbemClassObject,
    std::wstring PropertyName)
{
    std::wstring PropertyValue;

    VARIANT Property;
    ::VariantInit(&Property);
    winrt::check_hresult(WbemClassObject->Get(
        PropertyName.c_str(),
        0,
        &Property,
        0,
        0));
    PropertyValue = std::wstring(Property.bstrVal);
    ::VariantClear(&Property);

    return PropertyValue;
}

std::wstring GetSystemInformation()
{
    std::wstring DeviceName;
    std::wstring ProcessorName;
    std::uint64_t TotalPhysicalMemoryInMB = 0;
    std::wstring SystemType;
    std::wstring SystemVersion;
    std::wstring SystemBuild;
    std::wstring BIOSVersion;
    std::uint64_t UsedVirtualMemoryInMB = 0;
    std::uint64_t FreeVirtualMemoryInMB = 0;
    std::wstring DirectXVersion;
    std::wstring SystemManufacturer;
    std::wstring SystemModel;

    {
        // Length of "65535.65535.65535.65535" is 24.
        wchar_t CurrentBuild[24] = { 0 };
        DWORD CurrentBuildLength =
            sizeof(CurrentBuild) / sizeof(*CurrentBuild);
        winrt::check_win32(::RegGetValueW(
            HKEY_LOCAL_MACHINE,
            L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion",
            L"CurrentBuild",
            RRF_RT_REG_SZ,
            nullptr,
            CurrentBuild,
            &CurrentBuildLength));

        DWORD UBR = 0;
        DWORD UBRLength = sizeof(DWORD);
        winrt::check_win32(::RegGetValueW(
            HKEY_LOCAL_MACHINE,
            L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion",
            L"UBR",
            RRF_RT_REG_DWORD,
            nullptr,
            &UBR,
            &UBRLength));

        SystemBuild = std::format(
            L"{}.{}",
            CurrentBuild,
            UBR);
    }

    {
        USHORT NativeMachineType = ::GetNativeMachineTypeFromX86Process();
        switch (NativeMachineType)
        {
        case IMAGE_FILE_MACHINE_I386:
            SystemType = L"32 位操作系统，基于 x86 的处理器";
            break;
        case IMAGE_FILE_MACHINE_AMD64:
            SystemType = L"64 位操作系统，基于 x64 的处理器";
            break;
        case IMAGE_FILE_MACHINE_ARM64:
            SystemType = L"64 位操作系统，基于 ARM 的处理器";
            break;
        default:
            SystemType = L"未知 位操作系统，基于 未知 的处理器";
            break;
        }
    }

    winrt::com_ptr<IWbemLocator> WbemLocator =
        winrt::create_instance<IWbemLocator>(CLSID_WbemLocator);

    winrt::com_ptr<IWbemServices> WbemServices;
    winrt::check_hresult(WbemLocator->ConnectServer(
        winrt::bstr(::SysAllocString(L"root\\CIMV2")).get(),
        nullptr,
        nullptr,
        nullptr,
        0,
        nullptr,
        nullptr,
        WbemServices.put()));
    winrt::check_hresult(::CoSetProxyBlanket(
        WbemServices.get(),
        RPC_C_AUTHN_WINNT,
        RPC_C_AUTHZ_NONE,
        nullptr,
        RPC_C_AUTHN_LEVEL_CALL,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        nullptr,
        EOAC_NONE));

    {
        winrt::com_ptr<IEnumWbemClassObject> Enumerator;
        winrt::check_hresult(WbemServices->ExecQuery(
            winrt::bstr(::SysAllocString(
                L"WQL")).get(),
            winrt::bstr(::SysAllocString(
                L"SELECT * FROM Win32_OperatingSystem")).get(),
            WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
            NULL,
            Enumerator.put()));

        while (Enumerator)
        {
            winrt::com_ptr<IWbemClassObject> Current;
            ULONG Return = 0;
            winrt::check_hresult(Enumerator->Next(
                WBEM_INFINITE,
                1,
                Current.put(),
                &Return));
            if (0 == Return)
            {
                break;
            }

            SystemVersion = ::GetPropertyValueFromWbemClassObject(
                Current,
                L"Caption");

            std::uint64_t TotalVirtualMemorySize = std::stoull(
                ::GetPropertyValueFromWbemClassObject(
                    Current,
                    L"TotalVirtualMemorySize"));
            std::uint64_t FreeVirtualMemory = std::stoull(
                ::GetPropertyValueFromWbemClassObject(
                    Current,
                    L"FreeVirtualMemory"));
            UsedVirtualMemoryInMB =
                (TotalVirtualMemorySize - FreeVirtualMemory) / 1024;
            FreeVirtualMemoryInMB =
                FreeVirtualMemory / 1024;
        }
    }

    {
        winrt::com_ptr<IEnumWbemClassObject> Enumerator;
        winrt::check_hresult(WbemServices->ExecQuery(
            winrt::bstr(::SysAllocString(
                L"WQL")).get(),
            winrt::bstr(::SysAllocString(
                L"SELECT * FROM Win32_ComputerSystem")).get(),
            WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
            NULL,
            Enumerator.put()));

        while (Enumerator)
        {
            winrt::com_ptr<IWbemClassObject> Current;
            ULONG Return = 0;
            winrt::check_hresult(Enumerator->Next(
                WBEM_INFINITE,
                1,
                Current.put(),
                &Return));
            if (0 == Return)
            {
                break;
            }

            DeviceName = ::GetPropertyValueFromWbemClassObject(
                Current,
                L"Caption");

            TotalPhysicalMemoryInMB = std::stoull(
                ::GetPropertyValueFromWbemClassObject(
                    Current,
                    L"TotalPhysicalMemory")) / 1024 / 1024;

            SystemManufacturer = ::GetPropertyValueFromWbemClassObject(
                Current,
                L"Manufacturer");

            SystemModel = ::GetPropertyValueFromWbemClassObject(
                Current,
                L"Model");
        }
    }

    {
        winrt::com_ptr<IEnumWbemClassObject> Enumerator;
        winrt::check_hresult(WbemServices->ExecQuery(
            winrt::bstr(::SysAllocString(
                L"WQL")).get(),
            winrt::bstr(::SysAllocString(
                L"SELECT * FROM Win32_Processor")).get(),
            WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
            NULL,
            Enumerator.put()));

        while (Enumerator)
        {
            winrt::com_ptr<IWbemClassObject> Current;
            ULONG Return = 0;
            winrt::check_hresult(Enumerator->Next(
                WBEM_INFINITE,
                1,
                Current.put(),
                &Return));
            if (0 == Return)
            {
                break;
            }

            ProcessorName = ::GetPropertyValueFromWbemClassObject(
                Current,
                L"Name");
            wchar_t* SplitPoint = std::wcsstr(&ProcessorName[0], L" CPU @");
            if (!SplitPoint)
            {
                SplitPoint = std::wcsstr(&ProcessorName[0], L" @");
            }
            if (SplitPoint)
            {
                SplitPoint[0] = L'\0';
            }
            ProcessorName.resize(std::wcslen(ProcessorName.c_str()));
        }
    }

    {
        winrt::com_ptr<IEnumWbemClassObject> Enumerator;
        winrt::check_hresult(WbemServices->ExecQuery(
            winrt::bstr(::SysAllocString(
                L"WQL")).get(),
            winrt::bstr(::SysAllocString(
                L"SELECT * FROM Win32_BIOS")).get(),
            WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
            NULL,
            Enumerator.put()));

        while (Enumerator)
        {
            winrt::com_ptr<IWbemClassObject> Current;
            ULONG Return = 0;
            winrt::check_hresult(Enumerator->Next(
                WBEM_INFINITE,
                1,
                Current.put(),
                &Return));
            if (0 == Return)
            {
                break;
            }

            BIOSVersion = std::format(
                L"{} {}",
                ::GetPropertyValueFromWbemClassObject(
                    Current,
                    L"Manufacturer"),
                ::GetPropertyValueFromWbemClassObject(
                    Current,
                    L"SMBIOSBIOSVersion"));
        }
    }

    try
    {
        winrt::com_ptr<IDxDiagProvider> Provider;
        winrt::check_hresult(::CoCreateInstance(
            CLSID_DxDiagProvider,
            nullptr,
            CLSCTX_INPROC_SERVER,
            IID_IDxDiagProvider,
            Provider.put_void()));

        DXDIAG_INIT_PARAMS Parameters = { 0 };
        Parameters.dwSize = sizeof(DXDIAG_INIT_PARAMS);
        Parameters.dwDxDiagHeaderVersion = DXDIAG_DX9_SDK_VERSION;
        Parameters.bAllowWHQLChecks = FALSE;
        Parameters.pReserved = nullptr;
        winrt::check_hresult(Provider->Initialize(&Parameters));

        winrt::com_ptr<IDxDiagContainer> Root;
        winrt::check_hresult(Provider->GetRootContainer(Root.put()));

        winrt::com_ptr<IDxDiagContainer> SystemInfo;
        winrt::check_hresult(Root->GetChildContainer(
            L"DxDiag_SystemInfo",
            SystemInfo.put()));

        DWORD DirectXVersionMajor = 0;
        {
            VARIANT Property;
            ::VariantInit(&Property);
            winrt::check_hresult(SystemInfo->GetProp(
                L"dwDirectXVersionMajor",
                &Property));
            if (Property.vt == VT_UI4)
            {
                DirectXVersionMajor = Property.ulVal;
            }
            ::VariantClear(&Property);
        }

        DWORD DirectXVersionMinor = 0;
        {
            VARIANT Property;
            ::VariantInit(&Property);
            winrt::check_hresult(SystemInfo->GetProp(
                L"dwDirectXVersionMinor",
                &Property));
            if (Property.vt == VT_UI4)
            {
                DirectXVersionMinor = Property.ulVal;
            }
            ::VariantClear(&Property);
        }

        std::wstring DirectXVersionLetter;
        {
            VARIANT Property;
            ::VariantInit(&Property);
            winrt::check_hresult(SystemInfo->GetProp(
                L"szDirectXVersionLetter",
                &Property));
            DirectXVersionLetter = std::wstring(Property.bstrVal);
            ::VariantClear(&Property);
        }

        DirectXVersion = L"DirectX " + std::to_wstring(DirectXVersionMajor);
        if (DirectXVersionMinor)
        {
            DirectXVersion += L"." + std::to_wstring(DirectXVersionMinor);
        }
        DirectXVersion += DirectXVersionMinor;
    }
    catch (...)
    {
        DirectXVersion = L"不可用";
    } 

    return std::format(
        L"设备名称: {}\n"
        L"处理器: {}\n"
        L"物理内存: {} MB\n"
        L"系统类型: {}\n"
        L"系统版本: {}\n"
        L"Build 版本号: {}\n"
        L"BIOS 版本号: {}\n"
        L"页面文件: {} MB 已用 {} MB 可用\n"
        L"DirectX 版本: {}\n"
        L"系统制造商: {}\n"
        L"系统型号: {}\n",
        DeviceName,
        ProcessorName,
        TotalPhysicalMemoryInMB,
        SystemType,
        SystemVersion,
        SystemBuild,
        BIOSVersion,
        UsedVirtualMemoryInMB,
        FreeVirtualMemoryInMB,
        DirectXVersion,
        SystemManufacturer,
        SystemModel);
}

TopmoreKitSettingsTab::TopmoreKitSettingsTab(QWidget *parent)
	: QWidget(parent)
{
    this->ui.setupUi(this);

    this->connect(
        this->ui.WebsitePushButton,
        &QPushButton::clicked,
        this,
        []
    {
        ::OpenUriWithDefaultWebBrowser(L"https://www.topmore.com.tw");
    });

    this->connect(
        this->ui.SupportPushButton,
        &QPushButton::clicked,
        this,
        []
    {
        ::OpenUriWithDefaultWebBrowser(L"https://www.topmore.com.tw/edcontent_d.php?tb=3");
    });

    ui.SystemInfoPlainTextEdit->setPlainText(
        QString::fromWCharArray(::GetSystemInformation().c_str()));
}

TopmoreKitSettingsTab::~TopmoreKitSettingsTab()
{
}
