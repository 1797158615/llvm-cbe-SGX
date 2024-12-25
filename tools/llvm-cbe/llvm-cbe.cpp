//===-- llc.cpp - Implement the LLVM Native Code Generator ----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This is the llc code generator driver. It provides a convenient
// command-line interface for generating native assembly-language code
// or C code, given LLVM bitcode.
//
//===----------------------------------------------------------------------===//
#include <iostream>
#include <string>
#include "llvm/Analysis/TargetLibraryInfo.h"
#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/CodeGen/CommandFlags.h"
#include "llvm/CodeGen/LinkAllAsmWriterComponents.h"
#include "llvm/CodeGen/LinkAllCodegenComponents.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/IRPrintingPasses.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/InitializePasses.h"
#include "llvm/MC/MCTargetOptionsCommandFlags.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Pass.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/PluginLoader.h"
#include "llvm/Support/PrettyStackTrace.h"
#include "llvm/Support/Signals.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/ToolOutputFile.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/TargetParser/Host.h"
#include "llvm/TargetParser/SubtargetFeature.h"
#include <llvm/Config/llvm-config.h>
#include <memory>
#include <fstream>
#include <sys/stat.h>
#include <vector>
#include <sys/types.h>
#include <errno.h>
using namespace llvm;

static codegen::RegisterCodeGenFlags CGF;

extern "C" void LLVMInitializeCBackendTarget();
extern "C" void LLVMInitializeCBackendTargetInfo();
extern "C" void LLVMInitializeCBackendTargetMC();

// General options for llc.  Other pass-specific options are specified
// within the corresponding llc passes, and target-specific options
// and back-end code generation options are specified with the target machine.
//
static cl::opt<std::string>
    InputFilename(cl::Positional, cl::desc("<input bitcode>"), cl::init("-"));

//ta.c文件
static cl::opt<std::string> OutputFilename("o", cl::desc("Output filename"),
                                           cl::value_desc("filename"));

static cl::opt<unsigned>
    TimeCompilations("time-compilations", cl::Hidden, cl::init(1u),
                     cl::value_desc("N"),
                     cl::desc("Repeat compilation N times for timing"));

// Determine optimization level.
static cl::opt<char>
    OptLevel("O",
             cl::desc("Optimization level. [-O0, -O1, -O2, or -O3] "
                      "(default = '-O2')"),
             cl::Prefix, cl::ZeroOrMore, cl::init(' '));

static cl::opt<std::string>
    TargetTriple("mtriple", cl::desc("Override target triple for module"));

cl::opt<bool> NoVerify("disable-verify", cl::Hidden,
                       cl::desc("Do not verify input module"));

static int compileModule(char **, LLVMContext &);

// GetFileNameRoot - Helper function to get the basename of a filename.
static inline std::string GetFileNameRoot(const std::string &InputFilename) {
  std::string IFN = InputFilename;
  std::string outputFilename;
  int Len = IFN.length();
  if ((Len > 2) && IFN[Len - 3] == '.' &&
      ((IFN[Len - 2] == 'b' && IFN[Len - 1] == 'c') ||
       (IFN[Len - 2] == 'l' && IFN[Len - 1] == 'l'))) {
    outputFilename = std::string(IFN.begin(), IFN.end() - 3); // s/.bc/.s/
  } else {
    outputFilename = IFN;
  }
  return outputFilename;
}

//文件夹创建
// 创建单个目录
bool createFolder(const std::string& folderPath) {
    if (mkdir(folderPath.c_str(), 0755) == 0 || errno == EEXIST) {
        return true;
    } else {
        std::cerr << "Failed to create folder: " << folderPath << " (Error: " << strerror(errno) << ")" << std::endl;
        return false;
    }
}

// 创建多级目录并判断是否成功
bool createDirectoryStructure(const std::string& root, const std::vector<std::string>& subDirs) {
    // 创建根目录
    if (!createFolder(root)) {
        return false;
    }

    // 创建子目录
    for (const auto& subDir : subDirs) {
        std::string fullPath = root + "/" + subDir;
        if (!createFolder(fullPath)) {
            return false;
        }
    }
    return true;
}


