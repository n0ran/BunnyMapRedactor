#include "mapsizedialog.h"

MapSizeDialog::MapSizeDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	Init();
}

MapSizeDialog::~MapSizeDialog()
{
	 
}

void MapSizeDialog::Init()
{
	 ui.vertNum->setMinimum( 2 );
	 ui.vertNum->setMaximum( 12 );
	 ui.vertNum->setValue( 5 );
	 ui.horNum->setMinimum( 5 );
	 ui.horNum->setMaximum( 21 );
	 ui.horNum->setValue( 9 );
	 ui.stepsNum->setMinimum( 0 );
	 ui.stepsNum->setMaximum( 99999 );
	 ui.stepsNum->setValue( 20 );
	 setWindowModality( Qt::WindowModal );
	 setFixedSize( width(), height() );

	 connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	 connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

int MapSizeDialog::GetHeight()
{
	return ui.vertNum->value();
}

int MapSizeDialog::GetWidth()
{
	return ui.horNum->value();
}

int MapSizeDialog::GetSteps()
{
	return ui.stepsNum->value();
}