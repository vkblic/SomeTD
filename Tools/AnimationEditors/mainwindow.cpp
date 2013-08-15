#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	this->setWindowTitle(tr("AnimationEditors"));
	this->m_Image = new QImage();
	this->m_Timer=new QTimer(this);
	ui->treeWidget->setColumnHidden(1,true);
	ui->horizontalSlider->setRange(0,4000);
	ui->horizontalSlider->setValue(1000);
	ui->horizontalSlider->setPageStep(1000);
	ui->horizontalSlider->setTickPosition(QSlider::TicksAbove);
	connect(ui->addFileAction,&QAction::triggered,this,&MainWindow::AddFiles);
	connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(Play()));
	connect(ui->treeWidget,SIGNAL(itemSelectionChanged()),this,SLOT(TreeItemSelectionChange()));
	connect(ui->treeWidget,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(TreeItemClicked(QTreeWidgetItem*,int)));
	connect(this->m_Timer,SIGNAL(timeout()),this,SLOT(AutoPlay()));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::TreeItemClicked(QTreeWidgetItem *item, int column)
{

	if(item->childCount()!=0&&item->isSelected())
	{
		ui->treeWidget->clearSelection();
		ui->treeWidget->setSelectionMode(QTreeWidget::SingleSelection);
		item->setSelected(true);
	}
	else
	{
		ui->treeWidget->setSelectionMode(QTreeWidget::MultiSelection);
	}

}

void MainWindow::TreeItemSelectionChange()
{
	// qDebug()<<"the item selection";
}
void MainWindow::AddFiles()
{

	QString dirPath=QFileDialog::getExistingDirectory(this, tr("请选择文件夹"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks );
	QDir dir(dirPath);
	if(!dir.exists())
		return;
	dir.setFilter(QDir::Files);
	dir.setSorting(QDir::Name);
	QFileInfoList list = dir.entryInfoList();
	QTreeWidgetItem *root=new QTreeWidgetItem(ui->treeWidget);
	root->setExpanded(true);
	root->setText(0,dir.dirName());
	for(int i=0;i<list.length();i++)
	{
		QFileInfo fileInfo=list.at(i);
		qDebug()<<fileInfo.fileName();
		QTreeWidgetItem *item=new QTreeWidgetItem(root);
		item->setIcon(0,QIcon(fileInfo.filePath()));
		item->setText(1,fileInfo.filePath());
		item->setText(2,fileInfo.fileName());
		root->addChild(item);
	}
}

void MainWindow::AutoPlay()
{
	this->m_Timer->setInterval(1/60 * 1000);
	if( this->m_Index < this->m_SelectedItems.length()-1 )
	{
		this->m_Index ++;
		qDebug()<<this->m_SelectedItems.at(this->m_Index)->text(1)<<"\n";
		ui->label->setPixmap(this->m_SelectedItems.at(this->m_Index)->text(1));
		ui->filename->setText(this->m_SelectedItems.at(this->m_Index)->text(2));
		update();
	}
	else
	{
		this->m_Index = 0;
		qDebug()<<this->m_SelectedItems.at(0)->text(1)<<"\n";
		ui->label->setPixmap( this->m_SelectedItems.at(0)->text(1) );
		ui->filename->setText(this->m_SelectedItems.at(0)->text(2));
		update();
	}
}

void MainWindow::Play()
{
	if( ui->pushButton->text() == "Play" )
	{
		ui->treeWidget->setEnabled(false);
		this->m_SelectedItems.clear();
		if( ui->treeWidget->selectedItems().length()==0 )
			return;
		if(ui->treeWidget->selectedItems().length()==1&&ui->treeWidget->selectedItems().at(0)->childCount()!=0)
		{
			for(int i=0;i<ui->treeWidget->selectedItems().at(0)->childCount();i++)
			{
				this->m_SelectedItems.append(ui->treeWidget->selectedItems().at(0)->child(i));
			}
		}
		else
			this->m_SelectedItems=ui->treeWidget->selectedItems();
		ui->pushButton->setText("Stop");
		this->m_Index = 0;
		this->m_Timer->start(ui->horizontalSlider->value());
	}
	else if( ui->pushButton->text() == "Stop" )
	{
		ui->pushButton->setText("Play");
		ui->treeWidget->setEnabled(true);
		this->m_Timer->stop();
	}


}
