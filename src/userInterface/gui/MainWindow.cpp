#include "MainWindow.h"
#include "LoginDialog.h"
#include "DashboardWidget.h"
#include "TeamsWidget.h"
#include "JudgesWidget.h"
#include "EvaluationsWidget.h"
#include "RegisterTeamWidget.h"
#include "AddEvaluationWidget.h"
#include "ModifyTeamWidget.h"

#include <QFrame>
#include <QSpacerItem>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QApplication>

static const QString STYLE_MAIN = R"(
QMainWindow, QWidget#central {
    background: #070b18;
    color: #e2e8f0;
}
QWidget#sidebar {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #0a0f1e, stop:1 #0d1428);
    border-right: 1px solid rgba(255,255,255,0.07);
    min-width: 220px;
    max-width: 220px;
}
QPushButton#navBtn {
    background: transparent;
    color: #4a5568;
    border: none;
    border-left: 3px solid transparent;
    border-radius: 0px;
    text-align: left;
    padding: 11px 18px;
    font-size: 13px;
    font-family: 'Segoe UI', Arial;
    letter-spacing: 0.2px;
}
QPushButton#navBtn:hover {
    background: rgba(255,255,255,0.04);
    color: #94a3b8;
    border-left: 3px solid rgba(99,102,241,0.4);
}
QPushButton#navBtn[active="true"] {
    background: rgba(99,102,241,0.1);
    color: #818cf8;
    border-left: 3px solid #818cf8;
    font-weight: bold;
}
QPushButton#loginBtn {
    background: rgba(99,102,241,0.1);
    color: #818cf8;
    border: 1px solid rgba(99,102,241,0.3);
    border-radius: 10px;
    padding: 10px 14px;
    font-size: 13px;
    text-align: left;
    font-family: 'Segoe UI', Arial;
}
QPushButton#loginBtn:hover {
    background: rgba(99,102,241,0.2);
    border: 1px solid rgba(99,102,241,0.55);
    color: #a5b4fc;
}
QPushButton#logoutBtn {
    background: transparent;
    color: #f87171;
    border: none;
    font-size: 11px;
    padding: 2px 0px;
    text-align: left;
    font-family: 'Segoe UI', Arial;
}
QPushButton#logoutBtn:hover { color: #fca5a5; }
QLabel#logoTitle {
    color: #f1f5f9;
    font-size: 14px;
    font-weight: 700;
    letter-spacing: 0.3px;
    font-family: 'Segoe UI', Arial;
}
QLabel#logoSub {
    color: #334155;
    font-size: 10px;
    letter-spacing: 1.5px;
    font-family: 'Segoe UI', Arial;
}
QLabel#userLabel {
    color: #e2e8f0;
    font-size: 12px;
    font-weight: 700;
    font-family: 'Segoe UI', Arial;
}
QLabel#toast {
    background: rgba(16, 185, 129, 0.92);
    color: white;
    border-radius: 10px;
    padding: 10px 20px;
    font-size: 13px;
    font-weight: bold;
}
QLabel#toastError {
    background: rgba(239, 68, 68, 0.92);
    color: white;
    border-radius: 10px;
    padding: 10px 20px;
    font-size: 13px;
    font-weight: bold;
}
)";

void MainWindow::onLogoutClicked()
{
    setLoggedIn(false);
    showStartupLogin();
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Hackathon Manager — Virtual Platform");
    setMinimumSize(1100, 700);
    resize(1220, 760);
    setStyleSheet(STYLE_MAIN);
    setupUI();
}

MainWindow::~MainWindow() {}

void MainWindow::setInitialLoggedInState(bool state)
{
    setLoggedIn(state);
    m_startupLoginDone = true;
}

void MainWindow::setupUI()
{
    m_centralWidget = new QWidget(this);
    m_centralWidget->setObjectName("central");
    setCentralWidget(m_centralWidget);
    m_mainLayout = new QHBoxLayout(m_centralWidget);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);
    setupSidebar();
    setupPages();
    m_toast = new QLabel(this);
    m_toast->setObjectName("toast");
    m_toast->setAlignment(Qt::AlignCenter);
    m_toast->hide();
    m_toastTimer = new QTimer(this);
    m_toastTimer->setSingleShot(true);
    connect(m_toastTimer, &QTimer::timeout, m_toast, &QLabel::hide);
}

