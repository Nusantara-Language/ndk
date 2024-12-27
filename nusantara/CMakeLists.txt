# Cari package
# find_package(LLVM REQUIRED CONFIG)
# find_package(Clang REQUIRED CONFIG)
# find_package(LLD REQUIRED CONFIG)
# find_package(ZSTD REQUIRED CONFIG)
# find_package(libxml2 REQUIRED CONFIG)

# Cek
# if(LLVM_FOUND)
#   message(STATUS "LLVM ditemukan di: ${LLVM_DIR}")
# else()
#   message(FATAL_ERROR "LLVM tidak ditemukan. Pastikan LLVM_DIR diatur dengan benar.")
# endif()

# if(Clang_FOUND)
#   message(STATUS "Clang ditemukan di: ${Clang_DIR}")
# else()
#   message(FATAL_ERROR "Clang tidak ditemukan. Pastikan Clang_DIR diatur dengan benar.")
# endif()

# if(LLD_FOUND)
#   message(STATUS "LLD ditemukan di: ${LLD_DIR}")
# else()
#   message(FATAL_ERROR "LLD tidak ditemukan. Pastikan LLD_DIR diatur dengan benar atau LLD terinstal.")
# endif()

# if(ZSTD_FOUND)
#   message(STATUS "ZSTD ditemukan di: ${ZSTD_DIR}")
# else()
#   message(FATAL_ERROR "ZSTD tidak ditemukan. Pastikan ZSTD_DIR diatur dengan benar atau ZSTD terinstal.")
# endif()

# if(libxml2_FOUND)
#   message(STATUS "libxml2 ditemukan di: ${libxml2_DIR}")
# else()
#   message(FATAL_ERROR "libxml2 tidak ditemukan. Pastikan libxml2_DIR diatur dengan benar atau libxml2 terinstal.")
# endif()
# Opsi untuk memperlihatkan waktu eksekusi (ON/OFF)
option(PERLIHATKAN_WAKTU_EKSEKUSI "Memperlihatkan waktu yang di perlukan program untuk di eksekusi sampai selesai." ON)

# Versi proyek
set(NUSANTARA_VERSION_SUFFIX "-dev")
set(NUSANTARA_VERSION "0.0.1${NUSANTARA_VERSION_SUFFIX}")

# Perlihatkan waktu eksekusi
set(PERLIHATKAN_WAKTU_EKSEKUSI ON)

# Atur versi header sesuai template
configure_file(${CMAKE_SOURCE_DIR}/nusantara/muat/konfig/konfig.hpp.template ${CMAKE_SOURCE_DIR}/nusantara/muat/konfig/konfig.hpp)
configure_file(${CMAKE_SOURCE_DIR}/nusantara/muat/konfig/versi.hpp.template ${CMAKE_SOURCE_DIR}/nusantara/muat/konfig/versi.hpp)

# SRC FILE
file(GLOB_RECURSE LIB_SOURCES 
  "pustaka/**/*.cpp" 
  "pustaka/*.cpp"
)

# Executable
add_executable(nusantara "program/nusantara/nusantara.cpp" ${LIB_SOURCES})
add_executable(tests "program/test/test.cpp" ${LIB_SOURCES})

# Include folder
target_include_directories(tests PRIVATE "muat")
target_include_directories(nusantara PRIVATE "muat")
target_include_directories(nusantara PRIVATE "${CMAKE_SOURCE_DIR}/pustaka_eksternal/muat")
target_include_directories(nusantara PRIVATE ${LLVM_INCLUDE_DIRS})
target_include_directories(nusantara PRIVATE ${CLANG_INCLUDE_DIRS})
target_include_directories(nusantara PRIVATE ${LLD_INCLUDE_DIRS})

# Library folder
link_directories(${LLVM_LIBRARY_DIRS})

