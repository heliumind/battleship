#include "gui.h"
#include "ui_gui.h"



Gui::Gui(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::Gui)
{

    ui->setupUi(this);

    //initialize _map
    _map        = std::vector< std::vector<Button*> >(10, std::vector< Button* >(10));
    _enemmap    = std::vector< std::vector<Button*> >(10, std::vector< Button* >(10));

    setupFields();

    //initial server mode
    _server     = 0;
    _client     = 0;
    _connected  = 0;
    _yourturn   = 0;
    _setShipMode= 0;
    _shipCounter= 0;
    _gamerunning= 0;
    _readyToStart=0;
    _waitCoordinates=std::make_pair(-1, -1);
    _location =std::vector<std::pair<int, int>>(5);

    //connect mode buttons
    connect(ui->serverMode, SIGNAL(clicked()), this, SLOT(setServer()));
    connect(ui->clientMode, SIGNAL(clicked()), this, SLOT(setClient()));

    //connect network buttons
    connect(ui->client_connect, SIGNAL(clicked()), this, SLOT(connectclient()));
    connect(ui->server_search, SIGNAL(clicked()), this, SLOT(connectserver()));
    connect(ui->server_disconnect, SIGNAL(clicked()), this, SLOT(disconnectserver()));

    connect(ui->serverline, SIGNAL(returnPressed()), this, SLOT (connectserver()));
    connect(ui->portline, SIGNAL(returnPressed()), this, SLOT (connectserver()));

    //connect start button
    connect(ui->gameStart, SIGNAL(clicked()), this, SLOT(startButton()));
    ui->nt_status->append("Bitte den Modus einstellen.");


}

Gui::~Gui()
{
    delete ui;
}


void Gui::setupFields(){
    //setup enemy field
    for(int i=0; i<10; i++){ // row
        for(int j=0; j<10; j++){ // col

            Button* b1 = new Button(i, j);
            _enemmap[i][j] = b1;
            ui->enemyfield->addWidget(b1, i,j);
            connect(b1, &Button::clickedPos, this, &Gui::output);
            connect(b1, &Button::clickedPos, this, &Gui::getShoot);
        }
    }
    //setup playerfield
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){

            Button *b2 = new Button(i, j);
            _map[i][j] = b2;
            ui->field->addWidget(b2, i, j);
            connect(b2, &Button::clickedPos, this, &Gui::output);
            connect(b2, &Button::clickedPos, this, &Gui::getCoordinates);
         }
    }
}


void Gui::getError(position loc, int limit){

    bool flag1 = 0;
    bool flag2 = 0;
    bool flag3 = 0;
    bool flag4 = 0;
    int before= loc[0].first;
    int cons= loc[0].second;

     for(int i=0 ;i<limit; i++){
         if(loc[i].first!=before+i) flag1=1;
         if(loc[i].second!=cons)  flag1=1;
     }
     for(int i=0 ;i<limit; i++){
         if(loc[i].first!=before-i) flag2=1;
         if(loc[i].second!=cons)  flag2=1;
     }
     before= loc[0].second;
     cons= loc[0].first;
     for(int i=0 ;i<limit; i++){
         if(loc[i].second!=before+i) flag3=1;
         if(loc[i].first!=cons)     flag3=1;
     }
     for(int i=0 ;i<limit; i++){
         if(loc[i].second!=before-i) flag4=1;
         if(loc[i].first!=cons)     flag4=1;
     }
    if(flag1==0 || flag2==0 || flag3==0 || flag4==0) errorcheck=1;
    else errorcheck=0;
}

