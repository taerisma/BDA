%BDA 
%Erismann Marcel
%Vergleich S11 aus Simulation im Freiraum und mit Kunststoff
%Vergleich des Realteils und Imaginärteil im Freiraum, mit ABS und "ABS Stücken
%Dipol Antenne
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
close all;
clear all;
%sucht die zu oeffneden Fils im selben Ordner wie das skrip
fileItem = matlab.desktop.editor.getActive;
cd(fileparts(fileItem.Filename));

Simulation_frei = csvread('S11_Dipol_frei.csv',1,0) 
Simulation_ABS = csvread('S11_Dipol_ABS.csv',1,0) 
Simulation_2ABS = csvread('S11_Dipol_2ABS.csv',1,0) 

f40=figure(40); 
plot(Simulation_frei(:,1), Simulation_frei(:,2), 'r')
%grid on;
hold on;
plot(Simulation_ABS(:,1), Simulation_ABS(:,2), 'b');
plot(Simulation_2ABS(:,1), Simulation_2ABS(:,2), 'g'), grid;
legend('S_{11} Frei Raum','S_{11} mit ABS','S_{11} mit 2 ABS', 'Location', 'SouthEast')
ylabel('Amplitude in [dB]') 
xlabel('Frequenz in [GHz]')
title('Simulation des  |S_{11}| im Freiraum, mit einem und zwei ABS Stücken')
saveas(f40,'Vergleich_S11_Dipol','pdf');

%
%%
%Real und Imginärteil
%Dipol
%Im Freiraum mit ABS und 2ABS Stücken
Impedanz_frei = csvread('Impedanz_Dipol_frei.csv',1,0) 
Impedanz_ABS = csvread('Impedanz_Dipol_ABS.csv',1,0) 
Impedanz_2ABS = csvread('Impedanz_Dipol_2ABS.csv',1,0) 
f50=figure(50); 
plot(Impedanz_frei(:,1), Impedanz_frei(:,2), 'r')
grid on;
hold on;
plot(Impedanz_frei(:,3), Impedanz_frei(:,4), 'b');
plot(Impedanz_ABS(:,1), Impedanz_ABS(:,2), 'g')
plot(Impedanz_ABS(:,3), Impedanz_ABS(:,4), 'k');
plot(Impedanz_2ABS(:,1), Impedanz_2ABS(:,2), 'y')
plot(Impedanz_2ABS(:,3), Impedanz_2ABS(:,4), 'm');
legend('Realteil im Freien','Imaginärteil im Freien', 'Realteil mit ABS','Imaginärteil mit ABS','Realteil mit 2ABS','Imaginärteil mit 2ABS','Location', 'SouthEast')
ylabel('Impedanz [Ohm]') 
xlabel('Frequenz in [GHz]')
title('Impedanz der Dipolantenne im Freiraum, mit einem und zwei ABS Stücken')
saveas(50,'Vergleich_Impedanz_Dipol','pdf');
