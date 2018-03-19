#include "button.h"

#include <QDebug>



Button::Button(  int x,  int y)
    : _point(std::make_pair(x, y))
{

    connect(this, &QPushButton::clicked, this, &Button::forwardClick);
    _used=0;

}


void Button::forwardClick(){

    emit Button::clickedPos(_point);
  //  emit clickedPos(std::make_pair(0,0 ));

}