//counts fields of placed shipparts already placed
void Gui::getCoordinates(std::pair<int, int> point){
    if(_setShipMode){
        errorcheck=0;
        _waitCoordinates= point;

       switch (_shipnumber){

       case 0:  switch  (_shipCounter){
                case 0:
                        _location[_shipCounter]=_waitCoordinates;
                        _shipCounter++;
                        _map[point.first][point.second]->setFlat(1);
                        break;
                case 1: _location[_shipCounter]=_waitCoordinates;
                        _shipCounter++;
                       break;
                case 2: _location[_shipCounter]=_waitCoordinates;
                        _shipCounter++;
                       break;
                case 3: _location[_shipCounter]=_waitCoordinates;
                        _shipCounter++;
                       break;
                case 4: _location[_shipCounter]=_waitCoordinates;
                        _shipCounter=0;

                        getError(_location, 5);
                        if(errorcheck){
                            emit giveShip(_location);
                            for(int i=0; i<5; i++){
                                int x= _location[i].first;
                                int y= _location[i].second;
                                _map[x][y]->setStyleSheet("* { background-color: rgb(125,225,055) }");
                            }
                            ui->logic_status->append("Setze mittelhalbgroßes Schiff(4 Felder klicken)");
                            _shipnumber++;
                            errorcheck=0;
                        } else ui->logic_status->append("Error: Ship broken. Bitte erneut setzen.");
                        break;
                        default: ui->logic_status->append("Error.");
                }
                break;

       case 1:

       case 2:  switch  (_shipCounter){
           case 0:
              _location[_shipCounter]=_waitCoordinates;
              _shipCounter++;
              break;
           case 1: _location[_shipCounter]=_waitCoordinates;
              _shipCounter++;
             break;
           case 2: _location[_shipCounter]=_waitCoordinates;
              _shipCounter++;
             break;

           case 3: _location[_shipCounter]=_waitCoordinates;
              _shipCounter=0;
              getError(_location, 4);

              if(errorcheck){
                  emit giveShip(_location);
                  for(int i=0; i<4; i++){
                      int x= _location[i].first;
                      int y= _location[i].second;
                      _map[x][y]->setStyleSheet("* { background-color: rgb(125,225,055) }");
                  }
                  if(_shipnumber== 1) ui->logic_status->append("Setze mittelhalbgroßes Schiff(4 Felder klicken)");
                  else ui->logic_status->append("Setze mittelhalbgroßes Schiff(3 Felder klicken)");
                  _shipnumber++;
                  errorcheck=0;
              } else ui->logic_status->append("Error: Ship broken. Bitte erneut setzen.");
              break;
              default: ui->logic_status->append("Error.");
            } break;

       case 3:

       case 4:

       case 5:  switch  (_shipCounter){
           case 0:
              _location[_shipCounter]=_waitCoordinates;
              _shipCounter++;
              break;
           case 1: _location[_shipCounter]=_waitCoordinates;
              _shipCounter++;
             break;

           case 2: _location[_shipCounter]=_waitCoordinates;
              _shipCounter=0;
              getError(_location, 3);

              if(errorcheck){
                  emit giveShip(_location);
                  for(int i=0; i<3; i++){
                      int x= _location[i].first;
                      int y= _location[i].second;
                      _map[x][y]->setStyleSheet("* { background-color: rgb(125,225,055) }");   
                  }
                  if(_shipnumber< 5) ui->logic_status->append("Setze mittelhalbgroßes Schiff(3 Felder klicken)");
                  else ui->logic_status->append("Setze U-Boot(2 Felder klicken)");
                  _shipnumber++;
                  errorcheck=0;
              } else ui->logic_status->append("Error: Ship broken. Bitte erneut setzen.");
              break;
              default: ui->logic_status->append("Error.");
            } break;

       case 6:

       case 7:

       case 8:

       case 9: switch  (_shipCounter){
           case 0:
              _location[_shipCounter]=_waitCoordinates;
              _shipCounter++;
              break;

           case 1: _location[_shipCounter]=_waitCoordinates;
              _shipCounter=0;
              getError(_location, 2);

              if(errorcheck){
                  emit giveShip(_location);
                  for(int i=0; i<3; i++){
                      int x= _location[i].first;
                      int y= _location[i].second;
                      _map[x][y]->setStyleSheet("* { background-color: rgb(125,225,055) }");  
                  }
                  if(_shipnumber==9) ui->logic_status->append("Bereit um Spielstart. Drücke Start");
                  else ui->logic_status->append("Setze U-Boot(2 Felder klicken)");
                  _shipnumber++;
                  _readyToStart=1;
                  _gamerunning=0;
              } else ui->logic_status->append("Error: Ship broken. Bitte erneut setzen.");
              break;
              default: ui->logic_status->append("Error.");
            } break;
       case 10: ui->logic_status->append("Bereits alle Schiffe gesetzt.");
              break;

       default: ui->logic_status->append("Error.");
       }
    }
}

void Gui::output(std::pair<int, int> point){
//    ui->logic_status->append(QString::number(  point.first  ) + ", "+ QString::number(  point.second  )); //remove later//
}



