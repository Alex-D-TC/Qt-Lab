#ifndef LAB10_11_H
#define LAB10_11_H

#include <QtWidgets/QMainWindow>
#include "ui_lab10_11.h"
#include "Controller.h"

class Lab10_11 : public QMainWindow
{
	Q_OBJECT

public:
	Lab10_11(Controller& ctr, QWidget *parent = 0);
	~Lab10_11();

private:
	Ui::Lab10_11Class ui;
	Controller& ctr;
};

#endif // LAB10_11_H
