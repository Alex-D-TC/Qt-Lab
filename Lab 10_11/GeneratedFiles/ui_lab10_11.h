/********************************************************************************
** Form generated from reading UI file 'lab10_11.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAB10_11_H
#define UI_LAB10_11_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <QHboxLayout>
#include <QVBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QMessageBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QInputDialog>
#include <QDir>

#include <limits>
#include <vector>
#include <string>
#include "Controller.h"

QT_BEGIN_NAMESPACE

Q_DECLARE_METATYPE(Medicament)

class Ui_Lab10_11Class
{
private:

	QHBoxLayout* mainLayout;
	QVBoxLayout* leftLayout;
	QVBoxLayout* rightLayout;
	QWidget* rootW;
	QListWidget* productList;

	QLineEdit* name;
	QLineEdit* price;
	QLineEdit* producer;
	QLineEdit* activeSubstance;

	QMenuBar *menuBar;
	QToolBar *mainToolBar;
	QWidget *centralWidget;
	QStatusBar *statusBar;

	Controller& ctr;

	/*
	Populates the list with prodcts, sorted.
	order - The order in which to sort
	type - The field by which to sort
	inPlace - True: The population is 'in place', there's no need to retrieve items from the repository
	- False: The elements must be retrieved from the repository
	*/
	void populateList(string order, string type, bool inPlace = false) {
		vector<Medicament> list;
		if (!inPlace)
			list = ctr.get_sorted(order, type);
		else {
			list = getCurrentItems();
			list = ctr.get_sorted(order, type, &list);
		}
		populate(list);
	}

	/*
	Populates the list with prodcts, sorted.
	*/
	void populate(vector<Medicament>& list) {
		std::vector<QListWidgetItem*> resList = clearAndReuse();
		int size = resList.size();
		for (Medicament med : list) {
			QListWidgetItem* item;
			if (size != 0) {
				item = resList.at(size - 1);
				resList.pop_back();
				item->setText(QString{ med.getDenumire().c_str() });
				size--;
			}
			else {
				item = new QListWidgetItem(QString(med.getDenumire().c_str()));
			}
			QVariant data{};
			data.setValue<Medicament&>(med);
			item->setData(Qt::UserRole, data);
			productList->addItem(item);
		}
		for (QListWidgetItem* item : resList) {
			delete item;
		}
	}

	/*
	Returns the current items in the list
	*/
	vector<Medicament> getCurrentItems() {
		vector<Medicament> resultVector;
		int size = productList->count();
		for (int i = 0; i < size; ++i) {
			resultVector.push_back(productList->item(i)->data(Qt::UserRole).value<Medicament>());
		}
		return resultVector;
	}

	/*
	Clears the QListWidget and returns a vector of all listWidgets retrieved
	*/
	std::vector<QListWidgetItem*> clearAndReuse() {
		std::vector<QListWidgetItem*> resList;
		while (productList->count() > 0) {
			resList.push_back(productList->takeItem(0));
		}
		return resList;
	}

	/*
	Validates the textfields
	name - The name field
	producer - The producer field
	activeSubst - The active substance field
	throws invalid_argument if any of them are void
	*/
	void validateFields(string name, string producer, string activeSubst) {
		if (name == "")
			throw invalid_argument("Numele nu poate fi vid!");
		if (producer == "")
			throw invalid_argument("Producatorul nu poate fi vid!");
		if (activeSubst == "")
			throw invalid_argument("Substanta activa nu poate fi vida!");
	}

	/*
	Displays a generic message box for any given error text
	*/
	void mBoxError(string what) {
		char* substr = "stoi";
		if (strstr(what.c_str(), substr) != NULL)
			what = "Pretul nu poate fi vid!";
		QMessageBox m;
		m.setWindowTitle("Error!");
		m.setText(QString{ what.c_str() });
		m.setStandardButtons(QMessageBox::Ok);
		m.setDefaultButton(QMessageBox::Ok);
		m.exec();
	}

