#include <QDebug>
#include <cstdio>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "spcallback.h"
#include "sptoplist.h"
#include "spimage.h"
#include "mnenc.h"

extern SPCallback spc;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sw = new SPWrap();
    if(!sw->Initialize())
        qDebug()<<"Initialization failed";

    this->connect(&spc,SIGNAL(on_LoginFailed(sp_session*,sp_error)),this,SLOT(on_LoginFailed(sp_session*,sp_error)));
    this->connect(&spc,SIGNAL(on_LoginSucceeded(sp_session*)),this,SLOT(on_LoginSucceeded(sp_session*)));
    this->connect(&spc,SIGNAL(on_RootlistLoaded(sp_playlistcontainer*,void*)),this,SLOT(on_RootlistLoaded(sp_playlistcontainer*,void*)));
    this->connect(&spc,SIGNAL(on_PlaylistRenamed(sp_playlist *, void *)),this,SLOT(on_PlaylistRenamed(sp_playlist *, void *)));
    this->connect(&spc,SIGNAL(on_PlaylistAdded(sp_playlistcontainer *, sp_playlist *, int, void *)),this,SLOT(on_PlaylistAdded(sp_playlistcontainer *, sp_playlist *, int , void *)));
    this->connect(&spc,SIGNAL(on_ToplistbrowseLoaded(sp_toplistbrowse *, void *)),this,SLOT(on_ToplistbrowseLoaded(sp_toplistbrowse *, void *)));
    this->connect(&spc,SIGNAL(on_SearchComplete(sp_search *,void *)),this,SLOT(on_SearchComplete(sp_search *,void *)));
    this->connect(&spc,SIGNAL(on_SearchComplete(sp_search *,void *)),this,SLOT(on_SearchComplete(sp_search *,void *)));
    this->connect(&spc,SIGNAL(on_ImageLoaded(sp_image *, void*)),this,SLOT(on_ImageLoaded(sp_image*,void*)));
    this->connect(this->sw,SIGNAL(ShuffleStateChanged(bool)),this,SLOT(on_ShuffleStateChanged(bool)));
    this->connect(this->sw,SIGNAL(PlayStateChanged(bool)),this,SLOT(on_PlayStateChanged(bool)));

    this->ui->wPlayercontrols->hide();

    /* Check if we have an stored user and password pair */
    string username = getenv("USER"); //Get username
    string pfile = "/home/" + username + "/.qtify/.pfile";
    string ufile = "/home/" + username + "/.qtify/.ufile";

    mnenc passtore;

    if(passtore.from_file(pfile)) {
        if(passtore.user_from_file(ufile)) {
            /* We have a stored password, go on */
            this->ui->leUsername->setText(QString(passtore.get_user().c_str()));
            this->ui->lePassword->setText(QString(passtore.get_dec().c_str()));
            this->ui->cbRemember->setChecked(true);

            login();
        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }

}

void MainWindow::login (void)
{
    QByteArray u = this->ui->leUsername->text().toUtf8();
    QByteArray p = this->ui->lePassword->text().toUtf8();

    qDebug() << u;
    if(!sw->Authenticate(u,p))
        qDebug()<<"Authentication attempt failed";
}

void MainWindow::on_pbLogin_clicked()
{
    login();
}

void MainWindow::on_LoginFailed(sp_session *s, sp_error e) {

    QString sError;
    switch(e) {
    case SP_ERROR_BAD_USERNAME_OR_PASSWORD:
        sError = tr("Invalid username or password.");
        break;
    case SP_ERROR_USER_BANNED:
        sError = tr("Your account has been disabled.");
        break;
    case SP_ERROR_UNABLE_TO_CONTACT_SERVER:
        sError = tr("Unable to contact server.");
        break;
    case SP_ERROR_CLIENT_TOO_OLD:
    case SP_ERROR_OTHER_PERMANENT:
    case SP_ERROR_BAD_USER_AGENT:
        sError = tr("Client related error, please update client.");
        break;
    case SP_ERROR_USER_NEEDS_PREMIUM:
        sError = tr("You need a premium account to use this service.");
        break;
    case SP_ERROR_OTHER_TRANSIENT:
        sError = tr("Temporary error, try again later.");
        break;
    default:
        sError = tr("Unknown error, try again later.");
        break;
    }

    this->ui->lbLoginError->setText(sError);
}

void MainWindow::on_RootlistLoaded(sp_playlistcontainer *pc,void *userdata) {
    this->sw->pc = pc;

    /* Clear Treeview */

//    this->ui->twRootlist->clear();
    qDebug() << "Rootlist loaded";
    for(int i=0;i<sp_playlistcontainer_num_playlists(this->sw->pc);i++) {
        sp_playlist *pl2 = sp_playlistcontainer_playlist(this->sw->pc, i);
//        QTreeWidgetItem *l = new QTreeWidgetItem(this->ui->twRootlist);
//        l->setText(0,QString("").setNum(i));
//        l->setText(1,QString::fromUtf8(sp_playlist_name(pl2))/*.append(QString("\n").setNum(sp_playlist_num_tracks(pl2)))*/);
    }
}


