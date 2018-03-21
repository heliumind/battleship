#include "gui.h"
#include "ui_gui.h"



Gui::Gui(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::Gui)
{

    ui->setupUi(this);

    //initialize _maps
    _map        = std::vector< std::vector<Button*> >(10, std::vector< Button* >(10));
    _enemmap    = std::vector< std::vector<Button*> >(10, std::vector< Button* >(10));
    _location =std::vector<std::pair<int, int>>(5);
    setupFields();


    //initialize variables
    _server     = 0;
    _client     = 0;
    _connected  = 0;
    _yourturn   = 0;
    _setShipMode= 0;
    _shipCounter= 0;
    _gamerunning= 0;
    _readyToStart=0;
    _waitCoordinates=std::make_pair(-1, -1);

    _4count=0;
    _3count=0;
    _2count=0;

    //initialize start buttons enabled
    ui->serverline->setEnabled(0);
    ui->portline->setEnabled(0);
    ui->client_connect->setEnabled(0);
    ui->server_disconnect->setEnabled(0);
    ui->gameStart->setEnabled(0);

    //connect mode buttons
    connect(ui->serverMode, SIGNAL(clicked()), this, SLOT(setServer()));
    connect(ui->clientMode, SIGNAL(clicked()), this, SLOT(setClient()));

    //connect network buttons
    connect(ui->client_connect, SIGNAL(clicked()), this, SLOT(connectclient()));
    connect(ui->server_disconnect, SIGNAL(clicked()), this, SLOT(disconnectserver()));

    //connect start button
    connect(ui->gameStart, SIGNAL(clicked()), this, SLOT(startButton()));

    //connect extra features
    connect(ui->chat_send, SIGNAL(clicked()), this, SLOT(chatButton()));
    _yourName = "Du";

    //start message
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
            //connect(b1, &Button::clickedPos, this, &Gui::output);
            connect(b1, &Button::clickedPos, this, &Gui::getShoot);
        }
    }
    //setup playerfield
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){

            Button *b2 = new Button(i, j);
            _map[i][j] = b2;
            ui->field->addWidget(b2, i, j);
            //connect(b2, &Button::clickedPos, this, &Gui::output);
            connect(b2, &Button::clickedPos, this, &Gui::getCoordinates);
         }
    }
}


