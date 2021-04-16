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
pe %����IMF��PEֵ

%% PEֵ>2����Ϊ�Ǹ�Ƶ ��IMF1��IMF2�Ǹ�Ƶ����
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

%% ʵ��BP��Ч��
%��Ƶ����ʹ��BPԤ��
%��Ƶ����ʹ��KELMԤ��
%% ��ƵԤ��  SSC3-SSCend
BPN=zeros(1,73);
KELMN1=zeros(1,73);
KELMN2=zeros(1,73);
for i=3:m  %IMF3-IMF8��Ԥ����
    BPN=BPN+ML_BPN(imf(i,:),0.8,5,1);
end

for i=1:5%IMF1��Ԥ����
    KELMN1=KELMN1+ML_KELMN(IMF1_VMD(i,:),0.8,5,1);
end%IMF2��Ԥ����
for i=1:5
    KELMN2=KELMN2+ML_KELMN(IMF2_VMD(i,:),0.8,5,1);
end
%�ȷֽ���Ԥ���Ч��
YUC=BPN+KELMN1+KELMN2; 

%% ֱ��ʹ��BPԤ��
BPYUC=BPN+ML_BPN(data_PM25,0.8,5,1);
figure(4)
plot(1:73,YUC,'-b','LineWidth',1)
hold on
plot(1:73,BPYUC,'-r','LineWidth',1)
hold on
plot(1:73,data_PM25(end-73+1:end),'-*r','LineWidth',2)