SET gMinPlatformPkgTokenSpaceGuid.PcdFlashAreaSize             = 0x530000
SET gMinPlatformPkgTokenSpaceGuid.PcdFlashAreaBaseAddress      = 0xFFAD0000
#
# 0x270000
#
SET gMinPlatformPkgTokenSpaceGuid.PcdFlashFvPreMemorySize     = 0x00080000
SET gMinPlatformPkgTokenSpaceGuid.PcdFlashFvBspPreMemorySize  = 0x00080000
SET gMinPlatformPkgTokenSpaceGuid.PcdFlashFvFspTSize          = 0x00080000
SET gMinPlatformPkgTokenSpaceGuid.PcdFlashFvFspMSize          = 0x00060000
SET gMinPlatformPkgTokenSpaceGuid.PcdFlashFvFspSSize          = 0x00010000
SET gMinPlatformPkgTokenSpaceGuid.PcdFlashFvPostMemorySize    = 0x00040000
SET gMinPlatformPkgTokenSpaceGuid.PcdFlashFvBspSize           = 0x00040000

#
# 12MiB 0x2C0000
#
SET gMinPlatformPkgTokenSpaceGuid.PcdFlashFvUefiBootSize      = 0x00140000
SET gMinPlatformPkgTokenSpaceGuid.PcdFlashFvOsBootSize        = 0x00080000
SET gMinPlatformPkgTokenSpaceGuid.PcdFlashFvSecuritySize      = 0x00080000
SET gMinPlatformPkgTokenSpaceGuid.PcdFlashFvAdvancedSize      = 0x00080000 #gMinPlatformPkgTokenSpaceGuid.PcdFlashAreaSize - gMinPlatformPkgTokenSpaceGuid.PcdFlashFvBspSize - gMinPlatformPkgTokenSpaceGuid.PcdFlashFvPostMemorySize - gMinPlatformPkgTokenSpaceGuid.PcdFlashFvFspSSize - gMinPlatformPkgTokenSpaceGuid.PcdFlashFvFspMSize - gMinPlatformPkgTokenSpaceGuid.PcdFlashFvFspTSize - gMinPlatformPkgTokenSpaceGuid.PcdFlashFvBspPreMemorySize - gMinPlatformPkgTokenSpaceGuid.PcdFlashFvUefiBootSize - gMinPlatformPkgTokenSpaceGuid.PcdFlashFvOsBootSize - gMinPlatformPkgTokenSpaceGuid.PcdFlashFvSecuritySize

#
# Calculate Offsets Once (Do not modify)
# This layout is specified by the EDK II Minimum Platform Archicture specification.
# Each offset is the prior region's offset plus the prior region's size.
#

SET gMinPlatformPkgTokenSpaceGuid.PcdFlashFvAdvancedOffset      = 0x00000000
SET gMinPlatformPkgTokenSpaceGuid.PcdFlashFvSecurityOffset      = gMinPlatformPkgTokenSpaceGuid.PcdFlashFvAdvancedOffset      + gMinPlatformPkgTokenSpaceGuid.PcdFlashFvAdvancedSize
SET gMinPlatformPkgTokenSpaceGuid.PcdFlashFvOsBootOffset        = gMinPlatformPkgTokenSpaceGuid.PcdFlashFvSecurityOffset      + gMinPlatformPkgTokenSpaceGuid.PcdFlashFvSecuritySize
SET gMinPlatformPkgTokenSpaceGuid.PcdFlashFvUefiBootOffset      = gMinPlatformPkgTokenSpaceGuid.PcdFlashFvOsBootOffset        + gMinPlatformPkgTokenSpaceGuid.PcdFlashFvOsBootSize

SET gMinPlatformPkgTokenSpaceGuid.PcdFlashFvBspOffset           = gMinPlatformPkgTokenSpaceGuid.PcdFlashFvUefiBootOffset      + gMinPlatformPkgTokenSpaceGuid.PcdFlashFvUefiBootSize
SET gMinPlatformPkgTokenSpaceGuid.PcdFlashFvPostMemoryOffset    = gMinPlatformPkgTokenSpaceGuid.PcdFlashFvBspOffset           + gMinPlatformPkgTokenSpaceGuid.PcdFlashFvBspSize
SET gMinPlatformPkgTokenSpaceGuid.PcdFlashFvFspSOffset          = gMinPlatformPkgTokenSpaceGuid.PcdFlashFvPostMemoryOffset    + gMinPlatformPkgTokenSpaceGuid.PcdFlashFvPostMemorySize
SET gMinPlatformPkgTokenSpaceGuid.PcdFlashFvFspMOffset          = gMinPlatformPkgTokenSpaceGuid.PcdFlashFvFspSOffset          + gMinPlatformPkgTokenSpaceGuid.PcdFlashFvFspSSize
SET gMinPlatformPkgTokenSpaceGuid.PcdFlashFvFspTOffset          = gMinPlatformPkgTokenSpaceGuid.PcdFlashFvFspMOffset          + gMinPlatformPkgTokenSpaceGuid.PcdFlashFvFspMSize
SET gMinPlatformPkgTokenSpaceGuid.PcdFlashFvBspPreMemoryOffset  = gMinPlatformPkgTokenSpaceGuid.PcdFlashFvFspTOffset          + gMinPlatformPkgTokenSpaceGuid.PcdFlashFvFspTSize
SET gMinPlatformPkgTokenSpaceGuid.PcdFlashFvPreMemoryOffset     = gMinPlatformPkgTokenSpaceGuid.PcdFlashFvBspPreMemoryOffset  + gMinPlatformPkgTokenSpaceGuid.PcdFlashFvBspPreMemorySize

