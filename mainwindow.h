/* ----------------------------------------------------------------------------------------

Copyright 2010 Robin Nilsson <robinnilsson@gmail.com>. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are
permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice, this list of
    conditions and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright notice, this list
    of conditions and the following disclaimer in the documentation and/or other materials
    provided with the distribution.

THIS SOFTWARE IS PROVIDED BY Robin Nilsson ``AS IS'' AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL Robin Nilsson OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those of the
authors and should not be interpreted as representing official policies, either expressed
or implied, of Robin Nilsson.

------------------------------------------------------------------------------------------*/


#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QTreeWidgetItem>

#include "spwrap.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void login (void);
protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    SPWrap *sw;

public slots:
    void on_pbLogin_clicked();
    void on_pushButton_clicked();

    void on_RootlistLoaded(sp_playlistcontainer *pc,void *userdata);
    void on_LoginFailed(sp_session *s,sp_error e);
    void on_LoginSucceeded(sp_session *s);
    void on_PlaylistRenamed(sp_playlist *pl, void *userdata);
    void on_PlaylistAdded(sp_playlistcontainer *s, sp_playlist *p, int n, void *u);
    void on_ToplistbrowseLoaded(sp_toplistbrowse *tb, void *userdata);

    void on_ImageLoaded(sp_image *image, void* userdata);

    void on_SearchComplete(sp_search *s,void *userdata);

    void on_ShuffleStateChanged(bool s);
    void on_PlayStateChanged(bool s);

private slots:
    void on_twSearchSong_itemClicked(QTreeWidgetItem* item, int column);
    void on_pbBack_clicked();
    void on_pbPlaypause_clicked();
    void on_pbNext_clicked();
    void on_pbPrevious_clicked();
    void on_cbRemember_clicked(bool checked);
    void on_cbRemember_clicked();
    void on_pbShuffle_clicked();
    void on_pbPrec_clicked();
    void on_pbNextSong_clicked();
    void on_pushButton_2_clicked();
    void on_pbSearch_clicked();
    void on_twPlaylist_itemClicked(QTreeWidgetItem* item, int column);
    void on_twRootlist_itemClicked(QTreeWidgetItem* item, int column);

};

#endif // MAINWINDOW_H
