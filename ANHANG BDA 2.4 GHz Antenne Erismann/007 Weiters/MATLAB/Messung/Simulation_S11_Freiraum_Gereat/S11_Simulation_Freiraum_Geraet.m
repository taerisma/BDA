%BDA 
%Erismann Marcel
%Vergleich S11 aus Simulation im Freiraum und im Gerät
%Dipol Antenne
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
close all;
clear all;
%sucht die zu oeffneden Fils im selben Ordner wie das skrip
fileItem = matlab.desktop.editor.getActive;
cd(fileparts(fileItem.Filename));



%% S11
% Länge = 24.5mm
% Breite = 5mm
% Dicke = 0.026mm
% Freiraum  und im Gerät
Simulation_frei = csvread('S11_5mm_Freiraum_simulation2.csv',1,0) %simulationswerte CSV zuschneiden
Simulation_geraet = csvread('S11_5mm_Geraet_simulation.csv',1,0) %simulationswerte CSV zuschneiden

f6=figure(6); 
plot(Simulation_frei(:,1).*10^9, Simulation_frei(:,2), 'r')
hold on;
plot(Simulation_geraet(:,1).*10^9, Simulation_geraet(:,2), 'b'), grid;
legend('S_{11} Frei Raum','S_{11} im Gerät', 'Location', 'SouthEast')
ylabel('Amplitude in [dB]') 
xlabel('Frequenz in [Hz]')
title('Simulation des  S_{11} im Freiraum und dim Gerät eines Dipol 5mm breit')
saveas(f6,'Vergleich_s11_5mmDipol_Freiraum_Geraet','pdf');

%% S11
% Länge = 24.5mm
% Länge = 50.25
% Breite = 3mm
% Dicke = 0.026mm
% Freiraum  und im Gerät
Simulation_frei = csvread('S11_3mm_Freiraum_simulation.csv',1,0) %simulationswerte CSV zuschneiden
Simulation_geraet = csvread('S11_3mm_Geraet_simulation.csv',1,0) %simulationswerte CSV zuschneiden

f7=figure(7); 
plot(Simulation_frei(:,1).*10^9, Simulation_frei(:,2), 'r')
hold on;
plot(Simulation_geraet(:,1).*10^9, Simulation_geraet(:,2), 'b'), grid;
legend('S_{11} Frei Raum','S_{11} im Gerät', 'Location', 'SouthEast')
ylabel('Amplitude in [dB]') 
xlabel('Frequenz in [Hz]')
title('Simulation des  S_{11} im Freiraum und dim Gerät eines Dipol 3mm breit')
saveas(f7,'Vergleich_s11_3mmDipol_Freiraum_Geraet','pdf');
%% S11
% Länge = 24.5mm
% Breite = 1mm
% Dicke = 0.026mm
% Freiraum  und im Gerät
Simulation_frei = csvread('S11_1mm_Freiraum_simulation.csv',1,0) %simulationswerte CSV zuschneiden
Simulation_geraet = csvread('S11_1mm_Geraet_simulation.csv',1,0) %simulationswerte CSV zuschneiden

f8=figure(8); 
plot(Simulation_frei(:,1).*10^9, Simulation_frei(:,2), 'r')
hold on;
plot(Simulation_geraet(:,1).*10^9, Simulation_geraet(:,2), 'b'), grid;
legend('S_{11} Frei Raum','S_{11} im Gerät', 'Location', 'SouthEast')
ylabel('Amplitude in [dB]') 
xlabel('Frequenz in [Hz]')
title('Simulation des  S_{11} im Freiraum und dim Gerät eines Dipol 1mm breit')
saveas(f8,'Vergleich_s11_1mmDipol_Freiraum_Geraet','pdf');
%% S11
% Länge = 44.25mm
% Breite = 3mm
% Dicke = 0.026mm
% Freiraum  und im Gerät
Simulation_frei = csvread('S11_1mm_Freiraum_simulation_Dach.csv',1,0) %simulationswerte CSV zuschneiden
Simulation_geraet = csvread('S11_1mm_Geraet_simulation_Dach.csv',1,0) %simulationswerte CSV zuschneiden

f9=figure(9); 
plot(Simulation_frei(:,1).*10^9, Simulation_frei(:,2), 'r')
hold on;
plot(Simulation_geraet(:,1).*10^9, Simulation_geraet(:,2), 'b'), grid;
legend('S_{11} Frei Raum','S_{11} im Gerät', 'Location', 'SouthEast')
ylabel('Amplitude in [dB]') 
xlabel('Frequenz in [Hz]')
title('Simulation des  S_{11} im Freiraum und dim Gerät eines Dipol 1mm breit mit Dachkapazität')
saveas(f9,'Vergleich_s11_1mmDipol_Freiraum_Geraet_Dach','pdf');