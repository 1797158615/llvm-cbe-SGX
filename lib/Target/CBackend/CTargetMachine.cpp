//===-- CTargetMachine.cpp - TargetMachine for the C backend ----*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the TargetMachine that is used by the C backend.
//
//===----------------------------------------------------------------------===//

#include "CTargetMachine.h"
#include "CBackend.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/Transforms/Utils.h"
#include <iostream>

namespace llvm {

bool CTargetMachine::addPassesToEmitFile(PassManagerBase &PM,
                                         raw_pwrite_stream &Out, //TA文件
                                        //  raw_pwrite_stream &main, //main文件
                                        //  raw_pwrite_stream &ta_h, //ta.h文件
                                         raw_pwrite_stream *DwoOut,
                                         CodeGenFileType FileType,
                                         bool DisableVerify,
                                         MachineModuleInfoWrapperPass *MMI) {

  // std::cout << "yyyyyyyyyyyyyy"<<std::endl;
// std::cout << "DisableVerify:" << DisableVerify<<std::endl;

  if (FileType != CodeGenFileType::CGFT_AssemblyFile)
    return true;

  PM.add(new TargetPassConfig(*this, PM));
  PM.add(createGCLoweringPass());

  // Remove exception handling with LowerInvokePass. This would be done with
  // TargetPassConfig if TargetPassConfig supported TargetMachines that aren't
  // LLVMTargetMachines.
  PM.add(createLowerInvokePass());
  PM.add(createUnreachableBlockEliminationPass());

  // Lower atomic operations to libcalls
  PM.add(createAtomicExpandPass());

  // Lower vector operations into shuffle sequences
  PM.add(createExpandReductionsPass());

  if(DisableVerify == 1){
    //.h文件和.edl文件
    PM.add(new llvm_cbe::CWriter(Out, *DwoOut, true));
  } else {
    //app.c和enclave.c
    PM.add(new llvm_cbe::CWriter(Out, *DwoOut, false));
  }
  
  return false;
}

const TargetSubtargetInfo *
CTargetMachine::getSubtargetImpl(const Function &) const {
  return &SubtargetInfo;
}

bool CTargetSubtargetInfo::enableAtomicExpand() const { return true; }

const TargetLowering *CTargetSubtargetInfo::getTargetLowering() const {
  return &Lowering;
}

} // namespace llvm
