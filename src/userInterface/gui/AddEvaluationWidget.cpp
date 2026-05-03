#include "AddEvaluationWidget.h"
#include "../../projectLogic/crud.hpp"
#include "../../dataStore/dataStore.hpp"
#include "../../config/config.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>

static const QString EVAL_STYLE = R"(
QWidget#evalCard {
    background: rgba(13,20,38,0.92);
    border-radius: 20px;
    border: 1px solid rgba(255,255,255,0.09);
}
QWidget#lockedCard {
    background: rgba(13,20,38,0.92);
    border-radius: 20px;
    border: 1px solid rgba(248,113,113,0.22);
}
QLabel#formTitle  { color:#f1f5f9; font-size:20px; font-weight:700; background:transparent; font-family:'Segoe UI',Arial; }
QLabel#fieldLabel { color:#818cf8; font-size:11px; font-weight:700; letter-spacing:1px; background:transparent; font-family:'Segoe UI',Arial; }
QLabel#lockTitle  { color:#f87171; font-size:18px; font-weight:700; background:transparent; font-family:'Segoe UI',Arial; }
QLabel#lockSub    { color:#4a5568; font-size:13px; background:transparent; font-family:'Segoe UI',Arial; }
QLabel#errorLabel { color:#f87171; font-size:12px; background:transparent; font-family:'Segoe UI',Arial; }
QLabel#scoreVal   { color:#818cf8; font-size:14px; font-weight:700; background:transparent; font-family:'Segoe UI',Arial; }
QLabel#totalVal   { color:#818cf8; font-size:28px; font-weight:900; background:transparent; font-family:'Segoe UI',Arial; }
QComboBox {
    background: rgba(7,9,18,0.85);
    color: #e2e8f0;
    border: 1px solid rgba(255,255,255,0.09);
    border-radius: 10px;
    padding: 9px 14px;
    font-size: 13px;
    font-family: 'Segoe UI', Arial;
}
QComboBox:focus { border: 1px solid rgba(99,102,241,0.55); }
QComboBox::drop-down { border: none; width: 20px; }
QComboBox QAbstractItemView {
    background: #0d1428;
    color: #e2e8f0;
    border: 1px solid rgba(99,102,241,0.22);
    selection-background-color: rgba(99,102,241,0.18);
}
QSlider::groove:horizontal {
    height: 4px;
    background: #1a2234;
    border-radius: 2px;
}
QSlider::handle:horizontal {
    background: #818cf8;
    width: 16px;
    height: 16px;
    border-radius: 8px;
    margin: -6px 0;
    border: 2px solid rgba(99,102,241,0.45);
}
QSlider::sub-page:horizontal {
    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
        stop:0 #6366f1, stop:1 #4f46e5);
    border-radius: 2px;
}
QPushButton#submitEvalBtn {
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
QPushButton#submitEvalBtn:hover {
    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
        stop:0 #818cf8, stop:1 #6366f1);
}
)";

AddEvaluationWidget::AddEvaluationWidget(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("background:#070b18;");
    QVBoxLayout *outerL = new QVBoxLayout(this);
    outerL->setContentsMargins(0, 0, 0, 0);

    QScrollArea *scroll = new QScrollArea;
    scroll->setWidgetResizable(true);
    scroll->setStyleSheet("QScrollArea{border:none;background:#070b18;}");

    QWidget *inner = new QWidget;
    inner->setStyleSheet("background:#070b18;");
    QVBoxLayout *innerL = new QVBoxLayout(inner);
    innerL->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    innerL->setContentsMargins(24, 24, 24, 24);

    m_lockedWidget = new QWidget; buildLockedUI();
    m_formWidget   = new QWidget; buildFormUI();

    innerL->addWidget(m_lockedWidget, 0, Qt::AlignHCenter);
    innerL->addWidget(m_formWidget,   0, Qt::AlignHCenter);

    scroll->setWidget(inner);
    outerL->addWidget(scroll);
    setAdminMode(false);
}