//ta.c文件
static ToolOutputFile *GetOutputStream(const char *TargetName,
                                       Triple::OSType OS,
                                       const char *ProgName) {
  // If we don't yet have an output filename, make one.
  if (OutputFilename.empty()) {
    if (InputFilename == "-")
      OutputFilename = "-";
    else {
      OutputFilename = GetFileNameRoot(InputFilename);
      std::cout << OutputFilename <<std::endl;

      switch (codegen::getFileType()) {
      case CodeGenFileType::CGFT_AssemblyFile:
        if (TargetName[0] == 'c') {
          if (TargetName[1] == 0){
            OutputFilename += "_ta.c";
            //c代码输出的文件名字
            std::cout << OutputFilename <<std::endl;
          }
            
          else if (TargetName[1] == 'p' && TargetName[2] == 'p')
            OutputFilename += ".cpp";
          else
            OutputFilename += ".s";
        } else
          OutputFilename += ".s";
        break;

      case CodeGenFileType::CGFT_ObjectFile:
        if (OS == Triple::Win32)
          OutputFilename += ".obj";
        else
          OutputFilename += ".o";
        break;
      case CodeGenFileType::CGFT_Null:
        OutputFilename += ".null";
        break;
      }
    }
  }

  // Decide if we need "binary" output.
  bool Binary = false;
  switch (codegen::getFileType()) {
  case CodeGenFileType::CGFT_AssemblyFile:
    break;
  case CodeGenFileType::CGFT_ObjectFile:
  case CodeGenFileType::CGFT_Null:
    Binary = true;
    break;
  }

  // Open the file.
  std::error_code error;
  sys::fs::OpenFlags OpenFlags = sys::fs::OF_None;

  std::cout << "Binary:"<<Binary <<std::endl;

  if (Binary)
    OpenFlags |= sys::fs::OF_Text;
  // OutputFilename = "/home/yxk/t.cbe.c";
  // std::cout << Binary <<std::endl;

  std::string path = "./";
  path += GetFileNameRoot(InputFilename);
  path += "/ta/";
  path += OutputFilename;

  ToolOutputFile *FDOut =
      new ToolOutputFile(path.c_str(), error, OpenFlags);
  if (error) {
    errs() << error.message() << '\n';
    delete FDOut;
    return 0;
  }

  return FDOut;
}

//main.c文件
static ToolOutputFile *GetMainStream(){
  // Decide if we need "binary" output.
  // bool Binary = false;
  // switch (codegen::getFileType()) {
  // case CodeGenFileType::CGFT_AssemblyFile:
  //   break;
  // case CodeGenFileType::CGFT_ObjectFile:
  // case CodeGenFileType::CGFT_Null:
  //   Binary = true;
  //   break;
  // }
  std::string OutMainFilename = "./";
  OutMainFilename += GetFileNameRoot(InputFilename);
  OutMainFilename += "/host/";
  OutMainFilename += "main.c";
  // Open the file.
  std::error_code error;
  sys::fs::OpenFlags OpenFlags = sys::fs::OF_None;
  // if (Binary)
  //   OpenFlags |= sys::fs::OF_Text;
  // OutMainFilename = "/home/yxk/t.cbe.c";
  ToolOutputFile *FDOut =
      new ToolOutputFile(OutMainFilename.c_str(), error, OpenFlags);
  if (error) {
    errs() << error.message() << '\n';
    delete FDOut;
    return 0;
  }

  return FDOut;
}
//ta.h文件
static ToolOutputFile *GetTA_hStream(){
  // std::cout << "cuowu" <<std::endl;
  // Decide if we need "binary" output.
  bool Binary = false;
  switch (codegen::getFileType()) {
  case CodeGenFileType::CGFT_AssemblyFile:
    break;
  case CodeGenFileType::CGFT_ObjectFile:
  case CodeGenFileType::CGFT_Null:
    Binary = true;
    break;
  }

  std::string OutTA_hFilename = "./";
  OutTA_hFilename += GetFileNameRoot(InputFilename);
  OutTA_hFilename += "/ta/include/";
  OutTA_hFilename += GetFileNameRoot(InputFilename);
  OutTA_hFilename += ".h";
  // Open the file.
  std::error_code error;
  sys::fs::OpenFlags OpenFlags = sys::fs::OF_None;
  if (Binary)
    OpenFlags |= sys::fs::OF_Text;
  std::cout << OutTA_hFilename <<std::endl;
  ToolOutputFile *FDOut =
      new ToolOutputFile(OutTA_hFilename.c_str(), error, OpenFlags);
  if (error) {
    errs() << error.message() << '\n';
    // std::cout << "cuowu" <<std::endl;
    delete FDOut;
    return 0;
  }

  return FDOut;
}
//--------------------------------------------------

static LLVMContext TheContext;

