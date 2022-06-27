#include <PiPei.h>
#include <Ppi/SecPlatformInformation.h>
#include <Ppi/TemporaryRamSupport.h>
#include <Library/PcdLib.h>
#include <Ppi/PeiCoreFvLocation.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/HobLib.h>
#include <Library/MtrrLib.h>
#include <Library/PlatformSecLib.h>
#include <Library/PeiServicesLib.h>

EFI_PEI_CORE_FV_LOCATION_PPI gEfiPeiCoreFvLocationPpi = {
  (VOID*) 0xFFE20000 //Could be done automatically at build
};

EFI_PEI_PPI_DESCRIPTOR gEfiPeiCoreFvLocationDescriptor = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiPeiCoreFvLocationPpiGuid,
  &gEfiPeiCoreFvLocationPpi
};

EFI_PEI_PPI_DESCRIPTOR *
EFIAPI
SecPlatformMain (
  IN OUT   EFI_SEC_PEI_HAND_OFF  *SecCoreData
  )
{
    //Use half of available heap size for PpiList
    EFI_PEI_PPI_DESCRIPTOR * PpiList = (VOID*) (SecCoreData->PeiTemporaryRamBase + (SecCoreData->PeiTemporaryRamSize/2));
    CopyMem(PpiList, &gEfiPeiCoreFvLocationDescriptor, sizeof(EFI_PEI_PPI_DESCRIPTOR));
    return PpiList;
}

/**
  This interface conveys state information out of the Security (SEC) phase into PEI.

  @param  PeiServices               Pointer to the PEI Services Table.
  @param  StructureSize             Pointer to the variable describing size of the input buffer.
  @param  PlatformInformationRecord Pointer to the EFI_SEC_PLATFORM_INFORMATION_RECORD.

  @retval EFI_SUCCESS           The data was successfully returned.
  @retval EFI_BUFFER_TOO_SMALL  The buffer was too small.

**/
EFI_STATUS
EFIAPI
SecPlatformInformation (
  IN CONST EFI_PEI_SERVICES                  **PeiServices,
  IN OUT   UINT64                            *StructureSize,
  OUT   EFI_SEC_PLATFORM_INFORMATION_RECORD  *PlatformInformationRecord
  )
{
    return EFI_SUCCESS;
}

/**
  This interface disables temporary memory in SEC Phase.
**/
VOID
EFIAPI
SecPlatformDisableTemporaryMemory (
  VOID
  )
{

}