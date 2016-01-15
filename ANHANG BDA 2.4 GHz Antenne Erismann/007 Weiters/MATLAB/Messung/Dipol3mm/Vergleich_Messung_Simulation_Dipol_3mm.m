%BDA 
%Erismann Marcel
%Vergleich S11 aus Simulation und Messung
%Dipol Antenne
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
close all;
clear all;

%cleanfigure;
matlab2tikz('myfile.tex');

% 
% fileItem = matlab.desktop.editor.getActive;
% cd(fileparts(fileItem.Filename));

 M = csvread('simSIM.csv',1,0)
 M;
% %load('nameSIM.csv')%Simulations Daten 2.0 bis 3.0 GHZ Angaben in GHz 600 Werte
 load('NameMESSUNG.dat')%Messung S11 1.95E+9 Hz bis 2.95E+9Hz bis 200 Werte
% % Vektoren anpassen
% %nameSIM2=nameSIM
% k = 0;
% i = 0;
% for i = 1:571
%     nameSIM2(k) = M(i)
%     k=k+1;
%     i=i+3;
% end
% 
%Messvektor kuertzen von 2.0 bis 2.95
NameMESSUNG2x= NameMESSUNG(14:201,1);
NameMESSUNG2y=NameMESSUNG(14:201,2);

figure;
plot(NameMESSUNG2x,NameMESSUNG2y, 'r')
hold on;
plot(M(:,1).*10^9, M(:,2), 'b'), grid;
legend('S_{11} Messung','S_{11} Simulation', 'Location', 'SouthEast')
ylabel('Amplitude in [dB]') 
xlabel('Frequenz in [GHz]')
title('Verglech Messung und Simulation des  S_{11}')