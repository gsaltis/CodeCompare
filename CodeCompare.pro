QMAKE_CXX                       = @echo [C+] $@ && g++ 

QMAKE_CC                        = @echo [C+] $@ && gcc 

QMAKE_MOC                       = @echo [MO] $@ && moc 

QMAKE_LINK                      = @echo [LD] $@ && g++ 

QMAKE_RC                        = @echo [RC] $@ && windres 

#QMAKE_LFLAGS_WINDOWS            += -mwindows
QMAKE_LFLAGS_WINDOWS            += -Wl,--subsystem,console

QMAKE_CXXFLAGS                  += -DTRACE_USE -DTRACE_USE_PRINT

QMAKE_CXXFLAGS                  += 

QMAKE_LIBS                      = 

RESOURCES                       += images.qrc

TARGET                          = CodeCompare

VERSION                         = "0.0.1"

QMAKE_TARGET_COMPANY            = "Greg Saltis"

QMAKE_TARGET_PRODUCT            = "CodeCompare"

QMAKE_TARGET_COPYRIGHT          = "Copyright (C) 2023 Greg Saltis"

QT                              += core gui widgets

DEFINES                         += \

SOURCES                         += \
				   BuildARLine.cpp                              \
				   BuildCompileLine.cpp                         \
				   BuildEchoLine.cpp                            \
				   BuildElement.cpp                             \
				   BuildElementSet.cpp                          \
				   BuildForLine.cpp                             \
				   BuildLNLine.cpp                              \
				   BuildLine.cpp                                \
				   BuildLineARDisplayForm.cpp                   \
				   BuildLineBaseDisplayForm.cpp                 \
				   BuildLineDisplayForm.cpp                     \
				   BuildLineDisplayFormControls.cpp             \
				   BuildLineEchoDisplayForm.cpp                 \
				   BuildLineForDisplayForm.cpp                  \
				   BuildLineGCCDisplayForm.cpp                  \
				   BuildLineLNDisplayForm.cpp                   \
				   BuildLineRanlibDisplayForm.cpp               \
				   BuildLineSet.cpp                             \
				   BuildLineUnknownDisplayForm.cpp              \
				   BuildRanlibLine.cpp                          \
				   BuildSystem.cpp                              \
				   BuildTreeHierarchyContainer.cpp              \
				   BuildTreeHierarchyTable.cpp                  \
				   BuildTreeItem.cpp                            \
				   BuildTreeJSONCodeContainer.cpp               \
				   BuildTreeWindow.cpp                          \
				   BuildTreeWindowContainer.cpp                 \
				   BuildUnknownLine.cpp                         \
				   CodeBaseForm.cpp                             \
				   CodeBaseOpenDialog.cpp                       \
				   CodeNameWindow.cpp                           \
				   CodeWindow.cpp                               \
				   DependencyTreeWidgetItem.cpp                 \
				   DependencyTreeWindow.cpp                     \
				   DirectoryReadEntry.cpp                       \
				   DirectoryTreeElement.cpp                     \
				   MainDisplayWindow.cpp                        \
				   MainWindow.cpp                               \
				   SystemConfig.cpp                             \
				   WindowHeader.cpp                             \
				   main.cpp                                     \
				   trace.cpp                                    \

HEADERS                         += \
				   BuildARLine.h                                \
				   BuildCompileLine.h                           \
				   BuildEchoLine.h                              \
				   BuildElement.h                               \
				   BuildElementSet.h                            \
				   BuildForLine.h                               \
				   BuildLNLine.h                                \
				   BuildLine.h                                  \
				   BuildLineARDisplayForm.h                     \
				   BuildLineBaseDisplayForm.h                   \
				   BuildLineDisplayForm.h                       \
				   BuildLineDisplayFormControls.h               \
				   BuildLineEchoDisplayForm.h                   \
				   BuildLineForDisplayForm.h                    \
				   BuildLineGCCDisplayForm.h                    \
				   BuildLineLNDisplayForm.h                     \
				   BuildLineRanlibDisplayForm.h                 \
				   BuildLineSet.h                               \
				   BuildLineUnknownDisplayForm.h                \
				   BuildRanlibLine.h                            \
				   BuildSystem.h                                \
				   BuildTreeHierarchyContainer.h                \
				   BuildTreeHierarchyTable.h                    \
				   BuildTreeItem.h                              \
				   BuildTreeJSONCodeContainer.h                 \
				   BuildTreeWindow.h                            \
				   BuildTreeWindowContainer.h                   \
				   BuildUnknownLine.h                           \
				   CodeBaseForm.h                               \
				   CodeBaseOpenDialog.h                         \
				   CodeNameWindow.h                             \
				   CodeWindow.h                                 \
				   DependencyTreeWidgetItem.h                   \
				   DependencyTreeWindow.h                       \
				   DirectoryReadEntry.h                         \
				   DirectoryTreeElement.h                       \
				   MainDisplayWindow.h                          \
				   MainWindow.h                                 \
				   SystemConfig.h                               \
				   WindowHeader.h                               \
				   gui.h                                        \
				   trace.h                                      \
				   trace_file.h                                 \
				   trace_net.h                                  \
				   trace_none.h                                 \
				   trace_printf.h                               \

FORMS                           += \

QMAKE_EXTRA_TARGETS             += junkclean
junkclean.target                = junkclean
junkclean.commands              = @echo Removing junk                           \
                                  && rm -rf $(wildcard core* *~)
junkclean.depends               = 

QMAKE_EXTRA_TARGETS             += cleanall
cleanall.target                 = cleanall
cleanall.commands               = 
cleanall.depends                = junkclean                                     \
                                  clean