void Gui::getError(position loc, int limit){

    std::vector<int> xvec(limit);
    std::vector<int> yvec(limit);
    for(int i=0; i<limit; i++){
        xvec.push_back(loc[i].first);
        yvec.push_back(loc[i].second);
    }
    std::sort(xvec.begin(), xvec.begin()+limit-1);
    std::sort(yvec.begin(), yvec.begin()+limit-1);
    bool flag1 = 0;
    bool flag2 = 0;
    int before= xvec[0];
    int cons=   yvec[0];

     for(int i=1 ;i<limit; i++){
         if(xvec[i] != before+i) flag1=1;
         if(yvec[i] != cons)  flag1=1;
     }

     before= yvec[0];
     cons=   yvec[0];
     for(int i=1 ;i<limit; i++){
         if(yvec[i] != before+i) flag2=1;
         if(xvec[i] != cons)     flag2=1;
     }

    if(flag1==0 || flag2==0) errorcheck=1;
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
                        _map[point.first][point.second]->setEnabled(0);
                        break;
                case 1: _location[_shipCounter]=_waitCoordinates;
               _map[point.first][point.second]->setEnabled(0);
                        _shipCounter++;
                       break;
                case 2: _location[_shipCounter]=_waitCoordinates;
               _map[point.first][point.second]->setEnabled(0);
                        _shipCounter++;
                       break;
                case 3: _location[_shipCounter]=_waitCoordinates;
               _map[point.first][point.second]->setEnabled(0);
                        _shipCounter++;
                       break;
                case 4: _location[_shipCounter]=_waitCoordinates;
               _map[point.first][point.second]->setEnabled(0);
                        _shipCounter=0;

                        getError(_location, 5);
                        if(errorcheck){
                            emit giveShip(_location);
                            for(int i=0; i<5; i++){
                                int x= _location[i].first;
                                int y= _location[i].second;
                                _map[x][y]->setStyleSheet("* { background-color: rgb(125,225,055) }");
                            }
                            ui->logic_status->append("Setze Kreuzer (4 Felder klicken)");
                            _shipnumber++;
                            errorcheck=0;
                        } else {
                            ui->logic_status->append("Error: Ship broken. Bitte erneut setzen.");
                            for(int i=0; i<5; i++){
                                _map[_location[i].first][_location[i].second]->setEnabled(1);
                            }
                        }
                        break;
                        default: ui->logic_status->append("Error.");
                }
                break;
       case 1:
       case 2:  switch  (_shipCounter){
           case 0:
               _location.clear();
              _location.push_back(_waitCoordinates);
              _map[point.first][point.second]->setEnabled(0);
              _shipCounter++;
              break;
           case 1: _location.push_back(_waitCoordinates);
               _map[point.first][point.second]->setEnabled(0);
              _shipCounter++;
             break;
           case 2: _location.push_back(_waitCoordinates);
               _map[point.first][point.second]->setEnabled(0);
              _shipCounter++;
             break;

           case 3: _location.push_back(_waitCoordinates);
               _map[point.first][point.second]->setEnabled(0);
              _shipCounter=0;
              getError(_location, 4);

              if(errorcheck){
                  emit giveShip(_location);
                  for(int i=0; i<4; i++){
                      int x= _location[i].first;
                      int y= _location[i].second;
                      _map[x][y]->setStyleSheet("* { background-color: rgb(125,225,055) }");
                  }
                  if(_shipnumber== 1) ui->logic_status->append("Setze Kreuzer (4 Felder klicken)");
                  else ui->logic_status->append("Setze Zerstörer (3 Felder klicken)");
                  _shipnumber++;
                  errorcheck=0;
              } else {
                  ui->logic_status->append("Error: Ship broken. Bitte erneut setzen.");
                  for(int i=0; i<4; i++){
                      _map[_location[i].first][_location[i].second]->setEnabled(1);
                  }
              }
              break;
              default: ui->logic_status->append("Error.");
            } break;
       case 3:
       case 4:
       case 5:  switch  (_shipCounter){
           case 0:
               _location.clear();
               _location.push_back(_waitCoordinates);
              _map[point.first][point.second]->setEnabled(0);
              _shipCounter++;
              break;
           case 1: _location.push_back(_waitCoordinates);
               _map[point.first][point.second]->setEnabled(0);
              _shipCounter++;
             break;

           case 2: _location.push_back(_waitCoordinates);
               _map[point.first][point.second]->setEnabled(0);
              _shipCounter=0;
              getError(_location, 3);

              if(errorcheck){
                  emit giveShip(_location);
                  for(int i=0; i<3; i++){
                      int x= _location[i].first;
                      int y= _location[i].second;
                      _map[x][y]->setStyleSheet("* { background-color: rgb(125,225,055) }");   
                  }
                  if(_shipnumber< 5) ui->logic_status->append("Setze Zerstörer (3 Felder klicken)");
                  else ui->logic_status->append("Setze U-Boot(2 Felder klicken)");
                  _shipnumber++;
                  errorcheck=0;
              } else {
                  ui->logic_status->append("Error: Ship broken. Bitte erneut setzen.");
                  for(int i=0; i<3; i++){
                      _map[_location[i].first][_location[i].second]->setEnabled(1);
                  }
              }
              break;
              default: ui->logic_status->append("Error.");
            } break;
       case 6:
       case 7:
       case 8:
       case 9: switch  (_shipCounter){
           case 0:
               _location.clear();
              _location.push_back(_waitCoordinates);
              _map[point.first][point.second]->setEnabled(0);
              _shipCounter++;
              break;

           case 1: _location.push_back(_waitCoordinates);
               _map[point.first][point.second]->setEnabled(0);
              _shipCounter=0;
              getError(_location, 2);

              if(errorcheck){
                  emit giveShip(_location);
                  for(int i=0; i<2; i++){
                      int x= _location[i].first;
                      int y= _location[i].second;
                      _map[x][y]->setStyleSheet("* { background-color: rgb(125,225,055) }");  
                  }
                  if(_shipnumber==9) ui->logic_status->append("Bereit für Spielstart. Drücke Start.");
                  else ui->logic_status->append("Setze U-Boot(2 Felder klicken)");
                  _shipnumber++;
                  _readyToStart=1;
                  _gamerunning=0;
              } else {
                  ui->logic_status->append("Error: Ship broken. Bitte erneut setzen.");
                  for(int i=0; i<2; i++){
                      _map[_location[i].first][_location[i].second]->setEnabled(1);
                  }
              }
              break;
              default: ui->logic_status->append("Error.");
            } break;
       case 10: ui->logic_status->append("Bereits alle Schiffe gesetzt.");
              break;
       default: ui->logic_status->append("Error.");
       }
    }
}

//void Gui::output(std::pair<int, int> point){
//    ui->logic_status->append(QString::number(  point.first  ) + ", "+ QString::number(  point.second  )); //remove later//
//}



