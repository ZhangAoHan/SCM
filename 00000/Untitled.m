clear all
close all
clc
load data_PM25
data_PM25=data_PM25';
load imf
[m,~]=size(imf);
pe=zeros(1,m);
figure(1)
for i=1:m
    subplot(m,1,i)
    plot(imf(i,:))
    pe(i)=SA_PE(imf(i,:),4,1);
end
pe %各个IMF的PE值

%% PE值>2的认为是高频 则IMF1和IMF2是高频分量
IMF1_VMD=zeros(5,length(imf(1,:)));
IMF2_VMD=zeros(5,length(imf(2,:)));

IMF1_VMD=SAM_VMD(imf(1,:),1,5000,0.3,5,0,1,1e-7);
IMF2_VMD=SAM_VMD(imf(2,:),1,5000,0.3,5,0,1,1e-7);
figure(2)
for i=1:5
    subplot(5,1,i)
    plot(IMF1_VMD(i,:))
end
figure(3)
for i=1:5
    subplot(5,1,i)
    plot(IMF2_VMD(i,:))
end

%% 实验BP的效果
%低频分量使用BP预测
%高频分量使用KELM预测
%% 低频预测  SSC3-SSCend
BPN=zeros(1,73);
KELMN1=zeros(1,73);
KELMN2=zeros(1,73);
for i=3:m  %IMF3-IMF8的预测结果
    BPN=BPN+ML_BPN(imf(i,:),0.8,5,1);
end

for i=1:5%IMF1的预测结果
    KELMN1=KELMN1+ML_KELMN(IMF1_VMD(i,:),0.8,5,1);
end%IMF2的预测结果
for i=1:5
    KELMN2=KELMN2+ML_KELMN(IMF2_VMD(i,:),0.8,5,1);
end
%先分解再预测的效果
YUC=BPN+KELMN1+KELMN2; 

%% 直接使用BP预测
BPYUC=BPN+ML_BPN(data_PM25,0.8,5,1);
figure(4)
plot(1:73,YUC,'-b','LineWidth',1)
hold on
plot(1:73,BPYUC,'-r','LineWidth',1)
hold on
plot(1:73,data_PM25(end-73+1:end),'-*r','LineWidth',2)