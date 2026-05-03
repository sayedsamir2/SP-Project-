QT       += core gui widgets

CONFIG   += c++17
TEMPLATE = app
TARGET   = spProject-unstableRelease

INCLUDEPATH += /usr/local/include
INCLUDEPATH += C:\Users\ateee\Desktop\SP-Project-\libbcrypt-master\include

SOURCES += \
    libbcrypt-master/src/bcrypt.c \
    libbcrypt-master/src/crypt_blowfish.c \
    libbcrypt-master/src/crypt_gensalt.c \
    libbcrypt-master/src/wrapper.c \
    src/config/builders.cpp \
    src/dataStore/dataStore.cpp \
    src/database/dbApi.cpp \
    src/database/getShard.cpp \
    src/database/saveShard.cpp \
    src/projectLogic/analytics.cpp \
    src/projectLogic/auth.cpp \
    src/projectLogic/compute.cpp \
    src/projectLogic/crud.cpp \
    src/projectLogic/validations.cpp \
    src/userInterface/gui/AddEvaluationWidget.cpp \
    src/userInterface/gui/DashboardWidget.cpp \
    src/userInterface/gui/EvaluationsWidget.cpp \
    src/userInterface/gui/JudgesWidget.cpp \
    src/userInterface/gui/LoginDialog.cpp \
    src/userInterface/gui/MainWindow.cpp \
    src/userInterface/gui/ModifyTeamWidget.cpp \
    src/userInterface/gui/RegisterTeamWidget.cpp \
    src/userInterface/gui/TeamsWidget.cpp \
    src/userInterface/gui/main.cpp \
    src/utils/conversionUtils.cpp \
    src/utils/deserializationUtils.cpp \
    src/utils/numericUtils.cpp \
    src/utils/otherUtils.cpp \
    src/utils/serializationUtils.cpp \
    src/utils/stringUtils.cpp

HEADERS += \
    src/config/builders.hpp \
    src/config/config.hpp \
    src/dataStore/dataStore.hpp \
    src/database/dbApi.hpp \
    src/database/getShard.hpp \
    src/database/saveShard.hpp \
    src/projectLogic/analytics.hpp \
    src/projectLogic/auth.hpp \
    src/projectLogic/compute.hpp \
    src/projectLogic/crud.hpp \
    src/projectLogic/validations.hpp \
    src/userInterface/gui/AddEvaluationWidget.h \
    src/userInterface/gui/DashboardWidget.h \
    src/userInterface/gui/EvaluationsWidget.h \
    src/userInterface/gui/JudgesWidget.h \
    src/userInterface/gui/LoginDialog.h \
    src/userInterface/gui/MainWindow.h \
    src/userInterface/gui/ModifyTeamWidget.h \
    src/userInterface/gui/RegisterTeamWidget.h \
    src/userInterface/gui/TeamsWidget.h \
    src/utils/conversionUtils.hpp \
    src/utils/deserializationUtils.hpp \
    src/utils/numericUtils.hpp \
    src/utils/otherUtils.hpp \
    src/utils/serializationUtils.hpp \
    src/utils/stringUtils.hpp

FORMS += \
    src/userInterface/gui/AddEvaluationWidget.ui \
    src/userInterface/gui/LoginDialog.ui \
    src/userInterface/gui/MainWindow.ui \
    src/userInterface/gui/RegisterTeamWidget.ui

