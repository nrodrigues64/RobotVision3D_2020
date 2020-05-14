#include "ServeurTCP.h"

//Constructeur de ServeurTCP
ServeurTCP::ServeurTCP(QWidget *parent)
    : QMainWindow(parent)
{

    QWidget *win;
    win = new QWidget;
    win->setWindowTitle("Stéréo");
    this->setCentralWidget(win);

    //Le serveur écoute n'importe quel IP entrante sur le port 4242
    _server.listen(QHostAddress::Any, 4242);

    //Connecte au signal NewConnetion() le slot onNewConnection(), à chaque nouvelle connection la fonction onNewConnection est appelé.
    connect(&_server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
    createActions();
    win->setLayout(layout);
    win->show();
}

//Destructeur ServeurTCP
ServeurTCP::~ServeurTCP()
{
}

//Slot appelé quand une connection est détectée
void ServeurTCP::onNewConnection()
{

   socket = _server.nextPendingConnection();
   //Connecte le signal readyRead() à la fonction tcpReady(), quand le serveur reçoit quelque chose du client, appelle la fonction tcpReady()
   connect(socket, SIGNAL(readyRead()), this, SLOT(tcpReady()));
   qDebug() << socket->peerAddress().toString() << " connected to server !\n";
}

//Slot appelé quand un message du client est reçu
void ServeurTCP::tcpReady()
{
    socket->write("reçu");
    /*qDebug() << dataSize;
    if( dataSize == 0 )
    {
        qDebug() << "Test1";
        QDataStream stream( socket );
        stream.setVersion( QDataStream::Qt_4_8 );

        if( socket->bytesAvailable() < sizeof(quint32) ){
            qDebug() << "Test2";
            return;
        }
        stream >> dataSize;
        qDebug() << dataSize;
    }

    if( dataSize > socket->bytesAvailable() ) {
        qDebug() << socket->bytesAvailable();
        return;
    }
    QByteArray array = socket->read( dataSize );
    QBuffer buffer(&array);
    buffer.open( QIODevice::ReadOnly );

    QImageReader reader(&buffer, "PNG");
    qDebug() << reader.read();
    QImage image = reader.read();

    if( !image.isNull() )
    {
        image.save("D:/temp1");
    }
    else
    {
        qDebug()<<"Invalid image received!";
    }*/
}

//Fonction qui calcul la DepthMap et renvoie au client la valeur du pixel central
void ServeurTCP::getPixel()
{
        std::stringstream strs;
        strs << si.getCenterPixel();
        std::string temp_str = strs.str();
        char const* pchar = temp_str.c_str();
        if(socket->state() == QTcpSocket::ConnectedState)
            socket->write(pchar);
}

//Slot qui permet d'ajouter l'image gauche (à supprimer plus tard)
void ServeurTCP::openFileL()
{


    QString filename =  QFileDialog::getOpenFileName(
          this,
          "Open Image",
          "C:/Users/Nicolas/Pictures",
          "Image Files (*.png *.jpg *.bmp *.jpeg *.gif)");
    std::string st = filename.toUtf8().constData();

    if( filename.isNull() )
    {
        qDebug() << "error" << filename;
    } else {
        qDebug() << "selected file path : " << filename.toUtf8();
        imgL = cv::imread(st, cv::IMREAD_COLOR);
    }
    if(!imgL.empty() && !imgR.empty())
    {
        si = StereoImage(imgL,imgR);
        imgL = cv::Mat();
        imgR = cv::Mat();
    }
}
//Slot qui permet d'ajouter l'image droite (à supprimer plus tard)
void ServeurTCP::openFileR()
{


    QString filename =  QFileDialog::getOpenFileName(
          this,
          "Open Image",
          "../.",
          "Image Files (*.png *.jpg *.bmp *.jpeg *.gif)");

    std::string st = filename.toUtf8().constData();

    if( filename.isNull() )
    {
      qDebug() << "error" << filename;
    } else {
        qDebug() << "selected file path : " << filename.toUtf8();
        imgR = cv::imread(st, cv::IMREAD_COLOR);
    }
    if(!imgL.empty() && !imgR.empty())
    {
        si = StereoImage(imgL,imgR);
        imgL = cv::Mat();
        imgR = cv::Mat();
    }
}

//Initialise les boutons sur la fenêtre (à supprimer sûrement aussi)
void ServeurTCP::createActions()
{
    buttonLeft->setStatusTip(tr("Open Left Img"));
    connect(buttonLeft,SIGNAL(clicked()), this, SLOT(openFileL()));
    layout->addWidget(buttonLeft,0,2);
    buttonRight->setStatusTip(tr("Open Right Img"));
    connect(buttonRight,SIGNAL(clicked()), this, SLOT(openFileR()));
    layout->addWidget(buttonRight,1,2);
    buttonDepthMap->setStatusTip("Get center pixel");
    connect(buttonDepthMap,SIGNAL(clicked()), this, SLOT(depthMapEffect()));
    layout->addWidget(buttonDepthMap,2,2);

}




