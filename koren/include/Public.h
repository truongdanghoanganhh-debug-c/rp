/*++

Module Name:

    public.h

Abstract:

    This module contains the common declarations shared by driver
    and user applications.

Environment:

    user and kernel

--*/

//
// Define an Interface Guid so that app can find the device and talk to it.
//

DEFINE_GUID (GUID_DEVINTERFACE_koren,
    0xda4e4e0d,0x4e3f,0x477d,0x8b,0x7a,0x24,0x6e,0x7d,0x09,0x94,0xa0);
// {da4e4e0d-4e3f-477d-8b7a-246e7d0994a0}