// main - Entry point for the llc compiler.
//
int main(int argc, char **argv) {
  


  //开始执行main函数
  sys::PrintStackTraceOnErrorSignal(argv[0]);
  PrettyStackTraceProgram X(argc, argv);

  // Enable debug stream buffering.
  EnableDebugBuffering = true;

  llvm_shutdown_obj Y; // Call llvm_shutdown() on exit.

  // Initialize targets first, so that --version shows registered targets.
  InitializeAllTargets();
  InitializeAllTargetMCs();
  InitializeAllAsmPrinters();
  InitializeAllAsmParsers();

  LLVMInitializeCBackendTarget();
  LLVMInitializeCBackendTargetInfo();
  LLVMInitializeCBackendTargetMC();

  // Initialize codegen and IR passes used by llc so that the -print-after,
  // -print-before, and -stop-after options work.
  PassRegistry *Registry = PassRegistry::getPassRegistry();
  initializeCore(*Registry);
  initializeCodeGen(*Registry);
  initializeLoopStrengthReducePass(*Registry);
  initializeLowerIntrinsicsPass(*Registry);
  initializeUnreachableBlockElimLegacyPassPass(*Registry);

  // Register the target printer for --version.
  cl::AddExtraVersionPrinter(TargetRegistry::printRegisteredTargetsForVersion);

  cl::ParseCommandLineOptions(argc, argv, "llvm system compiler\n");

  // Compile the module TimeCompilations times to give better compile time
  // metrics.
  for (unsigned I = TimeCompilations; I; --I)
    if (int RetVal = compileModule(argv, TheContext))
      return RetVal;
  return 0;
}

