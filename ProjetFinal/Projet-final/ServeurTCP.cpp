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
void ServeurTCP::depthMapEffect()
{
        int ndisparities = 256;
        int SADWindowSize = 21;


        cv::Mat frame0gray, frame1gray, dispbm, dispnorm_bm;
        cv::cvtColor(img1, frame0gray, CV_BGR2GRAY);
        cv::cvtColor(img2, frame1gray, CV_BGR2GRAY);
        cv::Ptr<cv::StereoBM> sbm = cv::StereoBM::create( ndisparities, SADWindowSize);
        double minVal, maxVal;
        sbm->setSpeckleRange(125);
        sbm->setSpeckleWindowSize(150);
        sbm->compute(frame0gray,frame1gray,dispbm);
        cv::minMaxLoc(dispbm, &minVal, &maxVal);
        dispbm.convertTo( dispnorm_bm, CV_8UC1, 255/(maxVal-minVal));
        cv::namedWindow( "Display window", cv::WINDOW_NORMAL );// Create a window for display.
        cv::imshow( "Display window", dispnorm_bm );

        //char* t = (char*)dispnorm_bm.at<uchar>(dispnorm_bm.size().width, dispnorm_bm.size().height);
        qDebug() << "height: " << dispnorm_bm.size().height/2 << ", width: " << dispnorm_bm.size().width/2 << ", pixelV:" << (int)dispnorm_bm.at<uchar>(dispnorm_bm.size().height/2,dispnorm_bm.size().width/2);
        int number= (int)dispnorm_bm.at<uchar>(dispnorm_bm.size().height/2,dispnorm_bm.size().width/2);
        std::stringstream strs;
        strs << number;
        std::string temp_str = strs.str();
        char const* pchar = temp_str.c_str();
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

    if( !filename.isNull() )
    {
      qDebug() << "selected file path : " << filename.toUtf8();
    }
    img1 = cv::imread(st, cv::IMREAD_COLOR);
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
        img2 = cv::imread(st, cv::IMREAD_COLOR);
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
    buttonDepthMap->setStatusTip("Depth Map");
    connect(buttonDepthMap,SIGNAL(clicked()), this, SLOT(depthMapEffect()));
    layout->addWidget(buttonDepthMap,2,2);

}




