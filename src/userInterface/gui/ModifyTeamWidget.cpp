#include "ModifyTeamWidget.h"
#include "../../projectLogic/crud.hpp"
#include "../../projectLogic/validations.hpp"
#include "../../dataStore/dataStore.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>

static const QString MODIFY_STYLE = R"(
QWidget#formCard {
    background: rgba(13,20,38,0.92);
    border-radius: 20px;
    border: 1px solid rgba(255,255,255,0.09);
}
QLabel#formTitle {
    color: #f1f5f9;
    font-size: 22px;
    font-weight: 700;
    font-family: 'Segoe UI', Arial;
}
QLabel#formSub {
    color: #4a5568;
    font-size: 13px;
    font-family: 'Segoe UI', Arial;
}
QLabel#fieldLabel {
    color: #818cf8;
    font-size: 11px;
    font-weight: 700;
    font-family: 'Segoe UI', Arial;
    letter-spacing: 1px;
}
QLabel#idBadge {
    color: rgba(99,102,241,0.85);
    font-size: 12px;
    font-family: 'Segoe UI', Arial;
    background: rgba(99,102,241,0.1);
    border: 1px solid rgba(99,102,241,0.25);
    border-radius: 8px;
    padding: 5px 12px;
}
QLabel#errorLabel {
    color: #f87171;
    font-size: 12px;
    font-family: 'Segoe UI', Arial;
}
QLineEdit, QSpinBox {
    background: rgba(7,9,18,0.85);
    color: #e2e8f0;
    border: 1px solid rgba(255,255,255,0.09);
    border-radius: 10px;
    padding: 11px 14px;
    font-size: 13px;
    font-family: 'Segoe UI', Arial;
}
QLineEdit:focus, QSpinBox:focus {
    border: 1px solid rgba(99,102,241,0.55);
    background: rgba(7,9,22,0.95);
}
QSpinBox::up-button, QSpinBox::down-button {
    background: rgba(99,102,241,0.1);
    border: none;
    width: 18px;
}
QPushButton#submitBtn {
    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
        stop:0 #6366f1, stop:1 #4f46e5);
    color: white;
    border: none;
    border-radius: 10px;
    padding: 13px;
    font-size: 14px;
    font-weight: bold;
    font-family: 'Segoe UI', Arial;
}
QPushButton#submitBtn:hover {
    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
        stop:0 #818cf8, stop:1 #6366f1);
}
QPushButton#submitBtn:pressed { padding: 14px 12px; }
QPushButton#secondBtn {
    background: rgba(99,102,241,0.08);
    color: #818cf8;
    border: 1px solid rgba(99,102,241,0.28);
    border-radius: 10px;
    padding: 11px;
    font-size: 13px;
    font-weight: bold;
    font-family: 'Segoe UI', Arial;
}
QPushButton#secondBtn:hover {
    background: rgba(99,102,241,0.18);
    border: 1px solid rgba(99,102,241,0.5);
}
QPushButton#backBtn {
    background: transparent;
    color: #4a5568;
    border: none;
    font-size: 12px;
    font-family: 'Segoe UI', Arial;
    padding: 4px 0px;
    text-align: left;
}
QPushButton#backBtn:hover { color: #818cf8; }
)";

// ─────────────────────────────────────────────────────────────
// Helper: wrap a card + scroll in a page widget
// ─────────────────────────────────────────────────────────────
static QWidget* makeScrollPage(QWidget *card)
{
    QWidget *page = new QWidget;
    page->setStyleSheet("background:#070b18;");
    QVBoxLayout *outerL = new QVBoxLayout(page);
    outerL->setContentsMargins(0, 0, 0, 0);

    QScrollArea *scroll = new QScrollArea;
    scroll->setWidgetResizable(true);
    scroll->setStyleSheet("QScrollArea{border:none;background:#070b18;}");

    QWidget *inner = new QWidget;
    inner->setStyleSheet("background:#070b18;");
    QVBoxLayout *innerL = new QVBoxLayout(inner);
    innerL->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    innerL->setContentsMargins(24, 24, 24, 24);
    innerL->addWidget(card, 0, Qt::AlignHCenter);

    scroll->setWidget(inner);
    outerL->addWidget(scroll);
    return page;
}

