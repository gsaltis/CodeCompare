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
				   BuildSystemTree.cpp                          \
				   BuildTreeHierarchyContainer.cpp              \
				   BuildTreeHierarchyTable.cpp                  \
				   BuildTreeHierarchyTableItem.cpp              \
				   BuildTreeItem.cpp                            \
				   BuildTreeJSONCodeContainer.cpp               \
				   BuildTreeWindow.cpp                          \
				   BuildTreeWindowContainer.cpp                 \
				   BuildUnknownLine.cpp                         \
				   CodeBaseForm.cpp                             \
				   CodeBaseOpenDialog.cpp                       \
				   CodeCompareDir.cpp                           \
				   CodeCompareToolBarButton.cpp                 \
				   CodeEditor.cpp                               \
				   CodeHighlighter.cpp                          \
				   CodeNameWindow.cpp                           \
				   CodeTrack.cpp                                \
				   CodeWindow.cpp                               \
				   DependencyTreeWidgetItem.cpp                 \
				   DependencyTreeWindow.cpp                     \
				   DirectoryReadEntry.cpp                       \
				   DirectoryTreeElement.cpp                     \
				   FileContentsDiff.cpp                         \
				   FileSectionDiff.cpp                          \
				   FileTreeDirectory.cpp                        \
				   FileTreeElement.cpp                          \
				   FileTreeFile.cpp                             \
				   FileTreeWidgetItem.cpp                       \
				   FunctionType.cpp                             \
				   JSONAST.cpp                                  \
				   LineNumberArea.cpp                           \
				   MainDisplayWindow.cpp                        \
				   MainWindow.cpp                               \
				   MonitoredLabel.cpp                           \
				   SourceCodeComparisonToolBar.cpp              \
				   SourceDifferencesItem.cpp                    \
				   SourceDifferencesWindow.cpp                  \
				   SourceFileCompareAnalyzeStatsWindow.cpp      \
				   SourceFileCompareFileWindow.cpp              \
				   SourceFileCompareStatsWindow.cpp             \
				   SourceFileCompareTreeContainer.cpp           \
				   SystemConfig.cpp                             \
				   TitledWindow.cpp                             \
				   TranslationUnit.cpp                          \
				   TranslationUnitType.cpp                      \
				   VariableType.cpp                             \
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
				   BuildSystemTree.h                            \
				   BuildTreeHierarchyContainer.h                \
				   BuildTreeHierarchyTable.h                    \
				   BuildTreeHierarchyTableItem.h                \
				   BuildTreeItem.h                              \
				   BuildTreeJSONCodeContainer.h                 \
				   BuildTreeWindow.h                            \
				   BuildTreeWindowContainer.h                   \
				   BuildUnknownLine.h                           \
				   CodeBaseForm.h                               \
				   CodeBaseOpenDialog.h                         \
				   CodeCompareDir.h                             \
				   CodeCompareToolBarButton.h                   \
				   CodeEditor.h                                 \
				   CodeHighlighter.h                            \
				   CodeNameWindow.h                             \
				   CodeTrack.h                                  \
				   CodeWindow.h                                 \
				   DependencyTreeWidgetItem.h                   \
				   DependencyTreeWindow.h                       \
				   DirectoryReadEntry.h                         \
				   DirectoryTreeElement.h                       \
				   FileContentsDiff.h                           \
				   FileSectionDiff.h                            \
				   FileTreeDirectory.h                          \
				   FileTreeElement.h                            \
				   FileTreeFile.h                               \
				   FileTreeWidgetItem.h                         \
				   FunctionType.h                               \
				   JSONAST.h                                    \
				   LineNumberArea.h                             \
				   MainDisplayWindow.h                          \
				   MainWindow.h                                 \
				   MonitoredLabel.h                             \
				   SourceCodeComparisonToolBar.h                \
				   SourceDifferencesItem.h                      \
				   SourceDifferencesWindow.h                    \
				   SourceFileCompareAnalyzeStatsWindow.h        \
				   SourceFileCompareFileWindow.h                \
				   SourceFileCompareStatsWindow.h               \
				   SourceFileCompareTreeContainer.h             \
				   SystemConfig.h                               \
				   TitledWindow.h                               \
				   TranslationUnit.h                            \
				   TranslationUnitType.h                        \
				   VariableType.h                               \
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