#
# Calculate base
#
SET gMinPlatformPkgTokenSpaceGuid.PcdFlashFvAdvancedBase        = gMinPlatformPkgTokenSpaceGuid.PcdFlashAreaBaseAddress     + gMinPlatformPkgTokenSpaceGuid.PcdFlashFvAdvancedOffset
SET gMinPlatformPkgTokenSpaceGuid.PcdFlashFvSecurityBase        = gMinPlatformPkgTokenSpaceGuid.PcdFlashFvAdvancedBase      + gMinPlatformPkgTokenSpaceGuid.PcdFlashFvAdvancedSize
SET gMinPlatformPkgTokenSpaceGuid.PcdFlashFvOsBootBase          = gMinPlatformPkgTokenSpaceGuid.PcdFlashFvSecurityBase      + gMinPlatformPkgTokenSpaceGuid.PcdFlashFvSecuritySize
SET gMinPlatformPkgTokenSpaceGuid.PcdFlashFvUefiBootBase        = gMinPlatformPkgTokenSpaceGuid.PcdFlashFvOsBootBase        + gMinPlatformPkgTokenSpaceGuid.PcdFlashFvOsBootSize

SET gMinPlatformPkgTokenSpaceGuid.PcdFlashFvBspBase             = gMinPlatformPkgTokenSpaceGuid.PcdFlashFvUefiBootBase      + gMinPlatformPkgTokenSpaceGuid.PcdFlashFvUefiBootSize
SET gMinPlatformPkgTokenSpaceGuid.PcdFlashFvPostMemoryBase      = gMinPlatformPkgTokenSpaceGuid.PcdFlashFvBspBase           + gMinPlatformPkgTokenSpaceGuid.PcdFlashFvBspSize
SET gMinPlatformPkgTokenSpaceGuid.PcdFlashFvFspSBase            = gMinPlatformPkgTokenSpaceGuid.PcdFlashFvPostMemoryBase    + gMinPlatformPkgTokenSpaceGuid.PcdFlashFvPostMemorySize
SET gMinPlatformPkgTokenSpaceGuid.PcdFlashFvFspMBase            = gMinPlatformPkgTokenSpaceGuid.PcdFlashFvFspSBase          + gMinPlatformPkgTokenSpaceGuid.PcdFlashFvFspSSize
SET gMinPlatformPkgTokenSpaceGuid.PcdFlashFvFspTBase            = gMinPlatformPkgTokenSpaceGuid.PcdFlashFvFspMBase          + gMinPlatformPkgTokenSpaceGuid.PcdFlashFvFspMSize
SET gMinPlatformPkgTokenSpaceGuid.PcdFlashFvBspPreMemoryBase    = gMinPlatformPkgTokenSpaceGuid.PcdFlashFvFspTBase          + gMinPlatformPkgTokenSpaceGuid.PcdFlashFvFspTSize
SET gMinPlatformPkgTokenSpaceGuid.PcdFlashFvPreMemoryBase       = gMinPlatformPkgTokenSpaceGuid.PcdFlashFvBspPreMemoryBase  + gMinPlatformPkgTokenSpaceGuid.PcdFlashFvBspPreMemorySize

SET gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageFtwSpareBase    = 0x0003C000
SET gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageFtwWorkingBase  = 0x0003C000
SET gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageVariableSize    = 0x0003C000
SET gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageVariableBase    = 0x0003C000
SET gCpPlatFlashTokenSpaceGuid.PcdFlashFvNvStorageEventLogSize      = 0x00002000
SET gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageFtwWorkingSize  = 0x00002000
SET gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageFtwSpareSize    = gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageVariableSize + gCpPlatFlashTokenSpaceGuid.PcdFlashFvNvStorageEventLogSize +gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageFtwWorkingSize
