#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "parser.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private:
	Parser parser;

private slots:
	void on_action_open_triggered();
	void on_action_exit_triggered();

	void on_pushButton_XY_clicked();

	void on_pushButton_XZ_clicked();

	void on_pushButton_YZ_clicked();

private:
	Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
