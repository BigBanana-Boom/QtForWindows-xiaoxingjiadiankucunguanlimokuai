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
    CustomWidget/searchdialog.cpp \
    CustomWidget/simpledialog.cpp \
    Done/done.cpp \
    Done/DoneAdd/doneadd.cpp \
    Done/DoneAdd/doneadddialog.cpp \
    Done/DoneRemove/doneremove.cpp \
    Done/DoneRemove/doneremovedialog.cpp \
    Done/DoneRemove/doneremovedialog2.cpp \
    Done/DoneChange/donechange.cpp \
    Done/DoneChange/donechangedialog.cpp \
    Done/DoneSearch/donesearch.cpp \
    EventFilter/eventfilterformainwindow.cpp \
    InRepo/inrepo.cpp \
    InRepo/InRepoAdd/inrepoadd.cpp \
    InRepo/InRepoAdd/inrepoadddialog.cpp \
    InRepo/InRepoRemove/inreporemove.cpp \
    InRepo/InRepoRemove/inreporemovedialog.cpp \
    InRepo/InRepoChange/inrepochange.cpp \
    InRepo/InRepoChange/inrepochangedialog.cpp \
    InRepo/InRepoSearch/inreposearch.cpp \
    OutRepo/outrepo.cpp \
    OutRepo/OutRepoAdd/outrepoadd.cpp \
    OutRepo/OutRepoAdd/outrepoadddialog.cpp \
    OutRepo/OutRepoRemove/outreporemove.cpp \
    OutRepo/OutRepoRemove/outreporemovedialog.cpp \
    OutRepo/OutRepoChange/outrepochange.cpp \
    OutRepo/OutRepoChange/outrepochangedialog.cpp \
    OutRepo/OutRepoSearch/outreposearch.cpp \
    Repo/repo.cpp \
    Repo/RepoModify/repomodify.cpp \
    Repo/RepoAdjust/repoadjust.cpp \
    Repo/RepoAdjust/repoadjustdialog.cpp \
    Repo/RepoChange/repochange.cpp \
    Repo/RepoChange/repochangedialog.cpp \
    Repo/RepoSearch/reposearch.cpp \
    MethodClass/chinesesort.cpp \
    MethodClass/refreshrepotableid.cpp \
    ModifyRepo/modifyrepo.cpp \
    main.cpp \
    mainwindow.cpp
# C++源文件####################################################

# 头文件#######################################################
HEADERS += \
    CustomButton/dialoggradientbutton.h \
    CustomButton/dropdowngradientbutton.h \
    CustomButton/exitgradientbutton.h \
    CustomButton/normalgradientbutton.h \
    CustomButton/gradientbutton.h \
    CustomButton/gradientbuttonwithsimpleicon.h \
    CustomStruct/inputzone.h \
    CustomStruct/repoandcurrentnum.h \
    CustomStruct/repoandnumber.h \
    CustomWidget/searchdialog.h \
    CustomWidget/simpledialog.h \
    Done/done.h \
    Done/DoneAdd/doneadd.h \
    Done/DoneAdd/doneadddialog.h \
    Done/DoneRemove/doneremove.h \
    Done/DoneRemove/doneremovedialog.h \
    Done/DoneRemove/doneremovedialog2.h \
    Done/DoneChange/donechange.h \
    Done/DoneChange/donechangedialog.h \
    Done/DoneSearch/donesearch.h \
    EventFilter/eventfilterformainwindow.h \
    OutRepo/outrepo.h \
    OutRepo/OutRepoAdd/outrepoadd.h \
    OutRepo/OutRepoAdd/outrepoadddialog.h \
    OutRepo/OutRepoRemove/outreporemove.h \
    OutRepo/OutRepoRemove/outreporemovedialog.h \
    OutRepo/OutRepoChange/outrepochange.h \
    OutRepo/OutRepoChange/outrepochangedialog.h \
    OutRepo/OutRepoSearch/outreposearch.h \
    InRepo/inrepo.h \
    InRepo/InRepoAdd/inrepoadd.h \
    InRepo/InRepoAdd/inrepoadddialog.h \
    InRepo/InRepoRemove/inreporemove.h \
    InRepo/InRepoRemove/inreporemovedialog.h \
    InRepo/InRepoChange/inrepochange.h \
    InRepo/InRepoChange/inrepochangedialog.h \
    InRepo/InRepoSearch/inreposearch.h \
    Repo/repo.h \
    Repo/RepoModify/repomodify.h \
    Repo/RepoAdjust/repoadjust.h \
    Repo/RepoAdjust/repoadjustdialog.h \
    Repo/RepoChange/repochange.h \
    Repo/RepoChange/repochangedialog.h \
    Repo/RepoSearch/reposearch.h \
    MethodClass/chinesesort.h \
    MethodClass/refreshrepotableid.h \
    ModifyRepo/modifyrepo.h \
    mainwindow.h
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

RC_ICONS = Image/BrokenRice.ico