void Gui::setServer(){
    if(_client==0 && _server==0){
        _server=1;

        _yourName = ui->nameline->text();
        ui->nt_status->append("Gehe in Server Modus als " + _yourName );
        ui->logic_status->append("Suche nach Spieler...");
        ui->serverMode->setEnabled(0);
        ui->clientMode->setEnabled(0);
        ui->nameline->setEnabled(0);
        ui->serverline->setEnabled(0);
        ui->portline->setEnabled(0);
        ui->client_connect->setEnabled(0);
        ui->server_disconnect->setEnabled(1);
        emit serverMode();
    }
}
void Gui::setClient(){
    if(_server==0 && _client==0){
        _client=1;

        _yourName = ui->nameline->text();
        ui->nt_status->append("Gehe in Client Modus als " + _yourName);
        ui->logic_status->append("Server und Client auswählen.");
        ui->serverMode->setEnabled(0);
        ui->clientMode->setEnabled(0);
        ui->nameline->setEnabled(0);
        ui->serverline->setEnabled(1);
        ui->portline->setEnabled(1);
        ui->client_connect->setEnabled(1);
        ui->server_disconnect->setEnabled(0);
        emit clientMode();
    }
}

void Gui::startButton(){

    if(_connected==0 || _gamerunning==1) {
        ui->logic_status->append("Gerade nicht möglich.");
    }
    else {
        if(_readyToStart==0){

            _gamerunning=1;
            _setShipMode=1;
            _shipnumber= 0;
            _shipCounter= 0;
            ui->logic_status->append("Beginne mit Plazierung der Schiffe.");
            ui->logic_status->append("Setze Schlachtschiff (5 Felder klicken)");

         }  else {
                _readyToStart=0;
                _setShipMode =0;
                _gamerunning=1;
                emit giveStart();
                ui->logic_status->append("Spiel wird gestartet...");
                ui->b50->setStyleSheet("* { background-color: rgb(025,225,055) }");
                ui->b40->setStyleSheet("* { background-color: rgb(025,225,055) }");
                ui->b41->setStyleSheet("* { background-color: rgb(025,225,055) }");
                ui->b30->setStyleSheet("* { background-color: rgb(025,225,055) }");
                ui->b31->setStyleSheet("* { background-color: rgb(025,225,055) }");
                ui->b32->setStyleSheet("* { background-color: rgb(025,225,055) }");
                ui->b20->setStyleSheet("* { background-color: rgb(025,225,055) }");
                ui->b21->setStyleSheet("* { background-color: rgb(025,225,055) }");
                ui->b22->setStyleSheet("* { background-color: rgb(025,225,055) }");
                ui->b23->setStyleSheet("* { background-color: rgb(025,225,055) }");
            }
     }
}

void Gui::connectclient(){
    if(_client){
        if(_connected){

            emit disconnectClient();
            _connected= 0;
            _yourturn   = 0;
            _setShipMode= 0;
            _shipCounter= 0;
            _gamerunning= 0;
            _readyToStart=0;
            for(int i=0; i<10; i++){ // row
                for(int j=0; j<10; j++){ // col
                    _map[i][j]->setStyleSheet("* { background-color: rgb(255,255,255) }");
                    _enemmap[i][j]->setStyleSheet("* { background-color: rgb(255,255,255) }");
                    _map[i][j]->setEnabled(1);
                    _enemmap[i][j]->setEnabled(1);
                }
            }
            ui->nt_status->append("Client: Getrennt von Server");
        }   else {

            QString server  = ui->serverline->text();
            int port = ui->portline->text().toShort();

            emit connectClient(server, port);
            ui->nt_status->append("Verbinde zum Server " + server + " auf Port " + ui->portline->text() +"...");
            ui->logic_status->append("Verbinde zum Server...");
        }
    }
}

void Gui::foundServer(){
    _connected= 1;
    ui->nt_status->append("Verbunden mit Server.");
    ui->gameStart->setEnabled(1);
    ui->logic_status->append("Bereit für Spielstart. Drücke Start.");
}

void Gui::foundClient(){
    _connected= 1;
    ui->gameStart->setEnabled(1);
    ui->nt_status->append("Spieler gefunden.");
    ui->logic_status->append("Bereit für Spielstart. Drücke Start.");
}

