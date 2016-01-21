#include "imageproc.hpp"
#include <vector>

ImageProc::ImageProc()
{

}
/**
 * @brief imgProc
 * @param color
 * @param img
 * @return The number of percentage of the color in the image
 */
double imgProc(Vec3b color,const cv::Mat& img){
    int bins = 256;             // number of bins
    float quant=0;               //quantity of pixels with that color
    int nc = img.channels();    // number of channels
    //vector<Mat> hist(1);        // array for storing the histograms
    vector<Mat> canvas(1);      // images for displaying the histogram
    int hmax[3] = {0,0,0};      // peak value for each histogram

    int sml=255,big=0;

    Mat output (2*img.rows,img.cols,CV_8UC3, Scalar(0,0,0));
    for (int i = 0; i < hist.size(); i++)
        hist[i] = Mat::zeros(1, bins, CV_32SC1);

    for (int i = 0; i < img.rows; i++){
        for (int j = 0; j < img.cols; j++){
                Vec3b intensity = img.at<Vec3b>(i,j);
                float dx,dy,dz,dist;
                output.at<Vec3b>(Point(j,i))=intensity;
                /*if(intensity.val[0]==color.val[0])quant+= 1;
                if(intensity.val[1]==color.val[1])quant+= 1;
                if(intensity.val[2]==color.val[2])quant+= 1;*/
                //Vec3b color1 (255,255,255);
                int aux=quant;
                //output.at<Vec3b>(Point(j,i))=color1;

                dx=pow(intensity[0]-color[0],2);
                dy=pow(intensity[1]-color[1],2);
                dz=pow(intensity[2]-color[2],2);
                dist=sqrt(dx+dy+dz);
                if(dist>0){
                    quant+=(1-(dist/441.7));
                    int aux=(int)255*(1-(dist/441.7));
                }else if(dist==0){
                    sml=aux;
                    //Vec3b color2 (255,255,255);
                    quant=1;
                    //output.at<Vec3b>(Point(j,img.rows+i))=color2;
                }else{
                    qDebug()>>"Bad at the distance";
                }
                if(j==0&&i==0){
                    cout<<"\n\n--"<<intensity<<color<<dx<<"|"<<dy<<"|"<<dz<<"|"<<dist;
                }
                if(dist>THRESHOLD){
                    Vec3b color2 (0,0,0);
                    output.at<Vec3b>(Point(j,img.rows+i))=color2;
                }else{
                    Vec3b color2 (255,255,255);
                    output.at<Vec3b>(Point(j,img.rows+i))=color2;
                }
                /*if(quant-aux==3){
                    Vec3b color2 (0,0,0);
                    output.at<Vec3b>(Point(j,i))=color2;
                }else if(quant-aux==2){
                    Vec3b color2 (60,60,60);
                    output.at<Vec3b>(Point(j,i))=color2;
                }else if(quant-aux==1){
                    Vec3b color2 (120,120,120);
                    output.at<Vec3b>(Point(j,i))=color2;
                }*/
        }
    }
   // cout <<"\nColor Distance:"<<"\n\tBiggest: "<<big<<"\n\tSmallest: "<<sml<<"\n";
    //cout<<"\nR:"<<quant<<"=\n";

    //addToRank(img,quant/(float)(img.rows*img.cols));

    /*for (int i = 0; i < nc; i++){
        for (int j = 0; j < bins-1; j++)
            hmax[i] = hist[i].at<int>(j) > hmax[i] ? hist[i].at<int>(j) : hmax[i];
    }
    const char* wname[3] = { "blue", "green", "red" };
    Scalar colors[3] = { Scalar(255,0,0), Scalar(0,255,0), Scalar(0,0,255) };

    for (int i = 0; i < nc; i++){
        canvas[i] = Mat::ones(125, bins, CV_8UC3);

        for (int j = 0, rows = canvas[i].rows; j < bins-1; j++){
            line(
                canvas[i],
                Point(j, rows),
                Point(j, rows - (hist[i].at<int>(j) * rows/hmax[i])),
                nc == 1 ? Scalar(200,200,200) : colors[i],
                1, 8, 0
            );
        }
        //imshow(nc == 1 ? "value" : wname[i], canvas[i]);
    }*/
    vector<int> compression_params;
    compression_params.push_back(9);
    string out_str="out/alpha_";
    stringstream aux2;

}
