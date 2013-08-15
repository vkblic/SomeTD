#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QPushButton>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QWidget>
#include <QFileDialog>
#include <QListView>
#include <QImage>
#include <QLabel>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow         *ui;
    QFileDialog            *m_FileDialog;
    QImage                 *m_Image;
    QList<QTreeWidgetItem*> m_SelectedItems;
    int                     m_Index;
    QTimer                 *m_Timer;
private:
    void AddFiles();


public slots:
    void Play();
    void AutoPlay();
    void TreeItemSelectionChange();
    void TreeItemClicked(QTreeWidgetItem*,int);
};

#endif // MAINWINDOW_H