// ─────────────────────────────────────────────────────────────
ModifyTeamWidget::ModifyTeamWidget(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("background:#070b18;");
    QVBoxLayout *mainL = new QVBoxLayout(this);
    mainL->setContentsMargins(0, 0, 0, 0);

    m_stack = new QStackedWidget(this);
    m_stack->setStyleSheet("background:#070b18;");

    buildSearchPage();
    buildModifyPage();
    buildSubmitProjectPage();

    m_stack->addWidget(m_searchPage);     // index 0
    m_stack->addWidget(m_modifyPage);     // index 1
    m_stack->addWidget(m_submitPage);     // index 2

    mainL->addWidget(m_stack);
}

// ─────────────────────────────────────────────────────────────
// Page 0: Search by Team ID
// ─────────────────────────────────────────────────────────────
void ModifyTeamWidget::buildSearchPage()
{
    QWidget *card = new QWidget;
    card->setObjectName("formCard");
    card->setStyleSheet(MODIFY_STYLE);
    card->setMaximumWidth(540);
    card->setMinimumWidth(400);

    QVBoxLayout *cardL = new QVBoxLayout(card);
    cardL->setContentsMargins(40, 36, 40, 36);
    cardL->setSpacing(14);

    QLabel *title = new QLabel("Modify Team");
    title->setObjectName("formTitle");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("background:transparent;");
    cardL->addWidget(title);

    QLabel *sub = new QLabel("Enter the Team ID to load its current data");
    sub->setObjectName("formSub");
    sub->setAlignment(Qt::AlignCenter);
    sub->setWordWrap(true);
    sub->setStyleSheet("background:transparent;");
    cardL->addWidget(sub);
    cardL->addSpacing(10);

    QLabel *lbl = new QLabel("TEAM ID");
    lbl->setObjectName("fieldLabel");
    lbl->setStyleSheet("background:transparent;");
    cardL->addWidget(lbl);

    m_searchIdEdit = new QLineEdit;
    m_searchIdEdit->setPlaceholderText("e.g. TM-0001");
    cardL->addWidget(m_searchIdEdit);

    m_searchError = new QLabel("");
    m_searchError->setObjectName("errorLabel");
    m_searchError->setAlignment(Qt::AlignCenter);
    m_searchError->setStyleSheet("background:transparent;");
    cardL->addWidget(m_searchError);

    m_searchBtn = new QPushButton("Load Team");
    m_searchBtn->setObjectName("submitBtn");
    m_searchBtn->setCursor(Qt::PointingHandCursor);
    connect(m_searchBtn, &QPushButton::clicked, this, &ModifyTeamWidget::onSearch);
    cardL->addWidget(m_searchBtn);

    m_searchPage = makeScrollPage(card);
}