void MainWindow::on_PlaylistRenamed(sp_playlist *pl, void *userdata) {

    /* Clear Treeview */

//    this->ui->twRootlist->clear();
    qDebug() << "Rootlist loaded";
    for(int i=0;i<sp_playlistcontainer_num_playlists(this->sw->pc);i++) {
        sp_playlist *pl2 = sp_playlistcontainer_playlist(this->sw->pc, i);
//        QTreeWidgetItem *l = new QTreeWidgetItem(this->ui->twRootlist);
//        l->setText(0,QString("").setNum(i));
//        l->setText(1,QString::fromUtf8(sp_playlist_name(pl2))/*.append(QString("\n").setNum(sp_playlist_num_tracks(pl2)))*/);
    }

}

void MainWindow::on_PlaylistAdded(sp_playlistcontainer *s, sp_playlist *p, int n, void *u) {
    this->on_PlaylistRenamed(p,u);
}

void MainWindow::on_LoginSucceeded(sp_session *s) {
    this->ui->swWidgets->setCurrentWidget(this->ui->pgInside);
    this->ui->wPlayercontrols->show();

//    qDebug() << "Getting rootlist";

//    if(!this->sw->RequestRootlist(s)){
//        qDebug("Rootlist failed to load");
//    }

    qDebug("Requesting toplist");
    if(!this->sw->RequestToplist(s)) {
        qDebug("Toplist request failed");
    }

    /* Clear treeview */
    this->ui->twPlaylist->clear();

    /* Fetch playlist and check it's loaded */
    sp_playlist *playlist = sw->GetStarredPlaylist(s);
    int c = sp_playlist_num_tracks(playlist);
    qDebug() << "HALLOOO " << c;
    qDebug() << "HALLOOO " << sp_playlist_is_loaded(playlist);
    if(playlist!=NULL&&sp_playlist_is_loaded(playlist)) {

        /* Set this playlist to current */
        this->sw->SetCurrentPlaylist(playlist);

        /* Get track count */
        for(int i=0;i<c;i++){

            /* Get track and check it's loaded */
            sp_track *t = sp_playlist_track(playlist,i);
            if(sp_track_is_loaded(t)) {

                /* Concat artists */
                QString t_artist = QString::fromUtf8(sp_artist_name(sp_track_artist(t,0)));
                if(sp_track_num_artists (t) > 1) {
                    for(int     j=1;j<sp_track_num_artists (t);j++) {
                        t_artist += QString(" feat. ").append(QString::fromUtf8(sp_artist_name(sp_track_artist(t,j))));
                    }
                }

                QString t_title = QString::fromUtf8(sp_track_name(t));
                QString t_album = QString::fromUtf8(sp_album_name(sp_track_album(t)));
                QString t_length = QString("%1:%2").arg((int)(sp_track_duration (t) / 60000),2,10,QChar('0')).arg((int)(sp_track_duration (t) % 60000 / 1000),2,10,QChar('0'));

                /* Create and append new treeview item */
                QTreeWidgetItem *t_item = new QTreeWidgetItem(this->ui->twPlaylist);

                /* Print labels */
                t_item->setText(0,QString("").setNum(i));
                t_item->setText(1,t_title);
                t_item->setText(2,t_artist);
                t_item->setText(3,t_album);
                t_item->setText(4,t_length);

            }
        }

        /* Show playlist page */
        this->ui->swWidgets->setCurrentWidget(this->ui->pgPlaylist);
    }

}

void MainWindow::on_ToplistbrowseLoaded(sp_toplistbrowse *tb, void *userdata) {

    if(sp_toplistbrowse_error(tb)==SP_ERROR_OK) {
        int cnt = sp_toplistbrowse_num_albums(tb);
        if(cnt>12) cnt = 12;

        qDebug() << "    Ready to print toplistbrowse, " << cnt << " albums fetched";

        for( int i = 0 ; i < cnt ; i++ ) {
            qDebug() << "Fetchin album 1";
            /* Get album */
            sp_album *alb = sp_toplistbrowse_album(tb,i);

            /* Get albumart id */
            const byte *alb_art_id = sp_album_cover(alb);
            if(alb_art_id) {

                /* Get albumart image */
                this->sw->RequestImage(alb_art_id,(void*)i);

            }
        }
    } else {
        qDebug() << "Error loading toplistbrowse: " << sp_toplistbrowse_error(tb);
    }
}

