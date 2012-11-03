#ifndef __PLIST_H__
#define __PLIST_H__
#pragma once
#include <map>
#include "helper.h"
#include <QPushButton>
#include <QtXml/QXmlDefaultHandler>
#include <QMainWindow>
#include <QFile>
using std::map;

class cell
{
public:
  cell( int ind, state htype = s_original, int tmr = -1, bool vsbl = true );
  ~cell();

  void setState( state ht );
  void UpdateView();
  void initButton( QMainWindow * mWnd );
  bool Serialize( QTextStream * out, int &level );
public:
  state hextype;
  int   timer;
  int   index;
  bool  isVisible;

  QPushButton * button;
};

class parametres
{
public:
  parametres();
  bool Serialize( QTextStream * out, int &level );
public:
  int horizontalNumber;
  int verticalNumber;
};

;

class plist
{
public:
  plist(void);
  ~plist(void);

  void initArray( QMainWindow * mWnd = NULL );
  void initArray( QMainWindow * mWnd, QString &filename );
  //void initArray( QString &filename, QMainWindow * mWnd = NULL );
  cell * getItem( int index );
  void addItem( cell * pcell );
  int GetButtonIndex( QPushButton * button );
  bool Serialize( QTextStream * out, int &level );
  bool SaveInFile( QString filename );
  void clear();
private:
  map< int, cell* > arr;
  parametres params;
};

#endif