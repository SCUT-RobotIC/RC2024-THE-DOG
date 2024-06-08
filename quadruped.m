
clc;clear;clf;
grid on;
axis([-170 130 -180 60]);%��ʾ����ϵ��Χ
hold on;
plot(0,0,'r.','markersize',30);%�������ĵ�
l1=100;l2=180;%���ô���С�ȳ��ȣ�mm��

t=0:0.1*pi:2*pi;%����ʱ�䲽��

Freq = length(t);%����ʱ�䲽������Ƶ��

R=20;%���ߵ�Բ �뾶��mm��

Ltheta_need = repelem(0,Freq);Rtheta_need = repelem(0,Freq);

xL0 = zeros(1,Freq);        yL0 = zeros(1,Freq);
xL1 = zeros(1,Freq);        yL1 = zeros(1,Freq);
xL2 = R*(t-sin(t))-20*pi;   yL2 = R*(1-cos(t))-100*sqrt(3);
xR0 = zeros(1,Freq);        yR0 = zeros(1,Freq);
xR1 = zeros(1,Freq);        yR1 = zeros(1,Freq);
xR2 = R*(t-sin(t))-20*pi;   yR2 = R*(1-cos(t))-100*sqrt(3);
plot(xL2,yL2,'linewidth',2,'Color',[0 1 0]);
for i=1:Freq
    %���ݴ���С�ȳ��ȼ�������߳�
    l3=sqrt((xL0(i)-xL2(i)).*(xL0(i)-xR2(i))+(yL0(i)-yL2(i)).*(yL0(i)-yL2(i)));
    theta2=acos((l1.*l1+l2.*l2-l3.*l3)/(2*l1.*l2));%�����Ӧ�ĹؽڽǶ�
    
    theta3=acos((l2.*l2+l3.*l3-l1.*l1)/(2*l2.*l3));%�����Ӧ�ļн�
    disp(rad2deg(theta2));
    disp(rad2deg(theta3));
    
    %����
    if xL0(i) > xL2(i)
        Ltheta_need(i)=theta2-(pi-atan((yL0(i)-yL2(i))./(xL0(i)-xL2(i)))-theta3);
    elseif xL0(i) == xL2(i)
        Ltheta_need(i)=theta2-(pi/2-theta3);
    else
        Ltheta_need(i)=theta2-(atan((yL0(i)-yL2(i))./(xL2(i)-xL0(i)))-theta3);
    end
    %����
    if xR0(i) > xR2(i)
        Rtheta_need(i)=theta2-(atan((yR0(i)-yR2(i))./(xR0(i)-xR2(i)))-theta3);
    elseif xR0(i) == xR2(i)
        Rtheta_need(i)=theta2-(pi/2-theta3);
    else
        Rtheta_need(i)=theta2-(pi-atan((yR0(i)-yR2(i))./(xR2(i)-xR0(i)))-theta3);
    end
    %������Ӧ�ؽڵ�����-��
    xL1(i)=xL0(i)-l1*cos(Ltheta_need(i));    yL1(i)=yL0(i)-l1*sin(Ltheta_need(i));
    %������Ӧ�ؽڵ�����-��
    xR1(i)=xR0(i)+l1*cos(Rtheta_need(i));    yR1(i)=yR0(i)-l1*sin(Rtheta_need(i));
end
%��ͼ
for i=1:Freq
    L=plot([xL0(i),xL1(i),xL2(i)],[yL0(i),yL1(i),yL2(i)],'color','b');
    R=plot([xR0(i),xR1(i),xR2(i)],[yR0(i),yR1(i),yR2(i)],'color','r');
   
    pause(0.02);%20ms������
    delete (L);delete (R);%���֮ǰ�Ĺ켣
end
%���¼����������
xL2 = -20*pi:(40*pi)/20:20*pi; yL2 = repelem(-100*sqrt(3),21);
xR2 = -20*pi:40*pi/20:20*pi;   yR2 = repelem(-100*sqrt(3),21);
plot(xL2,yL2,'linewidth',2,'Color',[0 1 0]);
for i=Freq:-1:1
    %���ݴ���С�ȳ��ȼ�������߳�
    l3=sqrt((xL0(i)-xL2(i)).*(xL0(i)-xR2(i))+(yL0(i)-yL2(i)).*(yL0(i)-yL2(i)));
    theta2=acos((l1.*l1+l2.*l2-l3.*l3)/(2*l1.*l2));%�����Ӧ�ĹؽڽǶ�
    theta3=acos((l2.*l2+l3.*l3-l1.*l1)/(2*l2.*l3));%�����Ӧ�ļн�
    %����
    if xL0(i) > xL2(i)
        Ltheta_need(i)=theta2-(pi-atan((yL0(i)-yL2(i))./(xL0(i)-xL2(i)))-theta3);
    elseif xL0(i) == xL2(i)
        Ltheta_need(i)=theta2-(pi/2-theta3);
    else
        Ltheta_need(i)=theta2-(atan((yL0(i)-yL2(i))./(xL2(i)-xL0(i)))-theta3);
    end
    %����
    if xR0(i) > xR2(i)
        Rtheta_need(i)=theta2-(atan((yR0(i)-yR2(i))./(xR0(i)-xR2(i)))-theta3);
    elseif xR0(i) == xR2(i)
        Rtheta_need(i)=theta2-(pi/2-theta3);
    else
        Rtheta_need(i)=theta2-(pi-atan((yR0(i)-yR2(i))./(xR2(i)-xR0(i)))-theta3);
    end
    %������Ӧ�ؽڵ�����-��
    xL1(i)=xL0(i)-l1*cos(Ltheta_need(i));    yL1(i)=yL0(i)-l1*sin(Ltheta_need(i));
    %������Ӧ�ؽڵ�����-��
    xR1(i)=xR0(i)+l1*cos(Rtheta_need(i));    yR1(i)=yR0(i)-l1*sin(Rtheta_need(i));
end
%��ͼ
for i=Freq:-1:1
    L=plot([xL0(i),xL1(i),xL2(i)],[yL0(i),yL1(i),yL2(i)],'color','b');
    R=plot([xR0(i),xR1(i),xR2(i)],[yR0(i),yR1(i),yR2(i)],'color','r');
    pause(0.02);%20ms������
    if i>1%���һ���켣�����
        delete (L);delete (R);%���֮ǰ�Ĺ켣
    end
end