void MainWindow::on_ImageLoaded(sp_image *image, void* userdata) {

    /* Get albumart */
    size_t img_len;
    const uchar* albumart = (const uchar*)sp_image_data(image,&img_len);
    int id = (intptr_t)userdata;

    if(albumart != NULL) {
        QImage i;
        i.loadFromData(albumart,img_len,0);
        i = i.scaled(QSize(250,2502));
        if (id < 12) { //TODO
            this->ui->navigator->addAction(QPixmap::fromImage(i),id);
        }
//        if(id == 0) {
//            this->ui->lblTopAlbum1->setPixmap(QPixmap::fromImage(i));
//        } else if(id == 1) {
//            this->ui->lblTopAlbum2->setPixmap(QPixmap::fromImage(i));
//        } else if(id == 2) {
//            this->ui->lblTopAlbum3->setPixmap(QPixmap::fromImage(i));
//        } else if(id == 3) {
//            this->ui->lblTopAlbum4->setPixmap(QPixmap::fromImage(i));
//        } else if(id == 4) {
//            this->ui->lblTopAlbum5->setPixmap(QPixmap::fromImage(i));
//        } else if(id == 5) {
//            this->ui->lblTopAlbum6->setPixmap(QPixmap::fromImage(i));
//        } else if(id == 6) {
//            this->ui->lblTopAlbum7->setPixmap(QPixmap::fromImage(i));
//        } else if(id == 7) {
//            this->ui->lblTopAlbum8->setPixmap(QPixmap::fromImage(i));
//        }
    }

}

void MainWindow::on_twRootlist_itemClicked(QTreeWidgetItem* item, int column)
{
    /* Check which action */
    if(column==2) {
        sp_playlist *playlist = sp_playlistcontainer_playlist(this->sw->pc,item->text(0).toInt());
        sp_error err;
        if(!((err = sp_playlist_rename(playlist,"Doningar2"))==SP_ERROR_OK)) {
            qDebug()<<"Error changing playlist name"<<sp_error_message(err);
        } else {
            qDebug()<<"Playlist name changed";
        }

    } else {
        /* Clear treeview */
        this->ui->twPlaylist->clear();

        /* Fetch playlist and check it's loaded */
        sp_playlist *playlist = sp_playlistcontainer_playlist(this->sw->pc,item->text(0).toInt());
        if(playlist!=NULL&&sp_playlist_is_loaded(playlist)) {

            /* Set this playlist to current */
            this->sw->SetCurrentPlaylist(playlist);

            /* Get track count */
            int c = sp_playlist_num_tracks(playlist);
            for(int i=0;i<c;i++){

                /* Get track and check it's loaded */
                sp_track *t = sp_playlist_track(playlist,i);
                if(sp_track_is_loaded(t)) {

                    /* Concat artists */
                    QString t_artist = QString::fromUtf8(sp_artist_name(sp_track_artist(t,0)));
                    if(sp_track_num_artists (t) > 1) {
                        for(int     j=1;j<sp_track_num_artists (t);j++) {
                            t_artist += QString(" feat. ").append(QString::fromUtf8(sp_artist_name(sp_track_artist(t,j))));
                        }
                    }

                    QString t_title = QString::fromUtf8(sp_track_name(t));
                    QString t_album = QString::fromUtf8(sp_album_name(sp_track_album(t)));
                    QString t_length = QString("%1:%2").arg((int)(sp_track_duration (t) / 60000),2,10,QChar('0')).arg((int)(sp_track_duration (t) % 60000 / 1000),2,10,QChar('0'));

                    /* Create and append new treeview item */
                    QTreeWidgetItem *t_item = new QTreeWidgetItem(this->ui->twPlaylist);

                    /* Print labels */
                    t_item->setText(0,QString("").setNum(i));
                    t_item->setText(1,t_title);
                    t_item->setText(2,t_artist);
                    t_item->setText(3,t_album);
                    t_item->setText(4,t_length);

                }
            }

            /* Show playlist page */
            this->ui->swWidgets->setCurrentWidget(this->ui->pgPlaylist);
        }
    }
}

void MainWindow::on_twPlaylist_itemClicked(QTreeWidgetItem* item, int column)
{
    this->sw->PlayPlaylistTrack(item->text(0).toInt());
}

void MainWindow::on_pbSearch_clicked()
{
    QByteArray s = this->ui->leSearch->text().toUtf8();
    if(s.length()>1) {
        if(this->ui->cbSearch->currentText()==QString("Song")) {
            this->sw->RequestSearch(s,100,0,0);
        } else if(this->ui->cbSearch->currentText()==QString("Artist")) {
            this->sw->RequestSearch(s,0,0,100);
        } else if(this->ui->cbSearch->currentText()==QString("Album")) {
            this->sw->RequestSearch(s,0,100,0);
        }
    } else {

    }
}

