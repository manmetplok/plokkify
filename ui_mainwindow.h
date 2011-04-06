/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Apr 6 21:24:48 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QStackedWidget>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_10;
    QStackedWidget *swWidgets;
    QWidget *pgLogin;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *leUsername;
    QLineEdit *lePassword;
    QCheckBox *cbRemember;
    QPushButton *pbLogin;
    QSpacerItem *verticalSpacer;
    QLabel *lbLoginError;
    QSpacerItem *horizontalSpacer;
    QWidget *pgInside;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_7;
    QLabel *lblTopAlbum1;
    QLabel *lblTopAlbum2;
    QLabel *lblTopAlbum3;
    QLabel *lblTopAlbum4;
    QLabel *lblTopAlbum5;
    QLabel *lblTopAlbum6;
    QLabel *lblTopAlbum7;
    QLabel *lblTopAlbum8;
    QVBoxLayout *verticalLayout_4;
    QTreeWidget *twRootlist;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *leSearch;
    QComboBox *cbSearch;
    QPushButton *pbSearch;
    QWidget *pgPlaylist;
    QVBoxLayout *verticalLayout_5;
    QTreeWidget *twPlaylist;
    QWidget *pgSearchSong;
    QVBoxLayout *verticalLayout_6;
    QTreeWidget *twSearchSong;
    QWidget *wPlayercontrols;
    QHBoxLayout *horizontalLayout;
    QPushButton *pbPrevious;
    QPushButton *pbPlaypause;
    QPushButton *pbNext;
    QSlider *hsTimeline;
    QPushButton *pbShuffle;
    QPushButton *pbBack;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 404);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_10 = new QVBoxLayout(centralWidget);
        verticalLayout_10->setSpacing(3);
        verticalLayout_10->setContentsMargins(3, 3, 3, 3);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        swWidgets = new QStackedWidget(centralWidget);
        swWidgets->setObjectName(QString::fromUtf8("swWidgets"));
        pgLogin = new QWidget();
        pgLogin->setObjectName(QString::fromUtf8("pgLogin"));
        horizontalLayout_3 = new QHBoxLayout(pgLogin);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(143, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(pgLogin);
        label->setObjectName(QString::fromUtf8("label"));
        label->setEnabled(true);
        label->setMinimumSize(QSize(300, 300));
        label->setText(QString::fromUtf8(""));
        label->setPixmap(QPixmap(QString::fromUtf8(":/res/qtify.png")));

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(6, -1, -1, -1);
        leUsername = new QLineEdit(pgLogin);
        leUsername->setObjectName(QString::fromUtf8("leUsername"));

        verticalLayout_2->addWidget(leUsername);

        lePassword = new QLineEdit(pgLogin);
        lePassword->setObjectName(QString::fromUtf8("lePassword"));
        lePassword->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText);
        lePassword->setEchoMode(QLineEdit::Password);

        verticalLayout_2->addWidget(lePassword);

        cbRemember = new QCheckBox(pgLogin);
        cbRemember->setObjectName(QString::fromUtf8("cbRemember"));

        verticalLayout_2->addWidget(cbRemember);

        pbLogin = new QPushButton(pgLogin);
        pbLogin->setObjectName(QString::fromUtf8("pbLogin"));

        verticalLayout_2->addWidget(pbLogin);


        horizontalLayout_2->addLayout(verticalLayout_2);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        lbLoginError = new QLabel(pgLogin);
        lbLoginError->setObjectName(QString::fromUtf8("lbLoginError"));
        lbLoginError->setText(QString::fromUtf8(""));
        lbLoginError->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lbLoginError);


        horizontalLayout_3->addLayout(verticalLayout);

        horizontalSpacer = new QSpacerItem(134, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        swWidgets->addWidget(pgLogin);
        pgInside = new QWidget();
        pgInside->setObjectName(QString::fromUtf8("pgInside"));
        horizontalLayout_4 = new QHBoxLayout(pgInside);
        horizontalLayout_4->setSpacing(3);
        horizontalLayout_4->setContentsMargins(3, 3, 3, 3);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        scrollArea = new QScrollArea(pgInside);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setMaximumSize(QSize(120, 16777215));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setFrameShadow(QFrame::Plain);
        scrollArea->setLineWidth(0);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 120, 841));
        horizontalLayout_7 = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(3);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        lblTopAlbum1 = new QLabel(scrollAreaWidgetContents);
        lblTopAlbum1->setObjectName(QString::fromUtf8("lblTopAlbum1"));
        lblTopAlbum1->setMinimumSize(QSize(100, 100));
        lblTopAlbum1->setMaximumSize(QSize(100, 100));
        lblTopAlbum1->setText(QString::fromUtf8(""));

        verticalLayout_7->addWidget(lblTopAlbum1);

        lblTopAlbum2 = new QLabel(scrollAreaWidgetContents);
        lblTopAlbum2->setObjectName(QString::fromUtf8("lblTopAlbum2"));
        lblTopAlbum2->setMinimumSize(QSize(100, 100));
        lblTopAlbum2->setMaximumSize(QSize(100, 100));
        lblTopAlbum2->setText(QString::fromUtf8(""));

        verticalLayout_7->addWidget(lblTopAlbum2);

        lblTopAlbum3 = new QLabel(scrollAreaWidgetContents);
        lblTopAlbum3->setObjectName(QString::fromUtf8("lblTopAlbum3"));
        lblTopAlbum3->setMinimumSize(QSize(100, 100));
        lblTopAlbum3->setMaximumSize(QSize(100, 100));
        lblTopAlbum3->setText(QString::fromUtf8(""));

        verticalLayout_7->addWidget(lblTopAlbum3);

        lblTopAlbum4 = new QLabel(scrollAreaWidgetContents);
        lblTopAlbum4->setObjectName(QString::fromUtf8("lblTopAlbum4"));
        lblTopAlbum4->setMinimumSize(QSize(100, 100));
        lblTopAlbum4->setMaximumSize(QSize(100, 100));
        lblTopAlbum4->setText(QString::fromUtf8(""));

        verticalLayout_7->addWidget(lblTopAlbum4);

        lblTopAlbum5 = new QLabel(scrollAreaWidgetContents);
        lblTopAlbum5->setObjectName(QString::fromUtf8("lblTopAlbum5"));
        lblTopAlbum5->setMinimumSize(QSize(100, 100));
        lblTopAlbum5->setMaximumSize(QSize(100, 100));
        lblTopAlbum5->setText(QString::fromUtf8(""));

        verticalLayout_7->addWidget(lblTopAlbum5);

        lblTopAlbum6 = new QLabel(scrollAreaWidgetContents);
        lblTopAlbum6->setObjectName(QString::fromUtf8("lblTopAlbum6"));
        lblTopAlbum6->setMinimumSize(QSize(100, 100));
        lblTopAlbum6->setMaximumSize(QSize(100, 100));
        lblTopAlbum6->setText(QString::fromUtf8(""));

        verticalLayout_7->addWidget(lblTopAlbum6);

        lblTopAlbum7 = new QLabel(scrollAreaWidgetContents);
        lblTopAlbum7->setObjectName(QString::fromUtf8("lblTopAlbum7"));
        lblTopAlbum7->setMinimumSize(QSize(100, 100));
        lblTopAlbum7->setMaximumSize(QSize(100, 100));
        lblTopAlbum7->setText(QString::fromUtf8(""));

        verticalLayout_7->addWidget(lblTopAlbum7);

        lblTopAlbum8 = new QLabel(scrollAreaWidgetContents);
        lblTopAlbum8->setObjectName(QString::fromUtf8("lblTopAlbum8"));
        lblTopAlbum8->setMinimumSize(QSize(100, 100));
        lblTopAlbum8->setMaximumSize(QSize(100, 100));
        lblTopAlbum8->setText(QString::fromUtf8(""));

        verticalLayout_7->addWidget(lblTopAlbum8);


        horizontalLayout_7->addLayout(verticalLayout_7);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_3->addWidget(scrollArea);


        horizontalLayout_4->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        twRootlist = new QTreeWidget(pgInside);
        twRootlist->setObjectName(QString::fromUtf8("twRootlist"));
        twRootlist->setAlternatingRowColors(true);
        twRootlist->setRootIsDecorated(false);
        twRootlist->setAllColumnsShowFocus(true);
        twRootlist->setExpandsOnDoubleClick(false);
        twRootlist->header()->setVisible(false);

        verticalLayout_4->addWidget(twRootlist);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, 0, -1, -1);
        leSearch = new QLineEdit(pgInside);
        leSearch->setObjectName(QString::fromUtf8("leSearch"));

        horizontalLayout_5->addWidget(leSearch);

        cbSearch = new QComboBox(pgInside);
        cbSearch->setObjectName(QString::fromUtf8("cbSearch"));

        horizontalLayout_5->addWidget(cbSearch);

        pbSearch = new QPushButton(pgInside);
        pbSearch->setObjectName(QString::fromUtf8("pbSearch"));

        horizontalLayout_5->addWidget(pbSearch);


        verticalLayout_4->addLayout(horizontalLayout_5);


        horizontalLayout_4->addLayout(verticalLayout_4);

        swWidgets->addWidget(pgInside);
        pgPlaylist = new QWidget();
        pgPlaylist->setObjectName(QString::fromUtf8("pgPlaylist"));
        verticalLayout_5 = new QVBoxLayout(pgPlaylist);
        verticalLayout_5->setSpacing(3);
        verticalLayout_5->setContentsMargins(3, 3, 3, 3);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        twPlaylist = new QTreeWidget(pgPlaylist);
        twPlaylist->setObjectName(QString::fromUtf8("twPlaylist"));

        verticalLayout_5->addWidget(twPlaylist);

        swWidgets->addWidget(pgPlaylist);
        pgSearchSong = new QWidget();
        pgSearchSong->setObjectName(QString::fromUtf8("pgSearchSong"));
        verticalLayout_6 = new QVBoxLayout(pgSearchSong);
        verticalLayout_6->setSpacing(3);
        verticalLayout_6->setContentsMargins(3, 3, 3, 3);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        twSearchSong = new QTreeWidget(pgSearchSong);
        twSearchSong->setObjectName(QString::fromUtf8("twSearchSong"));

        verticalLayout_6->addWidget(twSearchSong);

        swWidgets->addWidget(pgSearchSong);

        verticalLayout_10->addWidget(swWidgets);

        wPlayercontrols = new QWidget(centralWidget);
        wPlayercontrols->setObjectName(QString::fromUtf8("wPlayercontrols"));
        horizontalLayout = new QHBoxLayout(wPlayercontrols);
        horizontalLayout->setSpacing(3);
        horizontalLayout->setContentsMargins(3, 3, 3, 3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pbPrevious = new QPushButton(wPlayercontrols);
        pbPrevious->setObjectName(QString::fromUtf8("pbPrevious"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/prev.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbPrevious->setIcon(icon);

        horizontalLayout->addWidget(pbPrevious);

        pbPlaypause = new QPushButton(wPlayercontrols);
        pbPlaypause->setObjectName(QString::fromUtf8("pbPlaypause"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/res/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbPlaypause->setIcon(icon1);

        horizontalLayout->addWidget(pbPlaypause);

        pbNext = new QPushButton(wPlayercontrols);
        pbNext->setObjectName(QString::fromUtf8("pbNext"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/res/next.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbNext->setIcon(icon2);

        horizontalLayout->addWidget(pbNext);

        hsTimeline = new QSlider(wPlayercontrols);
        hsTimeline->setObjectName(QString::fromUtf8("hsTimeline"));
        hsTimeline->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(hsTimeline);

        pbShuffle = new QPushButton(wPlayercontrols);
        pbShuffle->setObjectName(QString::fromUtf8("pbShuffle"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/res/shuffleoff.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbShuffle->setIcon(icon3);

        horizontalLayout->addWidget(pbShuffle);

        pbBack = new QPushButton(wPlayercontrols);
        pbBack->setObjectName(QString::fromUtf8("pbBack"));

        horizontalLayout->addWidget(pbBack);


        verticalLayout_10->addWidget(wPlayercontrols);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        swWidgets->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        cbRemember->setText(QApplication::translate("MainWindow", "Remember", 0, QApplication::UnicodeUTF8));
        pbLogin->setText(QApplication::translate("MainWindow", "Log in", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = twRootlist->headerItem();
        ___qtreewidgetitem->setText(2, QApplication::translate("MainWindow", "Rename", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(1, QApplication::translate("MainWindow", "Name", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "#", 0, QApplication::UnicodeUTF8));
        cbSearch->clear();
        cbSearch->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Song", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Artist", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Album", 0, QApplication::UnicodeUTF8)
        );
        pbSearch->setText(QApplication::translate("MainWindow", "Search", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem1 = twPlaylist->headerItem();
        ___qtreewidgetitem1->setText(5, QApplication::translate("MainWindow", "Popularity", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem1->setText(4, QApplication::translate("MainWindow", "Duration", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem1->setText(3, QApplication::translate("MainWindow", "Album", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem1->setText(2, QApplication::translate("MainWindow", "Artist", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem1->setText(1, QApplication::translate("MainWindow", "Track", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem1->setText(0, QApplication::translate("MainWindow", "#", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem2 = twSearchSong->headerItem();
        ___qtreewidgetitem2->setText(5, QApplication::translate("MainWindow", "Popularity", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem2->setText(4, QApplication::translate("MainWindow", "Duration", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem2->setText(3, QApplication::translate("MainWindow", "Album", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem2->setText(2, QApplication::translate("MainWindow", "Artist", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem2->setText(1, QApplication::translate("MainWindow", "Track", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem2->setText(0, QApplication::translate("MainWindow", "#", 0, QApplication::UnicodeUTF8));
        pbPrevious->setText(QString());
        pbPlaypause->setText(QString());
        pbNext->setText(QString());
        pbShuffle->setText(QString());
        pbBack->setText(QApplication::translate("MainWindow", "Home", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
