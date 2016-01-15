%BDA 
%Erismann Marcel
%Vergleich S11 aus Simulation und Messung
%Dipol Antenne
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
close all;
clear all;
%sucht die zu oeffneden Fils im selben Ordner wie das skrip
fileItem = matlab.desktop.editor.getActive;
cd(fileparts(fileItem.Filename));

%% 
load('NameMESSUNG.dat')%Messung S11 1.95E+9 Hz bis 2.95E+9Hz bis 200 Werte
Simulation = csvread('simSIM.csv',1,0) %simulationswerte CSV zuschneiden
NameMESSUNG2x= NameMESSUNG(14:201,1); %Mesung die Werrte zuschneiden x
NameMESSUNG2y=NameMESSUNG(14:201,2);  %Mesung die Werrte zuschneiden y
f1=figure(1); 
plot(NameMESSUNG2x,NameMESSUNG2y, 'r')
hold on;
plot(Simulation(:,1).*10^9, Simulation(:,2), 'b'), grid;
legend('S_{11} Messung','S_{11} Simulation', 'Location', 'SouthEast')
ylabel('Amplitude in [dB]') 
xlabel('Frequenz in [Hz]')
title('Verglech Messung und Simulation des  S_{11}')
saveas(f1,'Vergleich_s11_3mmDipol','fig'); 

%% S11
% Länge = 24.5mm
% Breite = 5mm
% Dicke = 0.035mm
% im Gerät

load('NameMESSUNG.dat')%Messung S11 1.95E+9 Hz bis 2.95E+9Hz bis 200 Werte
Simulation = csvread('S11_simulation_5mm_Dipol_Freiraum.csv',1,0) %simulationswerte CSV zuschneiden
NameMESSUNG2x= NameMESSUNG(14:201,1); %Mesung die Werrte zuschneiden x
NameMESSUNG2y=NameMESSUNG(14:201,2);  %Mesung die Werrte zuschneiden y
f2=figure(2); 
plot(NameMESSUNG2x,NameMESSUNG2y, 'r')
hold on;
plot(Simulation(:,1).*10^9, Simulation(:,2), 'b'), grid;
legend('S_{11} Messung','S_{11} Simulation', 'Location', 'SouthEast')
ylabel('Amplitude in [dB]') 
xlabel('Frequenz in [Hz]')
title('Verglech Messung und Simulation des  S_{11} im Gerät')
saveas(f2,'Vergleich_s11_5mmDipol','fig');




%% S11
% Länge = 24.5mm
% Breite = 5mm
% Dicke = 0.026mm
% Freiraum

%load('.dat')%Messung S11 1.95E+9 Hz bis 2.95E+9Hz bis 200 Werte
Simulation = csvread('S11_5mm_Geraet_simulation.csv',1,0) %simulationswerte CSV zuschneiden
NameMESSUNG2x= NameMESSUNG(14:201,1); %Mesung die Werrte zuschneiden x
NameMESSUNG2y=NameMESSUNG(14:201,2);  %Mesung die Werrte zuschneiden y
f3=figure(3); 
plot(NameMESSUNG2x,NameMESSUNG2y, 'r')
hold on;
plot(Simulation(:,1).*10^9, Simulation(:,2), 'b'), grid;
legend('S_{11} Messung','S_{11} Simulation', 'Location', 'SouthEast')
ylabel('Amplitude in [dB]') 
xlabel('Frequenz in [Hz]')
title('Verglech Messung und Simulation des  S_{11} im Freiraum')
saveas(f3,'Vergleich_s11_5mmDipol','fig');
