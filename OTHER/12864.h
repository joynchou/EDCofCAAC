#define LCD_dataBus  P0    //总线  
sbit LCD_EN = P3^4;        //使能控制  
sbit LCD_RS = P3^5;        //数据_命令选择端  
sbit LCD_RW = P3^6;        //读写控制  
sbit LCD_PSB= P3^7;        //串并选择,H并行,L串行  
  
  
extern bool bShowPicFlag;  //绘图时图像显示控制(仅控制GDRAM)  
  
/*************************基本功能函数*********************************************/  
extern void LCD12864_init();                    //初始化,必须置顶调用  
extern void LCD12864_setPos(u8 row, u8 cols);   //设置光标位置  
extern void LCD12864_writeByte(u8 dat);         //写一个字节  
extern void LCD12864_writeCmd(u8 cmd);          //写指令  
extern   u8 LCD12864_readByte();                //读一个字节ram  
extern   u8 LCD12864_readIR();                  //读暂存器  
extern bool LCD12864_isBusy();                  //判忙  
  
/*************************调用基本字库显示文字**************************************/   
//独创支持全角半角字符及中英混合的字符串,或字符串的子串,起始行号row(0-3)和列坐标cols(0-15),写满屏幕为止  
//行号4-7行是滚动区  
extern void LCD12864_writeData(u8 row, u8 cols,u8* pBuf,u8 dataSize);//写一堆数据  
extern void LCD12864_earseSomeDDRam(u8 row,u8 cols,u8 dataSize);    //擦除N字节DDRam  
  
/*************************用户自定义图标字体****************************************/  
extern void LCD12864_writeCGRAM(u8 userRamNum,u8* pCGRAM_userCode); //写自定义图标字体  
extern void LCD12864_showCGRAM(u8 row,u8 cols,u8 num) ; //显示自定义图标字体,row(0-3),cols(0-15)  
extern void LCD12864_clearCGRAM(u8 CGRAM_groupNum) ;    //CGRAM清零(初始化也可清0)  
  
/*************************图像显示功能函数**********************************************/  
extern void LCD12864_showGDRAM(bool bShowImage);     //GDRAM绘图显示开关  
extern void LCD12864_clearGDRAM();                   //液晶整个可视区的GDRAM快速清0  
//前4参数:起始点x(0-7)位址,y(0-63)坐标,要显示的宽度(1-128)和高度(1-64)[可显示从图像左上角开始的部分区域]  
//后4参数:图像代码地址,图像本身的宽度(1-128)和高度(1-64), 反白(true反白,false不反白)  
//画图填充GDRAM ,注:显示的区域或者图像本身宽度必须是8的倍数  
extern u8 LCD12864_drawGDRAM(u8 x,u8 y,u8 width,u8 height,u8 *pImageCode,u8 imageWidth,u8 imageHight,bool bReverse);  
extern void LCD12864_drawDot(u8 x,u8 y,u8 flag);        //打点,x(0-127),y(0-63),flag(0正常,1反白,2清0)  
extern bool LCD12864_drawXYLine(u8 x1, u8 y1,u8 x2, u8 y2,u8 flag);       //画水平或垂直直线  
extern void LCD12864_drawAnyLine(u8 x1, u8 y1,u8 x2, u8 y2,u8 flag) ;     //画任意直线  
extern void LCD12864_drawRectangle(u8 x,u8 y ,u8 width,u8 height,u8 flag);//画矩形  
extern void LCD12864_drawFillRect(u8 x,u8 y, u8 width,u8 hight,u8 flag);  //填充矩形,可对矩形区反白或清0  
extern void LCD12864_drawVerticalSquare(u8 x,u8 y,u8 r,u8 flag) ;         //画站立的正方形  
extern void LCD12864_drawCircle(u8 x0,u8 y0,u8 r,u8 flag);                //画圆  
  
//打点法全屏画图有点慢了,打点法反白矩形区还可以,建议矩形范围小一些,不然比较慢  
//打点法效果最好,因为文字的矩形区比较小,速度很快  
//不过绘图法反白文字效率高,flash空间充裕的建议用绘图法  
  
/***************************全屏滚动*******************************************/  
//需要滚动时,用LCD12864_writeScrollData()函数,参数和LCD12864_writeData()一样  
extern void LCD12864_writeScrollData(u8 row,u8 cols,u8* pBuf,u8 dataSize);//写数据 (滚动模式)  
extern void LCD12864_setScrollPos(u8 row, u8 cols);     //设置滚动模式的坐标  
extern void LCD12864_showScrollCGRAM(u8 row,u8 cols,u8 CGRAM_groupNum);//用于CGRAM滚动显示前执行  
extern void LCD12864_startScroll(u8 scrollNum,u16 delay_ms);  //滚动开始  