#include <opencv2/opencv.hpp>
#include <opencv2\imgproc\types_c.h>
#include <iostream>
#include <math.h>

void  Get_line_LMR(uint16_t enter_Image_H, uint16_t enter_Image_W);
using namespace std;
using namespace cv;

Mat src, hsv, hue, meblur_ima, dst_ima, gray_src, backPrjImage, mop_ima, not_ima;
Mat process_image;
struct coordinate
{
    float x[1024];
    float y[1024];
};

coordinate Left_line; //左边线列坐标 枚举 存左边线数组用
coordinate Right_line;//右边线列坐标 枚举 存右边线数组用
coordinate Midd_line; //中线列坐标   枚举 存中线数组用


int bins = 3;
void Hist_And_Backprojection(int, void*);
int main(int argc, char** argv) {
    src = imread("road_test/straight.jpg");
	if (src.empty()) {
		printf("could not load image...\n");
		while(!(waitKey(500) == 27));
		return -1;
	}

	namedWindow("input", 1);
    imshow("input",src);

    // // 中值模糊
    // medianBlur(src, meblur_ima, 11);
    // namedWindow("meblur_ima", 1);
    // imshow("meblur_ima",meblur_ima);


    cvtColor(src, gray_src, CV_BGR2GRAY);
    threshold(gray_src, process_image, 0, 255, THRESH_OTSU);  // 自动阈值


    // cvtColor(meblur_ima, hsv, CV_BGR2HSV);
	// hue.create(hsv.size(), hsv.depth());
	// int nchannels[] = { 0, 0 };
	// mixChannels(&hsv, 1, &hue, 1, nchannels, 1);

	// createTrackbar("Histogram Bins:", "BackProj", &bins, 180, Hist_And_Backprojection);
	// Hist_And_Backprojection(0, 0);  // 获得 backPrjImage 的二值化图像

    // namedWindow("backPrjImage", 1);
    // imshow("backPrjImage",backPrjImage);

    // not_ima = Mat::zeros(backPrjImage.size(), backPrjImage.type());
    // bitwise_not(backPrjImage,not_ima);   // 直接图片反转

    /*
    CV_MOP_OPEN/ CV_MOP_CLOSE/ CV_MOP_GRADIENT / 
    CV_MOP_TOPHAT/ CV_MOP_BLACKHAT 形态学操作类型
    */
    // Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1,-1));
    // morphologyEx(backPrjImage, process_image, 1, kernel);

    // namedWindow("process_image", 1);
    // imshow("process_image",process_image);

    // imwrite("road_test/straight.jpg", process_image);


    printf("input image channels:%d\n", process_image.channels());
    printf("input image rows:%d\n", process_image.rows);
    printf("input image cols:%d\n", process_image.cols);


	uint16_t height = process_image.rows;
	uint16_t width = process_image.cols;
    Get_line_LMR( process_image.rows,  process_image.cols);
	for (int row = 0; row < height; row++) {
		process_image.at<uchar>(row, Left_line.x[row]+10) = 0;
		process_image.at<uchar>(row, Right_line.x[row]-10) = 0;
		process_image.at<uchar>(row, Midd_line.x[row]) = 0;

        process_image.at<uchar>(row, Left_line.x[row]+11) = 0;
		process_image.at<uchar>(row, Right_line.x[row]-11) = 0;
		process_image.at<uchar>(row, Midd_line.x[row]-1) = 0;

        process_image.at<uchar>(row, Left_line.x[row]+9) = 0;
		process_image.at<uchar>(row, Right_line.x[row]-9) = 0;
		process_image.at<uchar>(row, Midd_line.x[row]+1) = 0;
	}
	namedWindow("process_image",1);
	imshow("process_image", process_image);

	waitKey(0);
	return 0;
}

