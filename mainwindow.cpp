#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "helper.h"
#include "mapsizedialog.h"
#include <vector>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QIcon>
#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    signalMapper( NULL ),
    ui( NULL )
{
  StartInit();

}

MainWindow::~MainWindow()
{
  delete toolMapper;
  Clear();
}

void MainWindow::Clear()
{
  if( signalMapper )
    delete signalMapper;
  delete ui->mainToolBar;
  delete ui;
}
void MainWindow::StartInit()
{
  ui = new Ui::MainWindow;
  ui->setupUi( this );
  LastChecked = NULL;
  lastToolClicked = NULL;
  curItemIndex = -1;
  tool_action = nothing;

  ui->mainToolBar->addWidget( ui->createFileButton );
  ui->mainToolBar->addWidget( ui->openFileButton );
  ui->mainToolBar->addWidget( ui->saveFileButton );
  ui->mainToolBar->addSeparator();

  toolMapper = new QSignalMapper( this );
  Helper * helper = Helper::Instance ();
  QPushButton * button = new QPushButton;
  button->setIcon( QIcon(":/cursor") );
  button->setCheckable( true );
  button->setFixedSize( 50, 50 );
  button->setIconSize( QSize(40, 40) );
  button->setObjectName( QString("cursor") );
  button->setFlat( true );
  connect( button, SIGNAL(clicked()), toolMapper, SLOT( map() ) ); 
  toolMapper->setMapping( button, button );
  ui->mainToolBar->addWidget( button );
  button = NULL;
	std::map< int, vector< state > > sequence;
	Helper::TBInitSequence( sequence );
	std::map< int, vector< state > >::const_iterator it;

	int last_key = -1;
	for( it = sequence.begin(); it != sequence.end(); ++it )
	{
		if( last_key != it->first )
		{
			last_key = it->first;
			ui->mainToolBar->addSeparator();
		}
		for( int i = 0; i < it->second.size(); ++i )
		{
			QPushButton * button = new QPushButton;
			QString fname = helper->GetItemNameByState( it->second[i] );
			button->setIcon( QIcon(":/" + fname ) );
			button->setCheckable( true );
			button->setFixedSize( 50, 50 );
			button->setIconSize(QSize(40, 40));
			button->setFlat( true );
			button->setObjectName( fname );
			connect( button, SIGNAL(clicked()), toolMapper, SLOT( map() ) ); 
			toolMapper->setMapping( button, button );
			ui->mainToolBar->addWidget( button );
			button = NULL;
		}
	}
  bool ret = connect(toolMapper, SIGNAL(mapped(QWidget*)),
    this, SLOT(ToolsClicked(QWidget*)));

  connect( ui->IsOriginal , SIGNAL(clicked()), this, SLOT(RBOriginalClicked() ) );
  connect( ui->IsActive   , SIGNAL(clicked()), this, SLOT(RBActiveClicked()   ) );
  connect( ui->IsBlock    , SIGNAL(clicked()), this, SLOT(RBBlockClicked()    ) );
  connect( ui->IsBomb     , SIGNAL(clicked()), this, SLOT(RBBombClicked()     ) );
  connect( ui->IsBunny    , SIGNAL(clicked()), this, SLOT(RBBunnyClicked()    ) );
  connect( ui->IsFire     , SIGNAL(clicked()), this, SLOT(RBFireClicked()     ) );
  connect( ui->IsMonster  , SIGNAL(clicked()), this, SLOT(RBMonsterClicked()  ) );
  connect( ui->IsStrong   , SIGNAL(clicked()), this, SLOT(RBStrongClicked()   ) );
  connect( ui->IsTeleport , SIGNAL(clicked()), this, SLOT(RBTeleportClicked() ) );
  connect( ui->Visible    , SIGNAL(clicked()), this, SLOT(CBVisibleClicked()  ) );
  connect( ui->Timer      , SIGNAL(valueChanged(int)), this, SLOT(SBTimerValueChanged( int )  ) );
  connect( ui->openFileButton, SIGNAL(clicked()), this, SLOT( OpenFileButtonClicked() ) );
  connect( ui->saveFileButton, SIGNAL(clicked()), this, SLOT( SaveFileButtonClicked() ) );
  connect( ui->createFileButton, SIGNAL(clicked()), this, SLOT( CreateFileButtonClicked() ) );

}