void AddEvaluationWidget::buildLockedUI()
{
    m_lockedWidget->setObjectName("lockedCard");
    m_lockedWidget->setStyleSheet(EVAL_STYLE);
    m_lockedWidget->setMaximumWidth(480);
    m_lockedWidget->setMinimumWidth(380);

    QVBoxLayout *l = new QVBoxLayout(m_lockedWidget);
    l->setContentsMargins(40, 44, 40, 44);
    l->setSpacing(12);
    l->setAlignment(Qt::AlignCenter);

    QLabel *ic = new QLabel("\xF0\x9F\x94\x92");
    ic->setAlignment(Qt::AlignCenter);
    ic->setStyleSheet(
        "font-size:40px;background:rgba(248,113,113,0.08);border-radius:36px;"
        "border:1px solid rgba(248,113,113,0.22);padding:8px;");
    ic->setFixedSize(72, 72);
    QHBoxLayout *icRow = new QHBoxLayout;
    icRow->setAlignment(Qt::AlignCenter);
    icRow->addWidget(ic);
    l->addLayout(icRow);

    QLabel *title = new QLabel("Admin Access Required");
    title->setObjectName("lockTitle");
    title->setAlignment(Qt::AlignCenter);
    QLabel *sub = new QLabel("You must be signed in as an admin to add evaluations");
    sub->setObjectName("lockSub");
    sub->setAlignment(Qt::AlignCenter);
    sub->setWordWrap(true);
    l->addWidget(title);
    l->addSpacing(4);
    l->addWidget(sub);
}

void AddEvaluationWidget::buildFormUI()
{
    m_formWidget->setObjectName("evalCard");
    m_formWidget->setStyleSheet(EVAL_STYLE);
    m_formWidget->setMaximumWidth(540);
    m_formWidget->setMinimumWidth(420);

    QVBoxLayout *cardL = new QVBoxLayout(m_formWidget);
    cardL->setContentsMargins(40, 36, 40, 36);
    cardL->setSpacing(14);


    QLabel *title = new QLabel("Add Evaluation");
    title->setObjectName("formTitle");
    title->setAlignment(Qt::AlignCenter);
    cardL->addWidget(title);
    cardL->addSpacing(6);

    QLabel *teamLbl = new QLabel("TEAM");
    teamLbl->setObjectName("fieldLabel");
    cardL->addWidget(teamLbl);
    m_teamCombo = new QComboBox;
    cardL->addWidget(m_teamCombo);

    QLabel *judgeLbl = new QLabel("JUDGE");
    judgeLbl->setObjectName("fieldLabel");
    cardL->addWidget(judgeLbl);
    m_judgeCombo = new QComboBox;
    cardL->addWidget(m_judgeCombo);

    cardL->addSpacing(4);

    auto addSlider = [&](const QString &label, QSlider *&slider, QLabel *&valLbl) {
        QHBoxLayout *hl = new QHBoxLayout;
        QLabel *lbl = new QLabel(label);
        lbl->setObjectName("fieldLabel");
        valLbl = new QLabel("5 / 10");
        valLbl->setObjectName("scoreVal");
        hl->addWidget(lbl, 1);
        hl->addWidget(valLbl);
        cardL->addLayout(hl);
        slider = new QSlider(Qt::Horizontal);
        slider->setStyleSheet("background:transparent;");
        slider->setRange(0, 10);
        slider->setValue(5);
        slider->setTickInterval(1);
        connect(slider, &QSlider::valueChanged, this, &AddEvaluationWidget::updateTotal);
        connect(slider, &QSlider::valueChanged, this, [valLbl](int v){
            valLbl->setText(QString("%1 / 10").arg(v));
        });
        cardL->addWidget(slider);
        cardL->addSpacing(4);
    };

    addSlider("INNOVATION SCORE", m_innovSlider, m_innovVal);
    addSlider("TECHNICAL SCORE",       m_techSlider,  m_techVal);
    addSlider("PRESENTATION SCORE",    m_presSlider,  m_presVal);

    // Total box
    QWidget *totalBox = new QWidget;
    totalBox->setStyleSheet(
        "background:transparent;border-radius:10px;"
        "border:1px solid rgba(99,102,241,0.22);");
    QHBoxLayout *tl = new QHBoxLayout(totalBox);
    tl->setContentsMargins(18, 12, 18, 12);
    QLabel *totLbl = new QLabel("Total Score:");
    totLbl->setStyleSheet("color:#4a5568;font-size:13px;background:transparent;font-family:'Segoe UI',Arial;border:none;");
    m_totalLabel = new QLabel("15 / 30");
    m_totalLabel->setStyleSheet("border:none;background:transparent;");
    m_totalLabel->setObjectName("totalVal");
    tl->addWidget(totLbl);
    tl->addStretch();
    tl->addWidget(m_totalLabel);
    cardL->addWidget(totalBox);

    m_errorLabel = new QLabel("");
    m_errorLabel->setObjectName("errorLabel");
    m_errorLabel->setAlignment(Qt::AlignCenter);
    cardL->addWidget(m_errorLabel);

    m_submitBtn = new QPushButton("Save Evaluation");
    m_submitBtn->setObjectName("submitEvalBtn");
    m_submitBtn->setCursor(Qt::PointingHandCursor);
    connect(m_submitBtn, &QPushButton::clicked, this, &AddEvaluationWidget::onSubmit);
    cardL->addWidget(m_submitBtn);
}