void MainWindow::on_SearchComplete(sp_search *s,void *userdata){
    if(sp_search_num_tracks(s)>0) {
        /* Clear treeview */
        this->ui->twSearchSong->clear();

        /* Set this playlist to current */
        this->sw->SetCurrentSearch(s);

        /* Get track count */
        int c = sp_search_num_tracks(s);
        for(int i=0;i<c;i++){

            /* Get track and check it's loaded */
            sp_track *t = sp_search_track(s,i);
            if(sp_track_is_loaded(t)) {

                /* Concat artists */
                QString t_artist = QString::fromUtf8(sp_artist_name(sp_track_artist(t,0)));
                if(sp_track_num_artists (t) > 1) {
                    for(int j=1;j<sp_track_num_artists (t);j++) {
                        t_artist += QString(" feat. ").append(QString::fromUtf8(sp_artist_name(sp_track_artist(t,j))));
                    }
                }

                QString t_title = QString::fromUtf8(sp_track_name(t));
                QString t_album = QString::fromUtf8(sp_album_name(sp_track_album(t)));
                QString t_length = QString("%1:%2").arg((int)(sp_track_duration (t) / 60000),2,10,QChar('0')).arg((int)(sp_track_duration (t) % 60000 / 1000),2,10,QChar('0'));

                /* Create and append new treeview item */
                QTreeWidgetItem *t_item = new QTreeWidgetItem(this->ui->twSearchSong);

                /* Print labels */
                t_item->setText(0,QString("").setNum(i));
                t_item->setText(1,t_title);
                t_item->setText(2,t_artist);
                t_item->setText(3,t_album);
                t_item->setText(4,t_length);

            }
        }

        /* Show playlist page */
        this->ui->swWidgets->setCurrentWidget(this->ui->pgSearchSong);

    }/* Artist and album to be included later */
}

void MainWindow::on_pushButton_2_clicked()
{
        this->ui->swWidgets->setCurrentWidget(this->ui->pgInside);
}
void MainWindow::on_pushButton_clicked()
{
    this->ui->swWidgets->setCurrentWidget(this->ui->pgInside);
}

void MainWindow::on_pbNextSong_clicked()
{
    this->sw->PlayQueue(1);
}

void MainWindow::on_pbPrec_clicked()
{
    this->sw->PlayQueue(-1);
}

void MainWindow::on_pbShuffle_clicked()
{
    this->sw->ToggleShuffle();
}


void MainWindow::on_cbRemember_clicked()
{

}

void MainWindow::on_cbRemember_clicked(bool checked)
{
    /* Prepare file paths */
    string username = getenv("USER"); //Get username
    string pfile = "/home/" + username + "/.qtify/.pfile";
    string ufile = "/home/" + username + "/.qtify/.ufile";

    if(checked) { /* checked - save password */

        /* Convert lineedit text to char* */
        QByteArray user = this->ui->leUsername->text().toLatin1();
        char *c_user = user.data();
        QByteArray pass = this->ui->lePassword->text().toLatin1();
        char *c_pass = pass.data();

        /* Save username and encrypted password */
        mnenc passtore;
        passtore.set_user(c_user);
        passtore.encrypt(c_pass);

        if(!(passtore.to_file(pfile))) qDebug() << "Failed saving username/password";
        if(!(passtore.user_to_file(ufile))) qDebug() << "Failed saving username/password";

    } else {

        /* unchecked - clear password */
        std::remove(pfile.c_str());
        std::remove(ufile.c_str());

    }
}

void MainWindow::on_pbPrevious_clicked()
{
    this->sw->PlayQueue(-1);
}

void MainWindow::on_pbNext_clicked()
{
    this->sw->PlayQueue(1);
}

void MainWindow::on_pbPlaypause_clicked()
{
    this->sw->PlayPause();
}

void MainWindow::on_ShuffleStateChanged(bool s){
    if(s) {
        this->ui->pbShuffle->setIcon(QIcon(":/res/shuffleon.png"));
    } else {
        this->ui->pbShuffle->setIcon(QIcon(":/res/shuffleoff.png"));
    }
}

void MainWindow::on_PlayStateChanged(bool s){
    if(s) {
        this->ui->pbPlaypause->setIcon(QIcon(":/res/play.png"));
    } else {
        this->ui->pbPlaypause->setIcon(QIcon(":/res/pause.png"));
    }
}

void MainWindow::on_pbBack_clicked()
{
    this->ui->swWidgets->setCurrentWidget(this->ui->pgInside);
}

void MainWindow::on_twSearchSong_itemClicked(QTreeWidgetItem* item, int column)
{
    this->sw->PlaySearchTrack(item->text(0).toInt());
}