void MainWindow::setupSidebar()
{
    m_sidebar = new QWidget(m_centralWidget);
    m_sidebar->setObjectName("sidebar");
    m_sidebarLayout = new QVBoxLayout(m_sidebar);
    m_sidebarLayout->setContentsMargins(0, 0, 0, 0);
    m_sidebarLayout->setSpacing(0);

    // Logo
    QWidget *logoSection = new QWidget;
    logoSection->setStyleSheet("border-bottom: 1px solid rgba(255,255,255,0.07);");
    QHBoxLayout *logoLayout = new QHBoxLayout(logoSection);
    logoLayout->setContentsMargins(16, 20, 16, 20);
    logoLayout->setSpacing(12);

    QWidget *logoText = new QWidget;
    QVBoxLayout *logoTextLayout = new QVBoxLayout(logoText);
    logoTextLayout->setContentsMargins(0, 0, 0, 0);
    logoTextLayout->setSpacing(2);
    m_logoLabel    = new QLabel("Code Horses");
    m_logoSubLabel = new QLabel("Hackathon management sys.");
    m_logoLabel->setObjectName("logoTitle");
    m_logoSubLabel->setObjectName("logoSub");
    logoTextLayout->addWidget(m_logoLabel);
    logoTextLayout->addWidget(m_logoSubLabel);
    logoLayout->addWidget(logoText);
    m_sidebarLayout->addWidget(logoSection);

    QLabel *navLabel = new QLabel("MAIN MENU");
    navLabel->setStyleSheet(
        "color:#1e3a5f;font-size:10px;font-weight:700;"
        "letter-spacing:1.5px;padding:16px 18px 6px 18px;background:transparent;");
    m_sidebarLayout->addWidget(navLabel);

    QWidget *navWidget = new QWidget;
    QVBoxLayout *navLayout = new QVBoxLayout(navWidget);
    navLayout->setContentsMargins(6, 4, 6, 8);
    navLayout->setSpacing(1);
    QStringList navItems = {
        "Dashboard",
        "Teams",
        "Judges",
        "Evaluations",
        "Register Team",
        "Modify Team",
        "Add Evaluation"
    };
    for (int i = 0; i < navItems.size(); ++i) {
        QPushButton *btn = new QPushButton(navItems[i], navWidget);
        btn->setObjectName("navBtn");
        btn->setProperty("active", i == 0);
        btn->setCursor(Qt::PointingHandCursor);
        connect(btn, &QPushButton::clicked, this, [this, i]{ onNavClicked(i); });
        m_navBtns.append(btn);
        navLayout->addWidget(btn);
    }
    navLayout->addStretch();
    m_sidebarLayout->addWidget(navWidget, 1);

    // Bottom
    QWidget *bottomSection = new QWidget;
    bottomSection->setStyleSheet("border-top:1px solid rgba(255,255,255,0.07);");
    QVBoxLayout *bottomLayout = new QVBoxLayout(bottomSection);
    bottomLayout->setContentsMargins(10, 12, 10, 16);
    m_loginBtn = new QPushButton("Admin Login", bottomSection);
    m_loginBtn->setObjectName("loginBtn");
    m_loginBtn->setCursor(Qt::PointingHandCursor);
    connect(m_loginBtn, &QPushButton::clicked, this, &MainWindow::onLoginClicked);
    bottomLayout->addWidget(m_loginBtn);

    m_userWidget = new QWidget(bottomSection);
    m_userWidget->setStyleSheet(
        "background:rgba(99,102,241,0.07);border-radius:10px;"
        "border:1px solid rgba(99,102,241,0.18);");
    QHBoxLayout *userLayout = new QHBoxLayout(m_userWidget);
    userLayout->setContentsMargins(10, 8, 10, 8);
    userLayout->setSpacing(10);
    QLabel *avatar = new QLabel("A");
    avatar->setStyleSheet(
        "background:qlineargradient(x1:0,y1:0,x2:1,y2:1,stop:0 #6366f1,stop:1 #4f46e5);"
        "color:white;border-radius:14px;font-weight:bold;font-size:13px;border:none;");
    avatar->setFixedSize(28, 28);
    avatar->setAlignment(Qt::AlignCenter);
    QWidget *userInfo = new QWidget;
    userInfo->setStyleSheet("background:transparent;border:none;");
    QVBoxLayout *infoL = new QVBoxLayout(userInfo);
    infoL->setContentsMargins(0, 0, 0, 0);
    infoL->setSpacing(0);
    m_userLabel = new QLabel("Admin");
    m_userLabel->setObjectName("userLabel");
    m_userLabel->setStyleSheet("background:transparent;border:none;");
    m_logoutBtn = new QPushButton("Sign Out");
    m_logoutBtn->setObjectName("logoutBtn");
    m_logoutBtn->setCursor(Qt::PointingHandCursor);
    m_logoutBtn->setStyleSheet("border:none;background:transparent;");
    connect(m_logoutBtn, &QPushButton::clicked, this, &MainWindow::onLogoutClicked);
    infoL->addWidget(m_userLabel);
    infoL->addWidget(m_logoutBtn);
    userLayout->addWidget(avatar);
    userLayout->addWidget(userInfo);
    m_userWidget->hide();
    bottomLayout->addWidget(m_userWidget);
    m_sidebarLayout->addWidget(bottomSection);
    m_mainLayout->addWidget(m_sidebar);
}

