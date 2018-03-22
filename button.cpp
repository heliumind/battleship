#include "button.h"

#include <QDebug>



Button::Button(  int x,  int y)
    : _point(std::make_pair(x, y))
{

    connect(this, &QPushButton::clicked, this, &Button::forwardClick);
}

//sending out coordinates
void Button::forwardClick(){

    emit Button::clickedPos(_point);
}
