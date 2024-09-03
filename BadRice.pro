# 项目需要的Qt模块################################################
QT       += core gui
QT       += widgets
QT       += sql
# 项目需要的Qt模块################################################

# 使用C++11标准#################################################
CONFIG += c++11
# 使用C++11标准#################################################

# Debug模式将文件放到_debug，Release模式将文件放到当前文件夹下的_release####
# 而不是放到外面的_release##########################################
CONFIG += debug_and_release
CONFIG(debug, debug|release){
    DESTDIR = $$PWD/_debug
} else {
    DESTDIR = $$PWD/_release
}
# Debug模式将文件放到_debug，Release模式将文件放到_release###############
# 而不是放到外面的_release##########################################

# C++源文件####################################################
SOURCES += \
    CustomButton/dialoggradientbutton.cpp \
    CustomButton/dropdowngradientbutton.cpp \
    CustomButton/exitgradientbutton.cpp \
    CustomButton/normalgradientbutton.cpp \
    CustomButton/gradientbutton.cpp \
    CustomButton/gradientbuttonwithsimpleicon.cpp \
    CustomWidget/doneadddialog.cpp \
    CustomWidget/donechangedialog.cpp \
    CustomWidget/doneremovedialog.cpp \
    CustomWidget/doneremovedialog2.cpp \
    CustomWidget/inrepoadddialog.cpp \
    CustomWidget/inrepochangedialog.cpp \
    CustomWidget/inreporemovedialog.cpp \
    CustomWidget/outrepoadddialog.cpp \
    CustomWidget/outrepochangedialog.cpp \
    CustomWidget/outreporemovedialog.cpp \
    CustomWidget/repoadjustdialog.cpp \
    CustomWidget/repochangedialog.cpp \
    CustomWidget/simpledialog.cpp \
    Done/done.cpp \
    Done/doneadd.cpp \
    Done/doneremove.cpp \
    Done/donechange.cpp \
    Done/donesearch.cpp \
    Done/doneaddcategory.cpp \
    Done/doneaddname.cpp \
    Done/doneremoveoutrepo.cpp \
    EventFilter/eventfilterformainwindow.cpp \
    InRepo/inrepo.cpp \
    InRepo/inrepoadd.cpp \
    InRepo/inreporemove.cpp \
    InRepo/inrepochange.cpp \
    InRepo/inreposearch.cpp \
    InRepo/inrepoaddcategory.cpp \
    InRepo/inrepoaddname.cpp \
    InRepo/inrepoaddrepo.cpp \
    OutRepo/outrepo.cpp \
    OutRepo/outrepoadd.cpp \
    OutRepo/outreporemove.cpp \
    OutRepo/outrepochange.cpp \
    OutRepo/outreposearch.cpp \
    Repo/repo.cpp \
    Repo/repomodify.cpp \
    Repo/repoadjust.cpp \
    Repo/repochange.cpp \
    Repo/reposearch.cpp \
    ModifyRepo/modifyrepo.cpp \
    chinesesort.cpp \
    main.cpp \
    mainwindow.cpp \
    refreshrepotableid.cpp
# C++源文件####################################################

# 头文件#######################################################
HEADERS += \
    CustomButton/dialoggradientbutton.h \
    CustomButton/dropdowngradientbutton.h \
    CustomButton/exitgradientbutton.h \
    CustomButton/normalgradientbutton.h \
    CustomButton/gradientbutton.h \
    CustomButton/gradientbuttonwithsimpleicon.h \
    CustomWidget/doneadddialog.h \
    CustomWidget/donechangedialog.h \
    CustomWidget/doneremovedialog.h \
    CustomWidget/doneremovedialog2.h \
    CustomWidget/inrepoadddialog.h \
    CustomWidget/inrepochangedialog.h \
    CustomWidget/inreporemovedialog.h \
    CustomWidget/outrepoadddialog.h \
    CustomWidget/outrepochangedialog.h \
    CustomWidget/outreporemovedialog.h \
    CustomWidget/repoadjustdialog.h \
    CustomWidget/repochangedialog.h \
    CustomWidget/simpledialog.h \
    Done/done.h \
    Done/doneadd.h \
    Done/doneremove.h \
    Done/donechange.h \
    Done/donesearch.h \
    Done/doneaddcategory.h \
    Done/doneaddname.h \
    Done/doneremoveoutrepo.h \
    EventFilter/eventfilterformainwindow.h \
    OutRepo/outrepo.h \
    OutRepo/outrepoadd.h \
    OutRepo/outreporemove.h \
    OutRepo/outrepochange.h \
    OutRepo/outreposearch.h \
    InRepo/inrepo.h \
    InRepo/inrepoadd.h \
    InRepo/inreporemove.h \
    InRepo/inrepochange.h \
    InRepo/inreposearch.h \
    InRepo/inrepoaddcategory.h \
    InRepo/inrepoaddname.h \
    InRepo/inrepoaddrepo.h \
    Repo/repo.h \
    Repo/repomodify.h \
    Repo/repoadjust.h \
    Repo/repochange.h \
    Repo/reposearch.h \
    ModifyRepo/modifyrepo.h \
    chinesesort.h \
    mainwindow.h \
    refreshrepotableid.h
# 头文件#######################################################

# 资源文件#####################################################
RESOURCES += \
    rc.qrc
# 资源文件#####################################################

# 发布包中应该有的文件############################################
DISTFILES += \
    Dependency/* \
# 发布包中应该有的文件############################################

# 项目包含文件###################################################
include(Frameless/frameless.pri)
include(Xlsx/qtxlsx.pri)
# 项目包含文件###################################################
