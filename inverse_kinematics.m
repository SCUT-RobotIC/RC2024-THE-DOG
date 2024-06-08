% 运动学逆解

L1 = 100;
L2 = 180;

x = 56;
y = -170;

L = sqrt(x^2 + y^2);

theta_left =  rad2deg(asin(x/L));

theta_right = rad2deg( acos((L^2 + L1^2-L2^2)/(2*L1*L)));



theta_OUT = theta_right-theta_left ;

theta_IN = theta_right+theta_left;


