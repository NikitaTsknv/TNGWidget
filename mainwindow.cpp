#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>
#include <QVector>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_action_open_triggered()
{
	parser.clearData();

	QString file_name = QFileDialog::getOpenFileName(this,tr("Открытие файла"),"",tr("Text Files (*.txt)"));

	std::vector<std::string> file_buffer;

	QFile file(file_name);
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::critical(this,tr("Ошибка"),tr("Файл не найден"));
		return;
	}
	else {
		QString str;
		QTextStream stream(&file);

		while (!stream.atEnd()) {
			str = stream.readLine();
			file_buffer.push_back(str.toStdString());
		}

		file.close();

		std::string f_n = QFileInfo(file_name).fileName().toStdString();

		parser.parsingFileBuffer(std::forward<std::vector<std::string>>(file_buffer), std::forward<std::string>(f_n));
	}

}

void MainWindow::on_action_exit_triggered()
{
	QApplication::quit();
}

void MainWindow::on_pushButton_XY_clicked()
{
	if (parser.getCoordX().empty() || parser.getCoordY().empty()) {
		QMessageBox::critical(this,tr("Ошибка"),tr("Данные отсутствуют"));
		return;
	}
	else {
		ui->widget_graph->addGraph();
		ui->widget_graph->graph(0)->setPen(QPen(Qt::red));
		ui->widget_graph->xAxis->setLabel("X");
		ui->widget_graph->yAxis->setLabel("Y");
		ui->widget_graph->addGraph(ui->widget_graph->xAxis, ui->widget_graph->yAxis);

		#if QT_VERSION <= QT_VERSION_CHECK(5,14,0)
			QVector<double> x  {QVector<double>::fromStdVector(parser.getCoordX())};
			QVector<double> y {QVector<double>::fromStdVector(parser.getCoordY())};
		#else
			std::vector<double> stdX {parser.getCoordX()};
			std::vector<double> stdY {parser.getCoordY()};
			QVector<double> x  = QVector<double>(stdX.begin(), stdX.end());
			QVector<double> y  = QVector<double>(stdY.begin(), stdY.end());
		#endif

		ui->widget_graph->graph(0)->setData(x, y);

		auto min_x = *std::min_element(std::begin(x), std::end(x));
		auto max_x = *std::max_element(std::begin(x), std::end(x));
		auto min_y = *std::min_element(std::begin(y), std::end(y));
		auto max_y = *std::max_element(std::begin(y), std::end(y));

		ui->widget_graph->xAxis->setRange(min_x,max_x);
		ui->widget_graph->yAxis->setRange(min_y,max_y);
		ui->widget_graph->replot();
	}
}

void MainWindow::on_pushButton_XZ_clicked()
{
	if (parser.getCoordX().empty() || parser.getCoordZ().empty()) {
		QMessageBox::critical(this,tr("Ошибка"),tr("Данные отсутствуют"));
		return;
	}
	else {
		ui->widget_graph->addGraph();
		ui->widget_graph->graph(0)->setPen(QPen(Qt::red));
		ui->widget_graph->xAxis->setLabel("X");
		ui->widget_graph->yAxis->setLabel("Z");
		ui->widget_graph->addGraph(ui->widget_graph->xAxis, ui->widget_graph->yAxis);

		#if QT_VERSION <= QT_VERSION_CHECK(5,14,0)
			QVector<double> x  {QVector<double>::fromStdVector(parser.getCoordX())};
			QVector<double> z {QVector<double>::fromStdVector(parser.getCoordZ())};
		#else
			std::vector<double> stdX {parser.getCoordX()};
			std::vector<double> stdZ {parser.getCoordZ()};
			QVector<double> x  = QVector<double>(stdX.begin(), stdX.end());
			QVector<double> z  = QVector<double>(stdZ.begin(), stdZ.end());
		#endif

		ui->widget_graph->graph(0)->setData(x, z);

		auto min_x = *std::min_element(std::begin(x), std::end(x));
		auto max_x = *std::max_element(std::begin(x), std::end(x));
		auto min_z = *std::min_element(std::begin(z), std::end(z));
		auto max_z = *std::max_element(std::begin(z), std::end(z));

		ui->widget_graph->xAxis->setRange(min_x,max_x);
		ui->widget_graph->yAxis->setRange(min_z,max_z);
		ui->widget_graph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
		ui->widget_graph->replot();
	}
}


void MainWindow::on_pushButton_YZ_clicked()
{
	if (parser.getCoordY().empty() || parser.getCoordZ().empty()) {
		QMessageBox::critical(this,tr("Ошибка"),tr("Данные отсутствуют"));
		return;
	}
	else {
		ui->widget_graph->addGraph();
		ui->widget_graph->graph(0)->setPen(QPen(Qt::red));
		ui->widget_graph->xAxis->setLabel("Y");
		ui->widget_graph->yAxis->setLabel("Z");
		ui->widget_graph->addGraph(ui->widget_graph->xAxis, ui->widget_graph->yAxis);

		#if QT_VERSION <= QT_VERSION_CHECK(5,14,0)
			QVector<double> y  {QVector<double>::fromStdVector(parser.getCoordY())};
			QVector<double> z {QVector<double>::fromStdVector(parser.getCoordZ())};
		#else
			std::vector<double> stdY {parser.getCoordY()};
			std::vector<double> stdZ {parser.getCoordZ()};
			QVector<double> y  = QVector<double>(stdY.begin(), stdY.end());
			QVector<double> z  = QVector<double>(stdZ.begin(), stdZ.end());
		#endif

		ui->widget_graph->graph(0)->setData(y, z);

		auto min_y = *std::min_element(std::begin(y), std::end(y));
		auto max_y = *std::max_element(std::begin(y), std::end(y));
		auto min_z = *std::min_element(std::begin(z), std::end(z));
		auto max_z = *std::max_element(std::begin(z), std::end(z));

		ui->widget_graph->xAxis->setRange(min_y,max_y);
		ui->widget_graph->yAxis->setRange(min_z,max_z);
		ui->widget_graph->replot();
	}
}

