#include <stdlib.h>
#include <crtdbg.h>

#include "lab10_11.h"
#include <QtWidgets/QApplication>
#include "Controller.h"
#include "FileRepository.h"

int execute(int argc, char *argv[]) {
	FileRepository repo{ "input" };
	Controller ctr{ repo };
	QApplication a(argc, argv);
	Lab10_11 w{ ctr };
	w.show();
	return a.exec();
}

int main(int argc, char *argv[])
{
	int result = execute(argc, argv);
	_CrtDumpMemoryLeaks();
	return result;
}
