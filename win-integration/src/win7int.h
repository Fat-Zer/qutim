#ifndef WIN7INT_H
#define WIN7INT_H

#include <QGraphicsView>
#include <QList>
#include <qutim/messagesession.h>
#include <qutim/plugin.h>
#include <WinThings/TaskbarPreviews.h>

class WPreviews;

class Win7Int2 : public qutim_sdk_0_3::Plugin
{
	Q_OBJECT
	Q_CLASSINFO("Service", "Dock")
	Q_CLASSINFO("Uses", "ChatLayer")

	QPixmap generateOverlayIcon(quint32 unreadConfs, quint32 unreadChats);
	QWidget   *chatWindow();
	void       testTab();
	QWidget   *previousWindow;
	unsigned   previousTabId;
	WPreviews *previews;


public:
	Win7Int2();
	void init();
	bool load();
	bool unload();

public slots:
	void onChatwidgetDestroyed();
	void onSessionActivated(bool);
	void onSessionCreated  (qutim_sdk_0_3::ChatSession*);
	void onUnreadChanged   (qutim_sdk_0_3::MessageList);

private:
};

#define CHATUNREAD_TITLE_X 10
#define CHATUNREAD_TITLE_Y 5
#define CHATUNREAD_X       5
#define CHATUNREAD_Y       18
#define CONFUNREAD_X       5
#define CONFUNREAD_Y       31
#define AUTHORS_TITLE_X    10
#define AUTHORS_TITLE_Y    49
#define AUTHORS_LIST_X     10
#define AUTHORS_LIST_Y     62
#define ICON_SIZE          64

namespace qutim_sdk_0_3
{
	class ChatSession;
}

class WPreviews : public PreviewProvider
{
	Q_OBJECT

	typedef QList<qutim_sdk_0_3::ChatSession *> SessionsList;

	QGraphicsPixmapItem *qutimIconItem;
	QGraphicsPixmapItem *sceneBgItem;
	QGraphicsTextItem   *textUnreadChats;
	QGraphicsTextItem   *textUnreadConfs;
	QGraphicsTextItem   *textUnreadTitle;
	QGraphicsTextItem   *textUnreadAuthorsTitle;
	QGraphicsTextItem   *textUnreadAuthorsList;
	QGraphicsView *grView;
	QPixmap  sceneBgImage;
	QPixmap  livePreview;
	QSize    currentBgSize;
	QWidget *lastOwner;
	SessionsList sessions;
	unsigned unreadChats, unreadConfs;
	Win7Int2 *parent;

public:
	WPreviews(Win7Int2 *parent = 0);
	~WPreviews();
	QPixmap IconicPreview(unsigned tabid, QWidget *owner, QSize);
	QPixmap LivePreview  (unsigned tabid, QWidget *owner);
	void updateNumbers   (unsigned confs, unsigned chats);

public slots:
	void onUnreadChanged(qutim_sdk_0_3::MessageList);
	void onSessionDestroyed(QObject *);
	void prepareLivePreview();
};

#endif // WIN7INT_H