// ─────────────────────────────────────────────────────────────
// Page 1: Edit team fields
// ─────────────────────────────────────────────────────────────
void ModifyTeamWidget::buildModifyPage()
{
    QWidget *card = new QWidget;
    card->setObjectName("formCard");
    card->setStyleSheet(MODIFY_STYLE);
    card->setMaximumWidth(540);
    card->setMinimumWidth(400);

    QVBoxLayout *cardL = new QVBoxLayout(card);
    cardL->setContentsMargins(40, 36, 40, 36);
    cardL->setSpacing(14);

    // Back button row
    QPushButton *backBtn = new QPushButton("← Back to Search");
    backBtn->setObjectName("backBtn");
    backBtn->setCursor(Qt::PointingHandCursor);
    connect(backBtn, &QPushButton::clicked, this, &ModifyTeamWidget::goToSearch);
    cardL->addWidget(backBtn);

    QLabel *title = new QLabel("Edit Team Details");
    title->setObjectName("formTitle");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("background:transparent;");
    cardL->addWidget(title);

    m_teamIdLabel = new QLabel("ID: —");
    m_teamIdLabel->setObjectName("idBadge");
    m_teamIdLabel->setAlignment(Qt::AlignCenter);
    cardL->addWidget(m_teamIdLabel);
    cardL->addSpacing(6);

    auto addField = [&](const QString &label, QLineEdit *&edit, const QString &ph) {
        QLabel *lbl = new QLabel(label);
        lbl->setObjectName("fieldLabel");
        lbl->setStyleSheet("background:transparent;");
        cardL->addWidget(lbl);
        edit = new QLineEdit;
        edit->setPlaceholderText(ph);
        cardL->addWidget(edit);
    };

    addField("TEAM NAME",    m_nameEdit,    "e.g. ByteMasters");
    addField("UNIVERSITY",   m_uniEdit,     "e.g. Cairo University");

    QLabel *membLbl = new QLabel("NUMBER OF MEMBERS");
    membLbl->setObjectName("fieldLabel");
    membLbl->setStyleSheet("background:transparent;");
    cardL->addWidget(membLbl);

    m_membersSpin = new QSpinBox;
    m_membersSpin->setRange(1, 20);
    m_membersSpin->setValue(1);
    m_membersSpin->setStyleSheet(
        "QSpinBox{background:rgba(7,9,18,0.0);color:#e2e8f0;"
        "border:1px solid rgba(255,255,255,0.09);border-radius:10px;"
        "padding:11px 14px;font-size:13px;}"
        "QSpinBox:focus{border:1px solid rgba(99,102,241,0.55);}"
        "QSpinBox::up-button,QSpinBox::down-button{"
        "background:rgba(99,102,241,0.1);border:none;width:20px;}");
    cardL->addWidget(m_membersSpin);

    addField("PROJECT TITLE", m_projectEdit, "Brief project description");

    m_modifyError = new QLabel("");
    m_modifyError->setObjectName("errorLabel");
    m_modifyError->setAlignment(Qt::AlignCenter);
    m_modifyError->setStyleSheet("background:transparent;");
    cardL->addWidget(m_modifyError);

    m_modifyBtn = new QPushButton("Save Changes");
    m_modifyBtn->setObjectName("submitBtn");
    m_modifyBtn->setCursor(Qt::PointingHandCursor);
    connect(m_modifyBtn, &QPushButton::clicked, this, &ModifyTeamWidget::onModifySubmit);
    cardL->addWidget(m_modifyBtn);

    // Divider
    QFrame *div = new QFrame;
    div->setFrameShape(QFrame::HLine);
    div->setStyleSheet("color:#1a2234;background:#1a2234;max-height:1px;margin:4px 0;");
    cardL->addWidget(div);

    m_submitProjBtn = new QPushButton("Submit / Update Project Title Only");
    m_submitProjBtn->setObjectName("secondBtn");
    m_submitProjBtn->setCursor(Qt::PointingHandCursor);
    connect(m_submitProjBtn, &QPushButton::clicked, this, [this]{
        m_stack->setCurrentIndex(2);
    });
    cardL->addWidget(m_submitProjBtn);

    m_modifyPage = makeScrollPage(card);
}

// ─────────────────────────────────────────────────────────────
// Page 2: Submit project title only
// ─────────────────────────────────────────────────────────────
void ModifyTeamWidget::buildSubmitProjectPage()
{
    QWidget *card = new QWidget;
    card->setObjectName("formCard");
    card->setStyleSheet(MODIFY_STYLE);
    card->setMaximumWidth(540);
    card->setMinimumWidth(400);

    QVBoxLayout *cardL = new QVBoxLayout(card);
    cardL->setContentsMargins(40, 36, 40, 36);
    cardL->setSpacing(14);

    QPushButton *backBtn = new QPushButton("← Back to Edit");
    backBtn->setObjectName("backBtn");
    backBtn->setCursor(Qt::PointingHandCursor);
    connect(backBtn, &QPushButton::clicked, this, [this]{
        m_stack->setCurrentIndex(1);
    });
    cardL->addWidget(backBtn);

    QLabel *title = new QLabel("Submit Project");
    title->setObjectName("formTitle");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("background:transparent;");
    cardL->addWidget(title);

    QLabel *sub = new QLabel("Update the project title without changing any other team info");
    sub->setObjectName("formSub");
    sub->setAlignment(Qt::AlignCenter);
    sub->setWordWrap(true);
    sub->setStyleSheet("background:transparent;");
    cardL->addWidget(sub);

    m_submitIdLabel = new QLabel("ID: —");
    m_submitIdLabel->setObjectName("idBadge");
    m_submitIdLabel->setAlignment(Qt::AlignCenter);
    cardL->addWidget(m_submitIdLabel);
    cardL->addSpacing(6);

    QLabel *lbl = new QLabel("NEW PROJECT TITLE");
    lbl->setObjectName("fieldLabel");
    lbl->setStyleSheet("background:transparent;");
    cardL->addWidget(lbl);

    m_newProjectEdit = new QLineEdit;
    m_newProjectEdit->setPlaceholderText("Enter updated project title");
    cardL->addWidget(m_newProjectEdit);

    m_submitError = new QLabel("");
    m_submitError->setObjectName("errorLabel");
    m_submitError->setAlignment(Qt::AlignCenter);
    m_submitError->setStyleSheet("background:transparent;");
    cardL->addWidget(m_submitError);

    m_submitBtn = new QPushButton("Submit Project");
    m_submitBtn->setObjectName("submitBtn");
    m_submitBtn->setCursor(Qt::PointingHandCursor);
    connect(m_submitBtn, &QPushButton::clicked, this, &ModifyTeamWidget::onSubmitProject);
    cardL->addWidget(m_submitBtn);

    m_submitPage = makeScrollPage(card);
}

