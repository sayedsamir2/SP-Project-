#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>

class ModifyTeamWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ModifyTeamWidget(QWidget *parent = nullptr);
    void refresh();

signals:
    void teamModified(const QString &message);

private slots:
    void onSearch();
    void onModifySubmit();
    void onSubmitProject();

private:
    void buildSearchPage();
    void buildModifyPage();
    void buildSubmitProjectPage();
    void goToSearch();

    // Search page
    QWidget     *m_searchPage     = nullptr;
    QLineEdit   *m_searchIdEdit   = nullptr;
    QLabel      *m_searchError    = nullptr;
    QPushButton *m_searchBtn      = nullptr;

    // Modify page
    QWidget     *m_modifyPage     = nullptr;
    QLabel      *m_teamIdLabel    = nullptr;
    QLineEdit   *m_nameEdit       = nullptr;
    QLineEdit   *m_uniEdit        = nullptr;
    QSpinBox    *m_membersSpin    = nullptr;
    QLineEdit   *m_projectEdit    = nullptr;
    QLabel      *m_modifyError    = nullptr;
    QPushButton *m_modifyBtn      = nullptr;
    QPushButton *m_submitProjBtn  = nullptr;

    // Submit project page
    QWidget     *m_submitPage     = nullptr;
    QLabel      *m_submitIdLabel  = nullptr;
    QLineEdit   *m_newProjectEdit = nullptr;
    QLabel      *m_submitError    = nullptr;
    QPushButton *m_submitBtn      = nullptr;

    QStackedWidget *m_stack       = nullptr;
    QString         m_currentId;
};
