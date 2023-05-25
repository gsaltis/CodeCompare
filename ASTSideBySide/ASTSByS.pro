QMAKE_CXX                       = @echo [C+] $@ && g++ 

QMAKE_CC                        = @echo [C+] $@ && gcc 

QMAKE_MOC                       = @echo [MO] $@ && moc 

QMAKE_LINK                      = @echo [LD] $@ && g++ 

QMAKE_RC                        = @echo [RC] $@ && windres 

#QMAKE_LFLAGS_WINDOWS           += -mwindows
QMAKE_LFLAGS_WINDOWS            += -Wl,--subsystem,console

QMAKE_CXXFLAGS                  += 

QMAKE_LIBS                      = 

TARGET                          = ASTSByS

VERSION                         = "0.0.0"
QMAKE_TARGET_COMPANY            = "Greg Saltis"

QMAKE_TARGET_PRODUCT            = "ASTSByS"

QMAKE_TARGET_COPYRIGHT          = "Copyright (C) 2023 Greg Saltis"

QT                              += core gui widgets

DEFINES                         += \

RESOURCES                       += images.qrc

SOURCES                         += \
				   BuildARLine.cpp				\
				   BuildCompileLine.cpp				\
				   BuildEchoLine.cpp				\
				   BuildElement.cpp				\
				   BuildElementSet.cpp				\
				   BuildForLine.cpp				\
				   BuildLine.cpp				\
				   BuildLineSet.cpp				\
				   BuildSystem.cpp				\
				   BuildTree.cpp				\
				   BuildTreeItem.cpp				\
				   BuildTreeItemComponent.cpp			\
				   BuildTreeItemSection.cpp			\
				   BuildTreeItemTop.cpp				\
				   BuildTreeContainer.cpp			\
				   CodeDisplay.cpp				\
				   CodeDisplayLine.cpp				\
				   CodeEditor.cpp				\
				   CodeHighlighter.cpp				\
                                   CodeTrack.cpp                                \
				   CommonFileTree.cpp				\
				   DirBuildContainer.cpp			\
				   DirTree.cpp					\
				   DirTreeContainer.cpp				\
				   DirTreeItem.cpp				\
				   DirTreeItemDir.cpp				\
				   DirTreeItemFile.cpp				\
				   FileContentsDiff.cpp				\
				   FileSectionDiff.cpp				\
                                   FileTreeElement.cpp                          \
                                   FileTreeFile.cpp                             \
				   JSONAST.cpp					\
				   LineNumberArea.cpp				\
				   MainDisplayWindow.cpp			\
				   MainWindow.cpp				\
				   SystemConfig.cpp				\
				   TUTree.cpp					\
				   TUTreeContainer.cpp				\
				   TUTreeContainerSplitter.cpp			\
				   TUTreeElement.cpp				\
				   TitledWindow.cpp				\
				   TopTranslationUnitElement.cpp		\
				   TranslationUnit.cpp				\			 
				   TranslationUnitType.cpp			\  
				   WindowHeader.cpp				\
				   main.cpp                                     \
				   trace.cpp                                    \

HEADERS                         += \
				   BuildARLine.h				\
				   BuildCompileLine.h				\
				   BuildEchoLine.h				\
				   BuildElement.h				\
				   BuildElementSet.h				\
				   BuildForLine.h				\
				   BuildLine.h					\
				   BuildLineSet.h				\
				   BuildSystem.h				\
				   BuildTree.h					\
				   BuildTreeItem.h				\
				   BuildTreeItemComponent.h			\
				   BuildTreeItemSection.h			\
				   BuildTreeItemTop.h				\
				   BuildTreeContainer.h				\
				   CodeDisplay.h				\
				   CodeDisplayLine.h				\
				   CodeEditor.h					\
				   CodeHighlighter.h				\
                                   CodeTrack.h                                  \
				   CommonFileTree.h				\
				   DirBuildContainer.h				\
				   DirTree.h					\
				   DirTreeContainer.h				\
				   DirTreeItem.h				\
				   DirTreeItemDir.h				\
				   DirTreeItemFile.h				\
				   FileContentsDiff.h				\
				   FileSectionDiff.h				\
                                   FileTreeElement.h                            \
                                   FileTreeFile.h                               \
				   JSONAST.h					\
				   LineNumberArea.h				\
				   MainDisplayWindow.h				\
				   MainWindow.h					\
				   SystemConfig.h				\
				   TUTree.h					\
				   TUTreeContainer.h				\
				   TUTreeContainerSplitter.h			\
				   TUTreeElement.h				\
				   TitledWindow.h				\
				   TopTranslationUnitElement.h			\
				   TranslationUnit.h				\			 
				   TranslationUnitType.h			\  
				   WindowHeader.h				\
				   trace.h                                      \
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
