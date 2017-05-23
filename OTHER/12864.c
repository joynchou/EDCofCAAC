#include "lcd12864.h"  
bool bShowPicFlag=false;          //绘图时图像显示控制  
  
/* 
u8 LCD12864_table[]={"123456789"}; 
*/  
  
void LCD12864_drawFillRect(u8 x,u8 y, u8 width,u8 hight,u8 flag)//填充任意位置的整个矩形  
{//矩形起始坐标x(0-127),y(0-63),宽(1-128)高(1-64),flag有3种值,0正常填充,1反色,2清0  
    u8 i=0;  
    u8 j=0;  
    if(0==width||0==hight)   //矩形宽度或高度为0时返回  
    {  
        return ;  
    }  
    if( (x+width>128 ||(y+hight)>64)  )  
    {  
        led2=0;  
        return;  
    }  
    for(j=0;j
    {         
        for(i=0;i
        {  
            LCD12864_drawDot(x+i, y+j,flag);          
        }  
    }             
}  
  
  
void LCD12864_drawRectangle(u8 x,u8 y, u8 width,u8 hight,u8 flag)//画矩形  
{   //矩形起始坐标x(0-127),y(0-63),宽度(1-128)和高度(1-64) flag有3种值,0正常写1,1反色,2清0  
    if(0==width||0==hight)   //矩形宽度或高度为0时返回  
    {  
        return ;  
    }  
    width--;hight--;  
    LCD12864_drawXYLine(x, y,x+width, y, flag);  
    LCD12864_drawXYLine(x+width, y,x+width, y+hight, flag);  
LCD12864_drawXYLine
LCD12864_drawXYLine(x, y,x, y+hight, flag);  
    LCD12864_drawXYLine(x, y+hight,x+width, y+hight, flag);   
}  
  
bool LCD12864_drawXYLine(u8 x1,u8 y1,  u8 x2, u8 y2,  u8 flag)//画水平或垂直直线  
{   //起始点坐标和终点坐标,x(0-127),y(0-63),  flag有3种值,0正常写1,1反色,2清0  
    u8 n=0;  
    if(flag>2|| x1>127||x2>127||y1>63||y2>63)  
    {  
        return false;  
    }  
  
    if(x1==x2)  
    {  
        for(n=0;n
        {  
            LCD12864_drawDot( x1,y1+(y2>=y1?n:-n) ,flag);      
        }  
    }  
  
    if(y1==y2)  
    {  
        for(n=0;n
        {  
             LCD12864_drawDot(x1+(x2>=x1?n:-n),y1,flag)  ;  
        }  
    }  
    return true;      
}  
  
void LCD12864_drawCircle(u8 x0,u8 y0,u8 r,u8 flag)  
{  
    s8 a,b;  
    s8 di;  
    if(r>31 ||r==0) return;    //参数过滤，次液晶显示的最大圆半径为31  
    a=0;  
    b=r;  
    di=3-2*r;       //判断下个点位置的标志  
    while(a<=b)  
    {  
        LCD12864_drawDot(x0-b,y0-a,flag);  //3             
        LCD12864_drawDot(x0+b,y0-a,flag);  //0             
        LCD12864_drawDot(x0-a,y0+b,flag);  //1         
        LCD12864_drawDot(x0-b,y0-a,flag);  //7             
        LCD12864_drawDot(x0-a,y0-b,flag);  //2               
        LCD12864_drawDot(x0+b,y0+a,flag);  //4                 
        LCD12864_drawDot(x0+a,y0-b,flag);  //5  
        LCD12864_drawDot(x0+a,y0+b,flag);  //6   
        LCD12864_drawDot(x0-b,y0+a,flag);               
        a++;  
        //使用Bresenham算法画圆       
        if(di<0)  
        di +=4*a+6;  
        else  
        {  
            di +=10+4*(a-b);     
            b--;  
        }   
        LCD12864_drawDot(x0+a,y0+b,flag);  
    }  
}  
  
  
void LCD12864_drawVerticalSquare(u8 x,u8 y,u8 r,u8 flag)    //画站立的正方形  
{  
    u8 a,b;  
    float c=0;  
    a = 0;  
    b = r;  
    c = 3 - 2*r;  
    while(a < b)  
    {  
        LCD12864_drawDot(x+a,y+b,flag);  
        LCD12864_drawDot(x-a,y+b,flag);  
        LCD12864_drawDot(x+a,y-b,flag);  
        LCD12864_drawDot(x-a,y-b,flag);  
          
        LCD12864_drawDot(x+b,y+a,flag);  
        LCD12864_drawDot(x-b,y+a,flag);  
        LCD12864_drawDot(x+b,y-a,flag);  
        LCD12864_drawDot(x-b,y-a,flag);  
          
        if(c < 0)  
        {  
            c = c+4*a + 6;   
        }  
        else  
        {  
            c= c + 4*(a - b) + 10;  
            b-=1;  
        }  
        a = a + 1;  //控制打点间隔  
          
    }  
    if(a == b)  
    {  
        LCD12864_drawDot(x+a,y+b,flag);  
        LCD12864_drawDot(x-a,y+b,flag);  
        LCD12864_drawDot(x+a,y-b,flag);  
        LCD12864_drawDot(x-a,y+b,flag);  
          
        LCD12864_drawDot(x+b,y+a,flag);  
        LCD12864_drawDot(x-b,y+a,flag);  
        LCD12864_drawDot(x+b,y-a,flag);  
        LCD12864_drawDot(x-b,y-a,flag);         
    }  
}  
  
  
void LCD12864_drawAnyLine(u8 StartX, u8 StartY,u8 EndX, u8 EndY, u8 flag)  //画任意直线  
{  
    u8 t, distance ;      /*根据屏幕大小改变变量类型(如改为int型)*/  
    s16 x = 0 , y = 0 ;  
    s8 incx, incy, dx, dy ;  
    if((StartX==EndX) ||(StartY==EndY))  
    {  
        LCD12864_drawXYLine(StartX,StartY,EndX,EndY,flag);  
        return;  
    }  
  
    dx = EndX - StartX ;  
    dy = EndY - StartY ;          
    incx = dx > 0 ?1:-1;  
    incy = dy > 0 ?1:-1;  
  
    dx = abs( dx );  
    dy = abs( dy );  
    if( dx > dy )  
    {  
        distance = dx ;  
    }  
    else  
    {  
distance = dy ;
distance = dy ;  
    }  
    LCD12864_drawDot( StartX, StartY, flag ) ;        //反白补点  
    for( t = 0 ; t <= distance+1 ; t++ )  
    {  
        LCD12864_drawDot( StartX, StartY, flag ) ;  
        x += dx ;  
        y += dy ;  
        if( x > distance )  
        {  
            x -= distance ;  
            StartX += incx ;  
        }  
        if( y > distance )  
        {  
            y -= distance ;  
            StartY += incy ;  
        }  
    }  
}  
  
void LCD12864_drawDot(u8 x, u8 y,u8 flag)   //画点,0打点,1反色,2清0  
{  //x(0-127),y(0-63),flag有3种值,0正常写1,1反色,2清0  
    u8 x_word=0;         //水平(0-127)个像素中的哪个字,一字16位  
    u8 x_mode=0;         //取余  
    u8 y_part=0;  
    u8 y_bit=0;  
    u8 tempH=0;  
    u8 tempL=0;  
    x_word=x>>4;      //在哪一个字(0-7)          ,x_word=x/16   
    x_mode=x&0x0f;      //在该字的哪一位         ,x_mode= x%16   
    y_part=y>>5;        //在哪个屏0或1           ,y_part=y/32   
    y_bit= y&0x1f;      //垂直方向,y_bit范围(0-31),y_bit=y%32   
    bShowPicFlag?LCD12864_writeCmd(0x36):LCD12864_writeCmd(0x34);  
    LCD12864_writeCmd(0x80+y_bit);  //垂直坐标  
    LCD12864_writeCmd(0x80+8*y_part+x_word);           //水平位址  
    
    LCD12864_readByte();  
    tempH=LCD12864_readByte();  //先将该字16位数据保存  
    tempL= LCD12864_readByte();  
      
    LCD12864_writeCmd(0x80+y_bit);                     //重设地址,因为AC计数器变了  
    LCD12864_writeCmd(0x80+8*y_part+x_word);           //水平位址  
    if(0==flag)                                     //不反白,打1,  
    {  
        if(x_mode<8)  //如果x_mode小于8,说明点应位于该字的左边高8位中  
        {  
            LCD12864_writeByte( tempH | bit(7- x_mode) );  
            //LCD12864_writeByte(tempL);  
        }  
        else  
        {  
            //LCD12864_writeByte(tempH);  
            LCD12864_readByte();     //让AC走半步  
            LCD12864_writeByte(tempL|bit(15-x_mode));  
        }     
    }  
    else if(1==flag)            //反白,该点与原来的状态相反  
    {  
        if(x_mode<8)  //如果x_mode小于8,说明点应位于该字的左边高8位中  
        {  
            if(tempH & bit(7- x_mode))       //原来是1  
            {  
                LCD12864_writeByte( tempH&~bit(7- x_mode) );    //写0  
            }  
            else                             //原来是0  
            {  
                LCD12864_writeByte( tempH | bit(7- x_mode) );   //写1  
            }  
              
        }  
        else  
        {  
            LCD12864_readByte();     //让AC走半字  
            if(tempL& bit(15-x_mode))     //原来是1的写0  
            {  
                  
                LCD12864_writeByte(tempL&~bit(15-x_mode));   //写0  
            }  
            else  
            {  
                LCD12864_writeByte(tempL|bit(15-x_mode));    //写0  
            }  
              
        }  
    }  
    else if(2==flag)              //清0  
    {  
        if(x_mode<8)  //如果x_mode小于8,说明点应位于该字的左边高8位中  
        {  
            LCD12864_writeByte( tempH&~bit(7- x_mode) );  
        }  
        else  
        {  
            LCD12864_readByte();     //让AC走半字  
            LCD12864_writeByte(tempL&~bit(15-x_mode));  
}
    }     
    }    
}  
  
void LCD12864_showGDRAM(bool bShowImage)    //GDRAM图像显示开关  
{  
    if(bShowImage)       //开启显示  
    {  
        LCD12864_writeCmd(0x36);  
        LCD12864_writeCmd(0x30);          
    }  
    else                 //关闭显示  
    {  
        LCD12864_writeCmd(0x34);  
        LCD12864_writeCmd(0x30);          
    }  
}  
  
  
//填充GDRAM  
u8 LCD12864_drawGDRAM(u8 x,u8 y,u8 width,u8 height,u8* pImageCode,u8 imageWidth,u8 imageHight,bool bReverse)  
{//前4参数:起始点x(0-7)位址,y(0-63)坐标,要显示的宽度(1-128)和高度(1-64)[可显示从图像左上角开始的部分区域]  
 //后4参数:图像代码地址,图像本身的宽度(1-128)和高度(1-64), 反白(true反白,false不反白)  
    u8 i=0;  
    u8 j=0;  
    if( height > imageHight )       //检测显示高度,宽度不检测不会乱码  
    {                              //显示的高度不能超过图片本身高度  
        return 0x01;               //也就是说可显示图像的部分区域(从图像左上角开始的部分区域)  
    }  
    width>>=3;                       //像素宽度转化为字节个数,所以width必须是8的整数倍  
    imageWidth>>=3;                  //像素宽度转化为字节个数,所以width必须是8的整数倍  
    if(bShowPicFlag)                  
    {  
        LCD12864_writeCmd(0x36);    //改写GDRAM时,开启绘图显示,可防止动画显示时闪动          
    }  
    else  
    {  
        LCD12864_writeCmd(0x34);    //改写GDRAM时,关闭绘图显示  
    }  
  
    for(j=0;j
    {  
        if(y+j>31)                           //地址变换  
        {  
            LCD12864_writeCmd(0x80+y+j-32); //垂直坐标  
            LCD12864_writeCmd(0x88+x);      //水平位址  
        }  
        else  
        {  
            LCD12864_writeCmd(0x80+y+j);      
            LCD12864_writeCmd(0x80+x);  
        }  
        for(i=0;i
        {  
            LCD12864_writeByte(bReverse?~pImageCode[imageWidth*j+i]:pImageCode[imageWidth*j+i]);      
        }     
    }  
    LCD12864_writeCmd(0x30);  
    return 0x02;  
}  
  
  
void LCD12864_clearGDRAM()          //液晶可视区的绘图GDRAM清0  
{      
    u8 j=0;  
    u8 i=0;  
    LCD12864_writeCmd(0x34);        //扩展指令  
    for(j=0;j<64;j++)            //垂直方向地址手动增加,当j=64时清整个GDram  
    {                               //我们只要清可视区的GDRAM就可以了  
        LCD12864_writeCmd(0x80+j);  //y轴坐标  
        LCD12864_writeCmd(0x80);    //x轴坐标  
        for(i=0;i<32;i++)           //水平方向位址自动增加  
        {  
            LCD12864_writeByte(0x00);  
        }  
    }  
    LCD12864_writeCmd(0x30);  //回到基本指令  
}       
  
  
/*--------------------------------CGRAM start----------------------------------------------*/  
void LCD12864_clearCGRAM(u8 CGRAM_groupNum)//将用户自定义编码区CGRAM清0      
{   //参数一是CGRAM的4组用户空间组号码(0~3) ,参数二是用户自定义图表或汉字的编码  
    u8 i,addr=0;      
    bShowPicFlag?LCD12864_writeCmd(0x36):LCD12864_writeCmd(0x34);//扩展指令,绘图开关保持                                
    LCD12864_writeCmd(0x02);        //SR等于0,允许设置卷动地址  
    LCD12864_writeCmd(0x30);        //恢复为8位并行,基本指令集  
    addr=(CGRAM_groupNum<<4)|0x40;    //将CGRAM空间号转换为相应存储地址  
    LCD12864_writeCmd(addr);        //定位到该位址(用户空间位址范围0x40-0x7F共128字节)  
    for(i=0;i<16;i++)                //将用户自定义编码写入该16*16位元组空间  
    {  
        LCD12864_writeByte(0);      //连续写2个字节共16位  
        LCD12864_writeByte(0);  
    }      
}  
  
void LCD12864_writeScrollCGRAM(u8 CGRAM_groupNum, u8* pUserCode)//将用户自定义编码写入CGRAM      
{   //参数一是CGRAM的4组用户空间组号码(0~3) ,参数二是用户自定义图表或汉字的编码  
    u8 i,addr=0;  
    if(bShowPicFlag)                  
    {  
        LCD12864_writeCmd(0x36);    //开启绘图显示,可流畅播放动画   
		}  
    else  
    {  
        LCD12864_writeCmd(0x34);    //默认关闭绘图显示  
    }                 
    LCD12864_writeCmd(0x02);        //SR等于0,允许设置卷动地址  
    LCD12864_writeCmd(0x30);        //恢复为8位并行,基本指令集  
    addr=(CGRAM_groupNum<<4)|0x40;    //将CGRAM空间号转换为相应存储地址  
    LCD12864_writeCmd(addr);        //定位到该位址(用户空间位址范围0x40-0x7F共128字节)  
    for(i=0;i<16;i++)                //将用户自定义编码写入该16*16位元组空间  
    {  
        LCD12864_writeByte(pUserCode[i*2]);      //连续写2个字节共16位  
        LCD12864_writeByte(pUserCode[i*2+1]);  
    }      
}  
  
void LCD12864_writeCGRAM(u8 CGRAM_groupNum, u8* pUserCode)//将用户自定义编码写入CGRAM    
{   //参数一是CGRAM的4组用户空间组号码(0~3) ,参数二是用户自定义图表或汉字的编码  
    u8 i,addr=0;  
    if(bShowPicFlag)                  
    {  
        LCD12864_writeCmd(0x36);    //开启绘图显示,可流畅播放动画          
    }  
    else  
    {  
        LCD12864_writeCmd(0x34);    //默认关闭绘图显示  
    }                 
    LCD12864_writeCmd(0x02);        //SR等于0,允许设置卷动地址  
    LCD12864_writeCmd(0x30);        //恢复为8位并行,基本指令集  
    addr=(CGRAM_groupNum<<4)|0x40;    //将CGRAM空间号转换为相应存储地址  
    LCD12864_writeCmd(addr);        //定位到该位址(用户空间位址范围0x40-0x7F共128字节)  
    for(i=0;i<16;i++)                //将用户自定义编码写入该16*16位元组空间  
    {  
        LCD12864_writeByte(pUserCode[i*2]);      //连续写2个字节共16位  
        LCD12864_writeByte(pUserCode[i*2+1]);  
    }      
}  
  
void LCD12864_showScrollCGRAM(u8 row,u8 cols,u8 CGRAM_groupNum)//滚动CGRAM  
{   //row(0-3), cols(0-15)  
    //第三个参数是用户空间号码(0~3共4组空间号码),该号码乘2就是它所对应的[调用用户空间编码]  
    LCD12864_setScrollPos(row,cols);  
    LCD12864_writeByte(0x00);//4组用户空间的编码的高字节都固定为0,我猜这是为和E文ASCII码区分开  
    LCD12864_writeByte(CGRAM_groupNum*2);   //对应编码00h,02h,04h,06h  
    LCD12864_showCGRAM(row,cols,CGRAM_groupNum);  
}  
  
void LCD12864_showCGRAM(u8 row,u8 cols,u8 CGRAM_groupNum)//定位液晶光标,并显示自定义内容  
{   //row(0-3), cols(0-15)  
    //第三个参数是用户空间号码(0~3共4组空间号码),该号码乘2就是它所对应的[调用用户空间编码]  
    LCD12864_setPos(row,cols);  
    LCD12864_writeByte(0x00);//4组用户空间的编码的高字节都固定为0,我猜这是为和E文ASCII码区分开  
    LCD12864_writeByte(CGRAM_groupNum*2);   //对应编码00h,02h,04h,06h  
}  
/*--------------------------------CGRAM end----------------------------------------------*/  
  
/*--------------------------------DDRAM start----------------------------------------------*/  
void LCD12864_earseSomeDDRam(u8 row,u8 cols,u8 dataSize) //擦除N个字节DDRam  
{   //row(0-3),cols(0-15),如果起始地址是汉字的低字节,则会一同擦除汉字的高字节  
    LCD12864_setPos(row, cols);                //定位                              
    if(cols%2!=0)                              //如果从奇数列开始  
    {  
        LCD12864_readByte();                   //空读一次,让位址指针移动半字  
        if(LCD12864_readByte()>127)             //检测高位是否是汉字码  
        {  
            LCD12864_setPos(row, cols);        //是汉字码的话要擦除,不然要乱码  
            LCD12864_writeByte(' ');           //其实是写空格,看不到了就等于擦除了  
        }                                      //连续写2个0的话是乱码  
    }     
    while(dataSize--)                          //擦除  
    {  
        if(cols)                               //cols>0  
        {  
            if(0==cols%16)                     //如果一行满了  
            {  
                row++;                         //准备将光标移到下一行  
                cols=0;                        //列坐标置于行首  
                LCD12864_setPos(row, cols);    //设置新光标  
            }                 
        }  
        LCD12864_writeByte(' ');               //其实是写空格,但为啥不写0呢  
cols++; //因为0与是CGRAM重码了,写2个0会乱
 cols++;                                //因为0与是CGRAM重码了,写2个0会乱码的  
    }  
      
}  
  
  
/***************************************************************************************** 
pBuf如果用来修饰字符串,dataSize=strlen(pBuf); 
pBuf如果是一个字符数组,dataSize=sizeof(pBuf); 
strlen()虽然也可以用来计算字符数组长度,但遇到'\0'时就会返回,不会再计算后面的其他字符 
在VC中strlen()只能计算字符串长度,不能计算字符数组,否则编译出错 
sizeof("你好5"),sizeof("你好56"),最终液晶光标位置是一样的,故不要用sizeof计算字符串 
*****************************************************************************************/  
void LCD12864_writeData(u8 row,u8 cols,u8* pBuf,u8 dataSize)//写数据  
{   //支持全角半角字符及中英混合的字符串,也可写入字符串的子串,(行坐标0~3,列坐标0~15)  
    u8 flag=0;                                  //液晶低字节ram数据检测标志,0不检测  
    LCD12864_setPos(row, cols);                 //设置光标      
    if(cols%2!=0)                               //列号不为偶数(汉字在液晶上要偶对齐)  
    {   //要让位址空移一个字节,执行下面这句读操作后,效果是达到了  
        LCD12864_readByte();//但AC值没变,我怀疑除了这个AC字型指针,另有一个标志位没公开)  
        flag=1;                                 //此时需要检测液晶低位字节ram     
    }                                           //因为高位字节现在可能是汉字码  
  
    while(dataSize--)                           //循环处理目标字节流  
    {                                             
        if(0==cols%2)                           //偶对齐时,对于ram高字节  
        {  
            if(*pBuf>127)                        //如果写入ram的高字节是汉字码  
            {  
                flag=0;                         //下一次不要检测低字节,因为肯定是汉字了  
            }  
            else                                //如果高字节是半角字符  
            {  
                flag=1;                         //若在低字节ram写入汉字就乱码了,故检测  
            }                 
        }  
  
        if(cols%2!=0)                           //对于液晶低字节  
        {  
            if(flag)                            //如果要检测低字节  
            {  
                if(*pBuf>127)                    //如果低字节是汉字码  
                {  
                    LCD12864_writeByte(0x20);   //插入一个空格  
                    cols++;                     //字节计数器++  
                    flag=0;                     //清检测标志  
                }                     
            }     
        }        
          
        if(cols)                                //行尾检测  
        {  
            if(0==cols%16)                      //如果一行满了  
            {  
                row++;                          //准备将光标移到下一行  
                cols=0;                         //列坐标置于行首  
                LCD12864_setPos(row, cols);     //设置新位址  
            }                 
        }   
  
        LCD12864_writeByte(*pBuf++);            //终于可以写数据了  
cols++;
 cols++;                                 //列号累加  
    }  
}  
  
  
//滚屏模式的写数据函数  
void LCD12864_writeScrollData(u8 row,u8 cols,u8* pBuf,u8 dataSize)//写数据,卷动模式  
{   //支持全角半角字符及中英混合的字符串,也可写入字符串的子串,(行坐标0~3,列坐标0~15)  
    u8 flag=0;                                  //液晶低字节ram数据检测标志,0不检测  
    LCD12864_writeData(row,cols,pBuf,dataSize);  
    LCD12864_setScrollPos(row, cols);                   //设置光标      
    if(cols%2!=0)                               //列号不为偶数(汉字在液晶上要偶对齐)  
    {   //要让位址空移一个字节,执行下面这句读操作后,效果是达到了  
        LCD12864_readByte();//但AC值没变,我怀疑除了这个AC字型指针,另有一个标志位没公开)  
        flag=1;                                 //此时需要检测液晶低位字节ram     
    }                                           //因为高位字节现在可能是汉字码  
  
    while(dataSize--)                           //循环处理目标字节流  
    {                                             
        if(0==cols%2)                           //偶对齐时,对于ram高字节  
        {  
            if(*pBuf>127)                        //如果写入ram的高字节是汉字码  
            {  
                flag=0;                         //下一次不要检测低字节,因为肯定是汉字了  
            }  
            else                                //如果高字节是半角字符  
            {  
                flag=1;                         //若在低字节ram写入汉字就乱码了,故检测  
            }                 
        }  
  
        if(cols%2!=0)                           //对于液晶低字节  
        {  
            if(flag)                            //如果要检测低字节  
            {  
                if(*pBuf>127)                    //如果低字节是汉字码  
                {  
                    LCD12864_writeByte(0x20);   //插入一个空格  
                    cols++;                     //字节计数器++  
                    flag=0;                     //清检测标志  
                }                     
            }     
        }        
          
        if(cols)                                //行尾检测  
        {  
            if(0==cols%16)                      //如果一行满了  
            {  
                row++;                          //准备将光标移到下一行  
                cols=0;                         //列坐标置于行首  
                LCD12864_setScrollPos(row, cols);       //设置新位址  
            }                 
        }   
  
        LCD12864_writeByte(*pBuf++);            //终于可以写数据了  
        cols++;                                 //列号累加  
    }  
}  
  
void  LCD12864_startScroll(u8 scrollNum,u16 delay_ms)  //滚动  
{   //scrollNum建议值为64  
    u8 i;  
LCD12864_writeCmd(0x34);
 LCD12864_writeCmd(0x34);      
    LCD12864_writeCmd(0x03);  
    for(i=0x40;i<0x40+scrollNum;i++)   
    {    
        LCD12864_writeCmd(i); //设置卷动地址  
        delayms(delay_ms);         //实际使用时建议用定时器处理  
    }  
    LCD12864_writeCmd(0x40);  //补滚一行  
    LCD12864_writeCmd(0x30);  
}  
  
void LCD12864_setScrollPos(u8 row, u8 cols)     //设置光标位置 ,卷动模式  
{                                               //row行坐标0~3  
    u8 newPos=0;                                //cols列坐标0~15  
    switch(row)  
    {  
        case 0:  
        {  
            row=0xa8;     
        }  
        break;  
        case 1:  
        {  
            row=0xb8;  
        }  
        break;  
        case 2:  
        {  
            row=0xa0;  
        }  
        break;  
        case 3:  
        {  
            row=0xb0;  
        }  
        break;  
        default:        //如果需要检测行坐标范围,可在这里加代码  
        break;            
    }  
    newPos=row+cols/2;  //液晶写指令坐标只能8级,我的函数中列坐标是16级的,支持半角全角混合  
    LCD12864_writeCmd(newPos);  
}  
  
  
void LCD12864_setPos(u8 row, u8 cols)           //设置光标位置  
{                                               //row行坐标0~3  
    u8 newPos=0;                                //cols列坐标0~15  
    switch(row)  
    {  
        case 0:  
        {  
            row=0x80;     
        }  
        break;  
        case 1:  
        {  
            row=0x90;  
        }  
        break;  
        case 2:  
        {  
            row=0x88;  
        }  
        break;  
        case 3:  
        {  
            row=0x98;  
        }  
        break;  
        case 4:  
        {  
            row=0xa0;  
        }  
        break;  
        case 5:  
        {  
            row=0xb0;  
        }  
        break;  
        case 6:  
        {  
            row=0xa8;  
        }  
        break;  
        case 7:  
        {  
            row=0xb8;  
        }  
        break;  
  
        default:        //如果需要检测行坐标范围,可在这里加代码  
        break;            
    }  
    newPos=row+cols/2;  //液晶写指令坐标只能8级,我的函数中列坐标是16级的,支持半角全角混合  
    LCD12864_writeCmd(newPos);  
}  
/* 
void LCD12864_setPos(u8 row, u8 cols)           //设置光标位置 
{                                               //row行坐标0~3 
    u8 newPos=0;                                //cols列坐标0~15 
    switch(row) 
    { 
        case 0: 
        { 
            row=0x80;    
        } 
        break; 
        case 1: 
        { 
            row=0x90; 
        } 
        break; 
        case 2: 
        { 
            row=0x88; 
        } 
        break; 
        case 3: 
        { 
            row=0x98; 
        } 
        break; 
default: //如果需要检测行坐标范
  default:        //如果需要检测行坐标范围,可在这里加代码 
        break;           
    } 
    newPos=row+cols/2;  //液晶写指令坐标只能8级,我的函数中列坐标是16级的,支持半角全角混合 
    LCD12864_writeCmd(newPos); 
} 
    */  
  
  
  
void LCD12864_init()                  //初始化  
{  
    delayms(40);                      //rst由低到高后保持40ms以上,我们的rst接VCC  
    LCD_PSB= 1;                       //选择并口方式  
  
    LCD12864_writeCmd( B(110000) );   //0x30,启用基本指令集  
    delayXus(15);                     //要求延时100us以上,(8+6x)*1.085=106us  
  
    LCD12864_writeCmd( B(110000) );   //0x30,要求写2次该指令  
    delayXus(5);                      //要求延时37us以上,(8+6x)*1.085=41us  
  
    LCD12864_writeCmd( B(1100) );     //0x0f,整体显示,游标,游标反白  
    delayXus(15);                     //要求延时100us以上  
  
    LCD12864_writeCmd( B(0001) );     //0x01,清屏指令,整屏幕写满空格  
    delayms(10);                      //要求延时10ms以上  
  
    LCD12864_writeCmd( B(110) );      //0x06,进入模式设置,游标自动指向下一位置,  
                                                  
    delayms(5);                       //手册上没说这里要延时,额,还是加上吧  
}  
  
  
void LCD12864_writeCmd(u8 cmd)        //写指令  
{  
    while(LCD12864_isBusy());  
    LCD_EN=0;                         //使能 拉低  
    LCD_RW=0;                         //写  
    LCD_RS=0;_nop_();                 //命令  
          
    LCD_EN=1;                         //使能  
    LCD_dataBus=cmd;                  //送指令  
    _nop_();_nop_();                  //稳定  
  
    LCD_EN=0;_nop_();                 //取走  
}  
  
void LCD12864_writeByte(u8 dat)       //写一个字节  
{  
    while(LCD12864_isBusy());  
    LCD_EN=0;                //使能先拉低  
    LCD_RW=0;                //写  
    LCD_RS=1;_nop_();        //数据  
      
    LCD_EN=1;  
    LCD_dataBus=dat;  
    _nop_();_nop_();         //延时大于1.5us  
  
    LCD_EN=0;_nop_();        //下降沿取走数据  
}  
  
u8 LCD12864_readByte()       //读数据暂存器Data Register  
{                            //用的时候要空操作一次  
    u8 temp=0;  
    while(LCD12864_isBusy());//忙检测  
    LCD_dataBus=0xff;        //用总线读数据时必须先置为输入模式  
    LCD_EN=0;                //使能线拉低  
    LCD_RW=1;                //读  
    LCD_RS=1;_nop_();        //数据                      
    LCD_EN=1;_nop_();        //使能  
    temp=LCD_dataBus;        //取走数据  
      
    _nop_();  
    LCD_EN=0;                //使能恢复  
    return temp;  
}  
  
bool LCD12864_isBusy()       //检测液晶是否忙  
{  
    if(LCD12864_readIR() & 0x80) //检测BF位  
    {  
        return TRUE;         //忙  
    }  
    return FALSE;            //不忙  
}  
  
u8 LCD12864_readIR()         //读指令暂存器Instruction Register  
{  
    u8 temp=0;  
    LCD_EN=0;                //使能准备  
    LCD_RW=1;                //读  
    LCD_RS=0;_nop_();        //命令字  
    LCD_dataBus=0xff;        //准备输入  
    LCD_EN=1;_nop_();        //使能  
    temp=LCD_dataBus;        //提取数据  
  
    _nop_();  
    LCD_EN=0;                //使能拉低  
    return temp;                
}  

//测试更新代码