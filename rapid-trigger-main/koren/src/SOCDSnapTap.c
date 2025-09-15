#include <ntddk.h>
#include <wdf.h>

// Simple context structure
typedef struct _DEVICE_CONTEXT {
    BOOLEAN driver_loaded;
} DEVICE_CONTEXT, * PDEVICE_CONTEXT;

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(DEVICE_CONTEXT, GetDeviceContext)

// Function prototypes  
DRIVER_INITIALIZE DriverEntry;
EVT_WDF_DRIVER_DEVICE_ADD EvtDeviceAdd;

#pragma alloc_text (INIT, DriverEntry)
#pragma alloc_text (PAGE, EvtDeviceAdd)

NTSTATUS
DriverEntry(
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PUNICODE_STRING RegistryPath
)
{
    NTSTATUS status;
    WDF_DRIVER_CONFIG config;

    KdPrint(("SOCD Minimal Driver Loading...\n"));

    WDF_DRIVER_CONFIG_INIT(&config, EvtDeviceAdd);

    status = WdfDriverCreate(
        DriverObject,
        RegistryPath,
        WDF_NO_OBJECT_ATTRIBUTES,
        &config,
        WDF_NO_HANDLE
    );

    if (!NT_SUCCESS(status)) {
        KdPrint(("WdfDriverCreate failed: 0x%08x\n", status));
        return status;
    }

    KdPrint(("SOCD Minimal Driver loaded successfully\n"));
    return STATUS_SUCCESS;
}

NTSTATUS
EvtDeviceAdd(
    _In_ WDFDRIVER Driver,
    _Inout_ PWDFDEVICE_INIT DeviceInit
)
{
    NTSTATUS status;
    WDFDEVICE device;
    WDF_OBJECT_ATTRIBUTES attributes;
    PDEVICE_CONTEXT deviceContext;

    UNREFERENCED_PARAMETER(Driver);
    PAGED_CODE();

    KdPrint(("EvtDeviceAdd called\n"));

    // Initialize device attributes with context
    WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&attributes, DEVICE_CONTEXT);

    // Create device
    status = WdfDeviceCreate(&DeviceInit, &attributes, &device);
    if (!NT_SUCCESS(status)) {
        KdPrint(("WdfDeviceCreate failed: 0x%08x\n", status));
        return status;
    }

    // Get and initialize context
    deviceContext = GetDeviceContext(device);
    deviceContext->driver_loaded = TRUE;

    KdPrint(("Device added successfully\n"));
    return STATUS_SUCCESS;
}