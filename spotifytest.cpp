#include "spotifytest.h"

SpotifyTest::SpotifyTest(QObject *parent) :
    QObject(parent)
{
}

void SpotifyTest::setUserName (QString userName)
{
    m_userName = userName;
}

QString SpotifyTest::userName (void)
{
    return m_userName;
}

void SpotifyTest::setPassword (QString aPassword)
{
    m_password = aPassword;
}

QString SpotifyTest::password (void)
{
    return m_password;
}
