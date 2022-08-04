#include <Library/OpenQemuFwCfgLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>

/**
 * @brief Reads 8 bits from the data register
 *
 * @retval UINT8
 */
UINT8
EFIAPI
QemuFwCfgRead8 (
  )
{
  return IoRead8 (FW_CFG_PORT_DATA);
}

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
  )
{
  UINT16  WritenSelector;

  WritenSelector = IoWrite16 (FW_CFG_PORT_SEL, Selector);

  if (WritenSelector != Selector) {
    return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}

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
  )
{
  IoReadFifo8 (FW_CFG_PORT_DATA, Size, Buffer);
}

/**
 * @brief Checks for Qemu fw_cfg device by reading "QEMU" using the signature selector
 *
 * @retval EFI_SUCCESS - The fw_cfg device is present
 * @retval EFI_UNSUPPORTED - The device is absent
 */
EFI_STATUS
EFIAPI
QemuFwCfgIsPresent (
  )
{
  EFI_STATUS  Status;
  CHAR8       Control[4];

  Status = QemuFwCfgSelectItem (FW_CFG_SIGNATURE);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  QemuFwCfgReadBytes (4, &Control);
  if (AsciiStrnCmp ((CHAR8 *)&Control, FW_CFG_QEMU_SIGNATURE, 4) != 0) {
    return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}

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
  )
{
  QEMU_FW_CFG_FILE  FirmwareConfigFile;
  UINT32            FilesCount;
  UINT32            Idx;

  QemuFwCfgSelectItem (FW_CFG_FILE_DIR);
  QemuFwCfgReadBytes (sizeof (UINT32), &FilesCount);

  FilesCount = SwapBytes32 (FilesCount);

  for (Idx = 0; Idx < FilesCount; Idx++) {
    QemuFwCfgReadBytes (sizeof (QEMU_FW_CFG_FILE), &FirmwareConfigFile);
    if (AsciiStrCmp ((CHAR8 *)&(FirmwareConfigFile.name), String) == 0) {
      FirmwareConfigFile.select = SwapBytes16 (FirmwareConfigFile.select);
      FirmwareConfigFile.size   = SwapBytes32 (FirmwareConfigFile.size);
      CopyMem (FWConfigFile, &FirmwareConfigFile, sizeof (QEMU_FW_CFG_FILE));
      return EFI_SUCCESS;
    }
  }

  return EFI_UNSUPPORTED;
}
