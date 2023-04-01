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
				   CodeBaseForm.cpp                             \
				   CodeBaseOpenDialog.cpp                       \
				   CodeNameWindow.cpp                           \
				   CodeWindow.cpp                               \
				   DependencyTreeWindow.cpp                     \
				   DirectoryReadEntry.cpp                       \
				   DirectoryTreeElement.cpp                     \
				   DirectoryTreeWindow.cpp                      \
				   MainDisplayWindow.cpp                        \
				   MainWindow.cpp                               \
				   SystemConfig.cpp                             \
				   WindowHeader.cpp                             \
				   main.cpp                                     \
				   trace.cpp                                    \

HEADERS                         += \
				   CodeBaseForm.h                               \
				   CodeBaseOpenDialog.h                         \
				   CodeNameWindow.h                             \
				   CodeWindow.h                                 \
				   DependencyTreeWindow.h                       \
				   DirectoryReadEntry.h                         \
				   DirectoryTreeElement.h                       \
				   DirectoryTreeWindow.h                        \
				   MainDisplayWindow.h                          \
				   MainWindow.h                                 \
				   SystemConfig.h                               \
				   WindowHeader.h                               \
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