void MainWindow::setupPages()
{
    QWidget *rightSide = new QWidget(m_centralWidget);
    rightSide->setStyleSheet("background:#070b18;");
    QVBoxLayout *rightLayout = new QVBoxLayout(rightSide);
    rightLayout->setContentsMargins(0, 0, 0, 0);
    rightLayout->setSpacing(0);

    QWidget *header = new QWidget;
    header->setFixedHeight(56);
    header->setStyleSheet(
        "background:rgba(10,15,30,0.95);"
        "border-bottom:1px solid rgba(255,255,255,0.07);");
    QHBoxLayout *headerLayout = new QHBoxLayout(header);
    headerLayout->setContentsMargins(28, 0, 28, 0);
    QLabel *pageTitle = new QLabel("Dashboard");
    pageTitle->setStyleSheet(
        "color:#f1f5f9;font-size:17px;font-weight:600;background:transparent;"
        "font-family:'Segoe UI',Arial;");
    headerLayout->addWidget(pageTitle);
    headerLayout->addStretch();
    QStringList titles = {"Dashboard","Teams","Judges","Evaluations","Register Team","Modify Team","Add Evaluation"};
    for (int i = 0; i < m_navBtns.size(); ++i) {
        connect(m_navBtns[i], &QPushButton::clicked, this, [pageTitle, titles, i]{
            pageTitle->setText(titles[i]);
        });
    }
    rightLayout->addWidget(header);

    m_stack = new QStackedWidget(rightSide);
    m_stack->setStyleSheet("background:#070b18;");
    m_dashboard    = new DashboardWidget(this);
    m_teams        = new TeamsWidget(this);
    m_judges       = new JudgesWidget(this);
    m_evaluations  = new EvaluationsWidget(this);
    m_registerTeam = new RegisterTeamWidget(this);
    m_modifyTeam   = new ModifyTeamWidget(this);
    m_addEval      = new AddEvaluationWidget(this);
    m_stack->addWidget(m_dashboard);
    m_stack->addWidget(m_teams);
    m_stack->addWidget(m_judges);
    m_stack->addWidget(m_evaluations);
    m_stack->addWidget(m_registerTeam);
    m_stack->addWidget(m_modifyTeam);
    m_stack->addWidget(m_addEval);
    rightLayout->addWidget(m_stack, 1);
    m_mainLayout->addWidget(rightSide, 1);

    connect(m_registerTeam, &RegisterTeamWidget::teamRegistered, this, [this](const QString &msg){
        m_teams->refresh(); m_dashboard->refresh(); showToast(msg, true); onNavClicked(1);
    });
    connect(m_modifyTeam, &ModifyTeamWidget::teamModified, this, [this](const QString &msg){
        m_teams->refresh(); m_dashboard->refresh(); showToast(msg, true); onNavClicked(1);
    });
    connect(m_addEval, &AddEvaluationWidget::evalAdded, this, [this](const QString &msg){
        m_evaluations->refresh(); m_dashboard->refresh(); showToast(msg, true); onNavClicked(3);
    });
}

void MainWindow::showEvent(QShowEvent *event) {
    QMainWindow::showEvent(event);
    if (!m_startupLoginDone) m_startupLoginDone = true;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveData();
    QMainWindow::closeEvent(event);
}

void MainWindow::showStartupLogin() {
    LoginDialog dlg(this);
    dlg.setStartupMode(true);
    if (dlg.exec() == QDialog::Accepted) {
        setLoggedIn(true);
        showToast("Welcome! You are now signed in.");
    } else {
        QApplication::quit();
    }
}

void MainWindow::onNavClicked(int index) {
    if (index == 6 && !m_isLoggedIn) { showToast("Admin login required", false); onLoginClicked(); return; }
    m_stack->setCurrentIndex(index);
    m_currentPage = index;
    updateNavStyles(index);
    if      (index == 0) m_dashboard->refresh();
    else if (index == 1) m_teams->refresh();
    else if (index == 2) m_judges->refresh();
    else if (index == 3) m_evaluations->refresh();
    else if (index == 5) m_modifyTeam->refresh();
    else if (index == 6) m_addEval->refresh();
}

void MainWindow::onLoginClicked() {
    LoginDialog dlg(this);
    dlg.setStartupMode(false);
    if (dlg.exec() == QDialog::Accepted) { setLoggedIn(true); showToast("Signed in successfully!"); }
}

void MainWindow::setLoggedIn(bool state) {
    m_isLoggedIn = state;
    m_loginBtn->setVisible(!state);
    m_userWidget->setVisible(state);
    m_navBtns[6]->setText(state ? "Add Evaluation"
                                : "Add Evaluation (locked)");
    m_addEval->setAdminMode(state);
}

void MainWindow::updateNavStyles(int active) {
    for (int i = 0; i < m_navBtns.size(); ++i) {
        m_navBtns[i]->setProperty("active", i == active);
        m_navBtns[i]->style()->unpolish(m_navBtns[i]);
        m_navBtns[i]->style()->polish(m_navBtns[i]);
    }
}

void MainWindow::showToast(const QString &msg, bool success) {
    m_toast->setText(msg);
    m_toast->setStyleSheet(success
                               ? "background:rgba(16,185,129,0.92);color:white;border-radius:10px;padding:10px 20px;font-size:13px;font-weight:bold;"
                               : "background:rgba(239,68,68,0.92);color:white;border-radius:10px;padding:10px 20px;font-size:13px;font-weight:bold;");
    m_toast->adjustSize();
    m_toast->move((width()-m_toast->width())/2, height()-m_toast->height()-30);
    m_toast->show();
    m_toast->raise();
    m_toastTimer->start(3000);
}