void Gui::setServer(){
    if(_client==0 && _server==0){
        _server=1;
        QString name = ui->nameline->text();
        ui->nt_status->append("Gehe in Server Modus als " + name );
    }   else if(_client==1) ui->nt_status->append("Schon in Client Modus.");
}
void Gui::setClient(){
    if(_server==0 && _client==0){
        _client=1;
        QString name = ui->nameline->text();
        ui->nt_status->append("Gehe in Client Modus als " + name);
    }   else if(_server==1) ui->nt_status->append("Schon in Server Modus.");
}
void Gui::connectclient(){
    if(_client){
        if(_connected){

            //disconnect//
            _connected= 0;
            _yourturn   = 0;
            _setShipMode= 0;
            _shipCounter= 0;
            _gamerunning= 0;
            _readyToStart=0;
            for(int i=0; i<10; i++){ // row
                for(int j=0; j<10; j++){ // col
                    _map[i][j]->setStyleSheet("* { background-color: rgb(225,225,255) }");
                    _enemmap[i][j]->setStyleSheet("* { background-color: rgb(225,225,255) }");
                }
            }
            ui->nt_status->append("Client: Getrennt von Server");
        }   else {

            //connect//
            QString server  = ui->serverline->text();

            _connected= 1;
            ui->nt_status->append("Client: Verbunden mit Server " + server + " auf Port " + ui->portline->text());
        }
    }
}
void Gui::connectserver(){
    if(_server){
        if(!(_connected)){

            //connect//
            _connected=1;
            ui->nt_status->append("Server: Verbunden mit Client");
        }
    }
}
void Gui::disconnectserver(){
    if(_server){
        if(_connected){

            //disconnect//
            _connected=0;
            _yourturn   = 0;
            _setShipMode= 0;
            _shipCounter= 0;
            _gamerunning= 0;
            _readyToStart=0;
            for(int i=0; i<10; i++){ // row
                for(int j=0; j<10; j++){ // col
                    _map[i][j]->setStyleSheet("* { background-color: rgb(225,225,255) }");
                    _enemmap[i][j]->setStyleSheet("* { background-color: rgb(225,225,255) }");
                }
            }
            ui->nt_status->append("Client: Getrennt von Server");
        }
    }
}



void Gui::startButton(){

    if(_connected==0 || _gamerunning==1) {
        ui->logic_status->append("Gerade nicht moeglich.");
    }
    else {
        if(_readyToStart==0){

            _gamerunning=1;
            _setShipMode=1;
            _shipnumber= 0;
            _shipCounter= 0;
            ui->logic_status->append("Setze Schlachtschiff (5 Felder klicken)");

         }  else {
                _readyToStart=0;
                _setShipMode =0;
                _gamerunning=1;
                _yourturn=1;
                ui->logic_status->append("Spiel wird gestartet...");
            }
     }
}


void Gui::getShoot(std::pair<int, int> loc){
    if(_yourturn){
      emit giveShoot(loc);
      _yourturn=0;
    }
}

void Gui::getWin(bool win){
    _yourturn   = 0;
    _setShipMode= 0;
    _shipCounter= 0;
    _gamerunning= 0;
    _readyToStart=0;
    for(int i=0; i<10; i++){ // row
        for(int j=0; j<10; j++){ // col
            _map[i][j]->setStyleSheet("* { background-color: rgb(225,225,255) }");
            _enemmap[i][j]->setStyleSheet("* { background-color: rgb(225,225,255) }");
        }
    }
    if(win)
    ui->logic_status->append("YOU WIN");
    else
    ui->logic_status->append("YOU LOOSE");
}

void Gui::getUpdateField(std::pair<int, int> point, int flag, bool own)
{
    if(own){

        _yourturn=1;


        if(flag== -1){
            _map[point.first][point.second]->setStyleSheet("* { background-color: rgb(225,125,055) }");
            ui->logic_status->append("Gegnerischer Treffer (- . -) ");
        }
        if(flag== -2){
            _map[point.first][point.second]->setStyleSheet("* { background-color: rgb(025,125,255) }");
            ui->logic_status->append("Kein gegnerischer Treffer (^ o ^) ");
        }
        if(flag==-3) _map[point.first][point.second]->setStyleSheet("* { background-color: rgb(0,0,0) }");

    }   else{

            if(flag== -1){
                _enemmap[point.first][point.second]->setStyleSheet("* { background-color: rgb(225,125,055) }");
                ui->logic_status->append("Treffer (^ o ^) ");
            }
            if(flag== -2){
                _enemmap[point.first][point.second]->setStyleSheet("* { background-color: rgb(025,125,255) }");
                ui->logic_status->append("Kein Treffer (- . -) ");
            }
            if(flag==-3) _enemmap[point.first][point.second]->setStyleSheet("* { background-color: rgb(0,0,0) }");
        }
}
