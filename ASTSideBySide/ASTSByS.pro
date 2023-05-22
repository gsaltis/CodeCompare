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
                                   CodeEditor.cpp                               \
                                   CodeDisplay.cpp                              \
                                   CodeDisplayLine.cpp                          \
                                   CodeHighlighter.cpp                          \
                                   DirTree.cpp                                  \
                                   DirTreeContainer.cpp                         \
                                   DirTreeItem.cpp                              \
                                   DirTreeItemDir.cpp                           \
                                   DirTreeItemFile.cpp                          \
                                   JSONAST.cpp                                  \
				   MainDisplayWindow.cpp                        \
                                   LineNumberArea.cpp                           \
				   MainWindow.cpp                               \
				   SystemConfig.cpp                             \
				   TUTreeElement.cpp                            \
				   TUTree.cpp                                   \
				   TUTreeContainer.cpp                          \
				   TUTreeContainerSplitter.cpp                  \
				   TitledWindow.cpp                             \
				   TopTranslationUnitElement.cpp                \
				   WindowHeader.cpp                             \
				   main.cpp                                     \
				   trace.cpp                                    \

HEADERS                         += \
                                   CodeDisplay.h                                \
                                   CodeDisplayLine.h                            \
                                   CodeEditor.h                                 \
                                   CodeHighlighter.h                            \
                                   DirTree.h                                    \
                                   DirTreeContainer.h                           \
                                   DirTreeItem.h                                \
                                   DirTreeItemDir.h                             \
                                   DirTreeItemFile.h                            \
				   JSONAST.h                                    \
                                   LineNumberArea.h                             \
				   MainDisplayWindow.h                          \
				   MainWindow.h                                 \
				   SystemConfig.h                               \
				   TUTree.h                                     \
				   TUTreeContainer.h                            \
				   TUTreeContainerSplitter.h                    \
				   TUTreeElement.h                              \
				   TitledWindow.h                               \
				   TopTranslationUnitElement.h                  \
				   WindowHeader.h                               \
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