void MainWindow::Init()
{
  StartInit();
  plst.clear();
	SetupParamsDialog();
  plst.initArray( this );
  SetupWidgets ();
}

void MainWindow::Init( QString &filename )
{
  StartInit();
  plst.clear();
  plst.initArray( this, filename );
  SetupWidgets ();
}

void MainWindow::SetupParamsDialog()
{
	MapSizeDialog msd;
	if( msd.exec() == QDialog::Accepted )
	{
		plst.SetWidth( msd.GetWidth() );
		plst.SetHeight( msd.GetHeight() );
	}
	
}

void MainWindow::SetupWidgets ()
{
    signalMapper = new QSignalMapper( this );
    ui->gridLayout->setSpacing( 10 );
    ui->gridLayout->setHorizontalSpacing( 0 );
    ui->gridLayout->setMargin( 10 );
    QVBoxLayout * vertLayout  = NULL;
    QHBoxLayout * horLayout   = NULL;
    int col = 0;
    for( int i = 0; i < plst.GetWidth() * plst.GetHeight();  )
    {
      horLayout = new QHBoxLayout( this );
      ui->gridLayout->addLayout( horLayout, 0, col  );
      vertLayout = new QVBoxLayout();
      vertLayout->setSpacing( 1 );
			vertLayout->setAlignment( Qt::AlignVCenter );
      horLayout->addLayout( vertLayout );
			horLayout->setAlignment( Qt::AlignHCenter );
      int num = (col%2 == 0) ? plst.GetHeight()-1 : plst.GetHeight();
      if( num == plst.GetHeight()-1 )
        i++;
      for( int k = 0; k < num; k++, i++ )
      {
        int ind = (col+1)*plst.GetHeight() - (k + 1);
				cell * item = plst.getItem( ind );
        QPushButton * button = item->button;
        vertLayout->addWidget( button );
        
				connect( button, SIGNAL(clicked()), signalMapper, SLOT( map() ) ); 
        signalMapper->setMapping( button, button );
				
				item->UpdateView();
      }
      col++;
    }
    connect(signalMapper, SIGNAL(mapped(QWidget*)),
            this, SLOT(labelClicked(QWidget*)));
}

void MainWindow::ResetWidgets()
{
  Clear();
  Init();
}
void MainWindow::ResetWidgets( QString &filename )
{
  Clear();
  Init(filename);
}
void MainWindow::labelClicked( QWidget * wdg )
{
  QPushButton * button = dynamic_cast<QPushButton*>( wdg );
  if( tool_action == nothing )
  {
    button->setChecked( false );
    return;
  }
  if( button->isChecked() )
  {
    if( LastChecked )
      LastChecked->setChecked( false );
    LastChecked = button;
    curItemIndex = plst.GetButtonIndex( button );
    ui->Number->setText( QString::number( plst.getItem( curItemIndex )->index ) );
  }
  cell * item = plst.getItem( curItemIndex );
  ToolAction( item );
  item->UpdateView();
  UpdateControls();
}
void MainWindow::ToolAction( cell * item )
{
  state st;
  switch( tool_action )
  {
  case nothing:
  case cursor:
    return;
  case set_original : st = s_original ; break;
  case set_bunny    : st = s_bunny    ; break; 
  case set_active   : st = s_active   ; break;
  case set_bomb     : st = s_bomb     ; break;
  case set_fire     : st = s_fire     ; break;
  case set_block    : st = s_block    ; break;
  case set_strong   : st = s_strong   ; break;
  case set_teleport : st = s_teleport ; break;
  case set_monster  : st = s_monster  ; break;
	case set_visibility : st = s_invisible; break;
  }
	item->setState( st );
}

