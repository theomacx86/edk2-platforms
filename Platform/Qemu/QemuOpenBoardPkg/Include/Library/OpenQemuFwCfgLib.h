#ifndef QEMUOPENBOARDPKG_QEMUFWCFGLIB_H
#define QEMUOPENBOARDPKG_QEMUFWCFGLIB_H

#include <PiPei.h>
#include <Library/IoLib.h>

// QEMU fw_cfg registers
#define FW_CFG_PORT_SEL   0x510
#define FW_CFG_PORT_DATA  0x511
#define FW_CFG_PORT_DMA   0x514

// QEMU Selectors
#define FW_CFG_SIGNATURE  0x0000
#define FW_CFG_ID         0x0001
#define FW_CFG_FILE_DIR   0x0019

#define FW_CFG_QEMU_SIGNATURE  "QEMU"

typedef struct {
  UINT32    size;
  UINT16    select;
  UINT16    reserved;
  CHAR8     name[56];
} QEMU_FW_CFG_FILE;

#pragma pack(1)

typedef struct {
  UINT64    BaseAddr;
  UINT64    Length;
  UINT32    Type;
} EFI_E820_ENTRY;

#define EFI_E820_ENTRY_TYPE_RAM       1
#define EFI_E820_ENTRY_TYPE_RESERVED  2
#define EFI_E820_ENTRY_TYPE_ACPI      3
#define EFI_E820_ENTRY_TYPE_NVS       4
#define EFI_E820_ENTRY_TYPE_UNUSABLE  5

#pragma pack()

/**
 * @brief Checks for Qemu fw_cfg device by reading "QEMU" using the signature selector
 *
 * @retval EFI_SUCCESS - The fw_cfg device is present
 * @retval EFI_UNSUPPORTED - The device is absent
 */
EFI_STATUS
EFIAPI
QemuFwCfgIsPresent (
  );

/**
 * @brief Sets the selector register to the specified value
 *
 * @param Selector
 * @retval EFI_SUCCESS
 * @retval EFI_UNSUPPORTED
 */
EFI_STATUS
EFIAPI
QemuFwCfgSelectItem (
  IN UINT16  Selector
  );

/**
 * @brief Reads 8 bits from the data register
 *
 * @retval UINT8
 */
UINT8
EFIAPI
QemuFwCfgRead8 (
  );

/**
 * @brief Reads N bytes from the data register
 *
 * @param Size
 * @param Buffer
 * @return VOID
 */
VOID
EFIAPI
QemuFwCfgReadBytes (
  IN UINTN  Size,
  OUT VOID  *Buffer
  );

/**
 * @brief Finds a file in fw_cfg by its name
 *
 * @param String Pointer to an ASCII string to match in the database
 * @param FWConfigFile Buffer for the config file
 * @retval EFI_STATUS - Entry was found, FWConfigFile is populated
 * @retval EFI_ERROR - Entry was not found
 */
EFI_STATUS
EFIAPI
QemuFwCfgFindFile (
  IN CHAR8              *String,
  OUT QEMU_FW_CFG_FILE  *FWConfigFile
  );

#endif
