#include "mainwindow.h"
#include <QApplication>
#include "CCEGLView.h"
#include "Classes/AppDelegate.h"

USING_NS_CC;

int main(int argc, char *argv[])
{
	AppDelegate app;
	CCEGLView* eglView = CCEGLView::sharedOpenGLView();
	eglView->setFrameSize(960, 720);


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