void Gui::disconnectserver(){
    if(_server){
        if(_connected){

            emit disconnectServer();
            _connected=0;
            _yourturn   = 0;
            _setShipMode= 0;
            _shipCounter= 0;
            _gamerunning= 0;
            _readyToStart=0;
            for(int i=0; i<10; i++){ // row
                for(int j=0; j<10; j++){ // col
                    _map[i][j]->setStyleSheet("* { background-color: rgb(255,255,255) }");
                    _enemmap[i][j]->setStyleSheet("* { background-color: rgb(255,255,255) }");
                    _map[i][j]->setEnabled(1);
                    _enemmap[i][j]->setEnabled(1);
                }
            }
            ui->nt_status->append("Server wir geschlossen.");
            ui->logic_status->append("Aktuelles Spiel wird beendet...");
        }
    }
}




void Gui::getShoot(std::pair<int, int> loc){
    if(_yourturn){
      emit giveShoot(loc);
      _yourturn=0;
      ui->logic_status->append("Schieße auf Feld "+ QString::number(loc.first)+", "+ QString::number(loc.second));
    } else ui->logic_status->append("Schuss nicht möglich. Nicht am Zug!");
}

void Gui::getYourTurn(bool turn){
    if(turn){
        ui->logic_status->append("DEIN ZUG!");
        _yourturn=1;
    }
}

void Gui::getWin(bool win){
    _yourturn   = 0;
    _setShipMode= 0;
    _shipCounter= 0;
    _readyToStart=0;

    if(win)
    ui->logic_status->append("DU GEWINNST \(^ 0 ^)/");
    else
    ui->logic_status->append("DU HAST VERLOREN (T . T)");
}

void Gui::getUpdateField(std::pair<int, int> point, int flag, bool own)
{
    ui->logic_status->append("Gegner schießt...");
    if(own){

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
            _enemmap[point.first][point.second]->setEnabled(0);

            if(flag== -1){
                _enemmap[point.first][point.second]->setStyleSheet("* { background-color: rgb(225,125,055) }");
                ui->logic_status->append("Treffer (^ _ ^) ");
            }
            if(flag== -2){
                _enemmap[point.first][point.second]->setStyleSheet("* { background-color: rgb(025,125,255) }");
                ui->logic_status->append("Kein Treffer (- . -) ");
            }
            if(flag==-3) _enemmap[point.first][point.second]->setStyleSheet("* { background-color: rgb(0,0,0) }");
        }
}

void Gui::getShipDestroyed(int target){
    ui->logic_status->append("Schiff zerstört!");
    switch(target){
    case 5: ui->b50->setStyleSheet("* { background-color: rgb(225,025,055) }");
            ui->b50->setEnabled(0);
        break;

    case 4: switch(_4count){
            case 0: ui->b40->setStyleSheet("* { background-color: rgb(225,025,055) }");
                    ui->b40->setEnabled(0);
                    _4count++;
                break;
            case 1: ui->b41->setStyleSheet("* { background-color: rgb(225,025,055) }");
                    ui->b41->setEnabled(0);
                    _4count++;
                break;
            default: ui->logic_status->append("Error: Schiff bereits zerstört.");
            }
        break;

    case 3: switch(_3count){
        case 0: ui->b30->setStyleSheet("* { background-color: rgb(225,025,055) }");
                ui->b30->setEnabled(0);
                _3count++;
            break;
        case 1: ui->b31->setStyleSheet("* { background-color: rgb(225,025,055) }");
                ui->b31->setEnabled(0);
                _3count++;
            break;
        case 2: ui->b32->setStyleSheet("* { background-color: rgb(225,025,055) }");
                ui->b32->setEnabled(0);
                _3count++;
            break;
        default: ui->logic_status->append("Error: Schiff bereits zerstört.");
        }
        break;

    case 2: switch(_2count){
        case 0: ui->b20->setStyleSheet("* { background-color: rgb(225,025,055) }");
                ui->b20->setEnabled(0);
                _2count++;
            break;
        case 1: ui->b21->setStyleSheet("* { background-color: rgb(225,025,055) }");
                ui->b21->setEnabled(0);
                _2count++;
            break;
        case 2: ui->b22->setStyleSheet("* { background-color: rgb(225,025,055) }");
                ui->b22->setEnabled(0);
                _2count++;
            break;
        case 3: ui->b23->setStyleSheet("* { background-color: rgb(225,025,055) }");
                ui->b23->setEnabled(0);
                _2count++;
            break;
        default: ui->logic_status->append("Error: Schiff bereits zerstört.");
        }
        break;

    default: ui->logic_status->append("Explosion Error.");
    }
}


void Gui::getChat(QString message){
    ui->chat_box->append("Gegner: " +message);
}

void Gui::chatButton(){
     QString message= ui->chat_line->text();
     ui->chat_box->append(_yourName +": " + message);
     emit giveChat(message);
}
