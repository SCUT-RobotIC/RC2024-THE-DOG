
clc;clear;clf;
grid on;
axis([-170 130 -180 60]);%显示坐标系范围
hold on;
plot(0,0,'r.','markersize',30);%画出轴心点
l1=100;l2=180;%设置大腿小腿长度（mm）

t=0:0.1*pi:2*pi;%设置时间步长

Freq = length(t);%根据时间步长计算频率

R=20;%摆线的圆 半径（mm）

Ltheta_need = repelem(0,Freq);Rtheta_need = repelem(0,Freq);

xL0 = zeros(1,Freq);        yL0 = zeros(1,Freq);
xL1 = zeros(1,Freq);        yL1 = zeros(1,Freq);
xL2 = R*(t-sin(t))-20*pi;   yL2 = R*(1-cos(t))-100*sqrt(3);
xR0 = zeros(1,Freq);        yR0 = zeros(1,Freq);
xR1 = zeros(1,Freq);        yR1 = zeros(1,Freq);
xR2 = R*(t-sin(t))-20*pi;   yR2 = R*(1-cos(t))-100*sqrt(3);
plot(xL2,yL2,'linewidth',2,'Color',[0 1 0]);
for i=1:Freq
    %根据大腿小腿长度计算第三边长
    l3=sqrt((xL0(i)-xL2(i)).*(xL0(i)-xR2(i))+(yL0(i)-yL2(i)).*(yL0(i)-yL2(i)));
    theta2=acos((l1.*l1+l2.*l2-l3.*l3)/(2*l1.*l2));%计算对应的关节角度
    
    theta3=acos((l2.*l2+l3.*l3-l1.*l1)/(2*l2.*l3));%计算对应的夹角
    disp(rad2deg(theta2));
    disp(rad2deg(theta3));
    
    %左腿
    if xL0(i) > xL2(i)
        Ltheta_need(i)=theta2-(pi-atan((yL0(i)-yL2(i))./(xL0(i)-xL2(i)))-theta3);
    elseif xL0(i) == xL2(i)
        Ltheta_need(i)=theta2-(pi/2-theta3);
    else
        Ltheta_need(i)=theta2-(atan((yL0(i)-yL2(i))./(xL2(i)-xL0(i)))-theta3);
    end
    %右腿
    if xR0(i) > xR2(i)
        Rtheta_need(i)=theta2-(atan((yR0(i)-yR2(i))./(xR0(i)-xR2(i)))-theta3);
    elseif xR0(i) == xR2(i)
        Rtheta_need(i)=theta2-(pi/2-theta3);
    else
        Rtheta_need(i)=theta2-(pi-atan((yR0(i)-yR2(i))./(xR2(i)-xR0(i)))-theta3);
    end
    %计算相应关节点坐标-左
    xL1(i)=xL0(i)-l1*cos(Ltheta_need(i));    yL1(i)=yL0(i)-l1*sin(Ltheta_need(i));
    %计算相应关节点坐标-右
    xR1(i)=xR0(i)+l1*cos(Rtheta_need(i));    yR1(i)=yR0(i)-l1*sin(Rtheta_need(i));
end
%绘图
for i=1:Freq
    L=plot([xL0(i),xL1(i),xL2(i)],[yL0(i),yL1(i),yL2(i)],'color','b');
    R=plot([xR0(i),xR1(i),xR2(i)],[yR0(i),yR1(i),yR2(i)],'color','r');
   
    pause(0.02);%20ms的周期
    delete (L);delete (R);%清除之前的轨迹
end
%重新计算足点坐标
xL2 = -20*pi:(40*pi)/20:20*pi; yL2 = repelem(-100*sqrt(3),21);
xR2 = -20*pi:40*pi/20:20*pi;   yR2 = repelem(-100*sqrt(3),21);
plot(xL2,yL2,'linewidth',2,'Color',[0 1 0]);
for i=Freq:-1:1
    %根据大腿小腿长度计算第三边长
    l3=sqrt((xL0(i)-xL2(i)).*(xL0(i)-xR2(i))+(yL0(i)-yL2(i)).*(yL0(i)-yL2(i)));
    theta2=acos((l1.*l1+l2.*l2-l3.*l3)/(2*l1.*l2));%计算对应的关节角度
    theta3=acos((l2.*l2+l3.*l3-l1.*l1)/(2*l2.*l3));%计算对应的夹角
    %左腿
    if xL0(i) > xL2(i)
        Ltheta_need(i)=theta2-(pi-atan((yL0(i)-yL2(i))./(xL0(i)-xL2(i)))-theta3);
    elseif xL0(i) == xL2(i)
        Ltheta_need(i)=theta2-(pi/2-theta3);
    else
        Ltheta_need(i)=theta2-(atan((yL0(i)-yL2(i))./(xL2(i)-xL0(i)))-theta3);
    end
    %右腿
    if xR0(i) > xR2(i)
        Rtheta_need(i)=theta2-(atan((yR0(i)-yR2(i))./(xR0(i)-xR2(i)))-theta3);
    elseif xR0(i) == xR2(i)
        Rtheta_need(i)=theta2-(pi/2-theta3);
    else
        Rtheta_need(i)=theta2-(pi-atan((yR0(i)-yR2(i))./(xR2(i)-xR0(i)))-theta3);
    end
    %计算相应关节点坐标-左
    xL1(i)=xL0(i)-l1*cos(Ltheta_need(i));    yL1(i)=yL0(i)-l1*sin(Ltheta_need(i));
    %计算相应关节点坐标-右
    xR1(i)=xR0(i)+l1*cos(Rtheta_need(i));    yR1(i)=yR0(i)-l1*sin(Rtheta_need(i));
end
%绘图
for i=Freq:-1:1
    L=plot([xL0(i),xL1(i),xL2(i)],[yL0(i),yL1(i),yL2(i)],'color','b');
    R=plot([xR0(i),xR1(i),xR2(i)],[yR0(i),yR1(i),yR2(i)],'color','r');
    pause(0.02);%20ms的周期
    if i>1%最后一个轨迹不清除
        delete (L);delete (R);%清除之前的轨迹
    end
end

