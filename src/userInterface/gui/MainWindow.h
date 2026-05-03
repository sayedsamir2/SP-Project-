#pragma once
#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QTimer>
#include <QShowEvent>
#include <QCloseEvent>
#include "../../dataStore/dataStore.hpp"

class DashboardWidget;
class TeamsWidget;
class JudgesWidget;
class EvaluationsWidget;
class RegisterTeamWidget;
class AddEvaluationWidget;
class ModifyTeamWidget;
class LoginDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool isAdminLoggedIn() const { return m_isLoggedIn; }
    void setInitialLoggedInState(bool state);

protected:
    void showEvent(QShowEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onNavClicked(int index);
    void onLoginClicked();
    void onLogoutClicked();
    void setLoggedIn(bool state);
    void showToast(const QString &msg, bool success = true);
    void showStartupLogin();

private:
    void setupUI();
    void setupSidebar();
    void setupPages();
    void updateNavStyles(int active);

    // Layout
    QWidget        *m_centralWidget;
    QHBoxLayout    *m_mainLayout;

    // Sidebar
    QWidget        *m_sidebar;
    QVBoxLayout    *m_sidebarLayout;
    QLabel         *m_logoLabel;
    QLabel         *m_logoSubLabel;
    QList<QPushButton*> m_navBtns;
    QPushButton    *m_loginBtn;
    QLabel         *m_userLabel;
    QPushButton    *m_logoutBtn;
    QWidget        *m_userWidget;

    // Pages
    QStackedWidget    *m_stack;
    DashboardWidget   *m_dashboard;
    TeamsWidget       *m_teams;
    JudgesWidget      *m_judges;
    EvaluationsWidget *m_evaluations;
    RegisterTeamWidget   *m_registerTeam;
    AddEvaluationWidget  *m_addEval;
    ModifyTeamWidget     *m_modifyTeam;

    // Toast
    QLabel  *m_toast;
    QTimer  *m_toastTimer;

    bool m_isLoggedIn = false;
    bool m_startupLoginDone = false;
    int  m_currentPage = 0;
};
