#include "mainwindow.h"
#include <QApplication>
#include "CCEGLView.h"
#include "Classes/AppDelegate.h"

USING_NS_CC;

int main(int argc, char *argv[])
{
	


    QApplication a(argc, argv);
    MainWindow w;

	AppDelegate app;

	CCEGLView::CreateWithHWnd(w.GetGLViweHandler());

	CCEGLView* eglView = CCEGLView::sharedOpenGLView();
	eglView->setFrameSize(480, 320);

	w.show();
	CCApplication::sharedApplication()->run();

	int i = 1;
	while (i++ && i < 1000)
	{
		CCApplication::sharedApplication()->triggerMainLoop();
	}
    
    return a.exec();
}