void AddEvaluationWidget::refresh()
{
    if (!m_teamCombo || !m_judgeCombo) return;
    m_teamCombo->clear();
    m_judgeCombo->clear();
    m_teamCombo->addItem("-- Select Team --", "");
    for (int i = 0; i < getNumberOfTeams(); ++i) {
        const Team &t = getTeamAt(i);
        m_teamCombo->addItem(
            QString::fromStdString(t.team_name_) + " (" + QString::fromStdString(t.team_id_) + ")",
            QString::fromStdString(t.team_id_));
    }
    m_teamCombo->setStyleSheet("background:transparent");
    m_judgeCombo->addItem("-- Select Judge --", "");
    for (int i = 0; i < getNumberOfJudges(); ++i) {
        const Judge &j = getJudgeAt(i);
        m_judgeCombo->addItem(
            QString::fromStdString(j.name_) + " — " + QString::fromStdString(j.specialty_),
            QString::fromStdString(j.judge_id_));
    }
    m_judgeCombo->setStyleSheet("background:transparent");
}

void AddEvaluationWidget::setAdminMode(bool isAdmin)
{
    m_isAdmin = isAdmin;
    m_lockedWidget->setVisible(!isAdmin);
    m_formWidget->setVisible(isAdmin);
    if (isAdmin) refresh();
}

void AddEvaluationWidget::updateTotal()
{
    if (!m_innovSlider) return;
    int total = m_innovSlider->value() + m_techSlider->value() + m_presSlider->value();
    m_totalLabel->setText(QString("%1 / 30").arg(total));
    QString color = total >= 25 ? "#34d399" : total >= 20 ? "#fb923c" : "#f87171";
    m_totalLabel->setStyleSheet(
        QString("color:%1;font-size:28px;font-weight:900;background:transparent;"
                "font-family:'Segoe UI',Arial;").arg(color));
}

void AddEvaluationWidget::onSubmit()
{
    QString teamId  = m_teamCombo->currentData().toString();
    QString judgeId = m_judgeCombo->currentData().toString();
    if (teamId.isEmpty() || judgeId.isEmpty()) {
        m_errorLabel->setText("Please select a team and a judge");
        return;
    }
    // Check if this judge already evaluated this team
    for (int i = 0; i < getNumberOfEvaluations(); ++i) {
        const Evaluation &ev = getEvalAt(i);
        if (ev.team_id_ == teamId.toStdString() && ev.judge_id_ == judgeId.toStdString()) {
            m_errorLabel->setText("This judge already evaluated this team!");
            return;
        }
    }
    AddEvaluation(
        teamId.toStdString(),
        judgeId.toStdString(),
        static_cast<unsigned short>(m_innovSlider->value()),
        static_cast<unsigned short>(m_techSlider->value()),
        static_cast<unsigned short>(m_presSlider->value())
        );
    m_innovSlider->setValue(5);
    m_techSlider->setValue(5);
    m_presSlider->setValue(5);
    m_teamCombo->setCurrentIndex(0);
    m_judgeCombo->setCurrentIndex(0);
    m_errorLabel->clear();
    emit evalAdded("Evaluation saved successfully!");
}