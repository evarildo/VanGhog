
#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#define COLUMNS 4

using namespace cv;
using namespace std;
using namespace ASM;

/**
 * @brief MainWindow::MainWindow
 * @param parent
 * It creates the new window
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget->setVisible(false);
    ui->widget_2->setVisible(false);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openFolder_clicked()
{

}
/**
 * @brief MainWindow::swapWidgets
 * @param widgetA The reference to the first Widget.
 * @param widgetB The reference to the second Widget.
 * It exchanges two widgets positions.
 */
void MainWindow::swapWidgets(QWidget *widgetA, QWidget *widgetB)
{
    int indexA = ui->gridLayout->indexOf(widgetA);
    int indexB = ui->gridLayout->indexOf(widgetB);
    int row1, column1, rowSpan1, columnSpan1;
    int row2, column2, rowSpan2, columnSpan2;

    ui->gridLayout->getItemPosition(indexA, &row1, &column1, &rowSpan1, &columnSpan1);
    ui->gridLayout->getItemPosition(indexB, &row2, &column2, &rowSpan2, &columnSpan2);

    ui->gridLayout->takeAt(indexA);
    ui->gridLayout->takeAt(indexB);

    ui->gridLayout->addWidget(widgetB, row1, column1, rowSpan1, columnSpan1);
    ui->gridLayout->addWidget(widgetA, row2, column2, rowSpan2, columnSpan2);
}

/**
 * @brief MainWindow::on_action_Open_Folder_triggered
 * Executed when the OpenFolder command is trggered.
 */
void MainWindow::on_action_Open_Folder_triggered()
{
    QButtonGroup *open =new QButtonGroup;
    QGridLayout *layout=new QGridLayout;
    QFileDialog::Options options;
    QString str_dir = QFileDialog::getExistingDirectory(this,
                                                    tr("Open Directory"),
                                                    "/home/lucas/Desktop/Van Ghog",
                                                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    qDebug()<< str_dir.toLatin1().data();

    //Display images in the grid
    struct dirent *ent;
    DIR *dir;
    QString img_dir;
    dir=opendir(str_dir.toLatin1().data());
    int i=0;
    if ((dir != NULL)){
        //deactivate button
        /*QPixmap img;
        img.load("/home/lucas/Desktop/Van Ghog/img/200 Amazing Vincent Van Gogh Artworks [Up to 7500 Px] [Set 2]/29.jpg");
        ui->setupUi(this);
        ui->cont->setPixmap(img);*/

        while ((ent = readdir (dir)) != NULL){
            qDebug() <<"\n-" << ent->d_name;

            if((strcmp(ent->d_name,".")!=0)&&(strcmp(ent->d_name,"..")!=0)){
                //checkImg(img_dir,color);
                //create item on list

                QString imgPath= str_dir+"/"+QString::fromLatin1(ent->d_name);
                qDebug()<<imgPath;
                QPixmap img_disp;
                Mat img_orig;
                img_orig=imread(imgPath.toLatin1().data());

                img_disp=cvMatToQPixmap(img_orig);

                imageData* tmp=new imageData(img_orig,new QLabel(),i);

                tmp->container->setFixedSize(200,200);
                ui->gridLayout->addWidget(tmp->container,(i/COLUMNS),i%COLUMNS);
                qDebug()<<((i/COLUMNS)-1) +(i%COLUMNS);

                tmp->container->setPixmap(img_disp.scaled(tmp->container->size(),Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation));

                imageList.push_back(tmp);
                i++;
            }
        }
        closedir(dir);
    }else{
        qDebug()<<"Failed to read directory";
    }
    //Create the color picker
    ui->widget->setVisible(true);
}

/**
 * @brief merge_sort
 * @param data
 * @return
 * Function to sort out the images processing each one
 */
vector<int> merge_sort(vector<int> &data){
    if (data.size() <= 1) {
        return data;
    }

    int middle = data.size() / 2;
    vector<int> left(data.begin(), data.begin()+middle);
    vector<int> right(data.begin()+middle, data.end());

    left = merge_sort(left);
    right = merge_sort(right);

    vector<int> result(data.size());
    merge(left.begin(), left.end(),
               right.begin(), right.end(),
               result.begin());

    return result;
}
/**
 * @brief MainWindow::setColor
 * @param color
 * @return
 */
Vec3b MainWindow::setColor(QString color){
    Vec3b ret;
    unsigned int x;
    unsigned char y;
    stringstream ss;

    //cout<<color.size();
    if(color.size()==6){
       //cout<<color.substr(0,2);
        for (int i = 0; i < 3; ++i) {
            //ss<<hex<< color.substr(i*2,2);
            ss>>x;
            ss>>y;

            if(x<256){
                //cout<<"\n|";
                y=(unsigned char)x;
                ret[2-i]=y;
            }else{
                cout<<"Input color in wrong format!\n";
            }
            //cout<<"\n--"<<x<<"--"<<(int)y;
        }
        //cout<<"~.."<<ret[0]<<" "<<ret[1]<<" "<<ret[2];
        return ret;
    }else{
        printf("Input color in wrong format!\n");
        //return NULL;
    }
}


/**
 * @brief MainWindow::on_pushButton_clicked
 * When the std
 */
void MainWindow::on_pushButton_clicked()
{
    //get text from Text Box
    QString hex=ui->textEdit->toPlainText();
    qDebug()<<hex<<endl;

    if(isHex(hex)){//check if the color hex is valid
        ui->widget_2->setVisible(true);

        //analyze all images in the list
        analyze(toVec3b(hex));

        //order images

        std::list<imageData*>::iterator it=imageList.begin();
        std::list<imageData*>::iterator it2=it++;
        std::swap(*it,*it2);//swap structure item
        swapWidgets((*it)->container,(*it2)->container);//swap images at the display


        std::list<imageData*>::iterator iterator;
        for (iterator = imageList.begin(); iterator != imageList.end(); ++iterator) {
            //qDebug() << (*iterator)->value;
        }
    } else{//if the color hex string is not valid

    }
}

void MainWindow::analyze(Vec3b color){
    std::list<imageData*>::iterator iterator;
    qDebug()<<color[0]<<" "<<color[1]<<" "<<color[2]<<endl;
    for (iterator = imageList.begin(); iterator != imageList.end(); ++iterator) {
        (*iterator)->value=imgProc(color,(*iterator)->img);
    }
}

void MainWindow::on_textEdit_textChanged()
{
    if(ui->textEdit->toPlainText().length()>6){
        ui->textEdit->textCursor().deletePreviousChar();
    }
    int length=ui->textEdit->toPlainText().length();

    String str_color=ui->textEdit->toPlainText().toUtf8().constData();
    if(length==3){
     /*for (int i = 0; i < 3; ++i){
            str.clear();
            if(str_color.at(i)<='f'){
                str+=str_color.at(i)+=str_color.at(i);
            }else{
                return output;
            }
            int val;
            cout <<"\n**"<<str;
            std::stringstream ss;
            ss<<str;
            ss >> std::hex >> val;
            output[2-i]=val;
        }*/
    }
    if(length==6){
       /* for (int i = 0; i < 3; ++i) {
            str.clear();
            if(str_color.at(2*i)<='f'&& str_color.at(1+2*i)<='f'){
                str.append(1u,str_color.at(2*i));
                str.append(1u,str_color.at(1+2*i));
            }else{
                return output;
            }
            int val;
            //cout <<"\nHEX:"<<str;
            std::stringstream ss;
            ss<<str;
            ss >> std::hex >> val;
            output[2-i]=val;
            //cout <<"\nDEC:"<<val;
        }*/
    }

}
