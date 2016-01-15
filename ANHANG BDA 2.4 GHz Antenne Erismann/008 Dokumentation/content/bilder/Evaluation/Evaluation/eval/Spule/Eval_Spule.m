%BDA 
%Erismann Marcel
%Vergleich S11 aus Simulation im Freiraum und mit Kunststoff
%Vergleich des Realteils und Imaginärteil im Freiraum, mit ABS und ABS Stücken
%Loop Antenne
%aus 3 Windungen
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
close all;
clear all;
%sucht die zu oeffneden Fils im selben Ordner wie das skrip
fileItem = matlab.desktop.editor.getActive;
cd(fileparts(fileItem.Filename));

Simulation_Spule_frei = csvread('S11_Spule_frei.csv',1,0) 
Simulation_Spule_1ABS = csvread('S11_Spule_1ABS.csv',1,0) 
Simulation_Spule_2ABS = csvread('S11_Spule_2ABS_2.csv',1,0) 

f80=figure(80); 
plot(Simulation_Spule_frei(:,1), Simulation_Spule_frei(:,2), 'r')
hold on;
plot(Simulation_Spule_1ABS(:,1), Simulation_Spule_1ABS(:,2), 'b');
plot(Simulation_Spule_2ABS(:,1), Simulation_Spule_2ABS(:,2), 'g'), grid;
legend('S_{11} Frei Raum','S_{11} mit ABS','S_{11} mit 2 ABS', 'Location', 'SouthWest')
ylabel('Amplitude in [dB]') 
xlabel('Frequenz in [GHz]')
title('Simulation des  |S_{11}| einer Loop Antnne mit drei Windungen im Freiraum, mit einem und zwei ABS Stücken')
saveas(f80,'Vergleich_S11_Spule','pdf');

%
%%
%Real und Imginärteil
%Loop Antenne
%Im Freiraum mit ABS und 2ABS Stücken
Impedanz_Spule_frei = csvread('Impedanz_Spule_frei.csv',1,0) 
Impedanz_Spule_1ABS = csvread('Impedanz_Spule_1ABS.csv',1,0) 
Impedanz_Spule_2ABS = csvread('Impedanz_Spule_2ABS_2.csv',1,0) 
f90=figure(90); 
plot(Impedanz_Spule_frei(:,1), Impedanz_Spule_frei(:,2), 'r')
grid on;
hold on;
plot(Impedanz_Spule_frei(:,3), Impedanz_Spule_frei(:,4), 'b');
plot(Impedanz_Spule_1ABS(:,1), Impedanz_Spule_1ABS(:,2), 'g')
plot(Impedanz_Spule_1ABS(:,3), Impedanz_Spule_1ABS(:,4), 'k');
plot(Impedanz_Spule_2ABS(:,1), Impedanz_Spule_2ABS(:,2), 'y')
plot(Impedanz_Spule_2ABS(:,3), Impedanz_Spule_2ABS(:,4), 'm');
legend('Realteil im Freien','Imaginärteil im Freien', 'Realteil mit ABS','Imaginärteil mit ABS','Realteil mit 2ABS','Imaginärteil mit 2ABS','Location', 'NorthEast')
ylabel('Impedanz [Ohm]') 
xlabel('Frequenz in [GHz]')
title('Impedanz der Loop Antenne mit drei Windungen im Freiraum, mit einem und zwei ABS Stücken')
saveas(90,'Vergleich_Impedanz_Spule','pdf');