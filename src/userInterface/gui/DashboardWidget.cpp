#include "DashboardWidget.h"
#include "../../dataStore/dataStore.hpp"
#include "../../config/config.hpp"
#include <QGridLayout>
#include <QScrollArea>
#include <algorithm>
#include <vector>
#include "../../projectLogic/compute.hpp"

// ── Style sheet ───────────────────────────────────────────────────────────────
static const QString DASH_STYLE = R"(
QWidget#dashPage { background: #070b18; }

QWidget#statCard {
    border-radius: 16px;
    border: 1px solid rgba(255,255,255,0.08);
}
QWidget#panel {
    background: rgba(13,20,38,0.85);
    border-radius: 16px;
    border: 1px solid rgba(255,255,255,0.08);
}
QLabel#statIcon       { font-size: 22px; background: transparent; }
QLabel#statValue      { font-size: 30px; font-weight: 800; background: transparent; font-family:'Segoe UI',Arial; }
QLabel#statLabel      { font-size: 11px; color: #4a5568; background: transparent; letter-spacing: 1px; font-family:'Segoe UI',Arial; }
QLabel#panelTitle     { font-size: 13px; font-weight: 700; color: #818cf8; background: transparent; letter-spacing: 0.5px; font-family:'Segoe UI',Arial; }
QLabel#teamName       { font-size: 13px; font-weight: 600; color: #f1f5f9; background: transparent; font-family:'Segoe UI',Arial; }
QLabel#teamSub        { font-size: 11px; color: #4a5568; background: transparent; font-family:'Segoe UI',Arial; }
QLabel#scoreLabel     { font-size: 16px; font-weight: 800; background: transparent; font-family:'Segoe UI',Arial; }
QLabel#evalTeam       { font-size: 12px; color: #e2e8f0; font-weight: 500; background: transparent; font-family:'Segoe UI',Arial; }
QLabel#evalJudge      { font-size: 11px; color: #4a5568; background: transparent; font-family:'Segoe UI',Arial; }
QFrame#divider        { color: #1a2234; }
)";

DashboardWidget::DashboardWidget(QWidget *parent) : QWidget(parent)
{
    setObjectName("dashPage");
    setStyleSheet(DASH_STYLE);
    buildUI();
}

void DashboardWidget::buildUI()
{
    QVBoxLayout *mainL = new QVBoxLayout(this);
    mainL->setContentsMargins(28, 28, 28, 28);
    mainL->setSpacing(18);

    // ── Stat cards ────────────────────────────────────────────────────────
    QGridLayout *statsGrid = new QGridLayout;
    statsGrid->setSpacing(14);

    struct StatDef { QString icon; QString label; QString color; QString bg; };
    QList<StatDef> stats = {
                            {"\xF0\x9F\x91\xA5", "TOTAL TEAMS",   "#38bdf8", "rgba(56,189,248,0.07)"},
                            {"\xE2\x9A\x96\xEF\xB8\x8F", "JUDGES", "#a78bfa", "rgba(167,139,250,0.07)"},
                            {"\xF0\x9F\x93\x8B", "EVALUATIONS",   "#34d399", "rgba(52,211,153,0.07)"},
                            {"\xF0\x9F\x8F\x86", "TOP SCORE",     "#fb923c", "rgba(251,146,60,0.07)"},
                            };

    for (int i = 0; i < 4; ++i) {
        QWidget *card = new QWidget;
        card->setObjectName("statCard");
        card->setStyleSheet(QString(
                                "QWidget#statCard{"
                                "border:1px solid rgba(255,255,255,0.08);"
                                "border-radius:16px;"
                                "background:%1;"
                                "}").arg(stats[i].bg));
        card->setMinimumHeight(118);

        QVBoxLayout *l = new QVBoxLayout(card);
        l->setContentsMargins(20, 18, 20, 18);
        l->setSpacing(6);

        // Icon chip
        QHBoxLayout *topRow = new QHBoxLayout;
        QLabel *ic = new QLabel(stats[i].icon);
        ic->setObjectName("statIcon");
        ic->setStyleSheet(QString(
                              "font-size:20px; background:%1; border-radius:9px;"
                              "padding:6px 8px; border:1px solid rgba(255,255,255,0.07);")
                              .arg(stats[i].bg));
        ic->setFixedSize(42, 42);
        ic->setAlignment(Qt::AlignCenter);
        topRow->addWidget(ic);
        topRow->addStretch();
        l->addLayout(topRow);

        m_statValues[i] = new QLabel("0");
        m_statValues[i]->setObjectName("statValue");
        m_statValues[i]->setStyleSheet(QString(
                                           "color:%1;font-size:28px;font-weight:800;background:transparent;"
                                           "font-family:'Segoe UI',Arial;").arg(stats[i].color));

        QLabel *lb = new QLabel(stats[i].label);
        lb->setObjectName("statLabel");
        l->addWidget(m_statValues[i]);
        l->addWidget(lb);
        statsGrid->addWidget(card, 0, i);
    }
    mainL->addLayout(statsGrid);

    // ── Bottom panels ─────────────────────────────────────────────────────
    QHBoxLayout *panelsRow = new QHBoxLayout;
    panelsRow->setSpacing(14);

    // Top Teams
    QWidget *teamsPanel = new QWidget;
    teamsPanel->setObjectName("panel");
    QVBoxLayout *teamsL = new QVBoxLayout(teamsPanel);
    teamsL->setContentsMargins(20, 18, 20, 18);
    teamsL->setSpacing(0);
    QLabel *tTitle = new QLabel("\xF0\x9F\x8F\x86   Top Teams");
    tTitle->setObjectName("panelTitle");
    teamsL->addWidget(tTitle);
    teamsL->addSpacing(14);

    QScrollArea *teamsScroll = new QScrollArea;
    teamsScroll->setWidgetResizable(true);
    teamsScroll->setFrameShape(QFrame::NoFrame);
    teamsScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    teamsScroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    teamsScroll->setStyleSheet("background:transparent;border:none;");
    teamsScroll->viewport()->setStyleSheet("background:transparent;");

    m_topTeamsContent = new QWidget;
    m_topTeamsContent->setStyleSheet("background:transparent;");
    teamsScroll->setWidget(m_topTeamsContent);
    teamsL->addWidget(teamsScroll, 1);
    panelsRow->addWidget(teamsPanel);

    // Recent Evals
    QWidget *evalPanel = new QWidget;
    evalPanel->setObjectName("panel");
    QVBoxLayout *evalL = new QVBoxLayout(evalPanel);
    evalL->setContentsMargins(20, 18, 20, 18);
    evalL->setSpacing(0);
    QLabel *eTitle = new QLabel("\xF0\x9F\x93\x8B   Recent Evaluations");
    eTitle->setObjectName("panelTitle");
    evalL->addWidget(eTitle);
    evalL->addSpacing(14);

    QScrollArea *evalsScroll = new QScrollArea;
    evalsScroll->setWidgetResizable(true);
    evalsScroll->setFrameShape(QFrame::NoFrame);
    evalsScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    evalsScroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    evalsScroll->setStyleSheet("background:transparent;border:none;");
    evalsScroll->viewport()->setStyleSheet("background:transparent;");

    m_recentEvalsContent = new QWidget;
    m_recentEvalsContent->setStyleSheet("background:transparent;");
    evalsScroll->setWidget(m_recentEvalsContent);
    evalL->addWidget(evalsScroll, 1);
    panelsRow->addWidget(evalPanel);

    mainL->addLayout(panelsRow, 1);
    refresh();
}

