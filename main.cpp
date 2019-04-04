#include "gui/mainwindow.hpp"
#include <QApplication>

#include "clone_format/jcln.hpp"

int main(int argc, char *argv[])
{
	qInstallMessageHandler(asterism::asterism_message_output);

	auto j=asterism::jcln::read("X:\\projects\\asterism\\ref.jcln");
	if(j)
	{
		asterism::jcln::write(j.value(), "loaded.jcln");
	}

	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
