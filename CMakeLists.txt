# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(CodeCompare LANGUAGES CXX)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "CodeCompare")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}")

set(CMAKE_CXX_FLAGS "-DTRACE_USE -DTRACE_USE_PRINT")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_standard_project_setup()

qt_add_executable(CodeCompare
    BuildARLine.cpp
    BuildARLine.h
    BuildCompileLine.cpp
    BuildCompileLine.h
    BuildEchoLine.cpp
    BuildEchoLine.h
    BuildElement.cpp
    BuildElement.h
    BuildElementSet.cpp
    BuildElementSet.h
    BuildForLine.cpp
    BuildForLine.h
    BuildLine.cpp
    BuildLine.h
    BuildLineARDisplayForm.cpp
    BuildLineARDisplayForm.h
    BuildLineBaseDisplayForm.cpp
    BuildLineBaseDisplayForm.h
    BuildLineDisplayForm.cpp
    BuildLineDisplayForm.h
    BuildLineDisplayFormControls.cpp
    BuildLineDisplayFormControls.h
    BuildLineEchoDisplayForm.cpp
    BuildLineEchoDisplayForm.h
    BuildLineForDisplayForm.cpp
    BuildLineForDisplayForm.h
    BuildLineGCCDisplayForm.cpp
    BuildLineGCCDisplayForm.h
    BuildLineLNDisplayForm.cpp
    BuildLineLNDisplayForm.h
    BuildLineRanlibDisplayForm.cpp
    BuildLineRanlibDisplayForm.h
    BuildLineSet.cpp
    BuildLineSet.h
    BuildLineUnknownDisplayForm.cpp
    BuildLineUnknownDisplayForm.h
    BuildLNLine.cpp
    BuildLNLine.h
    BuildRanlibLine.cpp
    BuildRanlibLine.h
    BuildSystem.cpp
    BuildSystem.h
    BuildTreeItem.cpp
    BuildTreeItem.h
    BuildTreeWindow.cpp
    BuildTreeWindow.h
    BuildUnknownLine.cpp
    BuildUnknownLine.h
    CodeBaseForm.cpp
    CodeBaseForm.h
    CodeBaseOpenDialog.cpp
    CodeBaseOpenDialog.h
    CodeNameWindow.cpp
    CodeNameWindow.h
    CodeWindow.cpp
    CodeWindow.h
    DependencyTreeWidgetItem.cpp
    DependencyTreeWidgetItem.h
    DependencyTreeWindow.cpp
    DependencyTreeWindow.h
    DirectoryReadEntry.cpp
    DirectoryReadEntry.h
    DirectoryTreeElement.cpp
    DirectoryTreeElement.h
    gui.h
    main.cpp
    main.h
    MainDisplayWindow.cpp
    MainDisplayWindow.h
    MainWindow.cpp
    MainWindow.h
    SystemConfig.cpp
    SystemConfig.h
    trace.cpp
    trace.h
    trace_file.h
    trace_net.h
    trace_none.h
    trace_printf.h
    WindowHeader.cpp
    WindowHeader.h
 )

set_target_properties(CodeCompare PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(CodeCompare PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

# Resources:
set(CodeCompare_resource_files
    "images/Left.png"
    "images/Right.png"
    "images/OpenFile.png"
)

qt_add_resources(CodeCompare "CodeCompare"
    PREFIX
        "/"
    FILES
        ${CodeCompare_resource_files}
)

install(TARGETS CodeCompare
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
