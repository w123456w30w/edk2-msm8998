/** @file
*
*  Copyright (c) 2011, ARM Limited. All rights reserved.
*  Copyright (c) 2019, RUIKAI LIU and MR TUNNEL. All rights reserved.
*
*  This program and the accompanying materials
*  are licensed and made available under the terms and conditions of the BSD License
*  which accompanies this distribution.  The full text of the license may be found at
*  http://opensource.org/licenses/bsd-license.php
*
*  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
*  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
*
**/

#include <Library/ArmPlatformLib.h>
#include <Library/DebugLib.h>

#include <Library/PlatformMemoryMapLib.h>
/**
  Return the Virtual Memory Map of your platform
  This Virtual Memory Map is used by MemoryInitPei Module to initialize the MMU on your platform.
  @param[out]   VirtualMemoryMap    Array of ARM_MEMORY_REGION_DESCRIPTOR describing a Physical-to-
                                    Virtual Memory mapping. This array must be ended by a zero-filled
                                    entry
**/

VOID
ArmPlatformGetVirtualMemoryMap (
  IN ARM_MEMORY_REGION_DESCRIPTOR** VirtualMemoryMap
  )
{
  //TO-DO:ADD MEMORY MAP HERE
  PARM_MEMORY_REGION_DESCRIPTOR_EX MemoryDescriptorEx =
      GetPlatformMemoryMap();
  ARM_MEMORY_REGION_DESCRIPTOR
        MemoryTable[MAX_ARM_MEMORY_REGION_DESCRIPTOR_COUNT];
  UINTN Index = 0;

  // Run through each memory descriptor
  while (MemoryDescriptorEx->Length != 0) {
    if (MemoryDescriptorEx->HobOption == HobOnlyNoCacheSetting) {
      MemoryDescriptorEx++;
      continue;
    }

    ASSERT(Index < MAX_ARM_MEMORY_REGION_DESCRIPTOR_COUNT);

    MemoryTable[Index].PhysicalBase = MemoryDescriptorEx->Address;
    MemoryTable[Index].VirtualBase  = MemoryDescriptorEx->Address;
    MemoryTable[Index].Length       = MemoryDescriptorEx->Length;
    MemoryTable[Index].Attributes   = MemoryDescriptorEx->ArmAttributes;

    Index++;
    MemoryDescriptorEx++;
  }

  // Last one (terminator)
  ASSERT(Index < MAX_ARM_MEMORY_REGION_DESCRIPTOR_COUNT);
  MemoryTable[Index].PhysicalBase = 0;
  MemoryTable[Index].VirtualBase  = 0;
  MemoryTable[Index].Length       = 0;
  MemoryTable[Index].Attributes   = 0;

  *VirtualMemoryMap = MemoryTable;

}