void DashboardWidget::refresh()
{
    rankAllTeams();
    sortTeams();

    int nTeams  = getNumberOfTeams();
    int nJudges = getNumberOfJudges();
    int nEvals  = getNumberOfEvaluations();

    float maxScore = 0;
    for (int i = 0; i < nTeams; ++i)
        if (getTeamAt(i).final_score_ > maxScore)
            maxScore = getTeamAt(i).final_score_;

    m_statValues[0]->setText(QString::number(nTeams));
    m_statValues[1]->setText(QString::number(nJudges));
    m_statValues[2]->setText(QString::number(nEvals));
    m_statValues[3]->setText(maxScore > 0 ? QString::number(maxScore, 'f', 1) : "N/A");

    // ── Top Teams ─────────────────────────────────────────────────────────
    // Properly clear old layout and all its children
    if (QLayout *oldLayout = m_topTeamsContent->layout()) {
        QLayoutItem *item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            if (item->widget()) {
                item->widget()->deleteLater();
            }
            delete item;
        }
        delete oldLayout;
    }
    QVBoxLayout *tl = new QVBoxLayout(m_topTeamsContent);
    tl->setContentsMargins(0, 0, 0, 0);
    tl->setSpacing(0);

    std::vector<int> idx;
    for (int i = 0; i < nTeams; ++i)
        if (getTeamAt(i).final_score_ >= 0) idx.push_back(i);
    std::sort(idx.begin(), idx.end(), [](int a, int b){
        return getTeamAt(a).final_score_ > getTeamAt(b).final_score_;
    });

    // Medals only for top 3
    QStringList medals      = {"\xF0\x9F\xA5\x87", "\xF0\x9F\xA5\x88", "\xF0\x9F\xA5\x89"};
    QStringList medalColors = {"#fb923c", "#94a3b8", "#a78bfa"};

    int show = (int)idx.size(); // show ALL teams

    if (show == 0) {
        QLabel *empty = new QLabel("No results yet");
        empty->setStyleSheet("color:#334155;font-size:13px;background:transparent;");
        empty->setAlignment(Qt::AlignCenter);
        tl->addWidget(empty);
    }
    for (int i = 0; i < show; ++i) {
        const Team &t = getTeamAt(idx[i]);
        QWidget *row = new QWidget;
        row->setStyleSheet("background:transparent;");
        QHBoxLayout *rl = new QHBoxLayout(row);
        rl->setContentsMargins(0, 10, 0, 10);

        // Medal badge only for top 3; plain rank number for the rest
        QLabel *medal = new QLabel;
        medal->setFixedWidth(26);
        if (i < 3) {
            medal->setText(medals[i]);
            medal->setStyleSheet("font-size:16px;background:transparent;");
        } else {
            medal->setText(QString::number(i + 1));
            medal->setStyleSheet("font-size:12px;color:#4a5568;background:transparent;font-family:'Segoe UI',Arial;");
            medal->setAlignment(Qt::AlignCenter);
        }

        QWidget *info = new QWidget;
        info->setStyleSheet("background:transparent;");
        QVBoxLayout *il = new QVBoxLayout(info);
        il->setContentsMargins(0, 0, 0, 0);
        il->setSpacing(1);
        QLabel *nm = new QLabel(QString::fromStdString(t.team_name_));
        nm->setObjectName("teamName");
        QLabel *pr = new QLabel(QString::fromStdString(t.project_title_));
        pr->setObjectName("teamSub");
        il->addWidget(nm);
        il->addWidget(pr);

        // Score color: use medal color for top 3, neutral for the rest
        QString scoreColor = (i < 3) ? medalColors[i] : "#64748b";
        QLabel *sc = new QLabel(QString::number(t.final_score_, 'f', 1));
        sc->setStyleSheet(QString("color:%1;font-size:16px;font-weight:800;background:transparent;")
                              .arg(scoreColor));
        rl->addWidget(medal);
        rl->addWidget(info, 1);
        rl->addWidget(sc);
        tl->addWidget(row);

        if (i < show - 1) {
            QFrame *div = new QFrame;
            div->setFrameShape(QFrame::HLine);
            div->setStyleSheet("color:#1a2234;background:#1a2234;max-height:1px;");
            tl->addWidget(div);
        }
    }
    tl->addStretch();

    // ── Recent Evaluations ────────────────────────────────────────────────
    if (QLayout *oldLayout = m_recentEvalsContent->layout()) {
        QLayoutItem *item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            if (item->widget()) {
                item->widget()->deleteLater();
            }
            delete item;
        }
        delete oldLayout;
    }
    QVBoxLayout *el = new QVBoxLayout(m_recentEvalsContent);
    el->setContentsMargins(0, 0, 0, 0);
    el->setSpacing(0);

    // Show last 8 evaluations (or fewer if not enough)
    int evalsToShow = std::min(nEvals, 8);
    int start = nEvals - evalsToShow;

    if (nEvals == 0) {
        QLabel *empty = new QLabel("No evaluations yet");
        empty->setStyleSheet("color:#334155;font-size:13px;background:transparent;");
        empty->setAlignment(Qt::AlignCenter);
        el->addWidget(empty);
    }
    for (int i = nEvals - 1; i >= start; --i) {
        const Evaluation &ev = getEvalAt(i);
        QString teamName  = QString::fromStdString(ev.team_id_);
        QString judgeName = QString::fromStdString(ev.judge_id_);
        for (int j = 0; j < getNumberOfTeams(); ++j)
            if (getTeamAt(j).team_id_ == ev.team_id_)
                teamName = QString::fromStdString(getTeamAt(j).team_name_);
        for (int j = 0; j < getNumberOfJudges(); ++j)
            if (getJudgeAt(j).judge_id_ == ev.judge_id_)
                judgeName = QString::fromStdString(getJudgeAt(j).name_);

        QWidget *row = new QWidget;
        row->setStyleSheet("background:transparent;");
        QHBoxLayout *rl = new QHBoxLayout(row);
        rl->setContentsMargins(0, 10, 0, 10);

        QWidget *info = new QWidget;
        info->setStyleSheet("background:transparent;");
        QVBoxLayout *il = new QVBoxLayout(info);
        il->setContentsMargins(0, 0, 0, 0);
        il->setSpacing(1);
        QLabel *tn = new QLabel(teamName);       tn->setObjectName("evalTeam");
        QLabel *jn = new QLabel("by " + judgeName); jn->setObjectName("evalJudge");
        il->addWidget(tn);
        il->addWidget(jn);

        int total = ev.total_score_;
        QString color   = total >= 25 ? "#34d399" : total >= 20 ? "#fb923c" : "#f87171";
        QString badgeBg = total >= 25 ? "rgba(52,211,153,0.12)"
                          : total >= 20 ? "rgba(251,146,60,0.12)"
                                        :               "rgba(248,113,113,0.12)";
        QLabel *badge = new QLabel(QString("%1/30").arg(total));
        badge->setStyleSheet(QString(
                                 "background:%1;color:%2;border-radius:10px;"
                                 "padding:3px 10px;font-size:12px;font-weight:700;"
                                 "border:1px solid %3;font-family:'Segoe UI',Arial;")
                                 .arg(badgeBg).arg(color).arg(color + "44"));

        rl->addWidget(info, 1);
        rl->addWidget(badge);
        el->addWidget(row);
        if (i > start) {
            QFrame *div = new QFrame;
            div->setFrameShape(QFrame::HLine);
            div->setStyleSheet("color:#1a2234;background:#1a2234;max-height:1px;");
            el->addWidget(div);
        }
    }
    el->addStretch();
}