void MainWindow::ToolsClicked( QWidget * wdg )
{
  QPushButton * button = dynamic_cast<QPushButton*>(wdg);

  if( lastToolClicked == button )
  {
    lastToolClicked = NULL;
    tool_action = nothing;
    return;
  }
  else
  {
    if( lastToolClicked )
      lastToolClicked->setChecked( false );
    lastToolClicked = button;
    QString & objname = button->objectName();
    Helper * helper = Helper::Instance();
    if( objname == QString("cursor") )
      tool_action = cursor;
    else if( objname == helper->GetItemNameByState( s_original ) )
      tool_action = set_original;
    else if( objname == helper->GetItemNameByState( s_bunny ) )
      tool_action = set_bunny;
    else if( objname == helper->GetItemNameByState( s_active ) )
      tool_action = set_active;
    else if( objname == helper->GetItemNameByState( s_bomb ) )
      tool_action = set_bomb;
    else if( objname == helper->GetItemNameByState( s_fire ) )
      tool_action = set_fire;
    else if( objname == helper->GetItemNameByState( s_block ) )
      tool_action = set_block;
    else if( objname == helper->GetItemNameByState( s_strong ) )
      tool_action = set_strong;
    else if( objname == helper->GetItemNameByState( s_teleport ) )
      tool_action = set_teleport;
    else if( objname == helper->GetItemNameByState( s_monster ) )
      tool_action = set_monster;
		else if( objname == helper->GetItemNameByState( s_invisible ) )
			tool_action = set_visibility;
  }

};
void MainWindow::RBOriginalClicked(){   PropertiesLogic( s_original );  }
void MainWindow::RBActiveClicked()  {   PropertiesLogic( s_active   );  }
void MainWindow::RBBlockClicked()   {   PropertiesLogic( s_block    );  }
void MainWindow::RBBombClicked()    {   PropertiesLogic( s_bomb     );  }
void MainWindow::RBBunnyClicked()   {   PropertiesLogic( s_bunny    );  }
void MainWindow::RBFireClicked()    {   PropertiesLogic( s_fire     );  }
void MainWindow::RBMonsterClicked() {   PropertiesLogic( s_monster  );  }
void MainWindow::RBStrongClicked()  {   PropertiesLogic( s_strong   );  }
void MainWindow::RBTeleportClicked(){   PropertiesLogic( s_teleport );  }

void MainWindow::CBVisibleClicked()
{
  if( !LastChecked || curItemIndex < 0 )
    return;

  cell * item = plst.getItem( curItemIndex );
  item->isVisible = ui->Visible->isChecked();
  item->UpdateView();
}

void MainWindow::SBTimerValueChanged( int val )
{
  if( !LastChecked || curItemIndex < 0 )
    return;

  cell * item = plst.getItem( curItemIndex );
  if( item->hextype == s_bomb )
    item->timer = ui->Timer->value();
  item->UpdateView();
}

void MainWindow::OpenFileButtonClicked()
{
  QString filename = QFileDialog::getOpenFileName(
    this, 
    tr("Open File"),
    QDir::currentPath(),
    tr("plist (*.plist)"));
  if( !filename.isNull() )
    ResetWidgets( filename );
}

void MainWindow::CreateFileButtonClicked()
{
  ResetWidgets();
}

void MainWindow::SaveFileButtonClicked()
{
  QString filename = QFileDialog::getSaveFileName( 
    this, 
    tr("Save File"), 
    QDir::currentPath(), 
    tr("plist (*.plist)"));
  if( !filename.isNull() )
    plst.SaveInFile( filename );
}

void MainWindow::PropertiesLogic( state st )
{
  if( !LastChecked || curItemIndex < 0 )
    return;

  cell * item = plst.getItem( curItemIndex );
  if( item->hextype != st && item->hextype == s_bomb )
  {
    item->timer = -1;
    ui->Timer->setValue( -1 );
  }
  item->hextype = st;

  ui->Timer->setEnabled( st == s_bomb );

  item->UpdateView();
}

void MainWindow::UpdateControls()
{
  const cell * pcell = plst.getItem( curItemIndex );
  state hextype = pcell->hextype;
  ui->Visible->setChecked( pcell->isVisible );
  ui->Timer->setEnabled( hextype == s_bomb );
  ui->Timer->setValue( pcell->timer );
  switch( hextype )
  {
  case s_original : 
    ui->IsOriginal->setChecked( true );
    return;
  case s_bunny    : 
    ui->IsBunny->setChecked( true );
    return;
  case s_active   :
    ui->IsActive->setChecked( true );
    return;
  case s_bomb     : 
    ui->IsBomb->setChecked( true );
    return;
  case s_fire     : 
    ui->IsFire->setChecked( true );
    return;
  case s_block    : 
    ui->IsBlock->setChecked( true );
    return;
  case s_strong   : 
    ui->IsStrong->setChecked( true );
    return;
  case s_teleport : 
    ui->IsTeleport->setChecked( true );
    return;
  case s_monster  : 
    ui->IsMonster->setChecked( true );
    return;
  }
}
//ui->MapItems->currentIndex()