// ─────────────────────────────────────────────────────────────
void ModifyTeamWidget::refresh()
{
    goToSearch();
}

void ModifyTeamWidget::goToSearch()
{
    m_searchIdEdit->clear();
    m_searchError->clear();
    m_stack->setCurrentIndex(0);
}

// ─────────────────────────────────────────────────────────────
// Slot: Search — load team data into the modify form
// ─────────────────────────────────────────────────────────────
void ModifyTeamWidget::onSearch()
{
    QString id = m_searchIdEdit->text().trimmed();
    if (id.isEmpty()) {
        m_searchError->setText("Please enter a Team ID.");
        return;
    }

    Response resp = isTeamPresentById(id.toStdString());
    if (resp.status_ != Status::STATUS_200_OK) {
        m_searchError->setText("Team not found. Check the ID and try again.");
        return;
    }

    m_currentId = id;
    const Team &t = *(Team*)resp.content_ptr_;

    // Populate modify form
    m_teamIdLabel->setText("ID: " + id);
    m_nameEdit->setText(QString::fromStdString(t.team_name_));
    m_uniEdit->setText(QString::fromStdString(t.university_name_));
    m_membersSpin->setValue(t.number_of_members_);
    m_projectEdit->setText(QString::fromStdString(t.project_title_));
    m_modifyError->clear();

    // Populate submit-project form
    m_submitIdLabel->setText("ID: " + id);
    m_newProjectEdit->setText(QString::fromStdString(t.project_title_));
    m_submitError->clear();

    m_stack->setCurrentIndex(1);
}

// ─────────────────────────────────────────────────────────────
// Slot: Save all changes
// ─────────────────────────────────────────────────────────────
void ModifyTeamWidget::onModifySubmit()
{
    QString name    = m_nameEdit->text().trimmed();
    QString uni     = m_uniEdit->text().trimmed();
    int     members = m_membersSpin->value();
    QString project = m_projectEdit->text().trimmed();

    if (name.isEmpty() || uni.isEmpty() || project.isEmpty()) {
        m_modifyError->setText("Please fill in all fields!");
        return;
    }

    Response resp = modifyTeamById(
        m_currentId.toStdString(),
        name.toStdString(),
        uni.toStdString(),
        static_cast<unsigned short>(members),
        project.toStdString()
    );

    if (resp.status_ == Status::STATUS_200_OK) {
        m_modifyError->clear();
        emit teamModified("Team updated successfully!");
        goToSearch();
    } else {
        m_modifyError->setText("Failed to update team. Please try again.");
    }
}

// ─────────────────────────────────────────────────────────────
// Slot: Submit project title only
// ─────────────────────────────────────────────────────────────
void ModifyTeamWidget::onSubmitProject()
{
    QString newTitle = m_newProjectEdit->text().trimmed();
    if (newTitle.isEmpty()) {
        m_submitError->setText("Please enter a project title.");
        return;
    }

    Response resp = submitProjectByTeamId(
        m_currentId.toStdString(),
        newTitle.toStdString()
    );

    if (resp.status_ == Status::STATUS_200_OK) {
        m_submitError->clear();
        emit teamModified("Project title submitted successfully!");
        goToSearch();
    } else {
        m_submitError->setText("Failed to submit project. Please try again.");
    }
}
