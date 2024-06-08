# RC2024-THE-DOG

华南理工大学RobotIC机器人实验室ROBOCON 2024 马术机器人仓库

第一步，先实现让机器人指哪里走哪里

![image](https://github.com/SCUT-RobotIC/RC2024-THE-DOG/blob/main/image/2024-04-10-05-04-46-image.png)

主体部分: 高97.5mmz

宽 ：350mm

长：520mm

+ 电机驱动 解决
  
  ## 贝塞尔曲线
  
  三层约束  路径  速度 加速度
  
  x 方向 y 方向 都有约束
  
  之后能解出这个，![image](https://github.com/SCUT-RobotIC/RC2024-THE-DOG/blob/main/image/2024-04-17-17-24-42-image.png)
  
  S 为步长
  
  H 为步高

+ 运动学解算 

+ 步态

+ 在32上实现机器狗的脉冲产生器 注意，现在用的那个板子上的晶振是8MHZ的

+ 注意把脉冲发生器的起始位置修改成竖直站立状态，便于每次的切换。
  
  大概是改成这样：
  
  ![image](https://github.com/SCUT-RobotIC/RC2024-THE-DOG/blob/main/image/2024-04-29-10-30-43-image.png)
  
  在 3/8处，这样的脉冲能确保每次产生的时候接入你站立的姿态

+ 

+  ![image](https://github.com/SCUT-RobotIC/RC2024-THE-DOG/blob/main/image/2024-04-29-10-34-38-image.png)

我们实际扔给贝塞尔曲线计算的脉冲是这样

当然，相关的转换处理已经写在了matlab函数中

## lw接手后改动↓

* 遥控通信 usart3改为uart5 06/07
* 遥控摇杆阈值更改 06/08
* simulink中将抬腿高度引出 06/08

## 遥控控制说明

* CH3：步频开关，默认±0.01
* CH2：步长开关，前后移动
* CH1：步长开关，左右移动
* CH5：抬腿高度，前中后 -> 20 40 60
* CH6：步频增益、步长增益，前中后 -> 大步慢走、正常行走、小步快走

![遥控器](https://github.com/SCUT-RobotIC/RC2024-THE-DOG/blob/main/image/%E9%81%A5%E6%8E%A7%E5%99%A8.jpg)

## 文件说明

* DOG/COMPLETETEST_InDividualLegControl: MATLAB仿真
* DOG/CONTROLLER：主控simulink模型文件
* WIRELESSCONTROL_PART_MOTORINI：主控代码
* 目前文件有些杂乱，24赛季结束后整理

## 注意事项

* simulink模型中关于腿的模型文件，MATLAB使用的是绝对路径，需要手动修改，文件在ABSTARCT文件夹中。
