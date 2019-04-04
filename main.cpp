#include "gui/mainwindow.hpp"
#include <QApplication>

#include "clone_format/jcln.hpp"

int main(int argc, char *argv[])
{
	qInstallMessageHandler(asterism::asterism_message_output);

	QApplication a(argc, argv);
	asterism::MainWindow w;
	w.show();
	return a.exec();
}