void Hist_And_Backprojection(int, void*) {
	float range[] = { 0, 180 };
	const float *histRanges = { range };
	Mat h_hist;
	calcHist(&hue, 1, 0, Mat(), h_hist, 1, &bins, &histRanges, true, false);
	normalize(h_hist, h_hist, 0, 255, NORM_MINMAX, -1, Mat());

	calcBackProject(&hue, 1, 0, h_hist, backPrjImage, &histRanges, 1, true);
	imshow("BackProj", backPrjImage);

	return;
}

























  



void  Get_line_LMR(uint16_t enter_Image_H, uint16_t enter_Image_W)
{

    #define Image_H   enter_Image_H
    #define Image_W   enter_Image_W
    uint8_t binary_img[enter_Image_H][enter_Image_W];//二值化后的图像数组

    /*************************以下为用于巡迹的相关全局变量*************************/ 
    uint8_t Left_line_lost[Image_H+100]; //存储对应行左边线的 搜索情况，1 为丢，未找到
    uint8_t Right_line_lost[Image_H+100];//存储对应行右边线的 搜索情况，1 为丢，未找到
    uint8_t Found_left_flag,Found_right_flag;//该行左、右边线黑点寻找标志位 1为找到
    uint8_t Cross_road_flag;//十字 标志位

    int16_t L_lost_cnt = 0,R_lost_cnt = 0;//左、右丢单边线（点）次数  
    int16_t L_R_lost_cnt,Cross_road_cnt;//左右同时丢边线（点）次数  十字丢线次数，有别双边丢线次数
    int16_t Row_begging = Image_H-1,Row_end = 0,Last_row_end,Column_end;//扫线 起始行 结束行  上一次扫线结束行 结束列（起始列）
    int16_t L_last_lost_row = Image_H-1,R_last_lost_row = Image_H-1;//左、右边最后丢的线的行数
    int16_t L_R_lost_row = Image_H-1;//十字行数
    int16_t Last_mid_line = Image_W/2;//最后的 中点的行数
    int16_t row = Image_H-1;//行数
    int16_t Row_start =Image_H-1;//扫线起始行;

    int16_t scanf_range = Image_W/20;

    float Middle_line = Image_W/2;//图像中线  可改动
    float Left_slope = 0; //左边线  延伸斜率
    float Right_slope = 0;//右边线 延伸斜率
    float Last_left_slope = 0; //上一场图像的左边线斜率
    float Last_right_slope = 0;//上一场图像的右边线斜率

    int16_t First_row;
    int16_t Last_row;

    float Single_L_line[Image_H] = {
                                    74,72,70,68,66,64,63,61,59,57, 
                                    55,54,52,51,49,47,46,44,43,41,
                                    40,38,37,36,34,33,32,30,29,28,
                                    27,25,24,23,22
                            };
    float Single_R_line[Image_H] = {
                                    99 ,101,103,105,107,109,111,112,114,116,
                                    118,119,121,123,124,126,128,129,131,132,
                                    133,135,137,138,140,141,142,144,145,146,
                                    148,149,150,152,153
                                };
    /*************************以上为用于巡迹的相关全局变量*************************/ 


    uint8_t Get_L_near_slope_flag = 0;//本场图像是否有尝试进行近处边线斜率的计算获取  以丢线前面几行为基准求斜率
    uint8_t Get_R_near_slope_flag = 0;//本场图像是否有尝试进行近处边线斜率的计算获取  以丢线前面几行为基准求斜率
    uint8_t Vertical_search_flag = 0;//纵向搜索标志位
    uint8_t Fill_line_flag = 0;//是否可以进行单边或十字补线标志位  
    uint8_t L_line_lost_flag = 0;//右 丢线标志位  辅助记录最先丢线的行
    uint8_t R_line_lost_flag = 0;//左 丢线标志位  辅助记录最先丢线的行
    uint8_t L_fir_line_flag = 0;//左 丢线标志位  辅助记录最先找到的行
    uint8_t R_fir_line_flag = 0;//右 丢线标志位  辅助记录最先找到的行
    uint8_t L_R_line_lost_flag = 0;//左右边线同时丢线标志位  辅助记录最先丢线的行
    uint8_t Vertical_find_left_flag = 0;//纵向搜索往前推几行后是否有找着左边界 默认0为未找着，0未找着则纵向搜索斜率沿用上一场图像斜率
    uint8_t Vertical_find_right_flag = 0;//纵向搜索往前推几行后是否有找着右边界 默认0为未找着，0未找着则纵向搜索斜率沿用上一场图像斜率

    uint8_t L_near_slope_flag  = 0;//是否有根据小车前面几行边界线求出左边界斜率 1为有
    uint8_t R_near_slope_flag  = 0;//是否有根据小车前面几行边界线求出右边界斜率 1为有
    int16_t L_earliest_lost_row = 0,R_earliest_lost_row = 0,L_R_earliest_lost_row = 0;//左、右边最早丢的行数
    int16_t Left_end = 0;//每场图像扫线时 左边界限制列数
    int16_t Right_end = Image_W-1;//每场图像扫线时 右边界限制列数
    int16_t i=Image_H-1,j = (int16_t)Middle_line;
    int16_t Left_start = Last_mid_line,Right_start = Last_mid_line;//初始化左右扫线起始列 起始为上一场图像中线
    int16_t Vertical_row_1 = Image_H-1;//纵向搜索最远端黑点所在的行
    int16_t Vertical_longest_length_1 = 0;//纵向搜索长度（最远端）
    int16_t Vertical_length = Image_H-1;//纵向搜索长度 
    int16_t Vertical_longest_length_2 = Image_H-1;//纵向搜索长度  用来比较
    int16_t Vertical_column_1 = Image_W/2;//纵向搜索记录到到最远端的 行数 列数
    int16_t Vertical_column_2 = Image_W/2;
    int16_t Vertical_column = Image_W/2;//最终记录的纵向搜索记录到到最远端的 行数 列数
    int16_t Vertical_search_row_left = 0,Vertical_search_row_right = 0;//纵向搜索时 从最远端往前面加n行 即为该变量，动态 用于搜索最远端前面(靠近小车)n行左右两边的黑点 用于丢线行前一行所在列做斜率用
    
    Left_slope = 0,Right_slope = 0;//左右边线 延伸  斜率  这里可考虑不清零
    Cross_road_flag = 0;//十字丢线标志位  不一定为真正的十字
    
    L_R_lost_cnt = 0;//左右边界同时丢线次数
    Cross_road_cnt = 0;//十字丢线次数
    Row_start =Image_H-1;//扫线起始行;

    L_lost_cnt = 0;//左边界丢线次数
    R_lost_cnt = 0;//右边界丢线次数

/*****************初始化数组************************************/
    for(int16_t i=0; i<Image_H+10; i++)
    {
        Left_line.x[i] = 0;   
        Midd_line.x[i] = Image_W/2;
        Right_line.x[i] = Image_W-10;
    }
/***************************************************************/

/*****************转为数组*********************************/
	uint16_t height = enter_Image_H;
	uint16_t width = enter_Image_W;
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
            int gray = process_image.at<uchar>(row, col);
            binary_img[row][col] = gray;
		}
	}