# Link library
target_link_libraries(nusantara PRIVATE
# LLVM
# libLLVMAArch64AsmParser.a
# libLLVMAArch64CodeGen.a
# libLLVMAArch64Desc.a
# libLLVMAArch64Disassembler.a
# libLLVMAArch64Info.a
# libLLVMAArch64Utils.a
# libLLVMAMDGPUAsmParser.a
# libLLVMAMDGPUCodeGen.a
# libLLVMAMDGPUDesc.a
# libLLVMAMDGPUDisassembler.a
# libLLVMAMDGPUInfo.a
# libLLVMAMDGPUTargetMCA.a
# libLLVMAMDGPUUtils.a
# libLLVMARMAsmParser.a
# libLLVMARMCodeGen.a
# libLLVMARMDesc.a
# libLLVMARMDisassembler.a
# libLLVMARMInfo.a
# libLLVMARMUtils.a
# libLLVMAVRAsmParser.a
# libLLVMAVRCodeGen.a
# libLLVMAVRDesc.a
# libLLVMAVRDisassembler.a
# libLLVMAVRInfo.a
# libLLVMAggressiveInstCombine.a
# libLLVMAnalysis.a
# libLLVMAsmParser.a
# libLLVMAsmPrinter.a
# libLLVMBPFAsmParser.a
# libLLVMBPFCodeGen.a
# libLLVMBPFDesc.a
# libLLVMBPFDisassembler.a
# libLLVMBPFInfo.a
# libLLVMBinaryFormat.a
# libLLVMBitReader.a
# libLLVMBitWriter.a
# libLLVMBitstreamReader.a
# libLLVMCFGuard.a
# libLLVMCFIVerify.a
# libLLVMCodeGen.a
# libLLVMCodeGenData.a
# libLLVMCodeGenTypes.a
# libLLVMCore.a
# libLLVMCoroutines.a
# libLLVMCoverage.a
# libLLVMDWARFLinker.a
# libLLVMDWARFLinkerClassic.a
# libLLVMDWARFLinkerParallel.a
# libLLVMDWP.a
# libLLVMDebugInfoBTF.a
# libLLVMDebugInfoCodeView.a
# libLLVMDebugInfoDWARF.a
# libLLVMDebugInfoGSYM.a
# libLLVMDebugInfoLogicalView.a
# libLLVMDebugInfoMSF.a
# libLLVMDebugInfoPDB.a
# libLLVMDebuginfod.a
# libLLVMDemangle.a
# libLLVMDiff.a
# libLLVMDlltoolDriver.a
# libLLVMExecutionEngine.a
# libLLVMExegesis.a
# libLLVMExegesisAArch64.a
# libLLVMExegesisMips.a
# libLLVMExegesisPowerPC.a
# libLLVMExegesisX86.a
# libLLVMExtensions.a
# libLLVMFileCheck.a
# libLLVMFrontendDriver.a
# libLLVMFrontendHLSL.a
# libLLVMFrontendOffloading.a
# libLLVMFrontendOpenACC.a
# libLLVMFrontendOpenMP.a
# libLLVMFuzzMutate.a
# libLLVMFuzzerCLI.a
# libLLVMGlobalISel.a
# libLLVMHexagonAsmParser.a
# libLLVMHexagonCodeGen.a
# libLLVMHexagonDesc.a
# libLLVMHexagonDisassembler.a
# libLLVMHexagonInfo.a
# libLLVMHipStdPar.a
# libLLVMIRPrinter.a
# libLLVMIRReader.a
# libLLVMInstCombine.a
# libLLVMInstrumentation.a
# libLLVMInterfaceStub.a
# libLLVMInterpreter.a
# libLLVMJITLink.a
# libLLVMLTO.a
# libLLVMLanaiAsmParser.a
# libLLVMLanaiCodeGen.a
# libLLVMLanaiDesc.a
# libLLVMLanaiDisassembler.a
# libLLVMLanaiInfo.a
# libLLVMLibDriver.a
# libLLVMLineEditor.a
# libLLVMLinker.a
# libLLVMLoongArchAsmParser.a
# libLLVMLoongArchCodeGen.a
# libLLVMLoongArchDesc.a
# libLLVMLoongArchDisassembler.a
# libLLVMLoongArchInfo.a
# libLLVMMC.a
# libLLVMMCA.a
# libLLVMMCDisassembler.a
# libLLVMMCJIT.a
# libLLVMMCParser.a
# libLLVMMIRParser.a
# libLLVMMSP430AsmParser.a
# libLLVMMSP430CodeGen.a
# libLLVMMSP430Desc.a
# libLLVMMSP430Disassembler.a
# libLLVMMSP430Info.a
# libLLVMMipsAsmParser.a
# libLLVMMipsCodeGen.a
# libLLVMMipsDesc.a
# libLLVMMipsDisassembler.a
# libLLVMMipsInfo.a
# libLLVMNVPTXCodeGen.a
# libLLVMNVPTXDesc.a
# libLLVMNVPTXInfo.a
# libLLVMObjCARCOpts.a
# libLLVMObjCopy.a
# libLLVMObject.a
# libLLVMObjectYAML.a
# libLLVMOptDriver.a
# libLLVMOption.a
# libLLVMOrcDebugging.a
# libLLVMOrcJIT.a
# libLLVMOrcShared.a
# libLLVMOrcTargetProcess.a
# libLLVMPasses.a
# libLLVMPowerPCAsmParser.a
# libLLVMPowerPCCodeGen.a
# libLLVMPowerPCDesc.a
# libLLVMPowerPCDisassembler.a
# libLLVMPowerPCInfo.a
# libLLVMProfileData.a
# libLLVMRISCVAsmParser.a
# libLLVMRISCVCodeGen.a
# libLLVMRISCVDesc.a
# libLLVMRISCVDisassembler.a
# libLLVMRISCVInfo.a
# libLLVMRISCVTargetMCA.a
# libLLVMRemarks.a
# libLLVMRuntimeDyld.a
# libLLVMSandboxIR.a
# libLLVMScalarOpts.a
# libLLVMSelectionDAG.a
# libLLVMSparcAsmParser.a
# libLLVMSparcCodeGen.a
# libLLVMSparcDesc.a
# libLLVMSparcDisassembler.a
# libLLVMSparcInfo.a
# libLLVMSupport.a
# libLLVMSymbolize.a
# libLLVMSystemZAsmParser.a
# libLLVMSystemZCodeGen.a
# libLLVMSystemZDesc.a
# libLLVMSystemZDisassembler.a
# libLLVMSystemZInfo.a
# libLLVMTableGen.a
# libLLVMTableGenBasic.a
# libLLVMTableGenCommon.a
# libLLVMTarget.a
# libLLVMTargetParser.a
# libLLVMTextAPI.a
# libLLVMTextAPIBinaryReader.a
# libLLVMTransformUtils.a
# libLLVMVEAsmParser.a
# libLLVMVECodeGen.a
# libLLVMVEDesc.a
# libLLVMVEDisassembler.a
# libLLVMVEInfo.a
# libLLVMVectorize.a
# libLLVMWebAssemblyAsmParser.a
# libLLVMWebAssemblyCodeGen.a
# libLLVMWebAssemblyDesc.a
# libLLVMWebAssemblyDisassembler.a
# libLLVMWebAssemblyInfo.a
# libLLVMWebAssemblyUtils.a
# libLLVMWindowsDriver.a
# libLLVMWindowsManifest.a
# libLLVMX86AsmParser.a
# libLLVMX86CodeGen.a
# libLLVMX86Desc.a
# libLLVMX86Disassembler.a
# libLLVMX86Info.a
# libLLVMX86TargetMCA.a
# libLLVMXCoreCodeGen.a
# libLLVMXCoreDesc.a
# libLLVMXCoreDisassembler.a
# libLLVMXCoreInfo.a
# libLLVMXRay.a
# libLLVMipo.a
# CLANG
# libclang.a
# libclangAPINotes.a
# libclangARCMigrate.a
# libclangAST.a
# libclangASTMatchers.a
# libclangAnalysis.a
# libclangAnalysisFlowSensitive.a
# libclangAnalysisFlowSensitiveModels.a
# libclangApplyReplacements.a
# libclangBasic.a
# libclangChangeNamespace.a
# libclangCodeGen.a
# libclangCrossTU.a
# libclangDaemon.a
# libclangDaemonTweaks.a
# libclangDependencyScanning.a
# libclangDirectoryWatcher.a
# libclangDoc.a
# libclangDriver.a
# libclangDynamicASTMatchers.a
# libclangEdit.a
# libclangExtractAPI.a
# libclangFormat.a
# libclangFrontend.a
# libclangFrontendTool.a
# libclangHandleCXX.a
# libclangHandleLLVM.a
# libclangIncludeCleaner.a
# libclangIncludeFixer.a
# libclangIncludeFixerPlugin.a
# libclangIndex.a
# libclangIndexSerialization.a
# libclangInstallAPI.a
# libclangInterpreter.a
# libclangLex.a
# libclangMove.a
# libclangParse.a
# libclangPseudo.a
# libclangPseudoCLI.a
# libclangPseudoCXX.a
# libclangPseudoGrammar.a
# libclangQuery.a
# libclangReorderFields.a
# libclangRewrite.a
# libclangRewriteFrontend.a
# libclangSema.a
# libclangSerialization.a
# libclangStaticAnalyzerCheckers.a
# libclangStaticAnalyzerCore.a
# libclangStaticAnalyzerFrontend.a
# libclangSupport.a
# libclangTooling.a
# libclangToolingASTDiff.a
# libclangToolingCore.a
# libclangToolingInclusions.a
# libclangToolingInclusionsStdlib.a
# libclangToolingRefactoring.a
# libclangToolingSyntax.a
# libclangTransformer.a
# LLD
# liblldCOFF.a
# liblldCommon.a
# liblldELF.a
# liblldMachO.a
# liblldMinGW.a
# liblldWasm.a
# C++
libc++.a
libc++abi.a
libunwind.a
# Other
# libffi.a
# ntdll
# version
# zstd
# libzlibstatic.a
# LibXml2::LibXml2
)