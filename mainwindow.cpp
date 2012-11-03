#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "helper.h"
#include <vector>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QIcon>
#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>

QStandardItem * GetStandardItemImage( QString & filename )
{
  QStandardItem * imageitem = new QStandardItem();
  imageitem->setText( filename);
  QImage image( ":/" + filename ); 
  imageitem->setIcon ( 
    QIcon( 
    QPixmap::fromImage( image.scaled( QSize( 104, 104 ), Qt::KeepAspectRatio, Qt::SmoothTransformation ) )
    ) 
    );
  return imageitem;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    signalMapper( NULL ),
    ui( NULL )
{
  StartInit();

}

MainWindow::~MainWindow()
{
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
  curItemIndex = -1;

  ui->mainToolBar->addWidget( ui->createFileButton );
  ui->mainToolBar->addWidget( ui->openFileButton );
  ui->mainToolBar->addWidget( ui->saveFileButton );
  ui->mainToolBar->addSeparator();

  Helper * helper = Helper::Instance ();
  pNamesVector names = helper->GetItemNames ();
  QPushButton * button = new QPushButton;
  button->setIcon( QIcon(":/cursor") );
  button->setCheckable( true );
  button->setFixedSize( 50, 50 );
  button->setIconSize(QSize(40, 40));
  button->setFlat( true );
  ui->mainToolBar->addWidget( button );
  button = NULL;
  for( size_t i = 0; i < names->size(); i++ )
  {
    QPushButton * button = new QPushButton;
    button->setIcon( QIcon(":/" + (*names)[i]) );
    button->setCheckable( true );
    button->setFixedSize( 50, 50 );
    button->setIconSize(QSize(40, 40));
    button->setFlat( true );
    ui->mainToolBar->addWidget( button );
    button = NULL;
  }

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
  //todo: dialog mapsize
  StartInit();
  plst.clear();
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
void MainWindow::SetupWidgets ()
{
    QStandardItemModel * model = new QStandardItemModel(this);
    ui->MapItems->setModel ( model );
    Helper * helper = Helper::Instance ();
    pNamesVector names = helper->GetItemNames ();
    model->appendRow( GetStandardItemImage( QString("cursor") ) );
    for( size_t i = 0; i < names->size(); i++ )
    {
        model->appendRow( GetStandardItemImage( (*names)[i] ) );
    }
    signalMapper = new QSignalMapper( this );
    ui->gridLayout->setSpacing( 10 );
    ui->gridLayout->setHorizontalSpacing( 0 );
    ui->gridLayout->setMargin( 10 );
    QVBoxLayout * vertLayout  = NULL;
    QHBoxLayout * horLayout   = NULL;
    int col = 0;
    for( int i = 0; i < 45;  )
    {
      horLayout = new QHBoxLayout( this );
      ui->gridLayout->addLayout( horLayout, 0, col  );
      vertLayout = new QVBoxLayout();
      vertLayout->setSpacing( 10 );
      horLayout->addLayout( vertLayout );
      int num = (col%2 == 0) ? 4 : 5;
      if( num == 4 )
        i++;
      for( int k = 0; k < num; k++, i++ )
      {
        int ind = (col+1)*5 - (k + 1);
        QPushButton * button = plst.getItem( ind )->button;
        vertLayout->addWidget( button );
        connect( button, SIGNAL(clicked()), signalMapper, SLOT( map() ) ); 
        signalMapper->setMapping( button, button );
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
  QModelIndex index = ui->MapItems->currentIndex();
  //QMessageBox::information(this, "debug" , QString::number( index.row() ), QMessageBox::Ok);
  QPushButton * button = dynamic_cast<QPushButton*>( wdg );
  if( button->isChecked() )
  {
    if( LastChecked )
      LastChecked->setChecked( false );
    LastChecked = button;
    curItemIndex = plst.GetButtonIndex( button );
    ui->Number->setText( QString::number( plst.getItem( curItemIndex )->index ) );
  }
  if( index.row() != 0 )
  {
    
    Helper * helper = Helper::Instance();
    pNamesVector vect = helper->GetItemNames();
    cell * item = plst.getItem( curItemIndex );
    item->setState( helper->GetStateByItemName((*vect)[index.row()-1]) );
    item->UpdateView();
    //button->setIcon( QIcon( ":/" + (*vect)[index.row()-1] ) );
  }
  UpdateControls();
}

void MainWindow::ToolsClicked(){ };
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