static int compileModule(char **argv, LLVMContext &Context) {
  // Load the module to be compiled...
  SMDiagnostic Err;

  std::unique_ptr<Module> M;

  Module *mod = 0;
  Triple TheTriple;

  auto MAttrs = codegen::getMAttrs();
  bool SkipModule = codegen::getMCPU() == "help" ||
                    (!MAttrs.empty() && MAttrs.front() == "help");

  // If user just wants to list available options, skip module loading
  if (!SkipModule) {
    M = parseIRFile(InputFilename, Err, Context);
    mod = M.get();
    if (mod == 0) {
      Err.print(argv[0], errs());
      return 1;
    }

    // If we are supposed to override the target triple, do so now.
    if (!TargetTriple.empty())
      mod->setTargetTriple(Triple::normalize(TargetTriple));
    TheTriple = Triple(mod->getTargetTriple());
  } else {
    TheTriple = Triple(Triple::normalize(TargetTriple));
  }

  if (TheTriple.getTriple().empty())
    TheTriple.setTriple(sys::getDefaultTargetTriple());

  // Get the target specific parser.
  std::string Error;
  // Override MArch
  // codegen::getMArch() = "c";
  const std::string MArch = "c";
  const Target *TheTarget =
      TargetRegistry::lookupTarget(MArch, TheTriple, Error);
  if (!TheTarget) {
    errs() << argv[0] << ": " << Error << "\n";
    return 1;
  }

  // Package up features to be passed to target/subtarget
  std::string FeaturesStr;
  if (MAttrs.size()) {
    SubtargetFeatures Features;
    for (unsigned i = 0; i != MAttrs.size(); ++i)
      Features.AddFeature(MAttrs[i]);
    FeaturesStr = Features.getString();
  }

  CodeGenOpt::Level OLvl = CodeGenOpt::Default;

  switch (OptLevel) {
  default:
    errs() << argv[0] << ": invalid optimization level.\n";
    return 1;
  case ' ':
    break;
  case '0':
    OLvl = CodeGenOpt::None;
    break;
  case '1':
    OLvl = CodeGenOpt::Less;
    break;
  case '2':
    OLvl = CodeGenOpt::Default;
    break;
  case '3':
    OLvl = CodeGenOpt::Aggressive;
    break;
  }

  TargetOptions Options;
  Options.AllowFPOpFusion = codegen::getFuseFPOps();
  Options.UnsafeFPMath = codegen::getEnableUnsafeFPMath();
  Options.NoInfsFPMath = codegen::getEnableNoInfsFPMath();
  Options.NoNaNsFPMath = codegen::getEnableNoNaNsFPMath();
  Options.HonorSignDependentRoundingFPMathOption =
      codegen::getEnableHonorSignDependentRoundingFPMath();
  if (codegen::getFloatABIForCalls() != FloatABI::Default)
    Options.FloatABIType = codegen::getFloatABIForCalls();
  Options.NoZerosInBSS = codegen::getDontPlaceZerosInBSS();
  Options.GuaranteedTailCallOpt = codegen::getEnableGuaranteedTailCallOpt();

  // Jackson Korba 9/30/14
  // OwningPtr<targetMachine>
  std::unique_ptr<TargetMachine> target(TheTarget->createTargetMachine(
      TheTriple.getTriple(), codegen::getMCPU(), FeaturesStr, Options,
      llvm::codegen::getRelocModel()));
  assert(target.get() && "Could not allocate target machine!");
  assert(mod && "Should have exited after outputting help!");
  TargetMachine &Target = *target.get();

  // Disable .loc support for older OS X versions.
  if (TheTriple.isMacOSX() && TheTriple.isMacOSXVersionLT(10, 6)) {
  }
  // TODO: Find a replacement to this function
  /* Greg Simpson 6-09-13
  no member named setMCUseLoc
  removed statement
  Target.setMCUseLoc(false);  */

  // Jackson Korba 9/30/14

  //生成文件夹
  // 根目录
  std::string rootDir = GetFileNameRoot(InputFilename);
  // 子目录结构
    std::vector<std::string> subDirs = {
        "host",
        "ta",
        "ta/include"
    };
  // 创建目录结构并检查是否成功
  if (createDirectoryStructure(rootDir, subDirs)) {
      std::cout << "Directory structure created successfully!" << std::endl;
  } else {
      std::cerr << "Failed to create the directory structure." << std::endl;
  }


  //ta.c文件
  std::unique_ptr<ToolOutputFile> Out(
      GetOutputStream(TheTarget->getName(), TheTriple.getOS(), argv[0]));
  if (!Out)
    return 1;
 //main文件
  std::unique_ptr<ToolOutputFile> MOut(GetMainStream());
  if (!MOut)
    return 1;
  //ta.h文件
  std::unique_ptr<ToolOutputFile> TA_hOut(GetTA_hStream());
  if (!TA_hOut)
    return 1;

  // Build up all of the passes that we want to do to the module.
  legacy::PassManager PM;

  // Add an appropriate TargetLibraryInfo pass for the module's triple.
  TargetLibraryInfoWrapperPass *TLI =
      new TargetLibraryInfoWrapperPass(TheTriple);
  PM.add(TLI);

  // Add intenal analysis passes from the target machine.
  PM.add(createTargetTransformInfoWrapperPass(Target.getTargetIRAnalysis()));

  if (mc::getExplicitRelaxAll()) {
    if (codegen::getFileType() != CodeGenFileType::CGFT_ObjectFile)
      errs() << argv[0]
             << ": warning: ignoring -mc-relax-all because filetype != obj\n";
  }

  //将ta.h头文件加入ta.c前面
  std::string OutTA_hFilename = GetFileNameRoot(InputFilename);
  OutTA_hFilename += ".h";
  std::string text = "#include <";
  text += OutTA_hFilename;
  text += ">\n";
  Out->os() << text;
  MOut->os() << text;
  // Ask the target to add backend passes as necessary.
  // bool CTargetMachine::addPassesToEmitFile(PassManagerBase &PM,
  //                                        raw_pwrite_stream &ta, //TA文件
  //                                        raw_pwrite_stream &main, //main文件
  //                                        raw_pwrite_stream &ta_h, //ta.h文件
  //                                        raw_pwrite_stream *DwoOut,
  //                                        CodeGenFileType FileType,
  //                                        bool DisableVerify,
  //                                        MachineModuleInfoWrapperPass *MMI)
  // if (Target.addPassesToEmitFile(PM, Out->os(), MOut->os(), TA_hOut->os(), nullptr, codegen::getFileType(),
  //                                NoVerify)) {
  // std::cout << "jjjjjjjjjjjjjj"<<std::endl;
  std::cout << "NoVerify:" << NoVerify<<std::endl;
  if (Target.addPassesToEmitFile(PM, Out->os(), &(MOut->os()), codegen::getFileType(),
                                 NoVerify)) {
    errs() << argv[0] << ": target does not support generation of this"
           << " file type!\n";
    return 1;
  }
  //main.c文件
  NoVerify = 1;
  std::cout << "NoVerify:" << NoVerify << std::endl;
  if (Target.addPassesToEmitFile(PM, TA_hOut->os(), nullptr, codegen::getFileType(),
                                 NoVerify)) {
    errs() << argv[0] << ": target does not support generation of this"
           << " file type!\n";
    return 1;
  }

  // Before executing passes, print the final values of the LLVM options.
  cl::PrintOptionValues();

  PM.run(*mod);

  // Declare success.
  //ta.c，ta.h,main.c保存
  Out->keep();
  TA_hOut->keep();
  MOut->keep();



  return 0;
}
