#include "lab10_11.h"

Lab10_11::Lab10_11(Controller& ctr, QWidget *parent) : 
	QMainWindow{ parent }, 
	ctr{ ctr }, 
	ui{ ctr }
{
	ui.setupUi(this);
}

Lab10_11::~Lab10_11()
{

}
