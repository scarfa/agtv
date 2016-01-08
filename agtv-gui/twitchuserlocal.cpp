#include "twitchuserlocal.h"

TwitchUserLocal::TwitchUserLocal(QObject *parent, const qint64 defaultTimerInterval) :
    QObject(parent)
{
    this->refreshTimerInterval = defaultTimerInterval;
    
    this->bookmarkedChannelsDataChanged = false;
    

}

QMap<QString, TwitchChannel *> TwitchUserLocal::getBookmarkedChannels()
{
    return this->bookmarkedChannels;
}


void TwitchUserLocal::loadBookmarks()
{
    QStringList loadedbookmarks;
    loadedbookmarks = this->getBookmarks();
    
    this->bookmarkedChannels.clear();

    QListIterator<QString> itr (loadedbookmarks);

    while (itr.hasNext()) {
        QString current = itr.next();
        TwitchChannel *twitchChannel = new TwitchChannel(this, "this->oAuthToken", current, this->getRefreshTimerInterval());
        this->bookmarkedChannels[current] = twitchChannel;

        this->bookmarkedChannelsDataChanged = true;
    }

     emit twitchBookmarkedChannelsDataChanged(this->bookmarkedChannelsDataChanged);
     
}

QString TwitchUserLocal::getStoredOAuthAccessToken(QString company, QString app)
{
    QSettings settings(company, app);
    
    QString _oauthtoken = "<NONE>";
    
    if (settings.value("oauthAccessToken", "").toString().length() > 1) {
        _oauthtoken = settings.value("oauthAccessToken", "").toString();
    
    }
    
    emit oAuthAccessTokenLoaded(_oauthtoken);
    
    return _oauthtoken;
}

QString TwitchUserLocal::getStoredUsername(QString company, QString app)
{
    QSettings settings(company, app);
    return settings.value("username", "").toString();
}

QStringList TwitchUserLocal::getBookmarks(QString company, QString app)
{
    QSettings settings(company, app);
      
    return settings.value("bookmarks", QStringList()).toStringList();    
}

bool TwitchUserLocal::setBookmarks(QStringList bookmarks, QString company, QString app)
{
    QSettings settings(company, app);
    settings.setValue("bookmarks", bookmarks);
    settings.sync();    
    
    return true;
}

bool TwitchUserLocal::addBookmark(QString bookmark, QString company, QString app)
{
    QStringList currentbookmarks = this->getBookmarks();
    if (currentbookmarks.count(bookmark) <= 0) {
        currentbookmarks << bookmark;
        this->setBookmarks(currentbookmarks);
    }    
    
    return true;
}



bool TwitchUserLocal::saveOAuthAccessToken(QString oAuthAccessToken, QString company, QString app)
{
    bool ok = false;
    
    if (oAuthAccessToken.length() > 0) {
        QSettings settings(company, app);
        settings.setValue("oauthAccessToken", oAuthAccessToken);
        settings.sync();    
        ok = true;
    }
    
    return ok;
}

bool TwitchUserLocal::saveUsername(QString userName, QString company, QString app)
{
    bool ok = false;
    
    if (userName.length() > 0) {
        QSettings settings(company, app);
        settings.setValue("username", userName);
        settings.sync();    
        ok = true;
    }
    
    return ok;    
}

bool TwitchUserLocal::isUserSetupOk(QString company, QString app)
{
    if (this->getStoredUsername() != "") {
        return true;
    } else {
        return false;
    }
}

void TwitchUserLocal::onSaveOAuthAccessToken(QString oAuthAccessToken)
{
    this->saveOAuthAccessToken(oAuthAccessToken);
}

void TwitchUserLocal::onSaveUsername(QString userName)
{
    this->saveUsername(userName);
}

qint64 TwitchUserLocal::getRefreshTimerInterval()
{
    return this->refreshTimerInterval;
}