public:


	Ui_Lab10_11Class(Controller& ctr) : ctr{ ctr } {}

	void setupUi(QMainWindow *Lab10_11Class)
	{
		if (Lab10_11Class->objectName().isEmpty())
			Lab10_11Class->setObjectName(QStringLiteral("Lab10_11Class"));
		Lab10_11Class->resize(600, 400);
		menuBar = new QMenuBar(Lab10_11Class);
		menuBar->setObjectName(QStringLiteral("menuBar"));
		Lab10_11Class->setMenuBar(menuBar);
		mainToolBar = new QToolBar(Lab10_11Class);
		mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
		Lab10_11Class->addToolBar(mainToolBar);
		centralWidget = new QWidget(Lab10_11Class);
		centralWidget->setObjectName(QStringLiteral("centralWidget"));
		Lab10_11Class->setCentralWidget(centralWidget);
		statusBar = new QStatusBar(Lab10_11Class);
		statusBar->setObjectName(QStringLiteral("statusBar"));
		Lab10_11Class->setStatusBar(statusBar);


		rootW = new QWidget();
		mainLayout = new QHBoxLayout();
		{
			leftLayout = new QVBoxLayout();
			{
				productList = new QListWidget();

				leftLayout->setSpacing(10);

				QHBoxLayout* buttonLayout = new QHBoxLayout();
				{
					QPushButton* removeButton = new QPushButton(QStringLiteral("Remove"));
					QPushButton* sortNameButton = new QPushButton(QStringLiteral("Sort by name"));
					QPushButton* sortPoducerButton = new QPushButton(QStringLiteral("Sort by producer"));

					/*
					Remove button event handler
					*/
					QObject::connect(removeButton, &QPushButton::clicked, [this]() {
						string name{ this->name->text().toUtf8().constData() },
							producer{ this->producer->text().toUtf8().constData() };
						try {
							validateFields(name, producer, "a");
							ctr.removeElement(name, producer);
							populateList("descrescator", "denumire");
						}
						catch (invalid_argument e) {
							mBoxError(e.what());
						}
					});

					/*
					Sort by name button event handler
					*/
					QObject::connect(sortNameButton, &QPushButton::clicked, [this]() {
						populateList("descrescator", "denumire", true);
					});

					/*
					Sort by producer button event handler
					*/
					QObject::connect(sortPoducerButton, &QPushButton::clicked, [this]() {
						populateList("descrescator", "producator", true);
					});

					buttonLayout->addWidget(removeButton);
					buttonLayout->addWidget(sortNameButton);
					buttonLayout->addWidget(sortPoducerButton);
				}
				leftLayout->addWidget(productList);
				leftLayout->addLayout(buttonLayout);
			}
			rightLayout = new QVBoxLayout();
			{
				rightLayout->setSpacing(10);

				QFormLayout* displayForm = new QFormLayout();
				{
					displayForm->setVerticalSpacing(10);

					name = new QLineEdit();
					price = new QLineEdit();
					producer = new QLineEdit();
					activeSubstance = new QLineEdit();

					displayForm->addRow(QStringLiteral("Name: "), name);
					displayForm->addRow(QStringLiteral("Price: "), price);
					displayForm->addRow(QStringLiteral("Producer: "), producer);
					displayForm->addRow(QStringLiteral("Active Substance: "), activeSubstance);

				}
				rightLayout->addLayout(displayForm);

				QListWidget* prList = productList;
				QLineEdit* nm = name;
				QLineEdit* pr = price;
				QLineEdit* prod = producer;
				QLineEdit* act = activeSubstance;

				QObject::connect(productList, &QListWidget::itemSelectionChanged, [
					prList,
						nm,
						pr,
						prod,
						act]() {
					QList<QListWidgetItem *> selected = prList->selectedItems();
					if (selected.size() == 0)
						return;
					Medicament& data = selected.at(0)->data(Qt::UserRole).value<Medicament>();

					nm->setText(data.getDenumire().c_str());
					prod->setText(QString(data.getProducator().c_str()));
					pr->setText(QString{ to_string(data.getPret()).c_str() });
					act->setText(QString(data.getSubstActiva().c_str()));
				});

				QWidget* wBtnL1 = new QWidget();
				QHBoxLayout* btnL1 = new QHBoxLayout();
				wBtnL1->setLayout(btnL1);
				{
					QPushButton* addBtn = new QPushButton(QStringLiteral("Add"));
					QPushButton* upBtn = new QPushButton(QStringLiteral("Update"));

					/*
					Add button event handler
					*/
					QObject::connect(addBtn, &QPushButton::clicked, [this]() {
						try {
							string name{ this->name->text().toUtf8().constData() },
								producer{ this->producer->text().toUtf8().constData() },
								activeSubst{ this->activeSubstance->text().toUtf8().constData() };
							int price = stoi(this->price->text().toUtf8().constData());
							validateFields(name, producer, activeSubst);
							ctr.addElement(name, price, producer, activeSubst);
							this->populateList("descrescator", "denumire");
						}
						catch (invalid_argument e) {
							mBoxError(e.what());
						}
					});

					/*
					Update button event handler
					*/
					QObject::connect(upBtn, &QPushButton::clicked, [this]() {
						string name{ this->name->text().toUtf8().constData() },
							producer{ this->producer->text().toUtf8().constData() },
							activeSubst{ this->activeSubstance->text().toUtf8().constData() };
						int price;
						try {
							validateFields(name, producer, activeSubst);
							price = stoi(this->price->text().toUtf8().constData());
							ctr.updateElement(name, price, producer, activeSubst);
							this->populateList("descrescator", "denumire");
						}
						catch (invalid_argument e) {
							mBoxError(e.what());
						}
					});


					btnL1->addWidget(addBtn);
					btnL1->addWidget(upBtn);
				}
				rightLayout->addWidget(wBtnL1);

				QWidget* wBtnL2 = new QWidget();
				QHBoxLayout* btnL2 = new QHBoxLayout();
				wBtnL2->setLayout(btnL2);
				{
					QPushButton* btnCos = new QPushButton("Show cart");
					QPushButton* btnCosGraphic = new QPushButton("Show cart graphically");

					btnL2->addWidget(btnCos);
					btnL2->addWidget(btnCosGraphic);
				}
				rightLayout->addWidget(wBtnL2);

				QWidget* wBtnL3 = new QWidget();
				QHBoxLayout* btnL3 = new QHBoxLayout();
				wBtnL3->setLayout(btnL3);
				{
					QPushButton* filterName = new QPushButton(QStringLiteral("Filter by name"));
					QPushButton* filterPrice = new QPushButton(QStringLiteral("Filter by price"));
					QPushButton* filterProducer = new QPushButton(QStringLiteral("Filter by producer"));
					QPushButton* filterSAct = new QPushButton(QStringLiteral("Filter by active substance"));

					/*
					Filter by name button event handler
					*/
					QObject::connect(filterName, &QPushButton::clicked, [this]() {
						bool ok;
						string result = QInputDialog::getText(rootW,
							"Input selection",
							QStringLiteral("Input your name: "),
							QLineEdit::Normal,
							QDir::home().dirName(),
							&ok).toUtf8().constData();
						if (ok) {
							vector<Medicament> res = this->ctr.filter("denumire", result);
							populate(res);
						}
					});

					/*
					Filter by price button event handler
					*/
					QObject::connect(filterPrice, &QPushButton::clicked, [this]() {
						bool ok;
						int result = QInputDialog::getInt(rootW,
							"Input selection",
							QStringLiteral("Input your price: "),
							0,
							INT_MIN,
							INT_MAX,
							1,
							&ok);
						if (ok) {
							vector<Medicament> res = this->ctr.filter("pret", to_string(result));
							populate(res);
						}
					});

					/*
					Filter by producer button event handler
					*/
					QObject::connect(filterProducer, &QPushButton::clicked, [this]() {
						bool ok;
						string result = QInputDialog::getText(rootW,
							"Input selection",
							QStringLiteral("Input your producer: "),
							QLineEdit::Normal,
							QStringLiteral("Producer"),
							&ok).toUtf8().constData();
						if (ok) {
							vector<Medicament> res = this->ctr.filter("producator", result);
							populate(res);
						}
					});

					/*
					Filter by active substance button event handler
					*/
					QObject::connect(filterSAct, &QPushButton::clicked, [this]() {
						bool ok;
						string result = QInputDialog::getText(rootW,
							"Input selection",
							QStringLiteral("Input your active substance: "),
							QLineEdit::Normal,
							QStringLiteral("Active substance"),
							&ok).toUtf8().constData();
						if (ok) {
							vector<Medicament> res = this->ctr.filter("substanta activa", result);
							populate(res);
						}
					});

					btnL3->addWidget(filterName);
					btnL3->addWidget(filterPrice);
					btnL3->addWidget(filterProducer);
					btnL3->addWidget(filterSAct);
				}
				rightLayout->addWidget(wBtnL3);
			}

			mainLayout->addItem(leftLayout);
			mainLayout->addItem(rightLayout);
		}
		rootW->setLayout(mainLayout);

		Lab10_11Class->setCentralWidget(rootW);

		populateList("descrescator", "denumire");

		retranslateUi(Lab10_11Class);

		QMetaObject::connectSlotsByName(Lab10_11Class);
	} // setupUi

	void retranslateUi(QMainWindow *Lab10_11Class)
	{
		Lab10_11Class->setWindowTitle(QApplication::translate("Lab10_11Class", "Lab10_11", 0));
	} // retranslateUi

};

namespace Ui {
	class Lab10_11Class : public Ui_Lab10_11Class {
	public:
		Lab10_11Class(Controller& ctr) : Ui_Lab10_11Class{ ctr } {}
	};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAB10_11_H