/**********************************************************/
    
    for(row=Row_start;row>=0;row--)
    {
        if(Left_line.x[row]<0)      
            Left_line.x[row] = 0;      //限制坐标平面，放置越界
        if(Right_line.x[row]>Image_W-10)
            Right_line.x[row] = Image_W-10;
        Left_end = (int16_t)Left_line.x[row];                     //扫描列结束限制
        Right_end = (int16_t)Right_line.x[row];
        if(Left_end<0)
            Left_end = 0;
        if(Right_end>Image_W-10)
            Right_end = Image_W-10;

        for(j=Left_start;j>Left_end;j--)
        {
            if(binary_img[row][j]==0&&binary_img[row][j-1]==0&&binary_img[row][j-2]==0&&binary_img[row][j-3]==0)//黑黑  易受噪点或者赛道上黑点干扰  后期考虑加滤波 如果控制周期允许的话  最原始滤波：两白点中间出现黑点，则该黑点为白
            {
                Left_line.x[row] = j;                                //记录黑点所在行的列数
                Found_left_flag = 1;                                 //黑点捕捉成功标记
                Left_line_lost[row] = 0;                            //记录所在点颜色，为黑色
                break;
            }
        }
        for(j=Right_start;j<Right_end;j++)
        {
            if(binary_img[row][j]==0&&binary_img[row][j+1]==0&&binary_img[row][j+2]==0&&binary_img[row][j+3]==0)                     //黑黑
            {
                Right_line.x[row] = j;
                Found_right_flag = 1;
                Right_line_lost[row] = 0;
                break;
            }
        }

        
        /*
        *  @brief        防畸变干扰
        *  @param       
        *  @param      
        *  Sample usage  
        */
        if(Found_left_flag&&Left_line.x[row]-Left_line.x[row+1]<0)//正常左线趋势  偏右，此处左线偏左  如果偏左则为左转  或者靠近十字导致的图像畸变  此时判断是右转还是图像畸变所找到的边界
        {
            if(!Found_right_flag||Right_line.x[row]-Right_line.x[row+1]>0)//右边未找到或者右边线减去上一行的右边线大于0，则认为是图像畸变
            {
                Found_left_flag = 0;                                 //标记本行未找到真正的边界，所找到的边界为图像畸变导致横向黑线所变成的纵向边界
                Left_line_lost[row] = 1;                            //标记本行丢线
            }
        }
        if(Found_right_flag&&Right_line.x[row]-Right_line.x[row+1]>0)//正常右线趋势  偏左，此处右线偏右  如果偏右则为左转  或者靠近十字导致的图像畸变  此时判断是左转还是图像畸变所找到的边界
        {
            if(!Found_left_flag||Left_line.x[row]-Left_line.x[row+1]<0)//左边未找到或者左边线减去上一行的右边线小于0，则认为是图像畸变
            {
                Found_right_flag = 0;                                 //标记本行未找到真正的边界，所找到的边界为图像畸变导致横向黑线所变成的纵向边界
                Left_line_lost[row] = 1;                            //标记本行丢线
            }
        }

        /*
        *  @brief        防噪点干扰  防左右线由于噪点干扰产生跳变
        *  @param       
        *  @param       
        *  Sample usage  
        */
        if(row<Image_H-1&&Found_left_flag&&Found_right_flag)
        {
            if(Left_line.x[row] - Left_line.x[row+1]>Image_W/7)
            {
                Left_line.x[row] = Left_line.x[row+1];
            }
            else if(Right_line.x[row+1] - Right_line.x[row]>Image_W/7)
            {
                Right_line.x[row] = Right_line.x[row+1];
            }
        }


        /*
        *  @brief          记录左右边界最先丢线所在的行
        *  @param         ~null
        *  @param         ~null 
        *  Sample usage   ~null
        */
        if(!Found_left_flag&&Found_right_flag&&!L_line_lost_flag)  //记录第一次左边界单边丢线所在的行
        {
            L_line_lost_flag = 1;
            L_earliest_lost_row = row;
        }
        if(!Found_right_flag&&Found_left_flag&&!R_line_lost_flag)//记录第一次右界单边丢线所在的行
        {
            R_line_lost_flag = 1;
            R_earliest_lost_row = row;
        }
        if(!Found_left_flag&&!Found_right_flag&&!L_R_line_lost_flag)//记录第一次左右边界同时丢线所在的行
        {
            L_R_line_lost_flag = 1;
            L_R_earliest_lost_row = row;
        }
        if(!L_fir_line_flag&&!Left_line_lost[row])//记录第一次左边界没丢线的所在行
        {
            L_fir_line_flag = 1;
        }
        if(!R_fir_line_flag&&!Right_line_lost[row])//记录第一次右边界没丢线的所在行
        {
            R_fir_line_flag = 1;
        }


        /*
        *  @brief        记录各边丢线次数  及最后丢线的 行
        *  @param         ~null
        *  @param         ~null 
        *  Sample usage   ~null
        */
        if(row>5)
        {
            if(!Found_left_flag||!Found_right_flag)//丢线的三种情况 做此判断非多此一举，如果两边都未丢，则无需再进行判断
            {
                if(!Found_left_flag&&!Found_right_flag)//十字丢线 两边全丢
                {
                    L_R_lost_cnt++;//十字丢线次数(也可以说是双边丢线次数，下面所写的Cross_road  即为近处真正的十字丢线)
                    L_R_lost_row = row;//记录一场图像最后一次两边同时丢线的行 
                    if(row>Image_H/4)
                      Cross_road_cnt++;
                }
                if(!Found_left_flag&&Found_right_flag)
                {
                    L_lost_cnt++;//单左边丢线次数
                    L_last_lost_row = row;//记录一场图像左边最后一次丢线的所在行
                }
                if(Found_left_flag&&!Found_right_flag)
                {
                    R_lost_cnt++;//单右边丢线次数
                    R_last_lost_row = row;//记录一场图像右边最后一次丢线的所在行
                }
            }
        }


        /*
        *  @brief 利用丢线行前面的有效行求斜率   这样就无需进行纵向求斜率   近处斜率比远处斜率准确稳定，近处斜率无法求再采用远端斜率
        *  @param         
        *  @param         
        *  Sample usage   ~null
        */
        if((L_line_lost_flag||L_R_line_lost_flag)&&!Get_L_near_slope_flag)
        {
            uint8_t L_slope_point = 0;
            int16_t Scan_L_slope_row;
            Get_L_near_slope_flag = 1;
            if(L_line_lost_flag)
            {
                Scan_L_slope_row = L_earliest_lost_row;
            }
            else
                Scan_L_slope_row = L_R_earliest_lost_row;
            for(i= Scan_L_slope_row+1;i< Scan_L_slope_row+30;i++)
            {
                if(!Left_line_lost[i])
                {
                    L_slope_point++;
                }
            }
            if(L_slope_point>19)    // 使用了15行的平均斜率
            {
                Left_slope = (Left_line.x[ Scan_L_slope_row+5] - Left_line.x[ Scan_L_slope_row+L_slope_point])/(L_slope_point - 5);
                if(Left_slope>0)
                {
                    L_near_slope_flag = 1;
                }
                else
                {
                    L_near_slope_flag = 0;
                }
            }
        }
        
        if((R_line_lost_flag||L_R_line_lost_flag)&&!Get_R_near_slope_flag)
        {
            uint8_t R_slope_point = 0;
            int16_t Scan_R_slope_row;
            Get_R_near_slope_flag = 1;
            
            if(R_line_lost_flag)
            {
                Scan_R_slope_row = R_earliest_lost_row;
            }
            else
                Scan_R_slope_row = L_R_earliest_lost_row;
            for(i=Scan_R_slope_row+1;i<Scan_R_slope_row+30;i++)
            {
                if(!Right_line_lost[i])
                {
                    R_slope_point++;
                }
            }         
            if(R_slope_point>19)        // 使用了15行的平均斜率
            {
                Right_slope = (Right_line.x[Scan_R_slope_row+5] - Right_line.x[Scan_R_slope_row+R_slope_point])/(R_slope_point - 5);
                if(Right_slope<0)
                {
                    R_near_slope_flag = 1;
                }
                else
                {
                    R_near_slope_flag = 0;
                }
            }
        }


        /*
        *  @brief          十字 环岛 补线   
        *  @param         ~null
        *  @param         ~null 
        *  Sample usage   ~null
        */   
         if(Vertical_search_flag||(L_near_slope_flag&&R_near_slope_flag))                      
        {
            if(!Found_left_flag&&!Found_right_flag)    
            {
                Left_line.x[row] = Left_line.x[row+1]+Left_slope;
                Right_line.x[row] = Right_line.x[row+1]+Right_slope;
            }
            else if(Left_slope>0&&(((Left_line.x[row+1]-Left_line.x[row+2]>0||Left_line.x[row+2]-Left_line.x[row+3]>0||L_near_slope_flag))&&!Found_left_flag&&Found_right_flag))  
            {
                Left_line.x[row] = Left_line.x[row+1]+Left_slope;//若左线斜率为k>0(k<0) 则每单位右(左)移|k|，以此类推
            }
            else if(Right_slope<0&&(((Right_line.x[row+2]-Right_line.x[row+1]>0||Right_line.x[row+3]-Right_line.x[row+2]>0||R_near_slope_flag))&&Found_left_flag&&!Found_right_flag))  
            {
                Right_line.x[row] = Right_line.x[row+1]+Right_slope;//若右线斜率为k>0(k<0) 则每单位右(左)移|k|，以此类推
            }
        }

        Midd_line.x[row] = (Left_line.x[row]+Right_line.x[row])/2;//每行中线列坐标


        /*
        *  @brief        纵向搜索，记录最远端边缘黑点坐标，
        *  @param         ~null
        *  @param         ~null 
        *  Sample usage   ~null
        */
        if((!Found_left_flag||!Found_right_flag)&&!Vertical_search_flag)  //单边丢线 或者上一场图像确定为环岛开启纵向搜索
        {
            Vertical_search_flag = 1;                                     //纵向搜索标志位
            if(!Found_left_flag||!Found_right_flag)  //0为meet——flag        
            {
                for(j=Image_W/8*3;j< Image_W/8*5;j++)//49~110  搜索列范围过大可能会受到临近赛道干扰
                {
                    for(i=row;i>Image_H/8;i--)
                    {
                      if(((binary_img[i][j]==0&&binary_img[i-1][j]==0)||(binary_img[i+1][j]!=0&&binary_img[i][j]==0))||(i==1))
                        {
                            Vertical_length = row-i;//本行row到纵向最远处的长度
                            if(Vertical_length>Vertical_longest_length_1)
                            {
                                Vertical_longest_length_1 = Vertical_length;//记录本行row到纵向最远处黑点的最长 长度
                                Vertical_row_1 = i;//记录本行row纵向 最远处黑点的W坐标（行数）
                                Vertical_column_1 = j;//记录本行row纵向 最远处黑点的H坐标（列数）
                            }
                            else if(Vertical_length==Vertical_longest_length_1)
                            {
                                Vertical_longest_length_2 = Vertical_length;
                                Vertical_column_2 = j;
                            }
                            break;
                        }
                    }
                }
            }
            if(Vertical_longest_length_1==Vertical_longest_length_2)
            {
                Vertical_column = (Vertical_column_1+Vertical_column_2)/2;
            }
            else        
                Vertical_column = Vertical_column_1;
        }

        
        /*
        *  @brief        若进行纵向搜索，则计算斜率，斜率相当于  每单位纵坐标 左右 移动几单位 上一次的左右黑线
        *  @param         ~null  此处用纵向搜索最远端所在行的前面n行往左右两边搜索黑点  并与丢线行做斜率 后面可再加一种求斜率方法
        *  @param         ~null  当某一边界丢线时，其前面的有效边界数大于某个值时，即可利用前面搜索到的有效边界求斜率，而不用进行纵向搜索
        *  Sample usage   ~null
        */
        if(Vertical_search_flag&&!Fill_line_flag&&(!L_near_slope_flag||!R_near_slope_flag))                 //纵向搜索结束
        {
            Fill_line_flag = 1;
            if(!L_near_slope_flag)
            {
                Vertical_search_row_left = Vertical_row_1 + 3;  //最远端图像赛道所在行 前面五行
                while(!Vertical_find_left_flag)
                {
                    for(j=Vertical_column;j>30;j--)//此处限制范围考虑放宽 减小
                    {   
                        if(binary_img[Vertical_search_row_left][j]==0&&binary_img[Vertical_search_row_left][j-1]==0)
                        {
                            Left_line.x[Vertical_search_row_left] = j;
                            Vertical_find_left_flag = 1;
                            break;
                        }
                    }
                    if(!Vertical_find_left_flag)
                    {
                        Vertical_search_row_left++;
                        if(Vertical_search_row_left- Vertical_row_1 - 3>10)
                        {
                            break;//当最远端前面十行均未搜索到边界点时，则退出不再搜索 斜率沿用上一场图像的边界斜率
                        }
                    }
                }
            }
            if(!R_near_slope_flag)
            {
                Vertical_search_row_right = Vertical_row_1 + 3;
                while(!Vertical_find_right_flag)
                {
                    for(j=Vertical_column;j<Image_W-10;j++)//此处限制范围考虑放宽 增大
                    {   
                        if(binary_img[Vertical_search_row_right][j]==0&&binary_img[Vertical_search_row_right][j+1]==0)
                        {
                            Right_line.x[Vertical_search_row_right] = j;
                            Vertical_find_right_flag = 1;
                            break;
                        }
                    }
                    if(!Vertical_find_right_flag)
                    {
                        Vertical_search_row_right++;
                        if(Vertical_search_row_right - Vertical_row_1 - 3>10)
                        {
                            break;//当最远端前面十行均未搜索到边界点时，则退出不再搜索 斜率沿用上一场图像的边界斜率
                        }
                    }
                }
            }
            if(Vertical_find_left_flag)
            {
                Left_slope = (Left_line.x[Vertical_search_row_left]-Left_line.x[row])/(row-Vertical_search_row_left);
            }
            if(Vertical_find_right_flag)
            {
                Right_slope = (Right_line.x[Vertical_search_row_right]-Right_line.x[row])/(row-Vertical_search_row_right);
            }
        }

        
        /*
        *  @brief        补线限制   后续需要修改
        *  @param         Near_flag  近处处理 标志
        *  @param         ~null 
        *  Sample usage   ~null
        */
        if(row<Row_start)
        {
            if((fabs)(Midd_line.x[row]-Midd_line.x[row+1])>Image_W/8)//相邻行中线值相差超过某个值，则可能为反光导致远处赛道中线值跳变，可考虑直接break退出后面的搜索
            {
                Midd_line.x[row] = Midd_line.x[row+1];
            }
            else
            {
                if(Midd_line.x[row]-Midd_line.x[row+1]>Image_W/25)
                {
                    Midd_line.x[row] = Midd_line.x[row+1]+Image_W/25;
                    if(Midd_line.x[row]>Image_W-1)        
                    {
                        Midd_line.x[row] = Image_W-1;
                    }
                }
                else if(Midd_line.x[row]-Midd_line.x[row+1]<-Image_W/25)
                {
                    Midd_line.x[row] = Midd_line.x[row+1]-Image_W/25;
                    if(Midd_line.x[row]<0)        
                    {
                        Midd_line.x[row] = 0;
                    }
                }
            }
        }
        if((((binary_img[row][(int16_t)Midd_line.x[row]]==0)&&(binary_img[row][(int16_t)Midd_line.x[row+1]]==0))
        ||((binary_img[row][(int16_t)Midd_line.x[row+1]]==0)&&(binary_img[row][(int16_t)Midd_line.x[row+2]]!=0)))
        ||Midd_line.x[row]==0||Midd_line.x[row]==  Image_W-10)
        {
              row = row+1;//该判断语句 需要重新定义  连续两个中点为黑色则退出扫线
              break;
        }

        Left_start = (int16_t)Midd_line.x[row];//下一行扫左边线时，起始列为本行中线所在列
        Right_start = (int16_t)Midd_line.x[row];//下一行扫右边线时，起始列为本行中线所在列

    }   //大循环结束

    Row_end = row+1;//记录本场图像所处理到的最远端的所在行
    Row_begging = Row_start;
    Last_row_end = Row_end;
    printf("Last_row_end:%d\n", Last_row_end);
}

