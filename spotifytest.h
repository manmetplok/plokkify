#ifndef SPOTIFYTEST_H
#define SPOTIFYTEST_H

#include <QObject>

class SpotifyTest : public QObject
{
    Q_OBJECT

    Q_PROPERTY( QString userName READ userName WRITE setUserName )
    Q_PROPERTY( QString password READ password WRITE setPassword )

    //Q_PROPERTY( QString playList READ playList WRITE setPlayList )
public:
    explicit SpotifyTest(QObject *parent = 0);

    void setUserName (QString userName);
    QString userName (void);

    void setPassword (QString aPassword);
    QString password (void);
signals:

public slots:

private:
    QString m_userName;
    QString m_password;

    QString m_playList;
};

#endif // SPOTIFYTEST_H
