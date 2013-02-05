#ifndef MAPSIZEDIALOG_H
#define MAPSIZEDIALOG_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QDialog>
#include "ui_mapsizedialog.h"

namespace Ui {
	class MapSizeDialog;
}

class MapSizeDialog : public QDialog
{
	Q_OBJECT

public:
	MapSizeDialog(QWidget *parent = 0);
	~MapSizeDialog();

	void Init();

	int GetWidth();
	int GetHeight();
	int GetSteps();
private:
	Ui::MapSizeDialog ui;
};

#endif // MAPSIZEDIALOG_H
